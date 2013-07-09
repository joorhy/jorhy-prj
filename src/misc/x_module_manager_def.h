#ifndef __ModuleManagerDef_h_
#define __ModuleManagerDef_h_

#include "x_adapter_factory.h"
#include "x_filter_factory.h"
#include "x_mux_factory.h"
#include "x_manager_factory.h"
#include "x_filereader_factory.h"
#include "x_parser_factory.h"
#include "x_decoder_factory.h"
#include "x_render_factory.h"
#include "x_player_factory.h"
#ifdef WIN32
#define MODULE_API  __declspec(dllexport) 
#else
#define MODULE_API
#endif

#define JO_IMPLEMENT_INTERFACE(_name, _type, _fun)\
extern "C"\
{\
	MODULE_API void Register()\
	{\
	Get##_name##FactoryLayer()->Register##_name((_type), (_fun));\
	}\
}

#endif //~__ModuleManagerDef_h_
