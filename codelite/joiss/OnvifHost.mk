##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=OnvifHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/06/2013
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/onvif_OnvifAdapter$(ObjectSuffix) $(IntermediateDirectory)/onvif_OnvifChannel$(ObjectSuffix) $(IntermediateDirectory)/onvif_OnvifParser$(ObjectSuffix) $(IntermediateDirectory)/onvif_OnvifStream$(ObjectSuffix) $(IntermediateDirectory)/onvif_RtspHelper$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug/plugins || $(MakeDirCommand) ./Debug/plugins

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/onvif_OnvifAdapter$(ObjectSuffix): ../../src/host/onvif/OnvifAdapter.cpp $(IntermediateDirectory)/onvif_OnvifAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/onvif_OnvifAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/onvif_OnvifAdapter$(DependSuffix): ../../src/host/onvif/OnvifAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/onvif_OnvifAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/onvif_OnvifAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifAdapter.cpp"

$(IntermediateDirectory)/onvif_OnvifAdapter$(PreprocessSuffix): ../../src/host/onvif/OnvifAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/onvif_OnvifAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifAdapter.cpp"

$(IntermediateDirectory)/onvif_OnvifChannel$(ObjectSuffix): ../../src/host/onvif/OnvifChannel.cpp $(IntermediateDirectory)/onvif_OnvifChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/onvif_OnvifChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/onvif_OnvifChannel$(DependSuffix): ../../src/host/onvif/OnvifChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/onvif_OnvifChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/onvif_OnvifChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifChannel.cpp"

$(IntermediateDirectory)/onvif_OnvifChannel$(PreprocessSuffix): ../../src/host/onvif/OnvifChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/onvif_OnvifChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifChannel.cpp"

$(IntermediateDirectory)/onvif_OnvifParser$(ObjectSuffix): ../../src/host/onvif/OnvifParser.cpp $(IntermediateDirectory)/onvif_OnvifParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/onvif_OnvifParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/onvif_OnvifParser$(DependSuffix): ../../src/host/onvif/OnvifParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/onvif_OnvifParser$(ObjectSuffix) -MF$(IntermediateDirectory)/onvif_OnvifParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifParser.cpp"

$(IntermediateDirectory)/onvif_OnvifParser$(PreprocessSuffix): ../../src/host/onvif/OnvifParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/onvif_OnvifParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifParser.cpp"

$(IntermediateDirectory)/onvif_OnvifStream$(ObjectSuffix): ../../src/host/onvif/OnvifStream.cpp $(IntermediateDirectory)/onvif_OnvifStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/onvif_OnvifStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/onvif_OnvifStream$(DependSuffix): ../../src/host/onvif/OnvifStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/onvif_OnvifStream$(ObjectSuffix) -MF$(IntermediateDirectory)/onvif_OnvifStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifStream.cpp"

$(IntermediateDirectory)/onvif_OnvifStream$(PreprocessSuffix): ../../src/host/onvif/OnvifStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/onvif_OnvifStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/OnvifStream.cpp"

$(IntermediateDirectory)/onvif_RtspHelper$(ObjectSuffix): ../../src/host/onvif/RtspHelper.cpp $(IntermediateDirectory)/onvif_RtspHelper$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/RtspHelper.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/onvif_RtspHelper$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/onvif_RtspHelper$(DependSuffix): ../../src/host/onvif/RtspHelper.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/onvif_RtspHelper$(ObjectSuffix) -MF$(IntermediateDirectory)/onvif_RtspHelper$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/RtspHelper.cpp"

$(IntermediateDirectory)/onvif_RtspHelper$(PreprocessSuffix): ../../src/host/onvif/RtspHelper.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/onvif_RtspHelper$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/onvif/RtspHelper.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/onvif_OnvifAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/onvif_OnvifStream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/onvif_RtspHelper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/onvif_RtspHelper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/onvif_RtspHelper$(PreprocessSuffix)
	$(RM) $(OutputFile)


