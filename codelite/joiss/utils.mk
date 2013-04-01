##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=utils
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/28/2013
CodeLitePath           :="/home/jorhy/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/common_x_base64$(ObjectSuffix) $(IntermediateDirectory)/common_x_crc32$(ObjectSuffix) $(IntermediateDirectory)/common_x_md5$(ObjectSuffix) $(IntermediateDirectory)/common_x_sha1$(ObjectSuffix) $(IntermediateDirectory)/faac_aacquant$(ObjectSuffix) $(IntermediateDirectory)/faac_backpred$(ObjectSuffix) $(IntermediateDirectory)/faac_bitstream$(ObjectSuffix) $(IntermediateDirectory)/faac_channels$(ObjectSuffix) $(IntermediateDirectory)/faac_fft$(ObjectSuffix) $(IntermediateDirectory)/faac_filtbank$(ObjectSuffix) \
	$(IntermediateDirectory)/faac_frame$(ObjectSuffix) $(IntermediateDirectory)/faac_huffman$(ObjectSuffix) $(IntermediateDirectory)/faac_ltp$(ObjectSuffix) $(IntermediateDirectory)/faac_midside$(ObjectSuffix) $(IntermediateDirectory)/faac_psychkni$(ObjectSuffix) $(IntermediateDirectory)/faac_tns$(ObjectSuffix) $(IntermediateDirectory)/faac_util$(ObjectSuffix) $(IntermediateDirectory)/tinyxml_tinystr$(ObjectSuffix) $(IntermediateDirectory)/tinyxml_tinyxml$(ObjectSuffix) $(IntermediateDirectory)/tinyxml_tinyxmlerror$(ObjectSuffix) \
	$(IntermediateDirectory)/tinyxml_tinyxmlparser$(ObjectSuffix) $(IntermediateDirectory)/uuid_clear$(ObjectSuffix) $(IntermediateDirectory)/uuid_compare$(ObjectSuffix) $(IntermediateDirectory)/uuid_copy$(ObjectSuffix) $(IntermediateDirectory)/uuid_gen_uuid$(ObjectSuffix) $(IntermediateDirectory)/uuid_isnull$(ObjectSuffix) $(IntermediateDirectory)/uuid_pack$(ObjectSuffix) $(IntermediateDirectory)/uuid_parse$(ObjectSuffix) $(IntermediateDirectory)/uuid_unpack$(ObjectSuffix) $(IntermediateDirectory)/uuid_unparse$(ObjectSuffix) \
	$(IntermediateDirectory)/uuid_uuid_time$(ObjectSuffix) $(IntermediateDirectory)/g722_1_G722_1_1C_Float$(ObjectSuffix) $(IntermediateDirectory)/json_c_arraylist$(ObjectSuffix) $(IntermediateDirectory)/json_c_debug$(ObjectSuffix) $(IntermediateDirectory)/json_c_json_object$(ObjectSuffix) $(IntermediateDirectory)/json_c_json_tokener$(ObjectSuffix) $(IntermediateDirectory)/json_c_json_util$(ObjectSuffix) $(IntermediateDirectory)/json_c_linkhash$(ObjectSuffix) $(IntermediateDirectory)/json_c_printbuf$(ObjectSuffix) $(IntermediateDirectory)/sqlite3_shell$(ObjectSuffix) \
	$(IntermediateDirectory)/sqlite3_sqlite3$(ObjectSuffix) $(IntermediateDirectory)/ghttp_ghttp$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_base64$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_date$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_hdrs$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_req$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_resp$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_trans$(ObjectSuffix) $(IntermediateDirectory)/ghttp_http_uri$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/common_x_base64$(ObjectSuffix): ../../src/utils/common/x_base64.cpp $(IntermediateDirectory)/common_x_base64$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_base64.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/common_x_base64$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_x_base64$(DependSuffix): ../../src/utils/common/x_base64.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/common_x_base64$(ObjectSuffix) -MF$(IntermediateDirectory)/common_x_base64$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_base64.cpp"

$(IntermediateDirectory)/common_x_base64$(PreprocessSuffix): ../../src/utils/common/x_base64.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_x_base64$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_base64.cpp"

