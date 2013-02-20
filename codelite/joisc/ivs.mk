##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ivs
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joisc"
ProjectPath            := "/home/jorhy/WorkSpace/jorhy-prj/codelite/joisc"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=root
Date                   :=02/02/2013
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
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g `pkg-config --cflags gtk+-2.0` $(shell wx-config --cxxflags) $(Preprocessors)
LinkOptions            :=  `wx-config --libs` $(shell pkg-config --libs libavdevice libavformat libavfilter libavcodec libswresample libswscale libavutil)
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)../../src/ui/wx_ivs/include" "$(IncludeSwitch)../../src/core" "$(IncludeSwitch)../../src/ui/wx_ivs/include/ffmpeg" 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)../../libs/ffmpeg" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix) $(IntermediateDirectory)/src_jo_frame$(ObjectSuffix) $(IntermediateDirectory)/src_jo_login$(ObjectSuffix) $(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix) $(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix) $(IntermediateDirectory)/src_x_catalog$(ObjectSuffix) $(IntermediateDirectory)/src_x_login$(ObjectSuffix) $(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix) $(IntermediateDirectory)/src_x_player$(ObjectSuffix) $(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix) \
	$(IntermediateDirectory)/src_x_title$(ObjectSuffix) $(IntermediateDirectory)/src_x_tree$(ObjectSuffix) $(IntermediateDirectory)/src_x_video$(ObjectSuffix) $(IntermediateDirectory)/src_x_window$(ObjectSuffix) $(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix) $(IntermediateDirectory)/src_x_tabview$(ObjectSuffix) $(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix) $(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix) $(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix) $(IntermediateDirectory)/src_x_reciver$(ObjectSuffix) \
	$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix) $(IntermediateDirectory)/src_x_render$(ObjectSuffix) $(IntermediateDirectory)/src_x_buffer$(ObjectSuffix) 

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
$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_browser.cpp $(IntermediateDirectory)/src_jo_browser$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_browser.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_browser$(DependSuffix): ../../src/ui/wx_ivs/src/jo_browser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_browser$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_browser.cpp"

$(IntermediateDirectory)/src_jo_browser$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_browser.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_browser$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_browser.cpp"

$(IntermediateDirectory)/src_jo_frame$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_frame.cpp $(IntermediateDirectory)/src_jo_frame$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_frame.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_frame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_frame$(DependSuffix): ../../src/ui/wx_ivs/src/jo_frame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_jo_frame$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_frame$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_frame.cpp"

$(IntermediateDirectory)/src_jo_frame$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_frame.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_frame$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_frame.cpp"

$(IntermediateDirectory)/src_jo_login$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_login.cpp $(IntermediateDirectory)/src_jo_login$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_login.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_login$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_login$(DependSuffix): ../../src/ui/wx_ivs/src/jo_login.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_jo_login$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_login$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_login.cpp"

$(IntermediateDirectory)/src_jo_login$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_login.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_login$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_login.cpp"

