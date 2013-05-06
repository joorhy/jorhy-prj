##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JoissManager
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=04/19/2013
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
LinkOptions            :=  $(mysql_config --libs)
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/control/cms" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/control/stream" "$(IncludeSwitch)../../src/control/record" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)mysqlclient 
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/joiss_ControlManager$(ObjectSuffix) $(IntermediateDirectory)/joiss_JoissManager$(ObjectSuffix) $(IntermediateDirectory)/joiss_MCManager$(ObjectSuffix) 

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
$(IntermediateDirectory)/joiss_ControlManager$(ObjectSuffix): ../../src/control/joiss/ControlManager.cpp $(IntermediateDirectory)/joiss_ControlManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/ControlManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/joiss_ControlManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/joiss_ControlManager$(DependSuffix): ../../src/control/joiss/ControlManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/joiss_ControlManager$(ObjectSuffix) -MF$(IntermediateDirectory)/joiss_ControlManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/ControlManager.cpp"

$(IntermediateDirectory)/joiss_ControlManager$(PreprocessSuffix): ../../src/control/joiss/ControlManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/joiss_ControlManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/ControlManager.cpp"

$(IntermediateDirectory)/joiss_JoissManager$(ObjectSuffix): ../../src/control/joiss/JoissManager.cpp $(IntermediateDirectory)/joiss_JoissManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/JoissManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/joiss_JoissManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/joiss_JoissManager$(DependSuffix): ../../src/control/joiss/JoissManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/joiss_JoissManager$(ObjectSuffix) -MF$(IntermediateDirectory)/joiss_JoissManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/JoissManager.cpp"

$(IntermediateDirectory)/joiss_JoissManager$(PreprocessSuffix): ../../src/control/joiss/JoissManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/joiss_JoissManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/JoissManager.cpp"

$(IntermediateDirectory)/joiss_MCManager$(ObjectSuffix): ../../src/control/joiss/MCManager.cpp $(IntermediateDirectory)/joiss_MCManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/MCManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/joiss_MCManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/joiss_MCManager$(DependSuffix): ../../src/control/joiss/MCManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/joiss_MCManager$(ObjectSuffix) -MF$(IntermediateDirectory)/joiss_MCManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/MCManager.cpp"

$(IntermediateDirectory)/joiss_MCManager$(PreprocessSuffix): ../../src/control/joiss/MCManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/joiss_MCManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/joiss/MCManager.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/joiss_ControlManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/joiss_ControlManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/joiss_ControlManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/joiss_JoissManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/joiss_JoissManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/joiss_JoissManager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/joiss_MCManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/joiss_MCManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/joiss_MCManager$(PreprocessSuffix)
	$(RM) $(OutputFile)


