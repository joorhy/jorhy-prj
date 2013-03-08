##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=LocalConfig
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/config/local" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/control/stream" "$(IncludeSwitch)../../src/control/record" "$(IncludeSwitch)../../src/control/joiss" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/localConfig_LocalManager$(ObjectSuffix) 

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
$(IntermediateDirectory)/localConfig_LocalManager$(ObjectSuffix): ../../src/config/localConfig/LocalManager.cpp $(IntermediateDirectory)/localConfig_LocalManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/config/localConfig/LocalManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/localConfig_LocalManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/localConfig_LocalManager$(DependSuffix): ../../src/config/localConfig/LocalManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/localConfig_LocalManager$(ObjectSuffix) -MF$(IntermediateDirectory)/localConfig_LocalManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/config/localConfig/LocalManager.cpp"

$(IntermediateDirectory)/localConfig_LocalManager$(PreprocessSuffix): ../../src/config/localConfig/LocalManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/localConfig_LocalManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/config/localConfig/LocalManager.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/localConfig_LocalManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/localConfig_LocalManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/localConfig_LocalManager$(PreprocessSuffix)
	$(RM) $(OutputFile)