$(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_media_obj.cpp $(IntermediateDirectory)/src_jo_media_obj$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_media_obj.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_media_obj$(DependSuffix): ../../src/ui/wx_ivs/src/jo_media_obj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_media_obj$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_media_obj.cpp"

$(IntermediateDirectory)/src_jo_media_obj$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_media_obj.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_media_obj$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_media_obj.cpp"

$(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_sdk.cpp $(IntermediateDirectory)/src_jo_sdk$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_sdk.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_sdk$(DependSuffix): ../../src/ui/wx_ivs/src/jo_sdk.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_sdk$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_sdk.cpp"

$(IntermediateDirectory)/src_jo_sdk$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_sdk.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_sdk$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_sdk.cpp"

$(IntermediateDirectory)/src_x_catalog$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_catalog.cpp $(IntermediateDirectory)/src_x_catalog$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_catalog.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_catalog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_catalog$(DependSuffix): ../../src/ui/wx_ivs/src/x_catalog.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_catalog$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_catalog$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_catalog.cpp"

$(IntermediateDirectory)/src_x_catalog$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_catalog.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_catalog$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_catalog.cpp"

$(IntermediateDirectory)/src_x_login$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_login.cpp $(IntermediateDirectory)/src_x_login$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_login.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_login$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_login$(DependSuffix): ../../src/ui/wx_ivs/src/x_login.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_login$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_login$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_login.cpp"

$(IntermediateDirectory)/src_x_login$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_login.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_login$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_login.cpp"

$(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_media_manager.cpp $(IntermediateDirectory)/src_x_media_manager$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_media_manager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_media_manager$(DependSuffix): ../../src/ui/wx_ivs/src/x_media_manager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_media_manager$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_media_manager.cpp"

$(IntermediateDirectory)/src_x_media_manager$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_media_manager.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_media_manager$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_media_manager.cpp"

$(IntermediateDirectory)/src_x_player$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_player.cpp $(IntermediateDirectory)/src_x_player$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_player.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_player$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_player$(DependSuffix): ../../src/ui/wx_ivs/src/x_player.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_player$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_player$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_player.cpp"

$(IntermediateDirectory)/src_x_player$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_player.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_player$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_player.cpp"

$(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_ptzctl.cpp $(IntermediateDirectory)/src_x_ptzctl$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_ptzctl.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_ptzctl$(DependSuffix): ../../src/ui/wx_ivs/src/x_ptzctl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_ptzctl$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_ptzctl.cpp"

$(IntermediateDirectory)/src_x_ptzctl$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_ptzctl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_ptzctl$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_ptzctl.cpp"

$(IntermediateDirectory)/src_x_title$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_title.cpp $(IntermediateDirectory)/src_x_title$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_title.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_title$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_title$(DependSuffix): ../../src/ui/wx_ivs/src/x_title.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_title$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_title$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_title.cpp"

$(IntermediateDirectory)/src_x_title$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_title.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_title$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_title.cpp"

$(IntermediateDirectory)/src_x_tree$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_tree.cpp $(IntermediateDirectory)/src_x_tree$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tree.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_tree$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_tree$(DependSuffix): ../../src/ui/wx_ivs/src/x_tree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_tree$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_tree$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tree.cpp"

$(IntermediateDirectory)/src_x_tree$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_tree.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_tree$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tree.cpp"

$(IntermediateDirectory)/src_x_video$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_video.cpp $(IntermediateDirectory)/src_x_video$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_video.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_video$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_video$(DependSuffix): ../../src/ui/wx_ivs/src/x_video.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_video$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_video$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_video.cpp"

$(IntermediateDirectory)/src_x_video$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_video.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_video$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_video.cpp"

$(IntermediateDirectory)/src_x_window$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_window.cpp $(IntermediateDirectory)/src_x_window$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_window.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_window$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_window$(DependSuffix): ../../src/ui/wx_ivs/src/x_window.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_window$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_window$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_window.cpp"

$(IntermediateDirectory)/src_x_window$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_window.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_window$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_window.cpp"

$(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_xml_stream.cpp $(IntermediateDirectory)/src_x_xml_stream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_xml_stream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_xml_stream$(DependSuffix): ../../src/ui/wx_ivs/src/x_xml_stream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_xml_stream$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_xml_stream.cpp"

$(IntermediateDirectory)/src_x_xml_stream$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_xml_stream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_xml_stream$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_xml_stream.cpp"

$(IntermediateDirectory)/src_x_tabview$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_tabview.cpp $(IntermediateDirectory)/src_x_tabview$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tabview.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_tabview$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_tabview$(DependSuffix): ../../src/ui/wx_ivs/src/x_tabview.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_tabview$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_tabview$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tabview.cpp"

$(IntermediateDirectory)/src_x_tabview$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_tabview.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_tabview$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tabview.cpp"

$(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_toolwin.cpp $(IntermediateDirectory)/src_x_toolwin$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_toolwin.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_toolwin$(DependSuffix): ../../src/ui/wx_ivs/src/x_toolwin.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_toolwin$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_toolwin.cpp"

$(IntermediateDirectory)/src_x_toolwin$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_toolwin.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_toolwin$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_toolwin.cpp"

$(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_rcdctl.cpp $(IntermediateDirectory)/src_x_rcdctl$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcdctl.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_rcdctl$(DependSuffix): ../../src/ui/wx_ivs/src/x_rcdctl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_rcdctl$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcdctl.cpp"

$(IntermediateDirectory)/src_x_rcdctl$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_rcdctl.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_rcdctl$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcdctl.cpp"

$(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_rcd_slider.cpp $(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcd_slider.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix): ../../src/ui/wx_ivs/src/x_rcd_slider.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcd_slider.cpp"

$(IntermediateDirectory)/src_x_rcd_slider$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_rcd_slider.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_rcd_slider$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcd_slider.cpp"

$(IntermediateDirectory)/src_x_reciver$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_reciver.cpp $(IntermediateDirectory)/src_x_reciver$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_reciver.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_reciver$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_reciver$(DependSuffix): ../../src/ui/wx_ivs/src/x_reciver.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_reciver$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_reciver$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_reciver.cpp"

$(IntermediateDirectory)/src_x_reciver$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_reciver.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_reciver$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_reciver.cpp"

$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_decoder.cpp $(IntermediateDirectory)/src_x_decoder$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_decoder.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_decoder$(DependSuffix): ../../src/ui/wx_ivs/src/x_decoder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_decoder$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_decoder.cpp"

$(IntermediateDirectory)/src_x_decoder$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_decoder.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_decoder$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_decoder.cpp"

$(IntermediateDirectory)/src_x_render$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_render.cpp $(IntermediateDirectory)/src_x_render$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_render.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_render$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_render$(DependSuffix): ../../src/ui/wx_ivs/src/x_render.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_render$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_render$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_render.cpp"

$(IntermediateDirectory)/src_x_render$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_render.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_render$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_render.cpp"

$(IntermediateDirectory)/src_x_buffer$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_buffer.cpp $(IntermediateDirectory)/src_x_buffer$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_buffer.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/src_x_buffer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_buffer$(DependSuffix): ../../src/ui/wx_ivs/src/x_buffer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/src_x_buffer$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_buffer$(DependSuffix) -MM "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_buffer.cpp"

$(IntermediateDirectory)/src_x_buffer$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_buffer.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_buffer$(PreprocessSuffix) "/home/jorhy/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_buffer.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/src_jo_browser$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_browser$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_browser$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_frame$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_frame$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_frame$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_login$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_login$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_login$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_media_obj$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_media_obj$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_sdk$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_jo_sdk$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_catalog$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_catalog$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_catalog$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_login$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_login$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_login$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_media_manager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_media_manager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_player$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_player$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_player$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_ptzctl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_ptzctl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_title$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_title$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_title$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_tree$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_tree$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_tree$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_video$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_video$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_video$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_window$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_window$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_window$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_xml_stream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_xml_stream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_tabview$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_tabview$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_tabview$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_toolwin$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_toolwin$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_rcdctl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_rcdctl$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_rcd_slider$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_reciver$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_reciver$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_reciver$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_decoder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_decoder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_decoder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_render$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_render$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_render$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/src_x_buffer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/src_x_buffer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/src_x_buffer$(PreprocessSuffix)
	$(RM) $(OutputFile)


