#ifndef __AIRONIXSTREAM_H_
#define __AIRONIXSTREAM_H_
#include "j_includes.h"
#include "x_time.h"
#include "DVR_NET_SDK.h"

class CAironixStreamBase : public J_MediaStream
{};

class CAironixStream : public J_BaseVideoStream<CAironixStreamBase>
{
	friend class CAironixChannel;
public:
	CAironixStream(std::string resid, int nChannel);
	~CAironixStream();

public:
	///J_VideoStream
	virtual int Startup();
	virtual int Shutdown();

protected:
	static void OnStreamCallBack(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser)
	{
		CAironixStream *pThis = static_cast<CAironixStream *>(pUser);
		if (pThis != NULL)
			pThis->OnRecv(lLiveHandle, frameInfo, pBuffer);
	}

private:
	void OnRecv(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer);

private:
	bool m_bStartup;
};

#endif //~__AIRONIXSTREAM_H_
