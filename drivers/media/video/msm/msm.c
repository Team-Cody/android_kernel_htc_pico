/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ioctl.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include "msm.h"
#include "msm_cam_server.h"
#include "msm_sensor.h"
#include "msm_actuator.h"
#include "msm_camera_eeprom.h"

#define MSM_MAX_CAMERA_SENSORS 5

#ifdef CONFIG_MSM_CAMERA_DEBUG
#define D(fmt, args...) pr_debug("msm: " fmt, ##args)
#else
#define D(fmt, args...) do {} while (0)
#endif

static unsigned msm_camera_v4l2_nr = -1;
static int vnode_count;

module_param(msm_camera_v4l2_nr, uint, 0644);
MODULE_PARM_DESC(msm_camera_v4l2_nr, "videoX start number, -1 is autodetect");

/* callback function from all subdevices of a msm_cam_v4l2_device */
static void msm_cam_v4l2_subdev_notify(struct v4l2_subdev *sd,
				unsigned int notification, void *arg)
{
	struct msm_cam_v4l2_device *pcam;
	struct msm_cam_media_controller *pmctl;

	if (sd == NULL)
		return;

	pcam = to_pcam(sd->v4l2_dev);

	if (pcam == NULL)
		return;

	pmctl = msm_cam_server_get_mctl(pcam->mctl_handle);
	if (pmctl == NULL)
		return;
}

/*
 *
 * implementation of v4l2_ioctl_ops
 *
 */
static int msm_camera_v4l2_querycap(struct file *f, void *pctx,
				struct v4l2_capability *pcaps)
{

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	/* some other day, some other time */
	/*cap->version = LINUX_VERSION_CODE; */
	pcaps->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING;
	return 0;
}

static int msm_camera_v4l2_queryctrl(struct file *f, void *pctx,
				struct v4l2_queryctrl *pqctrl)
{
	int rc = 0;
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	mutex_lock(&pcam->vid_lock);
	rc = msm_server_q_ctrl(pcam, pqctrl);
	mutex_unlock(&pcam->vid_lock);
	return rc;
}

static int msm_camera_v4l2_g_ctrl(struct file *f, void *pctx,
					struct v4l2_control *c)
{
	int rc = 0;
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	mutex_lock(&pcam->vid_lock);
	rc = msm_server_g_ctrl(pcam, c);
	mutex_unlock(&pcam->vid_lock);

	return rc;
}

static int msm_camera_v4l2_s_ctrl(struct file *f, void *pctx,
					struct v4l2_control *ctrl)
{
	int rc = 0;
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);

	WARN_ON(pctx != f->private_data);
	mutex_lock(&pcam->vid_lock);
	switch (ctrl->id) {
	case MSM_V4L2_PID_MMAP_INST:
		D("%s: mmap_inst=(0x%p, %d)\n",
			 __func__, pcam_inst, pcam_inst->my_index);
		pcam_inst->is_mem_map_inst = 1;
		break;
	case MSM_V4L2_PID_MMAP_ENTRY:
		if (copy_from_user(&pcam_inst->mem_map,
			(void *)ctrl->value,
			sizeof(struct msm_mem_map_info))) {
			rc = -EFAULT;
		} else
			D("%s:mmap entry:cookie=0x%x,mem_type=%d,len=%d\n",
				__func__, pcam_inst->mem_map.cookie,
				pcam_inst->mem_map.mem_type,
				pcam_inst->mem_map.length);
		break;
	default:
		if (ctrl->id == MSM_V4L2_PID_CAM_MODE)
			pcam->op_mode = ctrl->value;
		rc = msm_server_s_ctrl(pcam, ctrl);
		break;
	}
	mutex_unlock(&pcam->vid_lock);

	return rc;
}

static int msm_camera_v4l2_reqbufs(struct file *f, void *pctx,
				struct v4l2_requestbuffers *pb)
{
	int rc = 0, i, j;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);
	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);
	rc = vb2_reqbufs(&pcam_inst->vid_bufq, pb);
	if (rc < 0) {
		pr_err("%s reqbufs failed %d ", __func__, rc);
		return rc;
	}
	if (!pb->count) {
		/* Deallocation. free buf_offset array */
		D("%s Inst %p freeing buffer offsets array",
			__func__, pcam_inst);
		for (j = 0 ; j < pcam_inst->buf_count ; j++)
			kfree(pcam_inst->buf_offset[j]);
		kfree(pcam_inst->buf_offset);
		pcam_inst->buf_offset = NULL;
		/* If the userspace has deallocated all the
		 * buffers, then release the vb2 queue */
		if (pcam_inst->vbqueue_initialized) {
			vb2_queue_release(&pcam_inst->vid_bufq);
			pcam_inst->vbqueue_initialized = 0;
		}
	} else {
		D("%s Inst %p Allocating buf_offset array",
			__func__, pcam_inst);
		/* Allocation. allocate buf_offset array */
		pcam_inst->buf_offset = (struct msm_cam_buf_offset **)
			kzalloc(pb->count * sizeof(struct msm_cam_buf_offset *),
							GFP_KERNEL);
		if (!pcam_inst->buf_offset) {
			pr_err("%s out of memory ", __func__);
			return -ENOMEM;
		}
		for (i = 0; i < pb->count; i++) {
			pcam_inst->buf_offset[i] =
				kzalloc(sizeof(struct msm_cam_buf_offset) *
				pcam_inst->plane_info.num_planes, GFP_KERNEL);
			if (!pcam_inst->buf_offset[i]) {
				pr_err("%s out of memory ", __func__);
				for (j = i-1 ; j >= 0; j--)
					kfree(pcam_inst->buf_offset[j]);
				kfree(pcam_inst->buf_offset);
				pcam_inst->buf_offset = NULL;
				return -ENOMEM;
			}
		}
	}
	pcam_inst->buf_count = pb->count;
	return rc;
}

