##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=joies
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  -Wl,-rpath,./
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/pcap" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)jo_pcap $(LibrarySwitch)goose $(LibrarySwitch)jo_utils $(LibrarySwitch)jo_core $(LibrarySwitch)pcap $(LibrarySwitch)pthread $(LibrarySwitch)dl 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)./Debug" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/event_joies$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/event_joies$(ObjectSuffix): ../../src/event/joies.cpp $(IntermediateDirectory)/event_joies$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/event/joies.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/event_joies$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/event_joies$(DependSuffix): ../../src/event/joies.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/event_joies$(ObjectSuffix) -MF$(IntermediateDirectory)/event_joies$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/event/joies.cpp"

$(IntermediateDirectory)/event_joies$(PreprocessSuffix): ../../src/event/joies.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/event_joies$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/event/joies.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/event_joies$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/event_joies$(DependSuffix)
	$(RM) $(IntermediateDirectory)/event_joies$(PreprocessSuffix)
	$(RM) $(OutputFile)