$(IntermediateDirectory)/common_x_crc32$(ObjectSuffix): ../../src/utils/common/x_crc32.cpp $(IntermediateDirectory)/common_x_crc32$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_crc32.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/common_x_crc32$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_x_crc32$(DependSuffix): ../../src/utils/common/x_crc32.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/common_x_crc32$(ObjectSuffix) -MF$(IntermediateDirectory)/common_x_crc32$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_crc32.cpp"

$(IntermediateDirectory)/common_x_crc32$(PreprocessSuffix): ../../src/utils/common/x_crc32.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_x_crc32$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_crc32.cpp"

$(IntermediateDirectory)/common_x_md5$(ObjectSuffix): ../../src/utils/common/x_md5.cpp $(IntermediateDirectory)/common_x_md5$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_md5.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/common_x_md5$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_x_md5$(DependSuffix): ../../src/utils/common/x_md5.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/common_x_md5$(ObjectSuffix) -MF$(IntermediateDirectory)/common_x_md5$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_md5.cpp"

$(IntermediateDirectory)/common_x_md5$(PreprocessSuffix): ../../src/utils/common/x_md5.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_x_md5$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_md5.cpp"

$(IntermediateDirectory)/common_x_sha1$(ObjectSuffix): ../../src/utils/common/x_sha1.cpp $(IntermediateDirectory)/common_x_sha1$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_sha1.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/common_x_sha1$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_x_sha1$(DependSuffix): ../../src/utils/common/x_sha1.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/common_x_sha1$(ObjectSuffix) -MF$(IntermediateDirectory)/common_x_sha1$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_sha1.cpp"

$(IntermediateDirectory)/common_x_sha1$(PreprocessSuffix): ../../src/utils/common/x_sha1.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_x_sha1$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/common/x_sha1.cpp"

$(IntermediateDirectory)/faac_aacquant$(ObjectSuffix): ../../src/utils/faac/aacquant.c $(IntermediateDirectory)/faac_aacquant$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/aacquant.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_aacquant$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_aacquant$(DependSuffix): ../../src/utils/faac/aacquant.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_aacquant$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_aacquant$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/aacquant.c"

$(IntermediateDirectory)/faac_aacquant$(PreprocessSuffix): ../../src/utils/faac/aacquant.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_aacquant$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/aacquant.c"

$(IntermediateDirectory)/faac_backpred$(ObjectSuffix): ../../src/utils/faac/backpred.c $(IntermediateDirectory)/faac_backpred$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/backpred.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_backpred$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_backpred$(DependSuffix): ../../src/utils/faac/backpred.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_backpred$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_backpred$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/backpred.c"

$(IntermediateDirectory)/faac_backpred$(PreprocessSuffix): ../../src/utils/faac/backpred.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_backpred$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/backpred.c"

$(IntermediateDirectory)/faac_bitstream$(ObjectSuffix): ../../src/utils/faac/bitstream.c $(IntermediateDirectory)/faac_bitstream$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/bitstream.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_bitstream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_bitstream$(DependSuffix): ../../src/utils/faac/bitstream.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_bitstream$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_bitstream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/bitstream.c"

$(IntermediateDirectory)/faac_bitstream$(PreprocessSuffix): ../../src/utils/faac/bitstream.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_bitstream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/bitstream.c"

$(IntermediateDirectory)/faac_channels$(ObjectSuffix): ../../src/utils/faac/channels.c $(IntermediateDirectory)/faac_channels$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/channels.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_channels$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_channels$(DependSuffix): ../../src/utils/faac/channels.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_channels$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_channels$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/channels.c"

$(IntermediateDirectory)/faac_channels$(PreprocessSuffix): ../../src/utils/faac/channels.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_channels$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/channels.c"

$(IntermediateDirectory)/faac_fft$(ObjectSuffix): ../../src/utils/faac/fft.c $(IntermediateDirectory)/faac_fft$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/fft.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_fft$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_fft$(DependSuffix): ../../src/utils/faac/fft.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_fft$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_fft$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/fft.c"

$(IntermediateDirectory)/faac_fft$(PreprocessSuffix): ../../src/utils/faac/fft.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_fft$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/fft.c"

