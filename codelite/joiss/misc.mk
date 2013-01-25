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
Date                   :=01/24/2013
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
Objects=$(IntermediateDirectory)/misc_AdapterFactory$(ObjectSuffix) $(IntermediateDirectory)/misc_AdapterManager$(ObjectSuffix) $(IntermediateDirectory)/misc_FileReaderFactory$(ObjectSuffix) $(IntermediateDirectory)/misc_Filterfactory$(ObjectSuffix) $(IntermediateDirectory)/misc_ManagerFactory$(ObjectSuffix) $(IntermediateDirectory)/misc_MuxFactory$(ObjectSuffix) $(IntermediateDirectory)/misc_x_config$(ObjectSuffix) $(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix) $(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix) $(IntermediateDirectory)/misc_ParserFactory$(ObjectSuffix) \
	$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix) 

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
$(IntermediateDirectory)/misc_AdapterFactory$(ObjectSuffix): ../../src/misc/AdapterFactory.cpp $(IntermediateDirectory)/misc_AdapterFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/AdapterFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_AdapterFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_AdapterFactory$(DependSuffix): ../../src/misc/AdapterFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_AdapterFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_AdapterFactory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/AdapterFactory.cpp"

$(IntermediateDirectory)/misc_AdapterFactory$(PreprocessSuffix): ../../src/misc/AdapterFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_AdapterFactory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/AdapterFactory.cpp"

$(IntermediateDirectory)/misc_AdapterManager$(ObjectSuffix): ../../src/misc/AdapterManager.cpp $(IntermediateDirectory)/misc_AdapterManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/AdapterManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_AdapterManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_AdapterManager$(DependSuffix): ../../src/misc/AdapterManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_AdapterManager$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_AdapterManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/AdapterManager.cpp"

$(IntermediateDirectory)/misc_AdapterManager$(PreprocessSuffix): ../../src/misc/AdapterManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_AdapterManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/AdapterManager.cpp"

$(IntermediateDirectory)/misc_FileReaderFactory$(ObjectSuffix): ../../src/misc/FileReaderFactory.cpp $(IntermediateDirectory)/misc_FileReaderFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/FileReaderFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_FileReaderFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_FileReaderFactory$(DependSuffix): ../../src/misc/FileReaderFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_FileReaderFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_FileReaderFactory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/FileReaderFactory.cpp"

$(IntermediateDirectory)/misc_FileReaderFactory$(PreprocessSuffix): ../../src/misc/FileReaderFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_FileReaderFactory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/FileReaderFactory.cpp"

$(IntermediateDirectory)/misc_Filterfactory$(ObjectSuffix): ../../src/misc/Filterfactory.cpp $(IntermediateDirectory)/misc_Filterfactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/Filterfactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_Filterfactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_Filterfactory$(DependSuffix): ../../src/misc/Filterfactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_Filterfactory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_Filterfactory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/Filterfactory.cpp"

$(IntermediateDirectory)/misc_Filterfactory$(PreprocessSuffix): ../../src/misc/Filterfactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_Filterfactory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/Filterfactory.cpp"

$(IntermediateDirectory)/misc_ManagerFactory$(ObjectSuffix): ../../src/misc/ManagerFactory.cpp $(IntermediateDirectory)/misc_ManagerFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/ManagerFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_ManagerFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_ManagerFactory$(DependSuffix): ../../src/misc/ManagerFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_ManagerFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_ManagerFactory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/ManagerFactory.cpp"

$(IntermediateDirectory)/misc_ManagerFactory$(PreprocessSuffix): ../../src/misc/ManagerFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_ManagerFactory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/ManagerFactory.cpp"

$(IntermediateDirectory)/misc_MuxFactory$(ObjectSuffix): ../../src/misc/MuxFactory.cpp $(IntermediateDirectory)/misc_MuxFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/MuxFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_MuxFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_MuxFactory$(DependSuffix): ../../src/misc/MuxFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_MuxFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_MuxFactory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/MuxFactory.cpp"

$(IntermediateDirectory)/misc_MuxFactory$(PreprocessSuffix): ../../src/misc/MuxFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_MuxFactory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/MuxFactory.cpp"

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

$(IntermediateDirectory)/misc_ParserFactory$(ObjectSuffix): ../../src/misc/ParserFactory.cpp $(IntermediateDirectory)/misc_ParserFactory$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/ParserFactory.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_ParserFactory$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_ParserFactory$(DependSuffix): ../../src/misc/ParserFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_ParserFactory$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_ParserFactory$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/ParserFactory.cpp"

$(IntermediateDirectory)/misc_ParserFactory$(PreprocessSuffix): ../../src/misc/ParserFactory.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_ParserFactory$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/ParserFactory.cpp"

$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix): ../../src/misc/x_inet.c $(IntermediateDirectory)/misc_x_inet$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_inet.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/misc_x_inet$(DependSuffix): ../../src/misc/x_inet.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/misc_x_inet$(ObjectSuffix) -MF$(IntermediateDirectory)/misc_x_inet$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_inet.c"

$(IntermediateDirectory)/misc_x_inet$(PreprocessSuffix): ../../src/misc/x_inet.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/misc_x_inet$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/misc/x_inet.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/misc_AdapterFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_AdapterFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_AdapterFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_AdapterManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_AdapterManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_AdapterManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_FileReaderFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_FileReaderFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_FileReaderFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_Filterfactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_Filterfactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_Filterfactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_ManagerFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_ManagerFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_ManagerFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_MuxFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_MuxFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_MuxFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_config$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_config$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_config$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_http_helper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_http_helper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_http_helper$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_sdk$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_sdk$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_sdk$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_ParserFactory$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_ParserFactory$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_ParserFactory$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_inet$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_inet$(DependSuffix)
	$(RM) $(IntermediateDirectory)/misc_x_inet$(PreprocessSuffix)
	$(RM) $(OutputFile)


