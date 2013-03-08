##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=RtspRequest
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/rtsp_RtspFilter$(ObjectSuffix) 

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
$(IntermediateDirectory)/rtsp_RtspFilter$(ObjectSuffix): ../../src/access/rtsp/RtspFilter.cpp $(IntermediateDirectory)/rtsp_RtspFilter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/access/rtsp/RtspFilter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/rtsp_RtspFilter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rtsp_RtspFilter$(DependSuffix): ../../src/access/rtsp/RtspFilter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/rtsp_RtspFilter$(ObjectSuffix) -MF$(IntermediateDirectory)/rtsp_RtspFilter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/access/rtsp/RtspFilter.cpp"

$(IntermediateDirectory)/rtsp_RtspFilter$(PreprocessSuffix): ../../src/access/rtsp/RtspFilter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rtsp_RtspFilter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/access/rtsp/RtspFilter.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/rtsp_RtspFilter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/rtsp_RtspFilter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/rtsp_RtspFilter$(PreprocessSuffix)
	$(RM) $(OutputFile)