$(IntermediateDirectory)/faac_filtbank$(ObjectSuffix): ../../src/utils/faac/filtbank.c $(IntermediateDirectory)/faac_filtbank$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/filtbank.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_filtbank$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_filtbank$(DependSuffix): ../../src/utils/faac/filtbank.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_filtbank$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_filtbank$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/filtbank.c"

$(IntermediateDirectory)/faac_filtbank$(PreprocessSuffix): ../../src/utils/faac/filtbank.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_filtbank$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/filtbank.c"

$(IntermediateDirectory)/faac_frame$(ObjectSuffix): ../../src/utils/faac/frame.c $(IntermediateDirectory)/faac_frame$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/frame.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_frame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_frame$(DependSuffix): ../../src/utils/faac/frame.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_frame$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_frame$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/frame.c"

$(IntermediateDirectory)/faac_frame$(PreprocessSuffix): ../../src/utils/faac/frame.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_frame$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/frame.c"

$(IntermediateDirectory)/faac_huffman$(ObjectSuffix): ../../src/utils/faac/huffman.c $(IntermediateDirectory)/faac_huffman$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/huffman.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_huffman$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_huffman$(DependSuffix): ../../src/utils/faac/huffman.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_huffman$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_huffman$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/huffman.c"

$(IntermediateDirectory)/faac_huffman$(PreprocessSuffix): ../../src/utils/faac/huffman.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_huffman$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/huffman.c"

$(IntermediateDirectory)/faac_ltp$(ObjectSuffix): ../../src/utils/faac/ltp.c $(IntermediateDirectory)/faac_ltp$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/ltp.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_ltp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_ltp$(DependSuffix): ../../src/utils/faac/ltp.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_ltp$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_ltp$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/ltp.c"

$(IntermediateDirectory)/faac_ltp$(PreprocessSuffix): ../../src/utils/faac/ltp.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_ltp$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/ltp.c"

$(IntermediateDirectory)/faac_midside$(ObjectSuffix): ../../src/utils/faac/midside.c $(IntermediateDirectory)/faac_midside$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/midside.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_midside$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_midside$(DependSuffix): ../../src/utils/faac/midside.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_midside$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_midside$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/midside.c"

$(IntermediateDirectory)/faac_midside$(PreprocessSuffix): ../../src/utils/faac/midside.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_midside$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/midside.c"

$(IntermediateDirectory)/faac_psychkni$(ObjectSuffix): ../../src/utils/faac/psychkni.c $(IntermediateDirectory)/faac_psychkni$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/psychkni.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_psychkni$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_psychkni$(DependSuffix): ../../src/utils/faac/psychkni.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_psychkni$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_psychkni$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/psychkni.c"

$(IntermediateDirectory)/faac_psychkni$(PreprocessSuffix): ../../src/utils/faac/psychkni.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_psychkni$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/psychkni.c"

$(IntermediateDirectory)/faac_tns$(ObjectSuffix): ../../src/utils/faac/tns.c $(IntermediateDirectory)/faac_tns$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/tns.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_tns$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_tns$(DependSuffix): ../../src/utils/faac/tns.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_tns$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_tns$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/tns.c"

$(IntermediateDirectory)/faac_tns$(PreprocessSuffix): ../../src/utils/faac/tns.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_tns$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/tns.c"

$(IntermediateDirectory)/faac_util$(ObjectSuffix): ../../src/utils/faac/util.c $(IntermediateDirectory)/faac_util$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/util.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/faac_util$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/faac_util$(DependSuffix): ../../src/utils/faac/util.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/faac_util$(ObjectSuffix) -MF$(IntermediateDirectory)/faac_util$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/util.c"

$(IntermediateDirectory)/faac_util$(PreprocessSuffix): ../../src/utils/faac/util.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/faac_util$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/faac/util.c"

$(IntermediateDirectory)/tinyxml_tinystr$(ObjectSuffix): ../../src/utils/tinyxml/tinystr.cpp $(IntermediateDirectory)/tinyxml_tinystr$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinystr.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxml_tinystr$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxml_tinystr$(DependSuffix): ../../src/utils/tinyxml/tinystr.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxml_tinystr$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxml_tinystr$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinystr.cpp"

