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
	return JoRecoderManager->AddRecord(pResid);
}

int CDeviceControl::StopRecord(const char *pResid)
{
	return JoRecoderManager->DelRecord(pResid);
}

int CDeviceControl::PtzControl(const char *pResid, int nCmd, int nParam)
{
	if (memcmp(pResid, "-1", 2) == 0)
		return J_NOT_EXIST;

    int nStreamType = 1;
	J_Obj *pObj = GetAdapterFactoryLayer()->FatchChannel(pResid, nStreamType);
	if (pObj == NULL)
		return J_NOT_EXIST;

	J_ChannelStream *pChannelStream = dynamic_cast<J_ChannelStream *>(pObj);
	if (pChannelStream == NULL)
		return J_NOT_EXIST;

	J_PtzControl *pPtzControl = dynamic_cast<J_PtzControl *>(pChannelStream);
	if (pPtzControl == NULL)
	{
		J_OS::LOGINFO("CDeviceControl::PtzControl GetInstence error");
		return J_NOT_EXIST;
	}

	return pPtzControl->PtzControl(nCmd, nParam);
}
