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
	CAipstarStream(std::string resid, int nChannel);
	~CAipstarStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();

protected:
	static int OnStreamCallBack(HANDLE hHandle, tmRealStreamInfo_t *streamInfo, void *context)
	{
		CAipstarStream *pThis = static_cast<CAipstarStream *>(context);
		if (pThis != NULL)
			pThis->OnRecv(hHandle, streamInfo);

		return 0;
	}

private:
	void OnRecv(HANDLE hHandle, tmRealStreamInfo_t *streamInfo);

private:
	bool m_bStartup;
};

#endif //~__AIPSTARSTREAM_H_
