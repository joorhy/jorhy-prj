##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=JofsReader
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
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/josf_JofsFileReader$(ObjectSuffix) 

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
$(IntermediateDirectory)/josf_JofsFileReader$(ObjectSuffix): ../../src/files/josf/JofsFileReader.cpp $(IntermediateDirectory)/josf_JofsFileReader$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/files/josf/JofsFileReader.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/josf_JofsFileReader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/josf_JofsFileReader$(DependSuffix): ../../src/files/josf/JofsFileReader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/josf_JofsFileReader$(ObjectSuffix) -MF$(IntermediateDirectory)/josf_JofsFileReader$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/files/josf/JofsFileReader.cpp"

$(IntermediateDirectory)/josf_JofsFileReader$(PreprocessSuffix): ../../src/files/josf/JofsFileReader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/josf_JofsFileReader$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/files/josf/JofsFileReader.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/josf_JofsFileReader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/josf_JofsFileReader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/josf_JofsFileReader$(PreprocessSuffix)
	$(RM) $(OutputFile)