static int msm_camera_v4l2_querybuf(struct file *f, void *pctx,
					struct v4l2_buffer *pb)
{
	/* get the video device */
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);
	return vb2_querybuf(&pcam_inst->vid_bufq, pb);
}

static int msm_camera_v4l2_qbuf(struct file *f, void *pctx,
					struct v4l2_buffer *pb)
{
	int rc = 0, i = 0;
	/* get the camera device */
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s Inst=%p, mode=%d, idx=%d\n", __func__, pcam_inst,
		pcam_inst->image_mode, pb->index);
	WARN_ON(pctx != f->private_data);

	if (!pcam_inst->buf_offset) {
		pr_err("%s Buffer is already released. Returning. ", __func__);
		return -EINVAL;
	}

	if (pb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		/* Reject the buffer if planes array was not allocated */
		if (pb->m.planes == NULL) {
			pr_err("%s Planes array is null ", __func__);
			return -EINVAL;
		}
		for (i = 0; i < pcam_inst->plane_info.num_planes; i++) {
			D("%s stored offsets for plane %d as"
				"addr offset %d, data offset %d",
				__func__, i, pb->m.planes[i].reserved[0],
				pb->m.planes[i].data_offset);
			pcam_inst->buf_offset[pb->index][i].data_offset =
				pb->m.planes[i].data_offset;
			pcam_inst->buf_offset[pb->index][i].addr_offset =
				pb->m.planes[i].reserved[0];
		}
	} else {
		D("%s stored reserved info %d", __func__, pb->reserved);
		pcam_inst->buf_offset[pb->index][0].addr_offset = pb->reserved;
	}

	rc = vb2_qbuf(&pcam_inst->vid_bufq, pb);
	D("%s, videobuf_qbuf mode %d and idx %d returns %d\n", __func__,
		pcam_inst->image_mode, pb->index, rc);

	return rc;
}

static int msm_camera_v4l2_dqbuf(struct file *f, void *pctx,
					struct v4l2_buffer *pb)
{
	int rc = 0, i = 0;
	/* get the camera device */
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	rc = vb2_dqbuf(&pcam_inst->vid_bufq, pb,  f->f_flags & O_NONBLOCK);
	D("%s, videobuf_dqbuf returns %d\n", __func__, rc);

	if (pb->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		/* Reject the buffer if planes array was not allocated */
		if (pb->m.planes == NULL) {
			pr_err("%s Planes array is null\n", __func__);
			return -EINVAL;
		}
		for (i = 0; i < pcam_inst->plane_info.num_planes; i++) {
			pb->m.planes[i].data_offset =
				pcam_inst->buf_offset[pb->index][i].data_offset;
			pb->m.planes[i].reserved[0] =
				pcam_inst->buf_offset[pb->index][i].addr_offset;
			D("%s stored offsets for plane %d as "
				"addr offset %d, data offset %d\n",
				__func__, i, pb->m.planes[i].reserved[0],
				pb->m.planes[i].data_offset);
		}
	} else {
		D("%s stored reserved info %d\n", __func__, pb->reserved);
		pb->reserved = pcam_inst->buf_offset[pb->index][0].addr_offset;
	}

	return rc;
}

static int msm_camera_v4l2_streamon(struct file *f, void *pctx,
					enum v4l2_buf_type buf_type)
{
	int rc = 0;
	/* get the camera device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s Inst %p\n", __func__, pcam_inst);
	WARN_ON(pctx != f->private_data);

	if ((buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) &&
		(buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE)) {
		pr_err("%s Invalid buffer type ", __func__);
		return -EINVAL;
	}

	D("%s Calling videobuf_streamon", __func__);
	/* if HW streaming on is successful, start buffer streaming */
	rc = vb2_streamon(&pcam_inst->vid_bufq, buf_type);
	D("%s, videobuf_streamon returns %d\n", __func__, rc);

	mutex_lock(&pcam->vid_lock);
	/* turn HW (VFE/sensor) streaming */
	pcam_inst->streamon = 1;
	rc = msm_server_streamon(pcam, pcam_inst->my_index);
	mutex_unlock(&pcam->vid_lock);
	D("%s rc = %d\n", __func__, rc);
	return rc;
}

static int msm_camera_v4l2_streamoff(struct file *f, void *pctx,
					enum v4l2_buf_type buf_type)
{
	int rc = 0;
	/* get the camera device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s Inst %p\n", __func__, pcam_inst);
	WARN_ON(pctx != f->private_data);

	if ((buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) &&
		(buf_type != V4L2_BUF_TYPE_VIDEO_CAPTURE)) {
		pr_err("%s Invalid buffer type ", __func__);
		return -EINVAL;
	}

	/* first turn of HW (VFE/sensor) streaming so that buffers are
		not in use when we free the buffers */
	mutex_lock(&pcam->vid_lock);
	pcam_inst->streamon = 0;
	if (msm_server_get_usecount() > 0)
		rc = msm_server_streamoff(pcam, pcam_inst->my_index);
	mutex_unlock(&pcam->vid_lock);
	if (rc < 0)
		pr_err("%s: hw failed to stop streaming\n", __func__);

