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
	CAironixStream(j_string_t resid, j_int32_t nChannel);
	~CAironixStream();

public:
	///J_VideoStream
	virtual j_result_t Startup();
	virtual j_result_t Shutdown();

protected:
#ifdef WIN32
	static void CALL_METHOD OnStreamCallBack(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser)
#else
	static void OnStreamCallBack(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer, void *pUser)
#endif
	{
		CAironixStream *pThis = static_cast<CAironixStream *>(pUser);
		if (pThis != NULL)
			pThis->OnRecv(lLiveHandle, frameInfo, pBuffer);
	}

private:
	j_void_t OnRecv(LONG lLiveHandle, NET_SDK_FRAME_INFO frameInfo, BYTE *pBuffer);

private:
	j_boolean_t m_bStartup;
	j_uint32_t m_frameNum;
};

#endif //~__AIRONIXSTREAM_H_