$(IntermediateDirectory)/tinyxml_tinystr$(PreprocessSuffix): ../../src/utils/tinyxml/tinystr.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tinyxml_tinystr$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinystr.cpp"

$(IntermediateDirectory)/tinyxml_tinyxml$(ObjectSuffix): ../../src/utils/tinyxml/tinyxml.cpp $(IntermediateDirectory)/tinyxml_tinyxml$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxml.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxml_tinyxml$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxml_tinyxml$(DependSuffix): ../../src/utils/tinyxml/tinyxml.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxml_tinyxml$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxml_tinyxml$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxml.cpp"

$(IntermediateDirectory)/tinyxml_tinyxml$(PreprocessSuffix): ../../src/utils/tinyxml/tinyxml.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tinyxml_tinyxml$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxml.cpp"

$(IntermediateDirectory)/tinyxml_tinyxmlerror$(ObjectSuffix): ../../src/utils/tinyxml/tinyxmlerror.cpp $(IntermediateDirectory)/tinyxml_tinyxmlerror$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxmlerror.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxml_tinyxmlerror$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxml_tinyxmlerror$(DependSuffix): ../../src/utils/tinyxml/tinyxmlerror.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxml_tinyxmlerror$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxml_tinyxmlerror$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxmlerror.cpp"

$(IntermediateDirectory)/tinyxml_tinyxmlerror$(PreprocessSuffix): ../../src/utils/tinyxml/tinyxmlerror.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tinyxml_tinyxmlerror$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxmlerror.cpp"

$(IntermediateDirectory)/tinyxml_tinyxmlparser$(ObjectSuffix): ../../src/utils/tinyxml/tinyxmlparser.cpp $(IntermediateDirectory)/tinyxml_tinyxmlparser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxmlparser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/tinyxml_tinyxmlparser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tinyxml_tinyxmlparser$(DependSuffix): ../../src/utils/tinyxml/tinyxmlparser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/tinyxml_tinyxmlparser$(ObjectSuffix) -MF$(IntermediateDirectory)/tinyxml_tinyxmlparser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxmlparser.cpp"

$(IntermediateDirectory)/tinyxml_tinyxmlparser$(PreprocessSuffix): ../../src/utils/tinyxml/tinyxmlparser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tinyxml_tinyxmlparser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/tinyxml/tinyxmlparser.cpp"

$(IntermediateDirectory)/uuid_clear$(ObjectSuffix): ../../src/utils/uuid/clear.c $(IntermediateDirectory)/uuid_clear$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/clear.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_clear$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_clear$(DependSuffix): ../../src/utils/uuid/clear.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_clear$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_clear$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/clear.c"

$(IntermediateDirectory)/uuid_clear$(PreprocessSuffix): ../../src/utils/uuid/clear.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_clear$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/clear.c"

$(IntermediateDirectory)/uuid_compare$(ObjectSuffix): ../../src/utils/uuid/compare.c $(IntermediateDirectory)/uuid_compare$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/compare.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_compare$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_compare$(DependSuffix): ../../src/utils/uuid/compare.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_compare$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_compare$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/compare.c"

$(IntermediateDirectory)/uuid_compare$(PreprocessSuffix): ../../src/utils/uuid/compare.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_compare$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/compare.c"

$(IntermediateDirectory)/uuid_copy$(ObjectSuffix): ../../src/utils/uuid/copy.c $(IntermediateDirectory)/uuid_copy$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/copy.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_copy$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_copy$(DependSuffix): ../../src/utils/uuid/copy.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_copy$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_copy$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/copy.c"

$(IntermediateDirectory)/uuid_copy$(PreprocessSuffix): ../../src/utils/uuid/copy.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_copy$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/copy.c"

$(IntermediateDirectory)/uuid_gen_uuid$(ObjectSuffix): ../../src/utils/uuid/gen_uuid.c $(IntermediateDirectory)/uuid_gen_uuid$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/gen_uuid.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_gen_uuid$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_gen_uuid$(DependSuffix): ../../src/utils/uuid/gen_uuid.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_gen_uuid$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_gen_uuid$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/gen_uuid.c"

