##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=AironixHost
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/20/2013
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
LinkOptions            :=  -Wl,-rpath,./plugins/libs
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/host/aironix" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)dvrnetsdk $(LibrarySwitch)asound 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)../../libs/aironix" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/aironix_AironixAdapter$(ObjectSuffix) $(IntermediateDirectory)/aironix_AironixChannel$(ObjectSuffix) $(IntermediateDirectory)/aironix_AironixParser$(ObjectSuffix) $(IntermediateDirectory)/aironix_AironixStream$(ObjectSuffix) 

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
$(IntermediateDirectory)/aironix_AironixAdapter$(ObjectSuffix): ../../src/host/aironix/AironixAdapter.cpp $(IntermediateDirectory)/aironix_AironixAdapter$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixAdapter.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aironix_AironixAdapter$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aironix_AironixAdapter$(DependSuffix): ../../src/host/aironix/AironixAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aironix_AironixAdapter$(ObjectSuffix) -MF$(IntermediateDirectory)/aironix_AironixAdapter$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixAdapter.cpp"

$(IntermediateDirectory)/aironix_AironixAdapter$(PreprocessSuffix): ../../src/host/aironix/AironixAdapter.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aironix_AironixAdapter$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixAdapter.cpp"

$(IntermediateDirectory)/aironix_AironixChannel$(ObjectSuffix): ../../src/host/aironix/AironixChannel.cpp $(IntermediateDirectory)/aironix_AironixChannel$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixChannel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aironix_AironixChannel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aironix_AironixChannel$(DependSuffix): ../../src/host/aironix/AironixChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aironix_AironixChannel$(ObjectSuffix) -MF$(IntermediateDirectory)/aironix_AironixChannel$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixChannel.cpp"

$(IntermediateDirectory)/aironix_AironixChannel$(PreprocessSuffix): ../../src/host/aironix/AironixChannel.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aironix_AironixChannel$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixChannel.cpp"

$(IntermediateDirectory)/aironix_AironixParser$(ObjectSuffix): ../../src/host/aironix/AironixParser.cpp $(IntermediateDirectory)/aironix_AironixParser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixParser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aironix_AironixParser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aironix_AironixParser$(DependSuffix): ../../src/host/aironix/AironixParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aironix_AironixParser$(ObjectSuffix) -MF$(IntermediateDirectory)/aironix_AironixParser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixParser.cpp"

$(IntermediateDirectory)/aironix_AironixParser$(PreprocessSuffix): ../../src/host/aironix/AironixParser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aironix_AironixParser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixParser.cpp"

$(IntermediateDirectory)/aironix_AironixStream$(ObjectSuffix): ../../src/host/aironix/AironixStream.cpp $(IntermediateDirectory)/aironix_AironixStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/aironix_AironixStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/aironix_AironixStream$(DependSuffix): ../../src/host/aironix/AironixStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/aironix_AironixStream$(ObjectSuffix) -MF$(IntermediateDirectory)/aironix_AironixStream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixStream.cpp"

$(IntermediateDirectory)/aironix_AironixStream$(PreprocessSuffix): ../../src/host/aironix/AironixStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/aironix_AironixStream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/host/aironix/AironixStream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/aironix_AironixAdapter$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixAdapter$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixAdapter$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixChannel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixChannel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixChannel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixParser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixParser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixParser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/aironix_AironixStream$(PreprocessSuffix)
	$(RM) $(OutputFile)