	/* stop buffer streaming */
	rc = vb2_streamoff(&pcam_inst->vid_bufq, buf_type);
	D("%s, videobuf_streamoff returns %d\n", __func__, rc);
	return rc;
}

static int msm_camera_v4l2_enum_fmt_cap(struct file *f, void *pctx,
					struct v4l2_fmtdesc *pfmtdesc)
{
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	const struct msm_isp_color_fmt *isp_fmt;

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);
	if ((pfmtdesc->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) &&
		(pfmtdesc->type != V4L2_BUF_TYPE_VIDEO_CAPTURE))
		return -EINVAL;

	if (pfmtdesc->index >= pcam->num_fmts)
		return -EINVAL;

	isp_fmt = &pcam->usr_fmts[pfmtdesc->index];

	if (isp_fmt->name)
		strlcpy(pfmtdesc->description, isp_fmt->name,
						sizeof(pfmtdesc->description));

	pfmtdesc->pixelformat = isp_fmt->fourcc;

	D("%s: [%d] 0x%x, %s\n", __func__, pfmtdesc->index,
		isp_fmt->fourcc, isp_fmt->name);
	return 0;
}

static int msm_camera_v4l2_g_fmt_cap(struct file *f,
		void *pctx, struct v4l2_format *pfmt)
{
	int rc = 0;
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	if (pfmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	rc = msm_server_get_fmt(pcam, pcam_inst->my_index, pfmt);
	D("%s: current_fmt->fourcc: 0x%08x, rc = %d\n", __func__,
				pfmt->fmt.pix.pixelformat, rc);
	return rc;
}

static int msm_camera_v4l2_g_fmt_cap_mplane(struct file *f,
		void *pctx, struct v4l2_format *pfmt)
{
	int rc = 0;
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	if (pfmt->type != V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return -EINVAL;

	rc = msm_server_get_fmt_mplane(pcam, pcam_inst->my_index, pfmt);
	D("%s: current_fmt->fourcc: 0x%08x, rc = %d\n", __func__,
					pfmt->fmt.pix_mp.pixelformat, rc);
	return rc;
}

/* This function will readjust the format parameters based in HW
  capabilities. Called by s_fmt_cap
*/
static int msm_camera_v4l2_try_fmt_cap(struct file *f, void *pctx,
					struct v4l2_format *pfmt)
{
	int rc = 0;
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	rc = msm_server_try_fmt(pcam, pfmt);
	if (rc)
		pr_err("Format %x not found, rc = %d\n",
				pfmt->fmt.pix.pixelformat, rc);

	return rc;
}

static int msm_camera_v4l2_try_fmt_cap_mplane(struct file *f, void *pctx,
					struct v4l2_format *pfmt)
{
	int rc = 0;
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	rc = msm_server_try_fmt_mplane(pcam, pfmt);
	if (rc)
		pr_err("Format %x not found, rc = %d\n",
				pfmt->fmt.pix_mp.pixelformat, rc);

	return rc;
}

/* This function will reconfig the v4l2 driver and HW device, it should be
   called after the streaming is stopped.
*/
static int msm_camera_v4l2_s_fmt_cap(struct file *f, void *pctx,
					struct v4l2_format *pfmt)
{
	int rc;
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_media_controller *pmctl;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);
	D("%s, inst=0x%x,idx=%d,priv = 0x%p\n",
		__func__, (u32)pcam_inst, pcam_inst->my_index,
		(void *)pfmt->fmt.pix.priv);
	WARN_ON(pctx != f->private_data);

	pmctl = msm_cam_server_get_mctl(pcam->mctl_handle);
	if (pmctl == NULL)
		return -EINVAL;

	if (!pcam_inst->vbqueue_initialized) {
		pmctl->mctl_vbqueue_init(pcam_inst, &pcam_inst->vid_bufq,
					V4L2_BUF_TYPE_VIDEO_CAPTURE);
		pcam_inst->vbqueue_initialized = 1;
	}

	mutex_lock(&pcam->vid_lock);

	rc = msm_server_set_fmt(pcam, pcam_inst->my_index, pfmt);
	if (rc < 0) {
		pr_err("%s: msm_server_set_fmt Error: %d\n",
				__func__, rc);
	}
	mutex_unlock(&pcam->vid_lock);

	return rc;
}

static int msm_camera_v4l2_s_fmt_cap_mplane(struct file *f, void *pctx,
				struct v4l2_format *pfmt)
{
	int rc;
	struct msm_cam_v4l2_device *pcam = video_drvdata(f);
	struct msm_cam_media_controller *pmctl;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
			struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s Inst %p\n", __func__, pcam_inst);
	WARN_ON(pctx != f->private_data);

	pmctl = msm_cam_server_get_mctl(pcam->mctl_handle);
	if (pmctl == NULL)
		return -EINVAL;

	if (!pcam_inst->vbqueue_initialized) {
		pmctl->mctl_vbqueue_init(pcam_inst, &pcam_inst->vid_bufq,
					V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);
		pcam_inst->vbqueue_initialized = 1;
	}

	mutex_lock(&pcam->vid_lock);
	rc = msm_server_set_fmt_mplane(pcam, pcam_inst->my_index, pfmt);
	mutex_unlock(&pcam->vid_lock);

	return rc;
}
static int msm_camera_v4l2_g_jpegcomp(struct file *f, void *pctx,
				struct v4l2_jpegcompression *pcomp)
{
	int rc = -EINVAL;

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	return rc;
}

static int msm_camera_v4l2_s_jpegcomp(struct file *f, void *pctx,
				struct v4l2_jpegcompression *pcomp)
{
	int rc = -EINVAL;

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	return rc;
}


static int msm_camera_v4l2_g_crop(struct file *f, void *pctx,
					struct v4l2_crop *crop)
{
	int rc = -EINVAL;
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;

	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	mutex_lock(&pcam->vid_lock);
	rc = msm_server_get_crop(pcam, pcam_inst->my_index, crop);
	mutex_unlock(&pcam->vid_lock);
	return rc;
}

static int msm_camera_v4l2_s_crop(struct file *f, void *pctx,
					struct v4l2_crop *a)
{
	int rc = -EINVAL;

	D("%s\n", __func__);
	WARN_ON(pctx != f->private_data);

	return rc;
}

/* Stream type-dependent parameter ioctls */
static int msm_camera_v4l2_g_parm(struct file *f, void *pctx,
				struct v4l2_streamparm *a)
{
	int rc = -EINVAL;
	return rc;
}
static int msm_vidbuf_get_path(u32 extendedmode)
{
	switch (extendedmode) {
	case MSM_V4L2_EXT_CAPTURE_MODE_THUMBNAIL:
		return OUTPUT_TYPE_T;
	case MSM_V4L2_EXT_CAPTURE_MODE_MAIN:
		return OUTPUT_TYPE_S;
	case MSM_V4L2_EXT_CAPTURE_MODE_VIDEO:
		return OUTPUT_TYPE_V;
	case MSM_V4L2_EXT_CAPTURE_MODE_DEFAULT:
	case MSM_V4L2_EXT_CAPTURE_MODE_PREVIEW:
	default:
		return OUTPUT_TYPE_P;
	}
}

static int msm_camera_v4l2_s_parm(struct file *f, void *pctx,
				struct v4l2_streamparm *a)
{
	int rc = 0;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);
	pcam_inst->image_mode = a->parm.capture.extendedmode;
	pcam_inst->pcam->dev_inst_map[pcam_inst->image_mode] = pcam_inst;
	pcam_inst->path = msm_vidbuf_get_path(pcam_inst->image_mode);
	D("%spath=%d,rc=%d\n", __func__,
		pcam_inst->path, rc);
	return rc;
}

