#include "StdAfx.h"
#include "pl_com.h"
#include "pl_player.h"
#include "pl_err.h"

INT JoQueryInterface(void* pThis, const JoInterfaceEntry* entries, const GUID& iid, void*& pObj)
{
	ASSERT(pThis != NULL);

	// First entry in the com map should be a simple map entry
	ASSERT(entries->pFunc == _JO_SIMPLEMAPENTRY);

	if( IID_PlObj == iid )
	{
		PlObj* p = (PlObj*)((int)pThis+entries->dw);
		pObj= p;
		return PL_OK;
	}

	while(NULL != entries->pFunc)
	{
		BOOL bBlind = (entries->piid == NULL);
		if(bBlind || *(entries->piid)==iid)
		{
			if(entries->pFunc == _JO_SIMPLEMAPENTRY) //offset
			{
				ASSERT(!bBlind);
				PlObj* p = (PlObj*)((int)pThis+entries->dw);
				pObj= p;
				return PL_OK;
			}
			else //actual function call
			{
				INT ret = entries->pFunc(pThis, iid, pObj, entries->dw);
				if (ret == PL_OK || (!bBlind && PL_OK!=ret))
					return ret;
			}
		}
		++entries;
	}

	return PL_ERR_NO_JO_INTERFACE;
}