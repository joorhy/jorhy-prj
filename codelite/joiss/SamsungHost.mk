##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SamsungHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/22/2013
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/host/samsung" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/samsung_SamsungAdapter$(ObjectSuffix) $(IntermediateDirectory)/samsung_SamsungChannel$(ObjectSuffix) $(IntermediateDirectory)/samsung_SamsungParser$(ObjectSuffix) $(IntermediateDirectory)/samsung_SamsungStream$(ObjectSuffix) 

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
$(IntermediateDirectory)/samsung_SamsungAdapter$(ObjectSuffix): ../../src/host/samsung/SamsungAdapter.cpp $(IntermediateDirectory)/samsung_SamsungAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/samsung_SamsungAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/samsung_SamsungAdapter$(DependSuffix): ../../src/host/samsung/SamsungAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/samsung_SamsungAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/samsung_SamsungAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungAdapter.cpp"

$(IntermediateDirectory)/samsung_SamsungAdapter$(PreprocessSuffix): ../../src/host/samsung/SamsungAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/samsung_SamsungAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungAdapter.cpp"

$(IntermediateDirectory)/samsung_SamsungChannel$(ObjectSuffix): ../../src/host/samsung/SamsungChannel.cpp $(IntermediateDirectory)/samsung_SamsungChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/samsung_SamsungChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/samsung_SamsungChannel$(DependSuffix): ../../src/host/samsung/SamsungChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/samsung_SamsungChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/samsung_SamsungChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungChannel.cpp"

$(IntermediateDirectory)/samsung_SamsungChannel$(PreprocessSuffix): ../../src/host/samsung/SamsungChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/samsung_SamsungChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungChannel.cpp"

$(IntermediateDirectory)/samsung_SamsungParser$(ObjectSuffix): ../../src/host/samsung/SamsungParser.cpp $(IntermediateDirectory)/samsung_SamsungParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/samsung_SamsungParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/samsung_SamsungParser$(DependSuffix): ../../src/host/samsung/SamsungParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/samsung_SamsungParser$(ObjectSuffix) -MF$(IntermediateDirectory)/samsung_SamsungParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungParser.cpp"

$(IntermediateDirectory)/samsung_SamsungParser$(PreprocessSuffix): ../../src/host/samsung/SamsungParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/samsung_SamsungParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungParser.cpp"

$(IntermediateDirectory)/samsung_SamsungStream$(ObjectSuffix): ../../src/host/samsung/SamsungStream.cpp $(IntermediateDirectory)/samsung_SamsungStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/samsung_SamsungStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/samsung_SamsungStream$(DependSuffix): ../../src/host/samsung/SamsungStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/samsung_SamsungStream$(ObjectSuffix) -MF$(IntermediateDirectory)/samsung_SamsungStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungStream.cpp"

$(IntermediateDirectory)/samsung_SamsungStream$(PreprocessSuffix): ../../src/host/samsung/SamsungStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/samsung_SamsungStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/samsung/SamsungStream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/samsung_SamsungAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/samsung_SamsungStream$(PreprocessSuffix)
	$(RM) $(OutputFile)