$(IntermediateDirectory)/uuid_gen_uuid$(PreprocessSuffix): ../../src/utils/uuid/gen_uuid.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_gen_uuid$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/gen_uuid.c"

$(IntermediateDirectory)/uuid_isnull$(ObjectSuffix): ../../src/utils/uuid/isnull.c $(IntermediateDirectory)/uuid_isnull$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/isnull.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_isnull$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_isnull$(DependSuffix): ../../src/utils/uuid/isnull.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_isnull$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_isnull$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/isnull.c"

$(IntermediateDirectory)/uuid_isnull$(PreprocessSuffix): ../../src/utils/uuid/isnull.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_isnull$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/isnull.c"

$(IntermediateDirectory)/uuid_pack$(ObjectSuffix): ../../src/utils/uuid/pack.c $(IntermediateDirectory)/uuid_pack$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/pack.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_pack$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_pack$(DependSuffix): ../../src/utils/uuid/pack.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_pack$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_pack$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/pack.c"

$(IntermediateDirectory)/uuid_pack$(PreprocessSuffix): ../../src/utils/uuid/pack.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_pack$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/pack.c"

$(IntermediateDirectory)/uuid_parse$(ObjectSuffix): ../../src/utils/uuid/parse.c $(IntermediateDirectory)/uuid_parse$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/parse.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_parse$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_parse$(DependSuffix): ../../src/utils/uuid/parse.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_parse$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_parse$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/parse.c"

$(IntermediateDirectory)/uuid_parse$(PreprocessSuffix): ../../src/utils/uuid/parse.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_parse$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/parse.c"

$(IntermediateDirectory)/uuid_unpack$(ObjectSuffix): ../../src/utils/uuid/unpack.c $(IntermediateDirectory)/uuid_unpack$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/unpack.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_unpack$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_unpack$(DependSuffix): ../../src/utils/uuid/unpack.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_unpack$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_unpack$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/unpack.c"

$(IntermediateDirectory)/uuid_unpack$(PreprocessSuffix): ../../src/utils/uuid/unpack.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_unpack$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/unpack.c"

$(IntermediateDirectory)/uuid_unparse$(ObjectSuffix): ../../src/utils/uuid/unparse.c $(IntermediateDirectory)/uuid_unparse$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/unparse.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_unparse$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_unparse$(DependSuffix): ../../src/utils/uuid/unparse.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_unparse$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_unparse$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/unparse.c"

$(IntermediateDirectory)/uuid_unparse$(PreprocessSuffix): ../../src/utils/uuid/unparse.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_unparse$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/unparse.c"

$(IntermediateDirectory)/uuid_uuid_time$(ObjectSuffix): ../../src/utils/uuid/uuid_time.c $(IntermediateDirectory)/uuid_uuid_time$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/uuid_time.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/uuid_uuid_time$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/uuid_uuid_time$(DependSuffix): ../../src/utils/uuid/uuid_time.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/uuid_uuid_time$(ObjectSuffix) -MF$(IntermediateDirectory)/uuid_uuid_time$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/uuid_time.c"

$(IntermediateDirectory)/uuid_uuid_time$(PreprocessSuffix): ../../src/utils/uuid/uuid_time.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/uuid_uuid_time$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/uuid/uuid_time.c"

$(IntermediateDirectory)/g722_1_G722_1_1C_Float$(ObjectSuffix): ../../src/utils/g722_1/G722_1_1C_Float.c $(IntermediateDirectory)/g722_1_G722_1_1C_Float$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/g722_1/G722_1_1C_Float.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/g722_1_G722_1_1C_Float$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/g722_1_G722_1_1C_Float$(DependSuffix): ../../src/utils/g722_1/G722_1_1C_Float.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/g722_1_G722_1_1C_Float$(ObjectSuffix) -MF$(IntermediateDirectory)/g722_1_G722_1_1C_Float$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/g722_1/G722_1_1C_Float.c"

$(IntermediateDirectory)/g722_1_G722_1_1C_Float$(PreprocessSuffix): ../../src/utils/g722_1/G722_1_1C_Float.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/g722_1_G722_1_1C_Float$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/g722_1/G722_1_1C_Float.c"