static int msm_camera_v4l2_subscribe_event(struct v4l2_fh *fh,
			struct v4l2_event_subscription *sub)
{
	int rc = 0;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst =
		(struct msm_cam_v4l2_dev_inst *)container_of(fh,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s:fh = 0x%x, type = 0x%x\n", __func__, (u32)fh, sub->type);
	if (pcam_inst->my_index != 0)
		return -EINVAL;
	if (sub->type == V4L2_EVENT_ALL)
		sub->type = V4L2_EVENT_PRIVATE_START+MSM_CAM_APP_NOTIFY_EVENT;
	rc = v4l2_event_subscribe(fh, sub);
	if (rc < 0)
		D("%s: failed for evtType = 0x%x, rc = %d\n",
						__func__, sub->type, rc);
	return rc;
}

static int msm_camera_v4l2_unsubscribe_event(struct v4l2_fh *fh,
			struct v4l2_event_subscription *sub)
{
	int rc = 0;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst =
		(struct msm_cam_v4l2_dev_inst *)container_of(fh,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("%s: fh = 0x%x\n", __func__, (u32)fh);
	if (pcam_inst->my_index != 0)
		return -EINVAL;

	rc = v4l2_event_unsubscribe(fh, sub);
	D("%s: rc = %d\n", __func__, rc);
	return rc;
}

/* v4l2_ioctl_ops */
static const struct v4l2_ioctl_ops g_msm_ioctl_ops = {
	.vidioc_querycap = msm_camera_v4l2_querycap,

	.vidioc_s_crop = msm_camera_v4l2_s_crop,
	.vidioc_g_crop = msm_camera_v4l2_g_crop,

	.vidioc_queryctrl = msm_camera_v4l2_queryctrl,
	.vidioc_g_ctrl = msm_camera_v4l2_g_ctrl,
	.vidioc_s_ctrl = msm_camera_v4l2_s_ctrl,

	.vidioc_reqbufs = msm_camera_v4l2_reqbufs,
	.vidioc_querybuf = msm_camera_v4l2_querybuf,
	.vidioc_qbuf = msm_camera_v4l2_qbuf,
	.vidioc_dqbuf = msm_camera_v4l2_dqbuf,

	.vidioc_streamon = msm_camera_v4l2_streamon,
	.vidioc_streamoff = msm_camera_v4l2_streamoff,

	/* format ioctls */
	.vidioc_enum_fmt_vid_cap = msm_camera_v4l2_enum_fmt_cap,
	.vidioc_enum_fmt_vid_cap_mplane = msm_camera_v4l2_enum_fmt_cap,
	.vidioc_try_fmt_vid_cap = msm_camera_v4l2_try_fmt_cap,
	.vidioc_try_fmt_vid_cap_mplane = msm_camera_v4l2_try_fmt_cap_mplane,
	.vidioc_g_fmt_vid_cap = msm_camera_v4l2_g_fmt_cap,
	.vidioc_g_fmt_vid_cap_mplane = msm_camera_v4l2_g_fmt_cap_mplane,
	.vidioc_s_fmt_vid_cap = msm_camera_v4l2_s_fmt_cap,
	.vidioc_s_fmt_vid_cap_mplane = msm_camera_v4l2_s_fmt_cap_mplane,

	.vidioc_g_jpegcomp = msm_camera_v4l2_g_jpegcomp,
	.vidioc_s_jpegcomp = msm_camera_v4l2_s_jpegcomp,

	/* Stream type-dependent parameter ioctls */
	.vidioc_g_parm =  msm_camera_v4l2_g_parm,
	.vidioc_s_parm =  msm_camera_v4l2_s_parm,

	/* event subscribe/unsubscribe */
	.vidioc_subscribe_event = msm_camera_v4l2_subscribe_event,
	.vidioc_unsubscribe_event = msm_camera_v4l2_unsubscribe_event,
};

/* v4l2_file_operations */
static int msm_open(struct file *f)
{
	int i, rc = -EINVAL;
#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
	int ion_client_created = 0;
#endif
	int server_q_idx = 0;
	/*struct msm_isp_ops *p_isp = 0;*/
	/* get the video device */
	struct msm_cam_v4l2_device *pcam  = video_drvdata(f);
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	struct msm_cam_media_controller *pmctl = NULL;

	D("%s\n", __func__);

	if (!pcam) {
		pr_err("%s NULL pointer passed in!\n", __func__);
		return rc;
	}
	if (!msm_server_get_usecount()) {
		pr_err("%s: error, daemon not yet started.", __func__);
		return -EINVAL;
	}
	mutex_lock(&pcam->vid_lock);
	for (i = 0; i < MSM_DEV_INST_MAX; i++) {
		if (pcam->dev_inst[i] == NULL)
			break;
	}

	server_q_idx = msm_find_free_queue();
	if (server_q_idx < 0)
		return server_q_idx;

	/* if no instance is available, return error */
	if (i == MSM_DEV_INST_MAX) {
		mutex_unlock(&pcam->vid_lock);
		return rc;
	}
	pcam_inst = kzalloc(sizeof(struct msm_cam_v4l2_dev_inst), GFP_KERNEL);
	if (!pcam_inst) {
		mutex_unlock(&pcam->vid_lock);
		return rc;
	}
	pcam_inst->sensor_pxlcode = pcam->usr_fmts[0].pxlcode;
	pcam_inst->my_index = i;
	pcam_inst->pcam = pcam;
	pcam->dev_inst[i] = pcam_inst;

	D("%s index %d nodeid %d count %d\n", __func__,
			pcam_inst->my_index,
			pcam->vnode_id, pcam->use_count);
	pcam->use_count++;
	D("%s use_count %d\n", __func__, pcam->use_count);
	if (pcam->use_count == 1) {
		rc = msm_server_begin_session(pcam, server_q_idx);
		if (rc < 0) {
			pr_err("%s error starting server session ", __func__);
			goto msm_cam_server_begin_session_failed;
		}
		pmctl = msm_cam_server_get_mctl(pcam->mctl_handle);

#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
		pmctl->client = msm_ion_client_create(-1, "camera");
		kref_init(&pmctl->refcount);
		ion_client_created = 1;
#endif

		/* Should be set to sensor ops if any but right now its OK!! */
		if (!pmctl->mctl_open) {
			D("%s: media contoller is not inited\n", __func__);
			rc = -ENODEV;
			goto mctl_open_failed;
		}

		/* Now we really have to activate the camera */
		D("%s: call mctl_open\n", __func__);
		rc = pmctl->mctl_open(pmctl, MSM_APPS_ID_V4L2);
		if (rc < 0) {
			pr_err("%s: HW open failed rc = 0x%x\n",  __func__, rc);
			goto mctl_open_failed;
		}
		pmctl->pcam_ptr = pcam;

		rc = msm_setup_v4l2_event_queue(&pcam_inst->eventHandle,
			pcam->pvdev);
		if (rc < 0) {
			pr_err("%s: msm_setup_v4l2_event_queue failed %d",
				__func__, rc);
			goto mctl_event_q_setup_failed;
		}
	}
	pcam_inst->vbqueue_initialized = 0;
	rc = 0;

	f->private_data = &pcam_inst->eventHandle;

	D("f->private_data = 0x%x, pcam = 0x%x\n",
		(u32)f->private_data, (u32)pcam_inst);

	if (pcam->use_count == 1) {
		rc = msm_send_open_server(pcam);
		if (rc < 0 && rc != -ERESTARTSYS) {
			pr_err("%s: msm_send_open_server failed %d\n",
				__func__, rc);
			goto msm_send_open_server_failed;
		}
	}
	mutex_unlock(&pcam->vid_lock);
	D("%s: end\n", __func__);
	return rc;

msm_send_open_server_failed:
	v4l2_fh_del(&pcam_inst->eventHandle);
	v4l2_fh_exit(&pcam_inst->eventHandle);
mctl_event_q_setup_failed:
	if (pmctl->mctl_release)
		if (pmctl->mctl_release(pmctl) < 0)
			pr_err("%s: mctl_release failed\n", __func__);
mctl_open_failed:
	if (pcam->use_count == 1) {
#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
		if (ion_client_created) {
			D("%s: destroy ion client", __func__);
			kref_put(&pmctl->refcount, msm_release_ion_client);
		}
#endif
		if (msm_server_end_session(pcam) < 0)
			pr_err("%s: msm_server_end_session failed\n",
				__func__);
	}
msm_cam_server_begin_session_failed:
	if (pcam->use_count == 1) {
		pcam->dev_inst[i] = NULL;
		pcam->use_count = 0;
	}
	mutex_unlock(&pcam->vid_lock);
	kfree(pcam_inst);
	pr_err("%s: error end", __func__);
	return rc;
}

static int msm_addr_remap(struct msm_cam_v4l2_dev_inst *pcam_inst,
				struct vm_area_struct *vma)
{
	int phyaddr;
	int retval;
	unsigned long size;
	int rc = 0;
	struct msm_cam_media_controller *mctl;

