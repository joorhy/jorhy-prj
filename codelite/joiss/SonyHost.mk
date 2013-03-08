##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SonyHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/host/sony" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/sony_SonyAdapter$(ObjectSuffix) $(IntermediateDirectory)/sony_SonyChannel$(ObjectSuffix) $(IntermediateDirectory)/sony_SonyParser$(ObjectSuffix) $(IntermediateDirectory)/sony_SonyStream$(ObjectSuffix) 

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
$(IntermediateDirectory)/sony_SonyAdapter$(ObjectSuffix): ../../src/host/sony/SonyAdapter.cpp $(IntermediateDirectory)/sony_SonyAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sony_SonyAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sony_SonyAdapter$(DependSuffix): ../../src/host/sony/SonyAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sony_SonyAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/sony_SonyAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyAdapter.cpp"

$(IntermediateDirectory)/sony_SonyAdapter$(PreprocessSuffix): ../../src/host/sony/SonyAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sony_SonyAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyAdapter.cpp"

$(IntermediateDirectory)/sony_SonyChannel$(ObjectSuffix): ../../src/host/sony/SonyChannel.cpp $(IntermediateDirectory)/sony_SonyChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sony_SonyChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sony_SonyChannel$(DependSuffix): ../../src/host/sony/SonyChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sony_SonyChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/sony_SonyChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyChannel.cpp"

$(IntermediateDirectory)/sony_SonyChannel$(PreprocessSuffix): ../../src/host/sony/SonyChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sony_SonyChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyChannel.cpp"

$(IntermediateDirectory)/sony_SonyParser$(ObjectSuffix): ../../src/host/sony/SonyParser.cpp $(IntermediateDirectory)/sony_SonyParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sony_SonyParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sony_SonyParser$(DependSuffix): ../../src/host/sony/SonyParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sony_SonyParser$(ObjectSuffix) -MF$(IntermediateDirectory)/sony_SonyParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyParser.cpp"

$(IntermediateDirectory)/sony_SonyParser$(PreprocessSuffix): ../../src/host/sony/SonyParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sony_SonyParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyParser.cpp"

$(IntermediateDirectory)/sony_SonyStream$(ObjectSuffix): ../../src/host/sony/SonyStream.cpp $(IntermediateDirectory)/sony_SonyStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/sony_SonyStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/sony_SonyStream$(DependSuffix): ../../src/host/sony/SonyStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/sony_SonyStream$(ObjectSuffix) -MF$(IntermediateDirectory)/sony_SonyStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyStream.cpp"

$(IntermediateDirectory)/sony_SonyStream$(PreprocessSuffix): ../../src/host/sony/SonyStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/sony_SonyStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/sony/SonyStream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/sony_SonyAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/sony_SonyStream$(PreprocessSuffix)
	$(RM) $(OutputFile)


