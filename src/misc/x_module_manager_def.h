#ifndef __ModuleManagerDef_h_
#define __ModuleManagerDef_h_

#include "x_adapter_factory.h"
#include "x_filter_factory.h"
#include "x_mux_factory.h"
#include "x_manager_factory.h"
#include "x_filereader_factory.h"
#include "x_parser_factory.h"

///Adapter
#define ADAPTER_BEGIN_MAKER(type)\
	static int adapter_##type =

#define ADAPTER_ENTER_MAKER(adapterType, maker)\
	SingletonTmpl<CAdapterFactory>::Instance()->RegisterAdapter((adapterType), (maker))

#define ADAPTER_END_MAKER()\
	;

///Filter
#define FILTER_BEGIN_MAKER(type)\
	static int filter_##type =

#define FILTER_ENTER_MAKER(filterType, maker)\
	SingletonTmpl<CFilterFactory>::Instance()->RegisterFilter((filterType), (maker))

#define FILTER_END_MAKER()\
	;

///Mux
#define MUX_BEGIN_MAKER(type)\
	static int mux_##type =

#define MUX_ENTER_MAKER(muxType, maker)\
	SingletonTmpl<CMuxFactory>::Instance()->RegisterMux((muxType), (maker))

#define MUX_END_MAKER()\
	;

///Manager
#define MANAGER_BEGIN_MAKER(type)\
	static int manager_##type =

#define MANAGER_ENTER_MAKER(managerType, maker)\
	SingletonTmpl<CManagerFactory>::Instance()->RegisterManager((managerType), (maker))

#define MANAGER_END_MAKER()\
	;

///FileReader
#define FILEREADER_BEGIN_MAKER(type)\
	static int file_reader_##type =

#define FILEREADER_ENTER_MAKER(fileReaderType, maker)\
	SingletonTmpl<CFileReaderFactory>::Instance()->RegisterFileReader((fileReaderType), (maker))

#define FILEREADER_END_MAKER()\
	;
	
///CommandParser
#define PARSER_BEGIN_MAKER(type)\
	static int command_parser_##type =

#define PARSER_ENTER_MAKER(commandParserType, maker)\
	SingletonTmpl<CParserFactory>::Instance()->RegisterParser((commandParserType), (maker))

#define PARSER_END_MAKER()\
	;

#endif //~__ModuleManagerDef_h_