	mctl = msm_cam_server_get_mctl(pcam_inst->pcam->mctl_handle);
	if (!mctl) {
		pr_err("%s: invalid mctl pointer", __func__);
		return -EFAULT;
	}

	rc = msm_pmem_region_get_phy_addr(&mctl->stats_info.pmem_stats_list,
			&pcam_inst->mem_map,
			&phyaddr);
	if (rc) {
		pr_err("%s: cannot map vaddr", __func__);
		return -EFAULT;
	}
	size = vma->vm_end - vma->vm_start;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	retval = remap_pfn_range(vma, vma->vm_start,
			phyaddr >> PAGE_SHIFT,
			size, vma->vm_page_prot);
	if (retval) {
		pr_err("%s:mmap: remap failed with error %d. ",
			   __func__, retval);
		memset(&pcam_inst->mem_map, 0, sizeof(pcam_inst->mem_map));
		return -ENOMEM;
	}
	D("%s:mmap: phy_addr=0x%x: %08lx-%08lx, pgoff %08lx\n",
		   __func__, (uint32_t)phyaddr,
		   vma->vm_start, vma->vm_end, vma->vm_pgoff);
	memset(&pcam_inst->mem_map, 0, sizeof(pcam_inst->mem_map));
	return 0;
}

static int msm_mmap(struct file *f, struct vm_area_struct *vma)
{
	int rc = 0;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);

