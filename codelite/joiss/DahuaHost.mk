##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=DahuaHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/20/2013
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
LinkOptions            :=  -Wl,-rpath,./plugins/libs
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/host/dahua" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)dhnetsdk $(LibrarySwitch)dhparser 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)../../libs/dahua" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/dahua_DahuaAdapter$(ObjectSuffix) $(IntermediateDirectory)/dahua_DahuaChannel$(ObjectSuffix) $(IntermediateDirectory)/dahua_DahuaParser$(ObjectSuffix) $(IntermediateDirectory)/dahua_DahuaStream$(ObjectSuffix) 

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
$(IntermediateDirectory)/dahua_DahuaAdapter$(ObjectSuffix): ../../src/host/dahua/DahuaAdapter.cpp $(IntermediateDirectory)/dahua_DahuaAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dahua_DahuaAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dahua_DahuaAdapter$(DependSuffix): ../../src/host/dahua/DahuaAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dahua_DahuaAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/dahua_DahuaAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaAdapter.cpp"

$(IntermediateDirectory)/dahua_DahuaAdapter$(PreprocessSuffix): ../../src/host/dahua/DahuaAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dahua_DahuaAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaAdapter.cpp"

$(IntermediateDirectory)/dahua_DahuaChannel$(ObjectSuffix): ../../src/host/dahua/DahuaChannel.cpp $(IntermediateDirectory)/dahua_DahuaChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dahua_DahuaChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dahua_DahuaChannel$(DependSuffix): ../../src/host/dahua/DahuaChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dahua_DahuaChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/dahua_DahuaChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaChannel.cpp"

$(IntermediateDirectory)/dahua_DahuaChannel$(PreprocessSuffix): ../../src/host/dahua/DahuaChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dahua_DahuaChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaChannel.cpp"

$(IntermediateDirectory)/dahua_DahuaParser$(ObjectSuffix): ../../src/host/dahua/DahuaParser.cpp $(IntermediateDirectory)/dahua_DahuaParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dahua_DahuaParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dahua_DahuaParser$(DependSuffix): ../../src/host/dahua/DahuaParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dahua_DahuaParser$(ObjectSuffix) -MF$(IntermediateDirectory)/dahua_DahuaParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaParser.cpp"

$(IntermediateDirectory)/dahua_DahuaParser$(PreprocessSuffix): ../../src/host/dahua/DahuaParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dahua_DahuaParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaParser.cpp"

$(IntermediateDirectory)/dahua_DahuaStream$(ObjectSuffix): ../../src/host/dahua/DahuaStream.cpp $(IntermediateDirectory)/dahua_DahuaStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dahua_DahuaStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dahua_DahuaStream$(DependSuffix): ../../src/host/dahua/DahuaStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dahua_DahuaStream$(ObjectSuffix) -MF$(IntermediateDirectory)/dahua_DahuaStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaStream.cpp"

$(IntermediateDirectory)/dahua_DahuaStream$(PreprocessSuffix): ../../src/host/dahua/DahuaStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dahua_DahuaStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/dahua/DahuaStream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/dahua_DahuaAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dahua_DahuaStream$(PreprocessSuffix)
	$(RM) $(OutputFile)


