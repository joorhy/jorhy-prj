#include "LiveStream.h"

#include <asm/types.h>		/* for videodev2.h */
#include <linux/videodev2.h>

const char *dev_name_buf = "/dev/video%d";
#define CLEAR(x) memset (&(x), 0, sizeof (x))

static int xioctl(int fd, int request, void *arg)
{
  int r;

  do
    r = ioctl(fd, request, arg);
  while (-1 == r && EINTR == errno);

  return r;
}

CLiveStream::CLiveStream(std::string resid, int nChannel)
{
	m_cap_fd = -1;
	m_io = IO_METHOD_MMAP;
	m_pixel_format = V4L2_PIX_FMT_MJPEG;//V4L2_PIX_FMT_YUYV;
	m_buffers = NULL;
	m_nBuffers = 0;
	m_width = 640;
	m_height = 480;
	m_count = 10;
	m_pRecvBuff = NULL;
	m_bStartup = false;
	m_nChannel = nChannel;

	if (NULL == m_pRecvBuff)
		m_pRecvBuff = new char[1024 * 1024];
}

CLiveStream::~CLiveStream()
{
	if (m_pRecvBuff != NULL)
	{
		delete m_pRecvBuff;
		m_pRecvBuff = NULL;
	}
}

int CLiveStream::Startup()
{
	if (m_bStartup)
		return J_OK;

	OpenDevice();
	InitDevice();
	StartCapturing();

	m_bStartup = true;
	pthread_create(&m_recvThread, NULL, CLiveStream::WorkThread, this);
	J_OS::LOGINFO("CLiveStream::Startup Startup this = %d", this);

	return J_OK;
}

int CLiveStream::Shutdown()
{
	if (!m_bStartup)
		return J_OK;

	m_bStartup = false;
	pthread_cancel(m_recvThread);
	pthread_join(m_recvThread, NULL);

	StopCapturing();
	UninitDevice();
	CloseDevice();

	m_parser.Deinit();

	J_OS::LOGINFO("CLiveStream::Shutdown Shutdown this = %d", this);

	return J_OK;
}

int CLiveStream::OpenDevice()
{
	struct stat st;
	char dev_name[16] = {0};
	sprintf(dev_name, dev_name_buf, m_nChannel - 1);
	if (-1 == stat(dev_name, &st))
	{
	  J_OS::LOGERROR("CLiveStream::OpenDevice Cannot identify '%s'", dev_name);
	  return J_DEV_ERROR;
	}

	if (!S_ISCHR(st.st_mode))
	{
	  J_OS::LOGERROR("CLiveStream::OpenDevice %s is no device", dev_name);
	  return J_DEV_ERROR;
	}

	m_cap_fd = open(dev_name, O_RDWR /* required */  | O_NONBLOCK, 0);
	if (-1 == m_cap_fd)
	{
	  J_OS::LOGERROR("CLiveStream::OpenDevice Cannot open '%s'", dev_name);
	  return J_DEV_ERROR;
	}

  return J_OK;
}

int CLiveStream::CloseDevice()
{
	if (-1 == close(m_cap_fd))
	{
	  J_OS::LOGERROR("CLiveStream::CloseDevice error");
	  return J_DEV_ERROR;
	}
	m_cap_fd = -1;

	return J_OK;
}

