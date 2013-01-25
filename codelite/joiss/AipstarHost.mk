##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=AipstarHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=01/23/2013
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
LinkOptions            :=  -Wl,-rpath,./plugins/libs
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/host/aipstar" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)tmControlClient 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)../../libs/aipstar" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/aipstar_AipstarAdapter$(ObjectSuffix) $(IntermediateDirectory)/aipstar_AipstarChannel$(ObjectSuffix) $(IntermediateDirectory)/aipstar_AipstarParser$(ObjectSuffix) $(IntermediateDirectory)/aipstar_AipstarStream$(ObjectSuffix) 

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
$(IntermediateDirectory)/aipstar_AipstarAdapter$(ObjectSuffix): ../../src/host/aipstar/AipstarAdapter.cpp $(IntermediateDirectory)/aipstar_AipstarAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aipstar_AipstarAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aipstar_AipstarAdapter$(DependSuffix): ../../src/host/aipstar/AipstarAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aipstar_AipstarAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/aipstar_AipstarAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarAdapter.cpp"

$(IntermediateDirectory)/aipstar_AipstarAdapter$(PreprocessSuffix): ../../src/host/aipstar/AipstarAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aipstar_AipstarAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarAdapter.cpp"

$(IntermediateDirectory)/aipstar_AipstarChannel$(ObjectSuffix): ../../src/host/aipstar/AipstarChannel.cpp $(IntermediateDirectory)/aipstar_AipstarChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aipstar_AipstarChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aipstar_AipstarChannel$(DependSuffix): ../../src/host/aipstar/AipstarChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aipstar_AipstarChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/aipstar_AipstarChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarChannel.cpp"

$(IntermediateDirectory)/aipstar_AipstarChannel$(PreprocessSuffix): ../../src/host/aipstar/AipstarChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aipstar_AipstarChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarChannel.cpp"

$(IntermediateDirectory)/aipstar_AipstarParser$(ObjectSuffix): ../../src/host/aipstar/AipstarParser.cpp $(IntermediateDirectory)/aipstar_AipstarParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aipstar_AipstarParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aipstar_AipstarParser$(DependSuffix): ../../src/host/aipstar/AipstarParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aipstar_AipstarParser$(ObjectSuffix) -MF$(IntermediateDirectory)/aipstar_AipstarParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarParser.cpp"

$(IntermediateDirectory)/aipstar_AipstarParser$(PreprocessSuffix): ../../src/host/aipstar/AipstarParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aipstar_AipstarParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarParser.cpp"

$(IntermediateDirectory)/aipstar_AipstarStream$(ObjectSuffix): ../../src/host/aipstar/AipstarStream.cpp $(IntermediateDirectory)/aipstar_AipstarStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aipstar_AipstarStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aipstar_AipstarStream$(DependSuffix): ../../src/host/aipstar/AipstarStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aipstar_AipstarStream$(ObjectSuffix) -MF$(IntermediateDirectory)/aipstar_AipstarStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarStream.cpp"

$(IntermediateDirectory)/aipstar_AipstarStream$(PreprocessSuffix): ../../src/host/aipstar/AipstarStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aipstar_AipstarStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aipstar/AipstarStream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/aipstar_AipstarAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aipstar_AipstarStream$(PreprocessSuffix)
	$(RM) $(OutputFile)


