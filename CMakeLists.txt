#minium cmake version
cmake_minimum_required(VERSION 4.0.0)

#project name and version
project(ScriptEditor VERSION 1.0.0)

#cpp standarts
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find and add qt6
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

#setup qt for proj
qt_standard_project_setup()

#list of cpp and h files
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
    src/main.cpp
    src/scripteditor.cpp
    src/customtextedit.cpp
)

set(HEADERS
    include/scripteditor.h
    include/customtextedit.h
)

#make execut file
qt_add_executable(ScriptEditor ${SOURCES} ${HEADERS})

#add libs
target_link_libraries(ScriptEditor PRIVATE Qt6::Core Qt6::Widgets)