int CLiveStream::InitDevice()
{
	struct v4l2_capability cap;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_format fmt;

	CLEAR(cap);

	if (-1 == xioctl(m_cap_fd, VIDIOC_QUERYCAP, &cap))
	{
		if (EINVAL == errno)
		{
			J_OS::LOGERROR("CLiveStream::InitDevice %d is no V4L2 device", m_nChannel);
			return J_DEV_ERROR;
		}
		else
		{
			return J_DEV_ERROR;
		}
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE))
	{
		J_OS::LOGINFO("CLiveStream::InitDevice %d is no video capture device", m_nChannel);
		return J_DEV_ERROR;
	}

	switch (m_io)
	{
	case IO_METHOD_READ:
		if (!(cap.capabilities & V4L2_CAP_READWRITE))
		{
			J_OS::LOGINFO("CLiveStream::InitDevice %d does not support read i/o", m_nChannel);
			return J_DEV_ERROR;
		}
		break;

	case IO_METHOD_MMAP:
	case IO_METHOD_USERPTR:
		if (!(cap.capabilities & V4L2_CAP_STREAMING))
		{
			J_OS::LOGINFO("CLiveStream::InitDevice %d does not support streaming i/o\n", m_nChannel);
			return J_DEV_ERROR;
		}
		break;
	}

	/* Select video input, video standard and tune here. */
	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == xioctl(m_cap_fd, VIDIOC_CROPCAP, &cropcap))
	{
	  /* Errors ignored. */
	}

	crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	crop.c = cropcap.defrect;	/* reset to default */

	if (-1 == xioctl(m_cap_fd, VIDIOC_S_CROP, &crop))
	{
		switch (errno)
		{
		case EINVAL:
			/* Cropping not supported. */
			break;
		default:
			/* Errors ignored. */
			break;
		}
	}

	CLEAR(fmt);

	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = m_width;
	fmt.fmt.pix.height = m_height;
	fmt.fmt.pix.pixelformat = m_pixel_format;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if (-1 == xioctl(m_cap_fd, VIDIOC_G_FMT, &fmt))
	{
		J_OS::LOGERROR("CLiveStream::InitDevice errno = %d", errno);
		return J_DEV_ERROR;
	}

	//fmt.fmt.pix.pixelformat = m_pixel_format;
	//fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	//if (-1 == xioctl(m_cap_fd, VIDIOC_S_FMT, &fmt))
	//{
	//	J_OS::LOGINFO("CLiveStream::InitDevice errno = %d", errno);
	//	return J_DEV_ERROR;
	//}

	if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_YUYV)
	{
		m_parser.Init(J_VideoYuyv);
	}
	else if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_MJPEG)
	{
		m_parser.Init(J_VideoMjpeg);
	}
	else
	{
		m_parser.Init(J_VideoNormal);
	}

	/* Note VIDIOC_S_FMT may change width and height. */
	m_width = fmt.fmt.pix.width;
	m_height = fmt.fmt.pix.height;

	switch (m_io)
	{
	case IO_METHOD_READ:
		InitRead(fmt.fmt.pix.sizeimage);
		break;

	case IO_METHOD_MMAP:
	  InitMmap();
	  break;

	case IO_METHOD_USERPTR:
	  InitUserp(fmt.fmt.pix.sizeimage);
	  break;
	}

	return J_OK;
}

int CLiveStream::UninitDevice()
{
	unsigned int i;
	switch (m_io)
	{
	case IO_METHOD_READ:
	  free(m_buffers[0].start);
	  break;

	case IO_METHOD_MMAP:
	  for (i = 0; i < m_nBuffers; ++i)
		  if (-1 == munmap(m_buffers[i].start, m_buffers[i].length))
			  return J_DEV_ERROR;
	  break;

	case IO_METHOD_USERPTR:
	  for (i = 0; i < m_nBuffers; ++i)
		  free(m_buffers[i].start);
	  break;
	}

	free(m_buffers);

	return J_OK;
}

int CLiveStream::InitRead(unsigned int buffer_size)
{
	m_buffers = (buffer *)calloc(1, sizeof(*m_buffers));

	if (!m_buffers)
	{
		J_OS::LOGERROR("CLiveStream::InitRead Out of memory");
		return J_DEV_ERROR;
	}

	m_buffers[0].length = buffer_size;
	m_buffers[0].start = malloc(buffer_size);

	if (!m_buffers[0].start)
	{
		J_OS::LOGINFO("CLiveStream::InitRead Out of memory");
		return J_DEV_ERROR;
	}

	return J_OK;
}

