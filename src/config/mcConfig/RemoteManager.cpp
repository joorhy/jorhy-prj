#include "RemoteManager.h"
#include "RecoderManager.h"
#include "x_config.h"
#include "x_sdk.h"

JO_IMPLEMENT_INTERFACE(Manager, "mc", CRemoteManager::Maker)

CRemoteManager::CRemoteManager()
{
	m_regInfo = NULL;
}

CRemoteManager::~CRemoteManager()
{
	if (m_regInfo)
		free(m_regInfo);
}

j_result_t CRemoteManager::GetStreamServerInfo(const j_char_t *pResid, J_StreamServerInfo &ssInfo)
{
	j_result_t nResult = JoXSdk->GetStreamServerInfo((char *)pResid, (j_char_t *)CXConfig::GetUrl(), ssInfo);
	if (nResult != J_OK)
	{
		J_OS::LOGINFO("CRemoteManager::GetStreamServerInfo error, resid = %s", pResid);
		return J_DB_ERROR;
	}

	return J_OK;
}

j_result_t CRemoteManager::GetResourceInfo(ResourceMap &resInfo)
{
	return JoXSdk->Login(CXConfig::GetStreamServerId(), (j_char_t *)CXConfig::GetUrl(), resInfo);
}

j_result_t CRemoteManager::GetChannelInfo(const char *pResid, J_ResourceInfo &resInfo)
{
	return JoXSdk->GetResourceInfo((char *)pResid, (j_char_t *)CXConfig::GetUrl(), resInfo);
}

int CRemoteManager::StartRecord()
{ 
	JoRecoderManager->Single();
	return J_OK; 
}
