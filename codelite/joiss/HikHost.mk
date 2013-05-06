##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=HikHost
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/host/hik" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/hik_HikAdapter$(ObjectSuffix) $(IntermediateDirectory)/hik_HikChannel$(ObjectSuffix) $(IntermediateDirectory)/hik_HikIntercom$(ObjectSuffix) $(IntermediateDirectory)/hik_HikParser$(ObjectSuffix) $(IntermediateDirectory)/hik_HikStream$(ObjectSuffix) $(IntermediateDirectory)/hik_HikVodStream$(ObjectSuffix) $(IntermediateDirectory)/hik_HikParser2$(ObjectSuffix) 

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
$(IntermediateDirectory)/hik_HikAdapter$(ObjectSuffix): ../../src/host/hik/HikAdapter.cpp $(IntermediateDirectory)/hik_HikAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikAdapter$(DependSuffix): ../../src/host/hik/HikAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikAdapter.cpp"

$(IntermediateDirectory)/hik_HikAdapter$(PreprocessSuffix): ../../src/host/hik/HikAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikAdapter.cpp"

$(IntermediateDirectory)/hik_HikChannel$(ObjectSuffix): ../../src/host/hik/HikChannel.cpp $(IntermediateDirectory)/hik_HikChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikChannel$(DependSuffix): ../../src/host/hik/HikChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikChannel.cpp"

$(IntermediateDirectory)/hik_HikChannel$(PreprocessSuffix): ../../src/host/hik/HikChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikChannel.cpp"

$(IntermediateDirectory)/hik_HikIntercom$(ObjectSuffix): ../../src/host/hik/HikIntercom.cpp $(IntermediateDirectory)/hik_HikIntercom$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikIntercom.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikIntercom$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikIntercom$(DependSuffix): ../../src/host/hik/HikIntercom.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikIntercom$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikIntercom$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikIntercom.cpp"

$(IntermediateDirectory)/hik_HikIntercom$(PreprocessSuffix): ../../src/host/hik/HikIntercom.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikIntercom$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikIntercom.cpp"

$(IntermediateDirectory)/hik_HikParser$(ObjectSuffix): ../../src/host/hik/HikParser.cpp $(IntermediateDirectory)/hik_HikParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikParser$(DependSuffix): ../../src/host/hik/HikParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikParser$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikParser.cpp"

$(IntermediateDirectory)/hik_HikParser$(PreprocessSuffix): ../../src/host/hik/HikParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikParser.cpp"

$(IntermediateDirectory)/hik_HikStream$(ObjectSuffix): ../../src/host/hik/HikStream.cpp $(IntermediateDirectory)/hik_HikStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikStream$(DependSuffix): ../../src/host/hik/HikStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikStream$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikStream.cpp"

$(IntermediateDirectory)/hik_HikStream$(PreprocessSuffix): ../../src/host/hik/HikStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikStream.cpp"

$(IntermediateDirectory)/hik_HikVodStream$(ObjectSuffix): ../../src/host/hik/HikVodStream.cpp $(IntermediateDirectory)/hik_HikVodStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikVodStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikVodStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikVodStream$(DependSuffix): ../../src/host/hik/HikVodStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikVodStream$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikVodStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikVodStream.cpp"

$(IntermediateDirectory)/hik_HikVodStream$(PreprocessSuffix): ../../src/host/hik/HikVodStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikVodStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikVodStream.cpp"

$(IntermediateDirectory)/hik_HikParser2$(ObjectSuffix): ../../src/host/hik/HikParser2.cpp $(IntermediateDirectory)/hik_HikParser2$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikParser2.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/hik_HikParser2$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hik_HikParser2$(DependSuffix): ../../src/host/hik/HikParser2.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/hik_HikParser2$(ObjectSuffix) -MF$(IntermediateDirectory)/hik_HikParser2$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikParser2.cpp"

$(IntermediateDirectory)/hik_HikParser2$(PreprocessSuffix): ../../src/host/hik/HikParser2.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hik_HikParser2$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/hik/HikParser2.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/hik_HikAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikIntercom$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikIntercom$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikIntercom$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikStream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikVodStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikVodStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikVodStream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikParser2$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikParser2$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hik_HikParser2$(PreprocessSuffix)
	$(RM) $(OutputFile)