int CLiveStream::InitMmap()
{
	struct v4l2_requestbuffers req;
	CLEAR(req);

	req.count = 4;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	if (-1 == xioctl(m_cap_fd, VIDIOC_REQBUFS, &req))
	{
		if (EINVAL == errno)
		{
			J_OS::LOGERROR("CLiveStream::InitMmap %d does not support memory mapping", m_nChannel);
			return J_DEV_ERROR;
		}
		else
		{
			return J_DEV_ERROR;
		}
	}

	if (req.count < 2)
	{
		J_OS::LOGINFO("CLiveStream::InitMmap Insufficient buffer memory on %d", m_nChannel);
		return J_DEV_ERROR;
	}

	m_buffers = (buffer *)calloc(req.count, sizeof(*m_buffers));

	if (!m_buffers)
	{
		J_OS::LOGINFO("CLiveStream::InitMmap Out of memory");
		return J_DEV_ERROR;
	}

	for (m_nBuffers = 0; m_nBuffers < req.count; ++m_nBuffers)
	{
	  struct v4l2_buffer buf;
	  CLEAR(buf);

	  buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	  buf.memory = V4L2_MEMORY_MMAP;
	  buf.index = m_nBuffers;

	  if (-1 == xioctl(m_cap_fd, VIDIOC_QUERYBUF, &buf))
		  return J_DEV_ERROR;

	  m_buffers[m_nBuffers].length = buf.length;
	  m_buffers[m_nBuffers].start = mmap(NULL /* start anywhere */ ,
					  buf.length,
					  PROT_READ | PROT_WRITE /* required */ ,
					  MAP_SHARED /* recommended */ ,
					  m_cap_fd, buf.m.offset);

	  if (MAP_FAILED == m_buffers[m_nBuffers].start)
		  return J_DEV_ERROR;
	}

	return J_OK;
}

int CLiveStream::InitUserp(unsigned int buffer_size)
{
	struct v4l2_requestbuffers req;
	CLEAR(req);

	req.count = 4;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_USERPTR;

	if (-1 == xioctl(m_cap_fd, VIDIOC_REQBUFS, &req))
	{
		if (EINVAL == errno)
		{
			J_OS::LOGERROR("CLiveStream::InitUser %d does not support user pointer i/o", m_nChannel);
			return J_DEV_ERROR;
		}
		else
		{
			return J_DEV_ERROR;
		}
	}

	m_buffers = (buffer *)calloc(4, sizeof(*m_buffers));

	if (!m_buffers)
	{
		J_OS::LOGINFO("CLiveStream::InitUser Out of memory\n");
		return J_DEV_ERROR;
	}

	for (m_nBuffers = 0; m_nBuffers < 4; ++m_nBuffers)
	{
		m_buffers[m_nBuffers].length = buffer_size;
		m_buffers[m_nBuffers].start = malloc(buffer_size);

		if (!m_buffers[m_nBuffers].start)
		{
			J_OS::LOGINFO("CLiveStream::InitUser Out of memory\n");
			return J_DEV_ERROR;
		}
	}

	return J_OK;
}

int CLiveStream::StartCapturing()
{
	unsigned int i;
	enum v4l2_buf_type type;

	switch (m_io)
	{
	case IO_METHOD_READ:
	  /* Nothing to do. */
	  break;

	case IO_METHOD_MMAP:
		for (i = 0; i < m_nBuffers; ++i)
		{
			struct v4l2_buffer buf;
			CLEAR(buf);

			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_MMAP;
			buf.index = i;

			if (-1 == xioctl(m_cap_fd, VIDIOC_QBUF, &buf))
				return J_DEV_ERROR;
		}

		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if (-1 == xioctl(m_cap_fd, VIDIOC_STREAMON, &type))
			return J_DEV_ERROR;
		break;

	case IO_METHOD_USERPTR:
		for (i = 0; i < m_nBuffers; ++i)
		{
			struct v4l2_buffer buf;
			CLEAR(buf);

			buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory = V4L2_MEMORY_USERPTR;
			buf.m.userptr = (unsigned long)m_buffers[i].start;
			buf.length = m_buffers[i].length;

			if (-1 == xioctl(m_cap_fd, VIDIOC_QBUF, &buf))
				return J_DEV_ERROR;
		}
		type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

		if (-1 == xioctl(m_cap_fd, VIDIOC_STREAMON, &type))
			return J_DEV_ERROR;

		break;
	}

	return J_OK;
}

int CLiveStream::StopCapturing()
{
	enum v4l2_buf_type type;
	switch (m_io)
	{
	case IO_METHOD_READ:
	  /* Nothing to do. */
	  break;

	case IO_METHOD_MMAP:
	case IO_METHOD_USERPTR:
	  type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	  if (-1 == xioctl(m_cap_fd, VIDIOC_STREAMOFF, &type))
		  return J_DEV_ERROR;

	  break;
	}

	return J_OK;
}

