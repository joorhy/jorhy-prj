##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=jo_pcap
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/utils" "$(IncludeSwitch)../../src/goose" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/pcap_jo_pcap$(ObjectSuffix) 

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
$(IntermediateDirectory)/pcap_jo_pcap$(ObjectSuffix): ../../src/pcap/jo_pcap.cpp $(IntermediateDirectory)/pcap_jo_pcap$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/pcap/jo_pcap.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pcap_jo_pcap$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pcap_jo_pcap$(DependSuffix): ../../src/pcap/jo_pcap.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/pcap_jo_pcap$(ObjectSuffix) -MF$(IntermediateDirectory)/pcap_jo_pcap$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/pcap/jo_pcap.cpp"

$(IntermediateDirectory)/pcap_jo_pcap$(PreprocessSuffix): ../../src/pcap/jo_pcap.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/pcap_jo_pcap$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/pcap/jo_pcap.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/pcap_jo_pcap$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pcap_jo_pcap$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pcap_jo_pcap$(PreprocessSuffix)
	$(RM) $(OutputFile)


