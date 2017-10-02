cmake_minimum_required(VERSION 2.8.11)

project(ChobbyLauncher)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_REQUIRED TRUE)

set(CMAKE_AUTOUIC ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


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
Set(LD_FLAGS "-static-libstdc++ -static-libgcc")
Set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS}    ${LD_FLAGS}")
Set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LD_FLAGS}")

# Find the QtWidgets library
#find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# include_directories(${Qt5Widgets_INCLUDE_DIRS})

Add_Subdirectory(src)
# Tell CMake to create the ChobbyLauncher executable
add_executable(ChobbyLauncher ${launcherSources})

set(BINDIR  "bin"                CACHE STRING "Where to install binaries")
set(LIBDIR  "lib"                CACHE STRING "Where to install libraries")

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


# Use the Widgets module from Qt 5.
#target_link_libraries(ChobbyLauncher pr-downloader_static)
target_link_libraries(ChobbyLauncher Qt5::Widgets pr-downloader_static)
