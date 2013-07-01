#ifndef __ModuleManagerDef_h_
#define __ModuleManagerDef_h_

#include "x_adapter_factory.h"
#include "x_filter_factory.h"
#include "x_mux_factory.h"
#include "x_manager_factory.h"
#include "x_filereader_factory.h"
#include "x_parser_factory.h"

#define JO_IMPLEMENT_INTERFACE(_name, _type, _fun)\
extern "C"\
{\
	void __declspec(dllexport)  Register()\
	{\
		SingletonTmpl<C##_name##Factory>::Instance()->Register##_name((_type), (_fun));\
	}\
}

///Filter
//#define FILTER_IMPLEMENT_BEGIN(type)\	
//	extern "C"\ 
//	{\
//		void __declspec(dllexport)  Register()\
//		{
//#define FILTER_IMPLEMENT_ENTRY(type, maker)\
//		SingletonTmpl<CFilterFactory>::Instance()->RegisterFilter((filterType), (maker));
//#define FILTER_IMPLEMENT_END()\
//		}\
//	}

///Mux
//#define MUX_IMPLEMENT_BEGIN(type) \	
//	extern "C"\
//	{\
//		void __declspec(dllexport)  Register()\
//		{
//#define MUX_IMPLEMENT_ENTRY(type, maker)\
//		SingletonTmpl<CMuxFactory>::Instance()->RegisterMux((muxType), (maker));
//#define MUX_IMPLEMENT_END()\
//		}\
//	}

///Manager
//#define MANAGER_IMPLEMENT_BEGIN(type) \	
//	extern "C"\
//	{\
//		void __declspec(dllexport)  Register()\
//		{
//#define MANAGER_IMPLEMENT_ENTRY(type, maker)
//			SingletonTmpl<CManagerFactory>::Instance()->RegisterManager((managerType), (maker));\
//#define MANAGER_IMPLEMENT_END()\
//		}\
//	}

///FileReader
//#define FILEREADER_IMPLEMENT_BEGIN(type) \	
//	extern "C"\
//	{\
//		void __declspec(dllexport)  Register()\
//		{
//#define FILEREADER_IMPLEMENT_ENTRY(type, maker)\
//		SingletonTmpl<CFileReaderFactory>::Instance()->RegisterFileReader((fileReaderType), (maker));
//#define FILEREADER_IMPLEMENT_END()\
//		}\
//	}
	
///CommandParser
//#define PARSER_IMPLEMENT_BEGIN(type) \	
//	extern "C"\
//	{\
//		void __declspec(dllexport)  Register()\
//		{
//#define PARSER_IMPLEMENT_ENTRY(type, maker)
//			SingletonTmpl<CParserFactory>::Instance()->RegisterParser((commandParserType), (maker));
//#define PARSER_IMPLEMENT_END()\
//		}\
//	}

#endif //~__ModuleManagerDef_h_
