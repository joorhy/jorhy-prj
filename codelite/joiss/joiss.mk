##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=joiss
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  -Wl,-rpath,./
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/cms" "$(IncludeSwitch)../../src/control/joiss" "$(IncludeSwitch)../../src/control/stream" "$(IncludeSwitch)../../src/control/record" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/misc" "$(IncludeSwitch)../../src/utils" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)StreamManager $(LibrarySwitch)RecordManager $(LibrarySwitch)JoissManager $(LibrarySwitch)misc $(LibrarySwitch)core $(LibrarySwitch)utils $(LibrarySwitch)pthread $(LibrarySwitch)dl 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)./Debug" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/src_joiss$(ObjectSuffix) 

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
$(IntermediateDirectory)/src_joiss$(ObjectSuffix): ../../src/joiss.cpp $(IntermediateDirectory)/src_joiss$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/joiss.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_joiss$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_joiss$(DependSuffix): ../../src/joiss.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_joiss$(ObjectSuffix) -MF$(IntermediateDirectory)/src_joiss$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/joiss.cpp"

$(IntermediateDirectory)/src_joiss$(PreprocessSuffix): ../../src/joiss.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_joiss$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/joiss.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_joiss$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_joiss$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_joiss$(PreprocessSuffix)
	$(RM) $(OutputFile)