$(IntermediateDirectory)/json_c_arraylist$(ObjectSuffix): ../../src/utils/json_c/arraylist.c $(IntermediateDirectory)/json_c_arraylist$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/arraylist.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_arraylist$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_arraylist$(DependSuffix): ../../src/utils/json_c/arraylist.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_arraylist$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_arraylist$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/arraylist.c"

$(IntermediateDirectory)/json_c_arraylist$(PreprocessSuffix): ../../src/utils/json_c/arraylist.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_arraylist$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/arraylist.c"

$(IntermediateDirectory)/json_c_debug$(ObjectSuffix): ../../src/utils/json_c/debug.c $(IntermediateDirectory)/json_c_debug$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/debug.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_debug$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_debug$(DependSuffix): ../../src/utils/json_c/debug.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_debug$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_debug$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/debug.c"

$(IntermediateDirectory)/json_c_debug$(PreprocessSuffix): ../../src/utils/json_c/debug.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_debug$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/debug.c"

$(IntermediateDirectory)/json_c_json_object$(ObjectSuffix): ../../src/utils/json_c/json_object.c $(IntermediateDirectory)/json_c_json_object$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_object.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_json_object$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_json_object$(DependSuffix): ../../src/utils/json_c/json_object.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_json_object$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_json_object$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_object.c"

$(IntermediateDirectory)/json_c_json_object$(PreprocessSuffix): ../../src/utils/json_c/json_object.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_json_object$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_object.c"

$(IntermediateDirectory)/json_c_json_tokener$(ObjectSuffix): ../../src/utils/json_c/json_tokener.c $(IntermediateDirectory)/json_c_json_tokener$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_tokener.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_json_tokener$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_json_tokener$(DependSuffix): ../../src/utils/json_c/json_tokener.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_json_tokener$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_json_tokener$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_tokener.c"

$(IntermediateDirectory)/json_c_json_tokener$(PreprocessSuffix): ../../src/utils/json_c/json_tokener.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_json_tokener$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_tokener.c"

$(IntermediateDirectory)/json_c_json_util$(ObjectSuffix): ../../src/utils/json_c/json_util.c $(IntermediateDirectory)/json_c_json_util$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_util.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_json_util$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_json_util$(DependSuffix): ../../src/utils/json_c/json_util.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_json_util$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_json_util$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_util.c"

$(IntermediateDirectory)/json_c_json_util$(PreprocessSuffix): ../../src/utils/json_c/json_util.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_json_util$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/json_util.c"

$(IntermediateDirectory)/json_c_linkhash$(ObjectSuffix): ../../src/utils/json_c/linkhash.c $(IntermediateDirectory)/json_c_linkhash$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/linkhash.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_linkhash$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_linkhash$(DependSuffix): ../../src/utils/json_c/linkhash.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_linkhash$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_linkhash$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/linkhash.c"

$(IntermediateDirectory)/json_c_linkhash$(PreprocessSuffix): ../../src/utils/json_c/linkhash.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_linkhash$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/linkhash.c"

$(IntermediateDirectory)/json_c_printbuf$(ObjectSuffix): ../../src/utils/json_c/printbuf.c $(IntermediateDirectory)/json_c_printbuf$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/printbuf.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/json_c_printbuf$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/json_c_printbuf$(DependSuffix): ../../src/utils/json_c/printbuf.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/json_c_printbuf$(ObjectSuffix) -MF$(IntermediateDirectory)/json_c_printbuf$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/printbuf.c"

$(IntermediateDirectory)/json_c_printbuf$(PreprocessSuffix): ../../src/utils/json_c/printbuf.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/json_c_printbuf$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/json_c/printbuf.c"

$(IntermediateDirectory)/sqlite3_shell$(ObjectSuffix): ../../src/utils/sqlite3/shell.c $(IntermediateDirectory)/sqlite3_shell$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/sqlite3/shell.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sqlite3_shell$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sqlite3_shell$(DependSuffix): ../../src/utils/sqlite3/shell.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sqlite3_shell$(ObjectSuffix) -MF$(IntermediateDirectory)/sqlite3_shell$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/sqlite3/shell.c"

