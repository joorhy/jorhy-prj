##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=RtpStream
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug/plugins
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joiss"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=03/13/2013
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
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/output_stream/rtp" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/rtp_RtpMux$(ObjectSuffix) 

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
$(IntermediateDirectory)/rtp_RtpMux$(ObjectSuffix): ../../src/stream_output/rtp/RtpMux.cpp $(IntermediateDirectory)/rtp_RtpMux$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/stream_output/rtp/RtpMux.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/rtp_RtpMux$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rtp_RtpMux$(DependSuffix): ../../src/stream_output/rtp/RtpMux.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/rtp_RtpMux$(ObjectSuffix) -MF$(IntermediateDirectory)/rtp_RtpMux$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/stream_output/rtp/RtpMux.cpp"

$(IntermediateDirectory)/rtp_RtpMux$(PreprocessSuffix): ../../src/stream_output/rtp/RtpMux.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rtp_RtpMux$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/stream_output/rtp/RtpMux.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/rtp_RtpMux$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/rtp_RtpMux$(DependSuffix)
	$(RM) $(IntermediateDirectory)/rtp_RtpMux$(PreprocessSuffix)
	$(RM) $(OutputFile)


