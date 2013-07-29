#include "OnvifCore.h"

#include "OnvifAPIAll/DeviceBinding.nsmap"

COnvifCore::COnvifCore( void ) : m_SupportPTZ(NoSupport)
, MySoap(NULL)
{

}

COnvifCore::~COnvifCore( void )
{
	if (NULL != MySoap)
	{
		soap_free(MySoap);	// detach and free runtime context
		soap_done(MySoap);	// detach context (last use and no longer in scope)
	}
}

bool COnvifCore::InitCore( const char * szTargetIp )
{
	strHostName += "http://";
	strHostName += szTargetIp;
	strHostName += "/onvif/device_service";
	proxyDevice.endpoint = strHostName.c_str();

	soap_register_plugin(proxyDevice.soap,soap_wsse);
	soap_register_plugin(proxyMedia.soap,soap_wsse);
	soap_register_plugin(proxyPTZ.soap,soap_wsse);

	if (NULL == (MySoap = soap_new()))
	{
		return false;
	}
	return GetDeviceInfo();
}

bool COnvifCore::GetMediaProfile( void )
{
	bool bRet = false;

	if (!Authentication(proxyMedia.soap)
		|| !TokenTimestmap(proxyMedia.soap))
	{
		return bRet;
	}

	_trt__GetProfiles *trt__GetProfiles = soap_new__trt__GetProfiles(MySoap,-1);
	_trt__GetProfilesResponse *trt__GetProfilesResponse = soap_new__trt__GetProfilesResponse(MySoap,-1);

	if (SOAP_OK != proxyMedia.__trt__GetProfiles(trt__GetProfiles,trt__GetProfilesResponse))
	{
		PrintErr(proxyMedia.soap);
	}
	else
	{
		_trt__GetStreamUri *trt__GetStreamUri = soap_new__trt__GetStreamUri(MySoap,-1);
		trt__GetStreamUri->StreamSetup = soap_new_tt__StreamSetup(MySoap,-1);
		trt__GetStreamUri->StreamSetup->Stream = tt__StreamType__RTP_Unicast;
		trt__GetStreamUri->StreamSetup->Transport = soap_new_tt__Transport(MySoap,-1);
		trt__GetStreamUri->StreamSetup->Transport->Protocol = tt__TransportProtocol__RTSP;

		_trt__GetStreamUriResponse *trt__GetStreamUriResponse = soap_new__trt__GetStreamUriResponse(MySoap,-1);

		for (vector<tt__Profile * >::size_type i = 0; i < trt__GetProfilesResponse->Profiles.size(); i++)
		{
			MediaProfile tmp;
			tmp.Profile = trt__GetProfilesResponse->Profiles[i]->token.c_str();
			trt__GetStreamUri->ProfileToken = tmp.Profile;

			if(!Authentication(proxyMedia.soap))
			{
				return bRet;
			}

			if (SOAP_OK == proxyMedia.__trt__GetStreamUri(trt__GetStreamUri,trt__GetStreamUriResponse))
			{
				tmp.RtrpUrl = trt__GetStreamUriResponse->MediaUri->Uri.c_str();
				m_MediaProfileVec.push_back(tmp);
				bRet = true;
			}
			else
			{
				PrintErr(proxyMedia.soap);
			}
		}			
	}
	FreeSoap();
	return bRet;
}

bool COnvifCore::Authentication( soap *TargetSoap, 
								const char *szUserName /*= DEV_USERNAME*/, 
								const char *szPassWord /*= DEV_PASSWORD*/, 
								const char *szId /*= NULL*/ )
{
	if(SOAP_OK != soap_wsse_add_UsernameTokenDigest(TargetSoap, szId, szUserName, szPassWord))
	{
		return false;
	}
	return true;
}

bool COnvifCore::TokenTimestmap( soap *TargetSoap, 
								time_t lifetime /*= TOKEN_TIMESTAMP*/ )
{
	if(SOAP_OK != soap_wsse_add_Timestamp(TargetSoap, "Time", lifetime))
	{
		return false;
	}
	return true;
}

bool COnvifCore::GetDeviceInfo( void )
{
	bool bRet = false;

	if (!Authentication(proxyDevice.soap))
	{
		return bRet;
	}

	_tds__GetCapabilities *tds__GetCapabilities = soap_new__tds__GetCapabilities(MySoap, -1);
	tds__GetCapabilities->Category.push_back(tt__CapabilityCategory__All);
	_tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse = soap_new__tds__GetCapabilitiesResponse(MySoap, -1);

	if(SOAP_OK == proxyDevice.__tds__GetCapabilities(tds__GetCapabilities,tds__GetCapabilitiesResponse))
	{
		if (tds__GetCapabilitiesResponse->Capabilities->Media != NULL)
		{
			proxyMedia.endpoint = tds__GetCapabilitiesResponse->Capabilities->Media->XAddr.c_str();
		}

		if (tds__GetCapabilitiesResponse->Capabilities->PTZ != NULL)
		{
			proxyPTZ.endpoint = tds__GetCapabilitiesResponse->Capabilities->PTZ->XAddr.c_str();
			m_SupportPTZ = Support;
		}
		bRet = true;
	}
	FreeSoap();
	return bRet;
}

void COnvifCore::FreeSoap( void )
{
	soap_destroy(MySoap);	// remove deserialized class instances (C++ only)
	soap_end(MySoap);		// clean up and remove deserialized data
}

void COnvifCore::PrintErr( soap* ErrorSoap )
{
	fflush(stdout);
	fprintf(stdout,"error:%d faultstring:%s faultcode:%s faultsubcode:%s faultdetail:%s\r\n",
		ErrorSoap->error,*soap_faultstring(ErrorSoap),*soap_faultcode(ErrorSoap),
		*soap_faultsubcode(ErrorSoap),*soap_faultdetail(ErrorSoap));
}
