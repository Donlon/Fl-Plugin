cmake_minimum_required(VERSION 3.13)
project(Fl-Plug-in)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(_stdcall=__stdcall)

include_directories(JuceLibraryCode)
include_directories("D:\\Program Files (x86)\\JUCE\\modules")
include_directories("Source/fpsdk")

add_library(Fl-Plug-in SHARED
        Source/fpsdk/fp_cplug.cpp
        Source/fpsdk/fp_extra.cpp
        Source/fpsdk/fp_plugclass.cpp
        JuceLibraryCode/include_juce_audio_basics.cpp
        JuceLibraryCode/include_juce_audio_devices.cpp
        JuceLibraryCode/include_juce_audio_formats.cpp
        JuceLibraryCode/include_juce_audio_processors.cpp
        JuceLibraryCode/include_juce_core.cpp
        JuceLibraryCode/include_juce_data_structures.cpp
        JuceLibraryCode/include_juce_events.cpp
        JuceLibraryCode/include_juce_graphics.cpp
        JuceLibraryCode/include_juce_gui_basics.cpp
        JuceLibraryCode/include_juce_gui_extra.cpp
        Source/illuminations/network/IlluminationServer.cpp
        Source/illuminations/network/StreamConnection.cpp
        Source/illuminations/network/AddressInfo.cpp
        Source/interface/DllEntry.cpp
        Source/interface/Param.cpp
        Source/interface/ParamManager.cpp
        Source/plugin/Plugin.cpp
        Source/plugin/EditorWindow.cpp
        Source/plugin/LightSynthesizer.cpp
        Source/PluginInterface.cpp
        Source/ui/SliderEx.cpp
        Source/ui/utils/CursorUtils.cpp
        Source/ui/utils/ValueFormatters.cpp
        Source/ui/utils/Console.cpp
        Source/interface/Utils.cpp)