	D("mmap called, vma=0x%08lx\n", (unsigned long)vma);

	if (pcam_inst->is_mem_map_inst &&
		pcam_inst->mem_map.cookie) {
		rc = msm_addr_remap(pcam_inst, vma);
		D("%s: msm_addr_remap ret=%d\n", __func__, rc);
		return rc;
	} else
		rc = vb2_mmap(&pcam_inst->vid_bufq, vma);
	D("vma start=0x%08lx, size=%ld, ret=%d\n",
		(unsigned long)vma->vm_start,
		(unsigned long)vma->vm_end - (unsigned long)vma->vm_start,
		rc);

	return rc;
}

void msm_release_ion_client(struct kref *ref)
{
	struct msm_cam_media_controller *mctl = container_of(ref,
		struct msm_cam_media_controller, refcount);
	pr_err("%s Calling ion_client_destroy\n", __func__);
	ion_client_destroy(mctl->client);
}

static int msm_close(struct file *f)
{
	int rc = 0;
	struct msm_cam_v4l2_device *pcam;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	struct msm_cam_media_controller *pmctl;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);
	pcam = pcam_inst->pcam;
	if (!pcam) {
		pr_err("%s NULL pointer of camera device!\n", __func__);
		return -EINVAL;
	}

	pmctl = msm_cam_server_get_mctl(pcam->mctl_handle);
	if (!pmctl) {
		pr_err("%s NULL mctl pointer\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&pcam->vid_lock);

	if (pcam_inst->streamon) {
		/*something went wrong since instance
		is closing without streamoff*/
		if (pmctl->mctl_release) {
			rc = pmctl->mctl_release(pmctl);
			if (rc < 0)
				pr_err("mctl_release fails %d\n", rc);
		}
		pmctl->mctl_release = NULL;/*so that it isn't closed again*/
	}

	pcam_inst->streamon = 0;
	pcam->use_count--;
	pcam->dev_inst_map[pcam_inst->image_mode] = NULL;
	if (pcam_inst->vbqueue_initialized)
		vb2_queue_release(&pcam_inst->vid_bufq);
	D("%s Closing down instance %p ", __func__, pcam_inst);
	D("%s index %d nodeid %d count %d\n", __func__, pcam_inst->my_index,
		pcam->vnode_id, pcam->use_count);
	pcam->dev_inst[pcam_inst->my_index] = NULL;
	if (pcam_inst->my_index == 0) {
		v4l2_fh_del(&pcam_inst->eventHandle);
		v4l2_fh_exit(&pcam_inst->eventHandle);
	}
	kfree(pcam_inst);
	f->private_data = NULL;

	if (pcam->use_count == 0) {
		if (msm_server_get_usecount() > 0) {
			rc = msm_send_close_server(pcam);
			if (rc < 0)
				pr_err("msm_send_close_server failed %d\n", rc);
		}

		if (pmctl->mctl_release) {
			rc = pmctl->mctl_release(pmctl);
			if (rc < 0)
				pr_err("mctl_release fails %d\n", rc);
		}

#ifdef CONFIG_MSM_MULTIMEDIA_USE_ION
		kref_put(&pmctl->refcount, msm_release_ion_client);
#endif
		rc = msm_server_end_session(pcam);
		if (rc < 0)
			pr_err("msm_server_end_session fails %d\n", rc);
	}
	mutex_unlock(&pcam->vid_lock);
	return rc;
}

static unsigned int msm_poll(struct file *f, struct poll_table_struct *wait)
{
	int rc = 0;
	struct msm_cam_v4l2_device *pcam;
	struct msm_cam_v4l2_dev_inst *pcam_inst;
	pcam_inst = container_of(f->private_data,
		struct msm_cam_v4l2_dev_inst, eventHandle);
	pcam = pcam_inst->pcam;
	D("%s\n", __func__);
	if (!pcam) {
		pr_err("%s NULL pointer of camera device!\n", __func__);
		return -EINVAL;
	}
	if (pcam_inst->my_index == 0) {
		poll_wait(f, &(pcam_inst->eventHandle.events->wait), wait);
		if (v4l2_event_pending(&pcam_inst->eventHandle))
			rc |= POLLPRI;
	} else {
		if (!pcam_inst->vid_bufq.streaming) {
			D("%s vid_bufq.streaming is off, inst=0x%x\n",
			__func__, (u32)pcam_inst);
			return -EINVAL;
		}
		rc |= vb2_poll(&pcam_inst->vid_bufq, f, wait);
	}
	D("%s returns, rc  = 0x%x\n", __func__, rc);
	return rc;
}

long msm_v4l2_evt_notify(struct msm_cam_media_controller *mctl,
	unsigned int cmd, unsigned long evt)
{
	struct v4l2_event v4l2_ev;
	struct msm_cam_v4l2_device *pcam = NULL;

	if (!mctl) {
		pr_err("%s: mctl is NULL\n", __func__);
		return -EINVAL;
	}

	if (copy_from_user(&v4l2_ev, (void __user *)evt,
		sizeof(struct v4l2_event))) {
		ERR_COPY_FROM_USER();
		return -EFAULT;
	}

	pcam = mctl->pcam_ptr;
	ktime_get_ts(&v4l2_ev.timestamp);
	v4l2_event_queue(pcam->pvdev, &v4l2_ev);
	return 0;
}

int msm_setup_v4l2_event_queue(struct v4l2_fh *eventHandle,
	struct video_device *pvdev)
{
	int rc = 0;
	/* v4l2_fh support */
	spin_lock_init(&pvdev->fh_lock);
	INIT_LIST_HEAD(&pvdev->fh_list);

	rc = v4l2_fh_init(eventHandle, pvdev);
	if (rc < 0)
		return rc;

	if (eventHandle->events == NULL) {
		rc = v4l2_event_init(eventHandle);
		if (rc < 0)
			return rc;
	}

	/* queue of max size 30 */
	rc = v4l2_event_alloc(eventHandle, 30);
	if (rc < 0)
		return rc;

	v4l2_fh_add(eventHandle);
	return rc;
}

static struct v4l2_file_operations g_msm_fops = {
	.owner   = THIS_MODULE,
	.open	= msm_open,
	.poll	= msm_poll,
	.mmap	= msm_mmap,
	.release = msm_close,
	.ioctl   = video_ioctl2,
};

static int msm_cam_dev_init(struct msm_cam_v4l2_device *pcam)
{
	int rc = -ENOMEM;
	struct video_device *pvdev = NULL;
	struct i2c_client *client = v4l2_get_subdevdata(pcam->sensor_sdev);
	D("%s\n", __func__);

	/* first register the v4l2 device */
	pcam->v4l2_dev.dev = &client->dev;
	rc = v4l2_device_register(pcam->v4l2_dev.dev, &pcam->v4l2_dev);
	if (rc < 0)
		return -EINVAL;
	else
		pcam->v4l2_dev.notify = msm_cam_v4l2_subdev_notify;


	/* now setup video device */
	pvdev = video_device_alloc();
	if (pvdev == NULL) {
		pr_err("%s: video_device_alloc failed\n", __func__);
		return rc;
	}

	strlcpy(pcam->media_dev.model, QCAMERA_NAME,
			sizeof(pcam->media_dev.model));
	pcam->media_dev.dev = &client->dev;
	rc = media_device_register(&pcam->media_dev);
	pvdev->v4l2_dev = &pcam->v4l2_dev;
	pcam->v4l2_dev.mdev = &pcam->media_dev;

	/* init video device's driver interface */
	D("sensor name = %s, sizeof(pvdev->name)=%d\n",
		pcam->sensor_sdev->name, sizeof(pvdev->name));

	/* device info - strlcpy is safer than strncpy but
	   only if architecture supports*/
	strlcpy(pvdev->name, pcam->sensor_sdev->name, sizeof(pvdev->name));

	pvdev->release   = video_device_release;
	pvdev->fops	     = &g_msm_fops;
	pvdev->ioctl_ops = &g_msm_ioctl_ops;
	pvdev->minor	 = -1;
	pvdev->vfl_type  = 1;

	media_entity_init(&pvdev->entity, 0, NULL, 0);
	pvdev->entity.type = MEDIA_ENT_T_DEVNODE_V4L;
	pvdev->entity.group_id = QCAMERA_VNODE_GROUP_ID;

	/* register v4l2 video device to kernel as /dev/videoXX */
	D("video_register_device\n");
	rc = video_register_device(pvdev,
					VFL_TYPE_GRABBER,
					msm_camera_v4l2_nr);
	if (rc) {
		pr_err("%s: video_register_device failed\n", __func__);
		goto reg_fail;
	}
	pvdev->entity.name = video_device_node_name(pvdev);
	D("%s: video device registered as /dev/video%d\n",
		__func__, pvdev->num);

	/* connect pcam and video dev to each other */
	pcam->pvdev	= pvdev;
	video_set_drvdata(pcam->pvdev, pcam);

	return rc;

reg_fail:
	video_device_release(pvdev);
	v4l2_device_unregister(&pcam->v4l2_dev);
	pcam->v4l2_dev.dev = NULL;
	return rc;
}

static struct v4l2_subdev *msm_actuator_probe(
	struct msm_actuator_info *actuator_info)
{
	struct v4l2_subdev *act_sdev;
	struct i2c_adapter *adapter = NULL;
	struct msm_actuator_ctrl_t *actrl;
	void *act_client = NULL;

	D("%s called\n", __func__);

	if (!actuator_info)
		goto probe_fail;

	adapter = i2c_get_adapter(actuator_info->bus_id);
	if (!adapter)
		goto probe_fail;

	act_client = i2c_new_device(adapter, actuator_info->board_info);
	if (!act_client)
		goto device_fail;

	act_sdev = (struct v4l2_subdev *)i2c_get_clientdata(act_client);
	if (act_sdev == NULL)
		goto client_fail;

	if (actuator_info->vcm_enable) {
		actrl = get_actrl(act_sdev);
		if (actrl) {
			actrl->vcm_enable = actuator_info->vcm_enable;
			actrl->vcm_pwd = actuator_info->vcm_pwd;
		}
	}

	return act_sdev;

client_fail:
	i2c_unregister_device(act_client);
device_fail:
	i2c_put_adapter(adapter);
	adapter = NULL;
probe_fail:
	return NULL;
}

static struct v4l2_subdev *msm_eeprom_probe(
	struct msm_eeprom_info *eeprom_info)
{
	struct v4l2_subdev *eeprom_sdev;
	struct i2c_adapter *adapter = NULL;
	void *eeprom_client = NULL;

	D("%s called\n", __func__);

	if (!eeprom_info)
		goto probe_fail;

	adapter = i2c_get_adapter(eeprom_info->bus_id);
	if (!adapter)
		goto probe_fail;

	eeprom_client = i2c_new_device(adapter, eeprom_info->board_info);
	if (!eeprom_client)
		goto device_fail;

	eeprom_sdev = (struct v4l2_subdev *)i2c_get_clientdata(eeprom_client);
	if (eeprom_sdev == NULL)
		goto client_fail;

	return eeprom_sdev;
client_fail:
	pr_err("%s client_fail\n", __func__);
	i2c_unregister_device(eeprom_client);
device_fail:
	pr_err("%s device_fail\n", __func__);
	i2c_put_adapter(adapter);
	adapter = NULL;
probe_fail:
	pr_err("%s probe_fail\n", __func__);
	return NULL;
}

/* register a msm sensor into the msm device, which will probe the
 * sensor HW. if the HW exist then create a video device (/dev/videoX/)
 * to represent this sensor */
int msm_sensor_register(struct v4l2_subdev *sensor_sd)
{
	int rc = -EINVAL;
	struct msm_camera_sensor_info *sdata;
	struct msm_cam_v4l2_device *pcam;
	struct msm_sensor_ctrl_t *s_ctrl;

	D("%s for %s\n", __func__, sensor_sd->name);

	/* allocate the memory for the camera device first */
	pcam = kzalloc(sizeof(*pcam), GFP_KERNEL);
	if (!pcam) {
		pr_err("%s: could not allocate mem for msm_cam_v4l2_device\n",
			__func__);
		return -ENOMEM;
	}

	pcam->sensor_sdev = sensor_sd;
	s_ctrl = get_sctrl(sensor_sd);
	sdata = (struct msm_camera_sensor_info *) s_ctrl->sensordata;

	pcam->act_sdev = msm_actuator_probe(sdata->actuator_info);
	pcam->eeprom_sdev = msm_eeprom_probe(sdata->eeprom_info);

	D("%s: pcam =0x%p\n", __func__, pcam);

	pcam->sdata = sdata;

	/* init the user count and lock*/
	pcam->use_count = 0;
	mutex_init(&pcam->vid_lock);
	mutex_init(&pcam->mctl_node.dev_lock);

	/* Initialize the formats supported */
	rc  = msm_mctl_init_user_formats(pcam);
	if (rc < 0)
		goto failure;

	rc  = msm_cam_dev_init(pcam);
	if (rc < 0)
		goto failure;

	rc = msm_setup_mctl_node(pcam);
	if (rc < 0) {
		pr_err("%s:failed to create mctl device: %d\n",
			 __func__, rc);
		goto failure;
	}
	msm_server_update_sensor_info(pcam, sdata);

	/* register the subdevice, must be done for callbacks */
	rc = msm_cam_register_subdev_node(sensor_sd, SENSOR_DEV, vnode_count);
	if (rc < 0) {
		D("%s sensor sub device register failed\n",
			__func__);
		goto failure;
	}

	if (pcam->act_sdev) {
		rc = v4l2_device_register_subdev(&pcam->v4l2_dev,
				pcam->act_sdev);
		if (rc < 0) {
			D("%s actuator sub device register failed\n",
			  __func__);
			goto failure;
		}
	}

	if (pcam->eeprom_sdev) {
		rc = v4l2_device_register_subdev(&pcam->v4l2_dev,
			pcam->eeprom_sdev);
		if (rc < 0) {
			D("%s eeprom sub device register failed\n", __func__);
			goto failure;
		}
	}

	pcam->vnode_id = vnode_count++;
	return rc;

failure:
	kzfree(pcam);
	return rc;
}
EXPORT_SYMBOL(msm_sensor_register);

