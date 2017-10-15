cmake_minimum_required(VERSION 3.0)

project(ChobbyLauncher)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_REQUIRED TRUE)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH} )

set(BINDIR  "bin"                CACHE STRING "Where to install binaries")
set(LIBDIR  "lib"                CACHE STRING "Where to install libraries")

Set(LD_FLAGS "-static-libstdc++ -static-libgcc")
#--static -DCURL_STATICLIB
Set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    ${LD_FLAGS}")
Set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LD_FLAGS}")

# pr-downloader
If (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pr-downloader/CMakeLists.txt")
    MESSAGE(FATAL_ERROR "${CMAKE_CURRENT_SOURCE_DIR}/pr-downloader/ is missing, please run\n git submodule init && git submodule update")
EndIf()
find_package(CURL REQUIRED)
set(CMAKE_BUILD_TYPE "RELEASE")
set(CLEAR_COMPILER_FLAGS true)
set(PRD_BINDIR ${BINDIR} CACHE PATH "" FORCE)
set(PRD_LIBDIR ${LIBDIR} CACHE PATH "" FORCE)
Add_Subdirectory(pr-downloader)

#QT5
set(CMAKE_AUTOUIC ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Resource files
set(CMAKE_AUTORCC ON)

message("MODULE PATH: ${CMAKE_MODULE_PATH}")

#Static start
#set_target_properties(ChobbyLauncher PROPERTIES LINK_SEARCH_START_STATIC 1)
#set_target_properties(ChobbyLauncher PROPERTIES LINK_SEARCH_END_STATIC 1)
if    (WIN32 OR MINGW)
    SET(CMAKE_FIND_LIBRARY_SUFFIXES .a .lib ${CMAKE_FIND_LIBRARY_SUFFIXES})
else  (WIN32 OR MINGW)
    SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
endif (WIN32 OR MINGW)
#Static Libs
#ADD_LIBRARY(Qt5::Widgets STATIC IMPORTED)
#ADD_LIBRARY(Qt5::Core STATIC IMPORTED)
#SET_TARGET_PROPERTIES(Qt5::Widgets PROPERTIES IMPORTED_LOCATION /usr/lib/libboost_unit_test_framework.a)
#TARGET_LINK_LIBRARIES(mytarget A boost_unit_test_framework C)
#Set Linker flags
#Set(LD_FLAGS "-static-libstdc++ -static-libgcc -lpthread -lssl -lnettle -lcrypto -lwldap32 -lws2_32 -lgdi32")
#--static -DCURL_STATICLIB
#Set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    ${LD_FLAGS}")
#Set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LD_FLAGS}")

# Find the QtWidgets library
#find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS REQUIRED Core Widgets Gui)
foreach(plugin ${Qt5Gui_PLUGINS})
  get_target_property(_loc ${plugin} LOCATION)
  message("Plugin ${plugin} is at location ${_loc}")
  set(plugin_libs ${plugin_libs} ${_loc})
endforeach()

#find_package(Qt5PlatformSupport REQUIRED)
find_package(Qt5FontDatabaseSupport REQUIRED)
find_package(Qt5ThemeSupport REQUIRED)
find_package(Qt5EventDispatcherSupport REQUIRED)

# include_directories(${Qt5Widgets_INCLUDE_DIRS})

message("CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS}")
find_package(OpenSSL REQUIRED)

Add_Subdirectory(src)
# Tell CMake to create the ChobbyLauncher executable
add_executable(spring-launcher ${launcherSources} "${CMAKE_CURRENT_SOURCE_DIR}/res/resources.qrc")

set(MY_LINK_LIBS -lpthread -lssl -lnettle -lcrypto -lwldap32 -lws2_32 -lgdi32)

message("MY_LINK_LIBS: ${MY_LINK_LIBS}")
message("Qt5ThemeSupport_LIBRARIES ${Qt5ThemeSupport_LIBRARIES}")

add_definitions(-DQT_STATICPLUGIN)

target_link_libraries(spring-launcher ${Qt5Widgets_LIBRARIES}     ${Qt5Gui_LIBRARIES} ${Qt5Core_LIBRARIES} Qt5::QWindowsIntegrationPlugin ${Qt5FontDatabaseSupport_LIBRARIES} ${Qt5ThemeSupport_LIBRARIES} ${Qt5EventDispatcherSupport_LIBRARIES} pr-downloader_static ${MY_LINK_LIBS} ${CURL_LIBRARIES} ${OPENSSL_LIBRARIES} ${plugin_libs})

# Add these manually at the end