$(IntermediateDirectory)/sqlite3_shell$(PreprocessSuffix): ../../src/utils/sqlite3/shell.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sqlite3_shell$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/sqlite3/shell.c"

$(IntermediateDirectory)/sqlite3_sqlite3$(ObjectSuffix): ../../src/utils/sqlite3/sqlite3.c $(IntermediateDirectory)/sqlite3_sqlite3$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/sqlite3/sqlite3.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sqlite3_sqlite3$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sqlite3_sqlite3$(DependSuffix): ../../src/utils/sqlite3/sqlite3.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sqlite3_sqlite3$(ObjectSuffix) -MF$(IntermediateDirectory)/sqlite3_sqlite3$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/sqlite3/sqlite3.c"

$(IntermediateDirectory)/sqlite3_sqlite3$(PreprocessSuffix): ../../src/utils/sqlite3/sqlite3.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sqlite3_sqlite3$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/sqlite3/sqlite3.c"

$(IntermediateDirectory)/ghttp_ghttp$(ObjectSuffix): ../../src/utils/ghttp/ghttp.c $(IntermediateDirectory)/ghttp_ghttp$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/ghttp.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_ghttp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_ghttp$(DependSuffix): ../../src/utils/ghttp/ghttp.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_ghttp$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_ghttp$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/ghttp.c"

$(IntermediateDirectory)/ghttp_ghttp$(PreprocessSuffix): ../../src/utils/ghttp/ghttp.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_ghttp$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/ghttp.c"

$(IntermediateDirectory)/ghttp_http_base64$(ObjectSuffix): ../../src/utils/ghttp/http_base64.c $(IntermediateDirectory)/ghttp_http_base64$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_base64.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_base64$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_base64$(DependSuffix): ../../src/utils/ghttp/http_base64.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_base64$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_base64$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_base64.c"

$(IntermediateDirectory)/ghttp_http_base64$(PreprocessSuffix): ../../src/utils/ghttp/http_base64.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_base64$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_base64.c"

$(IntermediateDirectory)/ghttp_http_date$(ObjectSuffix): ../../src/utils/ghttp/http_date.c $(IntermediateDirectory)/ghttp_http_date$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_date.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_date$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_date$(DependSuffix): ../../src/utils/ghttp/http_date.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_date$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_date$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_date.c"

$(IntermediateDirectory)/ghttp_http_date$(PreprocessSuffix): ../../src/utils/ghttp/http_date.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_date$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_date.c"

$(IntermediateDirectory)/ghttp_http_hdrs$(ObjectSuffix): ../../src/utils/ghttp/http_hdrs.c $(IntermediateDirectory)/ghttp_http_hdrs$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_hdrs.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_hdrs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_hdrs$(DependSuffix): ../../src/utils/ghttp/http_hdrs.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_hdrs$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_hdrs$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_hdrs.c"

$(IntermediateDirectory)/ghttp_http_hdrs$(PreprocessSuffix): ../../src/utils/ghttp/http_hdrs.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_hdrs$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_hdrs.c"

$(IntermediateDirectory)/ghttp_http_req$(ObjectSuffix): ../../src/utils/ghttp/http_req.c $(IntermediateDirectory)/ghttp_http_req$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_req.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_req$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_req$(DependSuffix): ../../src/utils/ghttp/http_req.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_req$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_req$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_req.c"

$(IntermediateDirectory)/ghttp_http_req$(PreprocessSuffix): ../../src/utils/ghttp/http_req.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_req$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_req.c"

$(IntermediateDirectory)/ghttp_http_resp$(ObjectSuffix): ../../src/utils/ghttp/http_resp.c $(IntermediateDirectory)/ghttp_http_resp$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_resp.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_resp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_resp$(DependSuffix): ../../src/utils/ghttp/http_resp.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_resp$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_resp$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_resp.c"

$(IntermediateDirectory)/ghttp_http_resp$(PreprocessSuffix): ../../src/utils/ghttp/http_resp.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_resp$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_resp.c"

