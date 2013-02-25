##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TSStream
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=02/25/2013
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/output_stream/ts" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/ts_TsMux$(ObjectSuffix) 

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
$(IntermediateDirectory)/ts_TsMux$(ObjectSuffix): ../../src/stream_output/ts/TsMux.cpp $(IntermediateDirectory)/ts_TsMux$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/stream_output/ts/TsMux.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/ts_TsMux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/ts_TsMux$(DependSuffix): ../../src/stream_output/ts/TsMux.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/ts_TsMux$(ObjectSuffix) -MF$(IntermediateDirectory)/ts_TsMux$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/stream_output/ts/TsMux.cpp"

$(IntermediateDirectory)/ts_TsMux$(PreprocessSuffix): ../../src/stream_output/ts/TsMux.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/ts_TsMux$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/stream_output/ts/TsMux.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/ts_TsMux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/ts_TsMux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/ts_TsMux$(PreprocessSuffix)
	$(RM) $(OutputFile)


