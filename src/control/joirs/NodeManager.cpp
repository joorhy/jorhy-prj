#include "NodeManager.h"

CNodeManager::CNodeManager()
{

}

CNodeManager::~CNodeManager()
{

}

j_result_t CNodeManager::OnRead(const J_AsioDataBase *pAsioData, j_result_t nRet)
{
	J_OS::LOGINFO("%d", pAsioData->ioReceiveFrom.finishedLen);
	J_AsioDataBase *pDataBase = (J_AsioDataBase *)pAsioData;
	pDataBase->ioReceiveFrom.finishedLen = 0;
	pDataBase->ioReceiveFrom.bufLen = 15000;

	pDataBase->ioUser = this;
	pDataBase->ioCall = J_AsioDataBase::j_recvfrom_e;
	m_asio.Read(pDataBase);
	
	return J_OK;
}

j_result_t CNodeManager::OnWrite(const J_AsioDataBase *pAsioData, j_result_t nRet)
{
	return J_OK;
}

j_result_t CNodeManager::Start(j_int32_t nPort)
{
	m_asio.Init(nPort, this);
	J_AsioDataBase *pDataBase = new J_AsioDataBase;
	memset(pDataBase, 0, sizeof(J_AsioDataBase));
	pDataBase->ioReceiveFrom.buf = new j_char_t[15000];
	pDataBase->ioReceiveFrom.finishedLen = 0;
	pDataBase->ioReceiveFrom.bufLen = 15000;

	pDataBase->ioUser = this;
	pDataBase->ioCall = J_AsioDataBase::j_recvfrom_e;
	m_asio.Read(pDataBase);
	return J_OK;
}

j_void_t CNodeManager::Stop()
{
	m_asio.Deinit();
}