##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JoHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=05/06/2013
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
Objects=$(IntermediateDirectory)/jos_JoAdapter$(ObjectSuffix) $(IntermediateDirectory)/jos_JoChannel$(ObjectSuffix) $(IntermediateDirectory)/jos_JoStream$(ObjectSuffix) $(IntermediateDirectory)/jos_JospHelper$(ObjectSuffix) 

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
$(IntermediateDirectory)/jos_JoAdapter$(ObjectSuffix): ../../src/host/jos/JoAdapter.cpp $(IntermediateDirectory)/jos_JoAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jos_JoAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jos_JoAdapter$(DependSuffix): ../../src/host/jos/JoAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/jos_JoAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/jos_JoAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoAdapter.cpp"

$(IntermediateDirectory)/jos_JoAdapter$(PreprocessSuffix): ../../src/host/jos/JoAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jos_JoAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoAdapter.cpp"

$(IntermediateDirectory)/jos_JoChannel$(ObjectSuffix): ../../src/host/jos/JoChannel.cpp $(IntermediateDirectory)/jos_JoChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jos_JoChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jos_JoChannel$(DependSuffix): ../../src/host/jos/JoChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/jos_JoChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/jos_JoChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoChannel.cpp"

$(IntermediateDirectory)/jos_JoChannel$(PreprocessSuffix): ../../src/host/jos/JoChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jos_JoChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoChannel.cpp"

$(IntermediateDirectory)/jos_JoStream$(ObjectSuffix): ../../src/host/jos/JoStream.cpp $(IntermediateDirectory)/jos_JoStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jos_JoStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jos_JoStream$(DependSuffix): ../../src/host/jos/JoStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/jos_JoStream$(ObjectSuffix) -MF$(IntermediateDirectory)/jos_JoStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoStream.cpp"

$(IntermediateDirectory)/jos_JoStream$(PreprocessSuffix): ../../src/host/jos/JoStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jos_JoStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JoStream.cpp"

$(IntermediateDirectory)/jos_JospHelper$(ObjectSuffix): ../../src/host/jos/JospHelper.cpp $(IntermediateDirectory)/jos_JospHelper$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JospHelper.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/jos_JospHelper$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/jos_JospHelper$(DependSuffix): ../../src/host/jos/JospHelper.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/jos_JospHelper$(ObjectSuffix) -MF$(IntermediateDirectory)/jos_JospHelper$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JospHelper.cpp"

$(IntermediateDirectory)/jos_JospHelper$(PreprocessSuffix): ../../src/host/jos/JospHelper.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/jos_JospHelper$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/jos/JospHelper.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/jos_JoAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jos_JoStream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/jos_JospHelper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/jos_JospHelper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/jos_JospHelper$(PreprocessSuffix)
	$(RM) $(OutputFile)


