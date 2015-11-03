cmake_minimum_required(VERSION 2.8.3)

project(libminiking)

# Finding headers and launch files for QtCreator
file(GLOB_RECURSE HDRS ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp)
file(GLOB_RECURSE SRCS ${CMAKE_CURRENT_SOURCE_DIR} *.cxx *.cpp *.c *.py)
file(GLOB_RECURSE LNCH ${CMAKE_CURRENT_SOURCE_DIR} *.launch, *.yml)

# System dependencies
find_package(catkin REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

###########
## Build ##
###########

catkin_package(
 INCLUDE_DIRS include
 LIBRARIES miniking
)

# Including directories.
include_directories(include ${Boost_INCLUDE_DIRS})

# Custom target to include headers and launch files in QtCreator
#add_custom_target(dtarget_visual_indexing SOURCES ${HDRS} ${SRCS} ${LNCH})

# BinaryIndex library
add_library(miniking
    src/SerialPort.cpp
    src/Packet.cpp
    src/Message.cpp
    src/Command.cpp
    src/MtAlive.cpp
    src/MtBBUserData.cpp
    src/MtHeadData.cpp
    src/MtVersionData.cpp
    src/MtHeadCommand.cpp
    src/MtReboot.cpp
    src/MtSendBBUser.cpp
    src/MtSendData.cpp
    src/MtSendVersion.cpp
    src/MiniKing.cpp
)

target_link_libraries(miniking ${Boost_LIBRARIES})
