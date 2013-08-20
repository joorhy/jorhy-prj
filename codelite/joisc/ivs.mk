##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ivs
ConfigurationName      :=Debug
WorkspacePath          := "/home/danny/WorkSpace/jorhy-prj/codelite/joisc"
ProjectPath            := "/home/danny/WorkSpace/jorhy-prj/codelite/joisc"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Danny
Date                   :=2013年08月16日
CodeLitePath           :="/home/danny/.codelite"
LinkerName             :=g++
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="ivs.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  `wx-config --libs` $(shell pkg-config --libs libavdevice libavformat libavfilter libavcodec libswresample libswscale libavutil)
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../src/ui/wx_ivs/include $(IncludeSwitch)../../src/core $(IncludeSwitch)../../src/ui/wx_ivs/include/ffmpeg 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../libs/linux/ffmpeg 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g `pkg-config --cflags gtk+-2.0` $(shell wx-config --cxxflags) $(Preprocessors)
CFLAGS   :=  -g `pkg-config --cflags gtk+-2.0` $(shell wx-config --cxxflags) $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix) $(IntermediateDirectory)/src_jo_frame$(ObjectSuffix) $(IntermediateDirectory)/src_jo_login$(ObjectSuffix) $(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix) $(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix) $(IntermediateDirectory)/src_x_catalog$(ObjectSuffix) $(IntermediateDirectory)/src_x_login$(ObjectSuffix) $(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix) $(IntermediateDirectory)/src_x_player$(ObjectSuffix) $(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix) \
	$(IntermediateDirectory)/src_x_title$(ObjectSuffix) $(IntermediateDirectory)/src_x_tree$(ObjectSuffix) $(IntermediateDirectory)/src_x_video$(ObjectSuffix) $(IntermediateDirectory)/src_x_window$(ObjectSuffix) $(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix) $(IntermediateDirectory)/src_x_tabview$(ObjectSuffix) $(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix) $(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix) $(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix) $(IntermediateDirectory)/src_x_reciver$(ObjectSuffix) \
	$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix) $(IntermediateDirectory)/src_x_render$(ObjectSuffix) $(IntermediateDirectory)/src_x_buffer$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_browser.cpp $(IntermediateDirectory)/src_jo_browser$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_browser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_browser$(DependSuffix): ../../src/ui/wx_ivs/src/jo_browser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_jo_browser$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_browser$(DependSuffix) -MM "../../src/ui/wx_ivs/src/jo_browser.cpp"

$(IntermediateDirectory)/src_jo_browser$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_browser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_browser$(PreprocessSuffix) "../../src/ui/wx_ivs/src/jo_browser.cpp"

$(IntermediateDirectory)/src_jo_frame$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_frame.cpp $(IntermediateDirectory)/src_jo_frame$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_frame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_frame$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_frame$(DependSuffix): ../../src/ui/wx_ivs/src/jo_frame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_jo_frame$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_frame$(DependSuffix) -MM "../../src/ui/wx_ivs/src/jo_frame.cpp"

$(IntermediateDirectory)/src_jo_frame$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_frame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_frame$(PreprocessSuffix) "../../src/ui/wx_ivs/src/jo_frame.cpp"

$(IntermediateDirectory)/src_jo_login$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_login.cpp $(IntermediateDirectory)/src_jo_login$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_login.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_login$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_login$(DependSuffix): ../../src/ui/wx_ivs/src/jo_login.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_jo_login$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_login$(DependSuffix) -MM "../../src/ui/wx_ivs/src/jo_login.cpp"

$(IntermediateDirectory)/src_jo_login$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_login.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_login$(PreprocessSuffix) "../../src/ui/wx_ivs/src/jo_login.cpp"

