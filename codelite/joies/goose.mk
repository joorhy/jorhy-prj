##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=goose
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joies"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joies"
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
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/pcap" "$(IncludeSwitch)../../src/scd" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/goose_x_goose$(ObjectSuffix) $(IntermediateDirectory)/goose_gse_config$(ObjectSuffix) $(IntermediateDirectory)/goose_x_gse_scd$(ObjectSuffix) $(IntermediateDirectory)/goose_x_scd$(ObjectSuffix) 

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
$(IntermediateDirectory)/goose_x_goose$(ObjectSuffix): ../../src/goose/x_goose.cpp $(IntermediateDirectory)/goose_x_goose$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_goose.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/goose_x_goose$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/goose_x_goose$(DependSuffix): ../../src/goose/x_goose.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/goose_x_goose$(ObjectSuffix) -MF$(IntermediateDirectory)/goose_x_goose$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_goose.cpp"

$(IntermediateDirectory)/goose_x_goose$(PreprocessSuffix): ../../src/goose/x_goose.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/goose_x_goose$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_goose.cpp"

$(IntermediateDirectory)/goose_gse_config$(ObjectSuffix): ../../src/goose/gse_config.cpp $(IntermediateDirectory)/goose_gse_config$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/gse_config.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/goose_gse_config$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/goose_gse_config$(DependSuffix): ../../src/goose/gse_config.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/goose_gse_config$(ObjectSuffix) -MF$(IntermediateDirectory)/goose_gse_config$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/goose/gse_config.cpp"

$(IntermediateDirectory)/goose_gse_config$(PreprocessSuffix): ../../src/goose/gse_config.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/goose_gse_config$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/gse_config.cpp"

$(IntermediateDirectory)/goose_x_gse_scd$(ObjectSuffix): ../../src/goose/x_gse_scd.cpp $(IntermediateDirectory)/goose_x_gse_scd$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_gse_scd.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/goose_x_gse_scd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/goose_x_gse_scd$(DependSuffix): ../../src/goose/x_gse_scd.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/goose_x_gse_scd$(ObjectSuffix) -MF$(IntermediateDirectory)/goose_x_gse_scd$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_gse_scd.cpp"

$(IntermediateDirectory)/goose_x_gse_scd$(PreprocessSuffix): ../../src/goose/x_gse_scd.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/goose_x_gse_scd$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_gse_scd.cpp"

$(IntermediateDirectory)/goose_x_scd$(ObjectSuffix): ../../src/goose/x_scd.cpp $(IntermediateDirectory)/goose_x_scd$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_scd.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/goose_x_scd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/goose_x_scd$(DependSuffix): ../../src/goose/x_scd.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/goose_x_scd$(ObjectSuffix) -MF$(IntermediateDirectory)/goose_x_scd$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_scd.cpp"

$(IntermediateDirectory)/goose_x_scd$(PreprocessSuffix): ../../src/goose/x_scd.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/goose_x_scd$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/goose/x_scd.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/goose_x_goose$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_goose$(DependSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_goose$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/goose_gse_config$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/goose_gse_config$(DependSuffix)
	$(RM) $(IntermediateDirectory)/goose_gse_config$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_gse_scd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_gse_scd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_gse_scd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_scd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_scd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/goose_x_scd$(PreprocessSuffix)
	$(RM) $(OutputFile)


