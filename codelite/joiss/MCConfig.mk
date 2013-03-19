##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=MCConfig
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/19/2013
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/config/mc" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/mcConfig_RemoteManager$(ObjectSuffix) 

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
$(IntermediateDirectory)/mcConfig_RemoteManager$(ObjectSuffix): ../../src/config/mcConfig/RemoteManager.cpp $(IntermediateDirectory)/mcConfig_RemoteManager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/config/mcConfig/RemoteManager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/mcConfig_RemoteManager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mcConfig_RemoteManager$(DependSuffix): ../../src/config/mcConfig/RemoteManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/mcConfig_RemoteManager$(ObjectSuffix) -MF$(IntermediateDirectory)/mcConfig_RemoteManager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/config/mcConfig/RemoteManager.cpp"

$(IntermediateDirectory)/mcConfig_RemoteManager$(PreprocessSuffix): ../../src/config/mcConfig/RemoteManager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mcConfig_RemoteManager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/config/mcConfig/RemoteManager.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/mcConfig_RemoteManager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mcConfig_RemoteManager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mcConfig_RemoteManager$(PreprocessSuffix)
	$(RM) $(OutputFile)


