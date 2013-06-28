#ifndef __AIPSTARSTREAM_H_
#define __AIPSTARSTREAM_H_
#include "AipstarParser.h"
#include "x_time.h"

#include "config.h"
#include "tmTransDefine.h"
#include "tmControlClient.h"

class CAipstarStreamBase : public J_MediaStream
{};

class CAipstarStream : public J_BaseVideoStream<CAipstarStreamBase>
{
	friend class CAipstarChannel;
public:
	CAipstarStream(j_string_t resid, j_int32_t nChannel);
	~CAipstarStream();

public:
	///J_VideoStream
	virtual j_result_t Startup();
	virtual j_result_t Shutdown();
	
public:
	int Broken();

protected:
#ifdef WIN32
	static int CALLBACK OnStreamCallBack(HANDLE hHandle, tmRealStreamInfo_t *streamInfo, void *context)
#else
	static int OnStreamCallBack(HANDLE hHandle, tmRealStreamInfo_t *streamInfo, void *context)
#endif
	{
		CAipstarStream *pThis = static_cast<CAipstarStream *>(context);
		if (pThis != NULL)
			pThis->OnRecv(hHandle, streamInfo);

		return 0;
	}

private:
	j_void_t OnRecv(HANDLE hHandle, tmRealStreamInfo_t *streamInfo);

private:
	j_boolean_t m_bStartup;
	j_uint32_t m_frameNum;
};

#endif //~__AIPSTARSTREAM_H_
