#include "x_pl_record.h"
#include "x_pl_record_ts.h"

CXPlRecord::CXPlRecord(int nId)
{
	m_recodeID = nId;
}

CXPlRecord::~CXPlRecord()
{

}

CXPlRecord *CXPlRecord::CreateInstance(int nType)
{
	CXPlRecord *pInstance = NULL;
	switch(nType)
	{
	case RECORD_TS: 
		pInstance = new CXPlRecordTs(nType);
		break;
	}

	return pInstance;
}

void CXPlRecord::ReleaseInstance(CXPlRecord **pInstance)
{
	if(!pInstance || !(*pInstance))
		return;
	switch((*pInstance)->m_recodeID)
	{
	case RECORD_TS:
		delete (CXPlRecordTs*)(*pInstance);
		*pInstance = NULL;
		return;
	}
}