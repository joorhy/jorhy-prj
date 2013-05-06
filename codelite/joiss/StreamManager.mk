##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=StreamManager
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=05/06/2013
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/control/stream" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/control/record" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/stream_DeviceControl$(ObjectSuffix) $(IntermediateDirectory)/stream_RealMediaObj$(ObjectSuffix) $(IntermediateDirectory)/stream_StreamManager$(ObjectSuffix) $(IntermediateDirectory)/stream_VodMediaObj$(ObjectSuffix) $(IntermediateDirectory)/stream_VoiceIcomObj$(ObjectSuffix) 

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
$(IntermediateDirectory)/stream_DeviceControl$(ObjectSuffix): ../../src/control/stream/DeviceControl.cpp $(IntermediateDirectory)/stream_DeviceControl$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/DeviceControl.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/stream_DeviceControl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stream_DeviceControl$(DependSuffix): ../../src/control/stream/DeviceControl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/stream_DeviceControl$(ObjectSuffix) -MF$(IntermediateDirectory)/stream_DeviceControl$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/DeviceControl.cpp"

$(IntermediateDirectory)/stream_DeviceControl$(PreprocessSuffix): ../../src/control/stream/DeviceControl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stream_DeviceControl$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/DeviceControl.cpp"

$(IntermediateDirectory)/stream_RealMediaObj$(ObjectSuffix): ../../src/control/stream/RealMediaObj.cpp $(IntermediateDirectory)/stream_RealMediaObj$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/RealMediaObj.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/stream_RealMediaObj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stream_RealMediaObj$(DependSuffix): ../../src/control/stream/RealMediaObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/stream_RealMediaObj$(ObjectSuffix) -MF$(IntermediateDirectory)/stream_RealMediaObj$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/RealMediaObj.cpp"

$(IntermediateDirectory)/stream_RealMediaObj$(PreprocessSuffix): ../../src/control/stream/RealMediaObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stream_RealMediaObj$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/RealMediaObj.cpp"

$(IntermediateDirectory)/stream_StreamManager$(ObjectSuffix): ../../src/control/stream/StreamManager.cpp $(IntermediateDirectory)/stream_StreamManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/StreamManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/stream_StreamManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stream_StreamManager$(DependSuffix): ../../src/control/stream/StreamManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/stream_StreamManager$(ObjectSuffix) -MF$(IntermediateDirectory)/stream_StreamManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/StreamManager.cpp"

$(IntermediateDirectory)/stream_StreamManager$(PreprocessSuffix): ../../src/control/stream/StreamManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stream_StreamManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/StreamManager.cpp"

$(IntermediateDirectory)/stream_VodMediaObj$(ObjectSuffix): ../../src/control/stream/VodMediaObj.cpp $(IntermediateDirectory)/stream_VodMediaObj$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/VodMediaObj.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/stream_VodMediaObj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stream_VodMediaObj$(DependSuffix): ../../src/control/stream/VodMediaObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/stream_VodMediaObj$(ObjectSuffix) -MF$(IntermediateDirectory)/stream_VodMediaObj$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/VodMediaObj.cpp"

$(IntermediateDirectory)/stream_VodMediaObj$(PreprocessSuffix): ../../src/control/stream/VodMediaObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stream_VodMediaObj$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/VodMediaObj.cpp"

$(IntermediateDirectory)/stream_VoiceIcomObj$(ObjectSuffix): ../../src/control/stream/VoiceIcomObj.cpp $(IntermediateDirectory)/stream_VoiceIcomObj$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/VoiceIcomObj.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/stream_VoiceIcomObj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stream_VoiceIcomObj$(DependSuffix): ../../src/control/stream/VoiceIcomObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/stream_VoiceIcomObj$(ObjectSuffix) -MF$(IntermediateDirectory)/stream_VoiceIcomObj$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/VoiceIcomObj.cpp"

$(IntermediateDirectory)/stream_VoiceIcomObj$(PreprocessSuffix): ../../src/control/stream/VoiceIcomObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stream_VoiceIcomObj$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/stream/VoiceIcomObj.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/stream_DeviceControl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stream_DeviceControl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stream_DeviceControl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/stream_RealMediaObj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stream_RealMediaObj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stream_RealMediaObj$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/stream_StreamManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stream_StreamManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stream_StreamManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/stream_VodMediaObj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stream_VodMediaObj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stream_VodMediaObj$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/stream_VoiceIcomObj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stream_VoiceIcomObj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stream_VoiceIcomObj$(PreprocessSuffix)
	$(RM) $(OutputFile)


