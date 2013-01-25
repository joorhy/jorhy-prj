#ifndef __LIVESTREAM_H_
#define __LIVESTREAM_H_
#include "LiveParser.h"

typedef enum
{
  IO_METHOD_READ,
  IO_METHOD_MMAP,
  IO_METHOD_USERPTR,
} io_method;

struct buffer
{
  void *start;
  size_t length;
};

class CLiveStreamBase : public J_MediaStream
{};

class CLiveStream : public J_BaseVideoStream<CLiveStreamBase>
{
public:
	CLiveStream(std::string resid, int nChannel);
	~CLiveStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();

private:
	int OpenDevice();
	int CloseDevice();
	int InitDevice();
	int UninitDevice();
	int InitRead(unsigned int buffer_size);
	int InitMmap();
	int InitUserp(unsigned int buffer_size);
	int StartCapturing();
	int StopCapturing();
	int ReadFrame();
	int ProcessImage(const void *p, ssize_t size);

private:
	static void *WorkThread(void *param)
	{
		(static_cast<CLiveStream *>(param))->OnWork();
		return (void *)0;
	}
	void OnWork();

private:
	io_method m_io;
	/* can be V4L2_PIX_FMT_YUV420 or V4L2_PIX_FMT_PWC2 */
	int m_pixel_format;
	int m_cap_fd;
	buffer *m_buffers;
	unsigned int m_nBuffers;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_count;

	pthread_t m_recvThread;
	bool m_bStartup;
	CLiveParser m_parser;
	char *m_pRecvBuff;
	int m_nChannel;
};

#endif //~__LIVESTREAM_H_