$(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_media_obj.cpp $(IntermediateDirectory)/src_jo_media_obj$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_media_obj.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_media_obj$(DependSuffix): ../../src/ui/wx_ivs/src/jo_media_obj.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_jo_media_obj$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_media_obj$(DependSuffix) -MM "../../src/ui/wx_ivs/src/jo_media_obj.cpp"

$(IntermediateDirectory)/src_jo_media_obj$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_media_obj.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_media_obj$(PreprocessSuffix) "../../src/ui/wx_ivs/src/jo_media_obj.cpp"

$(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix): ../../src/ui/wx_ivs/src/jo_sdk.cpp $(IntermediateDirectory)/src_jo_sdk$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/jo_sdk.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_jo_sdk$(DependSuffix): ../../src/ui/wx_ivs/src/jo_sdk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_jo_sdk$(ObjectSuffix) -MF$(IntermediateDirectory)/src_jo_sdk$(DependSuffix) -MM "../../src/ui/wx_ivs/src/jo_sdk.cpp"

$(IntermediateDirectory)/src_jo_sdk$(PreprocessSuffix): ../../src/ui/wx_ivs/src/jo_sdk.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_jo_sdk$(PreprocessSuffix) "../../src/ui/wx_ivs/src/jo_sdk.cpp"

$(IntermediateDirectory)/src_x_catalog$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_catalog.cpp $(IntermediateDirectory)/src_x_catalog$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_catalog.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_catalog$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_catalog$(DependSuffix): ../../src/ui/wx_ivs/src/x_catalog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_catalog$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_catalog$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_catalog.cpp"

$(IntermediateDirectory)/src_x_catalog$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_catalog.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_catalog$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_catalog.cpp"

$(IntermediateDirectory)/src_x_login$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_login.cpp $(IntermediateDirectory)/src_x_login$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_login.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_login$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_login$(DependSuffix): ../../src/ui/wx_ivs/src/x_login.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_login$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_login$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_login.cpp"

$(IntermediateDirectory)/src_x_login$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_login.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_login$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_login.cpp"

$(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_media_manager.cpp $(IntermediateDirectory)/src_x_media_manager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_media_manager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_media_manager$(DependSuffix): ../../src/ui/wx_ivs/src/x_media_manager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_media_manager$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_media_manager$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_media_manager.cpp"

$(IntermediateDirectory)/src_x_media_manager$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_media_manager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_media_manager$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_media_manager.cpp"

$(IntermediateDirectory)/src_x_player$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_player.cpp $(IntermediateDirectory)/src_x_player$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_player$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_player$(DependSuffix): ../../src/ui/wx_ivs/src/x_player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_player$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_player$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_player.cpp"

$(IntermediateDirectory)/src_x_player$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_player$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_player.cpp"

$(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_ptzctl.cpp $(IntermediateDirectory)/src_x_ptzctl$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_ptzctl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_ptzctl$(DependSuffix): ../../src/ui/wx_ivs/src/x_ptzctl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_ptzctl$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_ptzctl$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_ptzctl.cpp"

$(IntermediateDirectory)/src_x_ptzctl$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_ptzctl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_ptzctl$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_ptzctl.cpp"

$(IntermediateDirectory)/src_x_title$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_title.cpp $(IntermediateDirectory)/src_x_title$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_title.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_title$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_title$(DependSuffix): ../../src/ui/wx_ivs/src/x_title.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_title$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_title$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_title.cpp"

$(IntermediateDirectory)/src_x_title$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_title.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_title$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_title.cpp"

$(IntermediateDirectory)/src_x_tree$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_tree.cpp $(IntermediateDirectory)/src_x_tree$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_tree$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_tree$(DependSuffix): ../../src/ui/wx_ivs/src/x_tree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_tree$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_tree$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_tree.cpp"

$(IntermediateDirectory)/src_x_tree$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_tree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_tree$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_tree.cpp"

$(IntermediateDirectory)/src_x_video$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_video.cpp $(IntermediateDirectory)/src_x_video$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_video.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_video$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_video$(DependSuffix): ../../src/ui/wx_ivs/src/x_video.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_video$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_video$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_video.cpp"

$(IntermediateDirectory)/src_x_video$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_video.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_video$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_video.cpp"

$(IntermediateDirectory)/src_x_window$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_window.cpp $(IntermediateDirectory)/src_x_window$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_window.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_window$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_window$(DependSuffix): ../../src/ui/wx_ivs/src/x_window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_window$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_window$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_window.cpp"

$(IntermediateDirectory)/src_x_window$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_window.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_window$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_window.cpp"

$(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_xml_stream.cpp $(IntermediateDirectory)/src_x_xml_stream$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_xml_stream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_xml_stream$(DependSuffix): ../../src/ui/wx_ivs/src/x_xml_stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_xml_stream$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_xml_stream$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_xml_stream.cpp"

$(IntermediateDirectory)/src_x_xml_stream$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_xml_stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_xml_stream$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_xml_stream.cpp"

$(IntermediateDirectory)/src_x_tabview$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_tabview.cpp $(IntermediateDirectory)/src_x_tabview$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_tabview.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_tabview$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_tabview$(DependSuffix): ../../src/ui/wx_ivs/src/x_tabview.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_tabview$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_tabview$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_tabview.cpp"

$(IntermediateDirectory)/src_x_tabview$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_tabview.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_tabview$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_tabview.cpp"

$(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_toolwin.cpp $(IntermediateDirectory)/src_x_toolwin$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_toolwin.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_toolwin$(DependSuffix): ../../src/ui/wx_ivs/src/x_toolwin.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_toolwin$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_toolwin$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_toolwin.cpp"

$(IntermediateDirectory)/src_x_toolwin$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_toolwin.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_toolwin$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_toolwin.cpp"

$(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_rcdctl.cpp $(IntermediateDirectory)/src_x_rcdctl$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcdctl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_rcdctl$(DependSuffix): ../../src/ui/wx_ivs/src/x_rcdctl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_rcdctl$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_rcdctl$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_rcdctl.cpp"

$(IntermediateDirectory)/src_x_rcdctl$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_rcdctl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_rcdctl$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_rcdctl.cpp"

$(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_rcd_slider.cpp $(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_rcd_slider.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix): ../../src/ui/wx_ivs/src/x_rcd_slider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_rcd_slider$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_rcd_slider$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_rcd_slider.cpp"

$(IntermediateDirectory)/src_x_rcd_slider$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_rcd_slider.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_rcd_slider$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_rcd_slider.cpp"

$(IntermediateDirectory)/src_x_reciver$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_reciver.cpp $(IntermediateDirectory)/src_x_reciver$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_reciver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_reciver$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_reciver$(DependSuffix): ../../src/ui/wx_ivs/src/x_reciver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_reciver$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_reciver$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_reciver.cpp"

$(IntermediateDirectory)/src_x_reciver$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_reciver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_reciver$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_reciver.cpp"

$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_decoder.cpp $(IntermediateDirectory)/src_x_decoder$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_decoder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_decoder$(DependSuffix): ../../src/ui/wx_ivs/src/x_decoder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_decoder$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_decoder$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_decoder.cpp"

$(IntermediateDirectory)/src_x_decoder$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_decoder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_decoder$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_decoder.cpp"

$(IntermediateDirectory)/src_x_render$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_render.cpp $(IntermediateDirectory)/src_x_render$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_render.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_render$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_render$(DependSuffix): ../../src/ui/wx_ivs/src/x_render.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_render$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_render$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_render.cpp"

$(IntermediateDirectory)/src_x_render$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_render.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_render$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_render.cpp"

$(IntermediateDirectory)/src_x_buffer$(ObjectSuffix): ../../src/ui/wx_ivs/src/x_buffer.cpp $(IntermediateDirectory)/src_x_buffer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/danny/WorkSpace/jorhy-prj/src/ui/wx_ivs/src/x_buffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_x_buffer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_x_buffer$(DependSuffix): ../../src/ui/wx_ivs/src/x_buffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_x_buffer$(ObjectSuffix) -MF$(IntermediateDirectory)/src_x_buffer$(DependSuffix) -MM "../../src/ui/wx_ivs/src/x_buffer.cpp"

$(IntermediateDirectory)/src_x_buffer$(PreprocessSuffix): ../../src/ui/wx_ivs/src/x_buffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_x_buffer$(PreprocessSuffix) "../../src/ui/wx_ivs/src/x_buffer.cpp"


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
	$(RM) ".build-debug/ivs"


