##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=misc
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/08/2013
CodeLitePath           :="/home/jorhy/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/misc_x_config$(ObjectSuffix) $(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix) $(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix) $(IntermediateDirectory)/misc_x_inet$(ObjectSuffix) $(IntermediateDirectory)/misc_x_adapter_factory$(ObjectSuffix) $(IntermediateDirectory)/misc_x_adapter_manager$(ObjectSuffix) $(IntermediateDirectory)/misc_x_filereader_factory$(ObjectSuffix) $(IntermediateDirectory)/misc_x_filterf_actory$(ObjectSuffix) $(IntermediateDirectory)/misc_x_manager_factory$(ObjectSuffix) $(IntermediateDirectory)/misc_x_mux_factory$(ObjectSuffix) \
	$(IntermediateDirectory)/misc_x_parser_factory$(ObjectSuffix) 

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
$(IntermediateDirectory)/misc_x_config$(ObjectSuffix): ../../src/misc/x_config.cpp $(IntermediateDirectory)/misc_x_config$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_config.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_config$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_config$(DependSuffix): ../../src/misc/x_config.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_config$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_config$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_config.cpp"

$(IntermediateDirectory)/misc_x_config$(PreprocessSuffix): ../../src/misc/x_config.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_config$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_config.cpp"

$(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix): ../../src/misc/x_http_helper.cpp $(IntermediateDirectory)/misc_x_http_helper$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_http_helper.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_http_helper$(DependSuffix): ../../src/misc/x_http_helper.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_http_helper$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_http_helper.cpp"

$(IntermediateDirectory)/misc_x_http_helper$(PreprocessSuffix): ../../src/misc/x_http_helper.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_http_helper$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_http_helper.cpp"

$(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix): ../../src/misc/x_sdk.cpp $(IntermediateDirectory)/misc_x_sdk$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_sdk.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_sdk$(DependSuffix): ../../src/misc/x_sdk.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_sdk$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_sdk.cpp"

$(IntermediateDirectory)/misc_x_sdk$(PreprocessSuffix): ../../src/misc/x_sdk.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_sdk$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_sdk.cpp"

$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix): ../../src/misc/x_inet.c $(IntermediateDirectory)/misc_x_inet$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_inet.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_inet$(DependSuffix): ../../src/misc/x_inet.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_inet$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_inet.c"

$(IntermediateDirectory)/misc_x_inet$(PreprocessSuffix): ../../src/misc/x_inet.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_inet$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_inet.c"

$(IntermediateDirectory)/misc_x_adapter_factory$(ObjectSuffix): ../../src/misc/x_adapter_factory.cpp $(IntermediateDirectory)/misc_x_adapter_factory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_adapter_factory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_adapter_factory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_adapter_factory$(DependSuffix): ../../src/misc/x_adapter_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_adapter_factory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_adapter_factory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_adapter_factory.cpp"

$(IntermediateDirectory)/misc_x_adapter_factory$(PreprocessSuffix): ../../src/misc/x_adapter_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_adapter_factory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_adapter_factory.cpp"

$(IntermediateDirectory)/misc_x_adapter_manager$(ObjectSuffix): ../../src/misc/x_adapter_manager.cpp $(IntermediateDirectory)/misc_x_adapter_manager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_adapter_manager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_adapter_manager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_adapter_manager$(DependSuffix): ../../src/misc/x_adapter_manager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_adapter_manager$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_adapter_manager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_adapter_manager.cpp"

$(IntermediateDirectory)/misc_x_adapter_manager$(PreprocessSuffix): ../../src/misc/x_adapter_manager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_adapter_manager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_adapter_manager.cpp"

$(IntermediateDirectory)/misc_x_filereader_factory$(ObjectSuffix): ../../src/misc/x_filereader_factory.cpp $(IntermediateDirectory)/misc_x_filereader_factory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_filereader_factory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_filereader_factory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_filereader_factory$(DependSuffix): ../../src/misc/x_filereader_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_filereader_factory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_filereader_factory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_filereader_factory.cpp"

$(IntermediateDirectory)/misc_x_filereader_factory$(PreprocessSuffix): ../../src/misc/x_filereader_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_filereader_factory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_filereader_factory.cpp"

$(IntermediateDirectory)/misc_x_filterf_actory$(ObjectSuffix): ../../src/misc/x_filterf_actory.cpp $(IntermediateDirectory)/misc_x_filterf_actory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_filterf_actory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_filterf_actory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_filterf_actory$(DependSuffix): ../../src/misc/x_filterf_actory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_filterf_actory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_filterf_actory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_filterf_actory.cpp"

$(IntermediateDirectory)/misc_x_filterf_actory$(PreprocessSuffix): ../../src/misc/x_filterf_actory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_filterf_actory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_filterf_actory.cpp"

$(IntermediateDirectory)/misc_x_manager_factory$(ObjectSuffix): ../../src/misc/x_manager_factory.cpp $(IntermediateDirectory)/misc_x_manager_factory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_manager_factory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_manager_factory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_manager_factory$(DependSuffix): ../../src/misc/x_manager_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_manager_factory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_manager_factory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_manager_factory.cpp"

$(IntermediateDirectory)/misc_x_manager_factory$(PreprocessSuffix): ../../src/misc/x_manager_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_manager_factory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_manager_factory.cpp"

$(IntermediateDirectory)/misc_x_mux_factory$(ObjectSuffix): ../../src/misc/x_mux_factory.cpp $(IntermediateDirectory)/misc_x_mux_factory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_mux_factory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_mux_factory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_mux_factory$(DependSuffix): ../../src/misc/x_mux_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_mux_factory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_mux_factory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_mux_factory.cpp"

$(IntermediateDirectory)/misc_x_mux_factory$(PreprocessSuffix): ../../src/misc/x_mux_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_mux_factory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_mux_factory.cpp"

$(IntermediateDirectory)/misc_x_parser_factory$(ObjectSuffix): ../../src/misc/x_parser_factory.cpp $(IntermediateDirectory)/misc_x_parser_factory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_parser_factory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_parser_factory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_parser_factory$(DependSuffix): ../../src/misc/x_parser_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_parser_factory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_parser_factory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_parser_factory.cpp"

$(IntermediateDirectory)/misc_x_parser_factory$(PreprocessSuffix): ../../src/misc/x_parser_factory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_parser_factory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_parser_factory.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/misc_x_config$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_config$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_config$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_http_helper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_http_helper$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_sdk$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_sdk$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_inet$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_inet$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_inet$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_adapter_factory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_adapter_factory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_adapter_factory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_adapter_manager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_adapter_manager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_adapter_manager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_filereader_factory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_filereader_factory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_filereader_factory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_filterf_actory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_filterf_actory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_filterf_actory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_manager_factory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_manager_factory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_manager_factory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_mux_factory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_mux_factory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_mux_factory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_parser_factory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_parser_factory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_parser_factory$(PreprocessSuffix)
	$(RM) $(OutputFile)