int CLiveStream::ReadFrame()
{
	struct v4l2_buffer buf;
	unsigned int i;
	ssize_t read_bytes;
	unsigned int total_read_bytes;

	switch (m_io)
	{
	case IO_METHOD_READ:
		total_read_bytes = 0;
		do
		{
			read_bytes = read(m_cap_fd, m_buffers[0].start, m_buffers[0].length);
			if (read_bytes < 0)
			{
				switch (errno)
				{
				case EIO:
				case EAGAIN:
					continue;
				default:
					return J_DEV_ERROR;
				}
			}
			total_read_bytes += read_bytes;

		} while (total_read_bytes < m_buffers[0].length);
		ProcessImage(m_buffers[0].start, m_buffers[0].length);

		break;

	case IO_METHOD_MMAP:
		CLEAR(buf);

		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;

		if (-1 == xioctl(m_cap_fd, VIDIOC_DQBUF, &buf))
		{
			switch (errno)
			{
			case EAGAIN:
				return 0;

			case EIO:
				/* Could ignore EIO, see spec. */

				/* fall through */

			default:
				return J_DEV_ERROR;
			}
		}

		assert(buf.index < m_nBuffers);

		ProcessImage(m_buffers[buf.index].start, buf.bytesused);

		if (-1 == xioctl(m_cap_fd, VIDIOC_QBUF, &buf))
			return J_DEV_ERROR;

		break;

	case IO_METHOD_USERPTR:
	  CLEAR(buf);

	  buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	  buf.memory = V4L2_MEMORY_USERPTR;

	  if (-1 == xioctl(m_cap_fd, VIDIOC_DQBUF, &buf))
	  {
		  switch (errno)
		  {
		  case EAGAIN:
			  return 0;

		  case EIO:
		  /* Could ignore EIO, see spec. */

		  /* fall through */

		  default:
			  {
				  J_OS::LOGERROR("errno = %d", errno);
				  return J_DEV_ERROR;
			  }
		  }
	  }

	  for (i = 0; i < m_nBuffers; ++i)
		  if (buf.m.userptr == (unsigned long) m_buffers[i].start
				  && buf.length == m_buffers[i].length)
			  break;

	  assert(i < m_nBuffers);

	  ProcessImage((void *) buf.m.userptr, buf.length);

	  if (-1 == xioctl(m_cap_fd, VIDIOC_QBUF, &buf))
		  return J_DEV_ERROR;

	  break;
	}

	return 1;
}

int CLiveStream::ProcessImage(const void *p, ssize_t size)
{
	/*static FILE *fp = NULL;
	if (fp == NULL)
		fp = fopen("test.jpg", "wb+");
	fwrite(p, 1, size, fp);*/
	m_parser.InputData((const char *)p, size);

	int nRet = 0;
	do
	{
		J_StreamHeader streamHeader;
		nRet = m_parser.GetOnePacket(m_pRecvBuff, streamHeader);
		if (nRet == J_OK)
		{
			std::vector<CRingBuffer *>::iterator it = m_vecRingBuffer.begin();
			for (; it != m_vecRingBuffer.end(); it++)
			{
				(*it)->PushBuffer(m_pRecvBuff, streamHeader);
			}
		}
	}while (nRet == J_OK);

	return J_OK;
}

void CLiveStream::OnWork()
{
	//while (m_count-- > 0)
	while (m_bStartup)
	{
		for (;;)
		{
			fd_set fds;
			struct timeval tv;
			int r;

			FD_ZERO(&fds);
			FD_SET(m_cap_fd, &fds);

			/* Timeout. */
			tv.tv_sec = 3;
			tv.tv_usec = 0;

			r = select(m_cap_fd + 1, &fds, NULL, NULL, &tv);

			if (-1 == r)
			{
				if (EINTR == errno)
					continue;

				return;
			}

			if (0 == r)
			{
				J_OS::LOGERROR("CLiveStream::InitUser select timeout");
				return;
			}

			if (ReadFrame())
				break;

			/* EAGAIN - continue select loop. */
		}
	}
}
