##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=RecordManager
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/27/2013
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/control/record" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/record_RecoderManager$(ObjectSuffix) $(IntermediateDirectory)/record_RecordMediaObj$(ObjectSuffix) 

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
$(IntermediateDirectory)/record_RecoderManager$(ObjectSuffix): ../../src/control/record/RecoderManager.cpp $(IntermediateDirectory)/record_RecoderManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/record/RecoderManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/record_RecoderManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/record_RecoderManager$(DependSuffix): ../../src/control/record/RecoderManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/record_RecoderManager$(ObjectSuffix) -MF$(IntermediateDirectory)/record_RecoderManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/record/RecoderManager.cpp"

$(IntermediateDirectory)/record_RecoderManager$(PreprocessSuffix): ../../src/control/record/RecoderManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/record_RecoderManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/record/RecoderManager.cpp"

$(IntermediateDirectory)/record_RecordMediaObj$(ObjectSuffix): ../../src/control/record/RecordMediaObj.cpp $(IntermediateDirectory)/record_RecordMediaObj$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/record/RecordMediaObj.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/record_RecordMediaObj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/record_RecordMediaObj$(DependSuffix): ../../src/control/record/RecordMediaObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/record_RecordMediaObj$(ObjectSuffix) -MF$(IntermediateDirectory)/record_RecordMediaObj$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/record/RecordMediaObj.cpp"

$(IntermediateDirectory)/record_RecordMediaObj$(PreprocessSuffix): ../../src/control/record/RecordMediaObj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/record_RecordMediaObj$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/record/RecordMediaObj.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/record_RecoderManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/record_RecoderManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/record_RecoderManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/record_RecordMediaObj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/record_RecordMediaObj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/record_RecordMediaObj$(PreprocessSuffix)
	$(RM) $(OutputFile)


