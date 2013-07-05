#ifndef __X_DECODER_FACTORY_H_
#define __X_DECODER_FACTORY_H_
#include "j_includes.h"
#include "x_singleton.h"
#include "x_lock.h"

typedef int (*J_MakeDecoderFun)(J_Obj *&);

class JO_API CDecoderFactory
{
	typedef std::map<j_string_t, J_MakeDecoderFun> DecoderRegistMap;
	typedef std::map<j_wnd_t, J_Decoder *> DecoderMap;
public:
	CDecoderFactory() {}
	~CDecoderFactory() {}

public:
	///注册Player类
	///@param[in] 	decType decoder
	///@param[in] 	J_MakeDecoderFun Decoder的构造函数
	///@return 		参考x_error_type.h
	int RegisterDecoder(const char *decType, J_MakeDecoderFun pFun);

	J_Decoder *GetDecoder(j_wnd_t hWindow, const char *pType);
	void DelDecoder(j_wnd_t hWindow);

private:
	DecoderRegistMap m_decRegistMap;
	DecoderMap m_decMap;
	J_OS::TLocker_t m_lock;
};
JO_DECLARE_SINGLETON(DecoderFactory)

#endif //~__X_DECODER_FACTORY_H_