#ifndef __LIVEADAPTER_H_
#define __LIVEADAPTER_H_
#include "j_includes.h"
#include "ModuleManagerDef.h"

class CLiveAdapterBase : public J_DevAdapter
{};

class CLiveAdapter : public J_BaseAdapter<CLiveAdapterBase>
{
	friend class CLiveChannel;
public:
	CLiveAdapter(int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword);
	~CLiveAdapter();

	static int Maker(J_Obj *&pObj, int nDevId, const char *pAddr, int nPort, const char *pUsername, const char *pPassword)
	{
		pObj = new CLiveAdapter(nDevId, pAddr, nPort, pUsername, pPassword);
		return J_OK;
	}

public:
	///J_VideoAdapter
	virtual J_DevStatus GetStatus() const;
	virtual int Broken();
	virtual int MakeChannel(const char *pResid, void *&pObj, void *pOwner, int nChannel, int nStream, int nMode);

private:
	J_DevStatus m_status;
};

ADAPTER_BEGIN_MAKER(live)
	ADAPTER_ENTER_MAKER("live", CLiveAdapter::Maker)
ADAPTER_END_MAKER()

#endif //~__LIVEADAPTER_H_
