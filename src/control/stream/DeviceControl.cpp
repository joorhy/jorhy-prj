#include "x_adapter_manager.h"
#include "DeviceControl.h"
#include "RecoderManager.h"

CDeviceControl::CDeviceControl()
{

}

CDeviceControl::~CDeviceControl()
{

}

int CDeviceControl::StartRecord(const char *pResid)
{
	return SingletonTmpl<CRecoderManager>::Instance()->AddRecord(pResid);
}

int CDeviceControl::StopRecord(const char *pResid)
{
	return SingletonTmpl<CRecoderManager>::Instance()->DelRecord(pResid);
}

int CDeviceControl::PtzControl(const char *pResid, int nCmd, int nParam)
{
	if (memcmp(pResid, "-1", 2) == 0)
		return J_NOT_EXIST;

    int nStreamType = 1;
	J_PtzControl *pPtzControl = dynamic_cast<J_PtzControl *>((J_ChannelStream *)SingletonTmpl<CAdapterFactory>::Instance()->GetInstance(pResid, OBJ_CHANNEL, nStreamType));
	if (pPtzControl == NULL)
	{
		J_OS::LOGINFO("CDeviceControl::PtzControl GetInstence error");
		return J_NOT_EXIST;
	}

	return pPtzControl->PtzControl(nCmd, nParam);
}
