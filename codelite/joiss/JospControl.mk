##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JospControl
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/control/stream" "$(IncludeSwitch)../../src/control/record" "$(IncludeSwitch)../../src/control/joiss" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/josp_JospParser$(ObjectSuffix) 

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
$(IntermediateDirectory)/josp_JospParser$(ObjectSuffix): ../../src/control/josp/JospParser.cpp $(IntermediateDirectory)/josp_JospParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/control/josp/JospParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/josp_JospParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/josp_JospParser$(DependSuffix): ../../src/control/josp/JospParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/josp_JospParser$(ObjectSuffix) -MF$(IntermediateDirectory)/josp_JospParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/control/josp/JospParser.cpp"

$(IntermediateDirectory)/josp_JospParser$(PreprocessSuffix): ../../src/control/josp/JospParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/josp_JospParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/control/josp/JospParser.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/josp_JospParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/josp_JospParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/josp_JospParser$(PreprocessSuffix)
	$(RM) $(OutputFile)


