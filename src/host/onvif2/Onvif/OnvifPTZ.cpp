#include "OnvifPTZ.h"


COnvifPTZ::COnvifPTZ( void ) : tptz__ContinuousMove(NULL)
, tptz__ContinuousMoveResponse(NULL)
, tptz__Stop(NULL)
, tptz__StopResponse(NULL)
{

}

COnvifPTZ::~COnvifPTZ( void )
{
	FreeSoap();
}

void COnvifPTZ::InitPTZ( void )
{
	strProfileToken = m_MediaProfileVec[0].Profile;

	tptz__ContinuousMove = soap_new__tptz__ContinuousMove(MySoap, -1);
	tptz__ContinuousMoveResponse = soap_new__tptz__ContinuousMoveResponse(MySoap, -1);

	tptz__ContinuousMove->ProfileToken = strProfileToken;
	tptz__ContinuousMove->Velocity = soap_new_tt__PTZSpeed(MySoap, -1);
	tptz__ContinuousMove->Velocity->PanTilt = soap_new_tt__Vector2D(MySoap, -1);
	tptz__ContinuousMove->Velocity->Zoom = soap_new_tt__Vector1D(MySoap, -1);

	tptz__Stop = soap_new__tptz__Stop(MySoap,-1);
	tptz__StopResponse = soap_new__tptz__StopResponse(MySoap,-1);
	tptz__Stop->ProfileToken = strProfileToken;
}

bool COnvifPTZ::PTZLeft( float LeftUnitRange /*= ONVIF_SPEEND*/ )
{
	if (!Authentication(proxyPTZ.soap) ||
		!TokenTimestmap(proxyPTZ.soap))
	{
		return false;
	}

	tptz__ContinuousMove->Velocity->PanTilt->x = LeftUnitRange;
	tptz__ContinuousMove->Velocity->PanTilt->y = ONVIF_ZERO;
	if (proxyPTZ.__tptz__ContinuousMove(tptz__ContinuousMove, tptz__ContinuousMoveResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);
	}
	return true;
}

bool COnvifPTZ::PTZRight( float RightUnitRange /*= ONVIF_SPEEND*/ )
{
	if (!Authentication(proxyPTZ.soap))
	{
		return false;
	}

	tptz__ContinuousMove->Velocity->PanTilt->x = -RightUnitRange;
	tptz__ContinuousMove->Velocity->PanTilt->y = ONVIF_ZERO;

	if (proxyPTZ.__tptz__ContinuousMove(tptz__ContinuousMove,tptz__ContinuousMoveResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);
	}
	return true;
}

bool COnvifPTZ::PTZUp( float UpUnitRange /*= ONVIF_UPDOWN*/ )
{
	if (!Authentication(proxyPTZ.soap))
	{
		return false;
	}

	tptz__ContinuousMove->Velocity->PanTilt->x = ONVIF_ZERO;
	tptz__ContinuousMove->Velocity->PanTilt->y = UpUnitRange;

	if (proxyPTZ.__tptz__ContinuousMove(tptz__ContinuousMove, tptz__ContinuousMoveResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);	
	}
	return true;
}

bool COnvifPTZ::PTZDown( float DownUnitRange /*= ONVIF_UPDOWN*/ )
{
	if (!Authentication(proxyPTZ.soap))
	{
		return false;
	}

	tptz__ContinuousMove->Velocity->PanTilt->x = ONVIF_ZERO;
	tptz__ContinuousMove->Velocity->PanTilt->y = -DownUnitRange;
	if (proxyPTZ.__tptz__ContinuousMove(tptz__ContinuousMove,tptz__ContinuousMoveResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);	
	}
	return true;
}

bool COnvifPTZ::PTZZoomIn( float InUnitRange /*= ONVIF_ZOOM*/ )
{
	if (!Authentication(proxyPTZ.soap))
	{
		return false;
	}

	tptz__ContinuousMove->Velocity->Zoom->x = InUnitRange;
	if (proxyPTZ.__tptz__ContinuousMove(tptz__ContinuousMove,tptz__ContinuousMoveResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);	
	}
	return true;
}

bool COnvifPTZ::PTZZoomOut( float OutUnitRange /*= ONVIF_ZOOM*/ )
{
	if (!Authentication(proxyPTZ.soap))
	{
		return false;
	}

	tptz__ContinuousMove->Velocity->Zoom->x = -OutUnitRange;
	if (proxyPTZ.__tptz__ContinuousMove(tptz__ContinuousMove,tptz__ContinuousMoveResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);	
	}
	return true;
}

bool COnvifPTZ::PTZStop( void )
{
//	Sleep(PTZ_TIME);

	if (!Authentication(proxyPTZ.soap) ||
		!TokenTimestmap(proxyPTZ.soap))
	{
		return false;
	}

	if (proxyPTZ.__tptz__Stop(tptz__Stop, tptz__StopResponse) != SOAP_OK)
	{
		PrintErr(proxyPTZ.soap);	
	}
	return true;
}