$(IntermediateDirectory)/ghttp_http_trans$(ObjectSuffix): ../../src/utils/ghttp/http_trans.c $(IntermediateDirectory)/ghttp_http_trans$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_trans.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_trans$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_trans$(DependSuffix): ../../src/utils/ghttp/http_trans.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_trans$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_trans$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_trans.c"

$(IntermediateDirectory)/ghttp_http_trans$(PreprocessSuffix): ../../src/utils/ghttp/http_trans.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_trans$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_trans.c"

$(IntermediateDirectory)/ghttp_http_uri$(ObjectSuffix): ../../src/utils/ghttp/http_uri.c $(IntermediateDirectory)/ghttp_http_uri$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_uri.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ghttp_http_uri$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ghttp_http_uri$(DependSuffix): ../../src/utils/ghttp/http_uri.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ghttp_http_uri$(ObjectSuffix) -MF$(IntermediateDirectory)/ghttp_http_uri$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_uri.c"

$(IntermediateDirectory)/ghttp_http_uri$(PreprocessSuffix): ../../src/utils/ghttp/http_uri.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ghttp_http_uri$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/utils/ghttp/http_uri.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/common_x_base64$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/common_x_base64$(DependSuffix)
	$(RM) $(IntermediateDirectory)/common_x_base64$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/common_x_crc32$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/common_x_crc32$(DependSuffix)
	$(RM) $(IntermediateDirectory)/common_x_crc32$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/common_x_md5$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/common_x_md5$(DependSuffix)
	$(RM) $(IntermediateDirectory)/common_x_md5$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/common_x_sha1$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/common_x_sha1$(DependSuffix)
	$(RM) $(IntermediateDirectory)/common_x_sha1$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_aacquant$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_aacquant$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_aacquant$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_backpred$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_backpred$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_backpred$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_bitstream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_bitstream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_bitstream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_channels$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_channels$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_channels$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_fft$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_fft$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_fft$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_filtbank$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_filtbank$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_filtbank$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_frame$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_frame$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_frame$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_huffman$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_huffman$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_huffman$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_ltp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_ltp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_ltp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_midside$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_midside$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_midside$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_psychkni$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_psychkni$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_psychkni$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_tns$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_tns$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_tns$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/faac_util$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/faac_util$(DependSuffix)
	$(RM) $(IntermediateDirectory)/faac_util$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinystr$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinystr$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinystr$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxml$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxml$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxml$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxmlerror$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxmlerror$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxmlerror$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxmlparser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxmlparser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/tinyxml_tinyxmlparser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_clear$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_clear$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_clear$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_compare$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_compare$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_compare$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_copy$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_copy$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_copy$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_gen_uuid$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_gen_uuid$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_gen_uuid$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_isnull$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_isnull$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_isnull$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_pack$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_pack$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_pack$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_parse$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_parse$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_parse$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_unpack$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_unpack$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_unpack$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_unparse$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_unparse$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_unparse$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/uuid_uuid_time$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/uuid_uuid_time$(DependSuffix)
	$(RM) $(IntermediateDirectory)/uuid_uuid_time$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/g722_1_G722_1_1C_Float$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/g722_1_G722_1_1C_Float$(DependSuffix)
	$(RM) $(IntermediateDirectory)/g722_1_G722_1_1C_Float$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_arraylist$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_arraylist$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_arraylist$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_debug$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_debug$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_debug$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_object$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_object$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_object$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_tokener$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_tokener$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_tokener$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_util$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_util$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_json_util$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_linkhash$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_linkhash$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_linkhash$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/json_c_printbuf$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/json_c_printbuf$(DependSuffix)
	$(RM) $(IntermediateDirectory)/json_c_printbuf$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3_shell$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3_shell$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3_shell$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3_sqlite3$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3_sqlite3$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sqlite3_sqlite3$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_ghttp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_ghttp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_ghttp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_base64$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_base64$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_base64$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_date$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_date$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_date$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_hdrs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_hdrs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_hdrs$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_req$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_req$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_req$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_resp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_resp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_resp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_trans$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_trans$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_trans$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_uri$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_uri$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ghttp_http_uri$(PreprocessSuffix)
	$(RM) $(OutputFile)


