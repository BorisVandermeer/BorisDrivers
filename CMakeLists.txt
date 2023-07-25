
cmake_minimum_required(VERSION 3.21.0)
project(BorisDrivers VERSION 0.0.1)

# Top Level Check
if( BorisDrivers_IS_TOP_LEVEL)
    SET(IS_TOP_DIR YES)
    SET(ENABLE_TEST YES)
else()
    SET(IS_TOP_DIR NO)
    SET(ENABLE_TEST NO)
endif()

# Build Config
if(IS_TOP_DIR)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
endif()

# DeviceNeeded
SET(BUILD_ALL OFF)
if(BUILD_ALL)
    SET(BUILD_NPOS220 ON)
else()
    SET(BUILD_NPOS220 ON)
endif()

# <<<<< Find Dependencies <<<<< #
if(NOT BORIS_SERIAL_FOUND)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty)
        execute_process(COMMAND mkdir ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty)
    endif()
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty/BorisSerial)
        execute_process(COMMAND git clone git@github.com:BorisVandermeer/BorisSerial.git --depth=1
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty)
    endif()

    add_subdirectory(SecondParty/BorisSerial)
endif()

# >>>>> Find Dependencies >>>>> #

SET(BORIS_DRIVERS_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${BORIS_SERIAL_INCLUDE_DIRS})

# Build Libs
add_subdirectory(Protocols)
# add_subdirectory(Communication)
add_subdirectory(Drivers)

SET(BORIS_DRIVERS_LIBRARIES ${BORIS_DRIVERS_COMM_LIBRARIES} ${BORIS_DRIVERS_DRIVERS_LIBRARIES} 
    ${BORIS_DRIVERS_PROTOCOLS_LIBRARIES})

if(IS_TOP_DIR)
    SET(BORIS_DRIVERS_VERSION BorisDrivers_VERSION )
    SET(BORIS_DRIVERS_FOUND YES )
    SET(BORIS_DRIVERS_LIBRARIES ${BORIS_DRIVERS_LIBRARIES})
    SET(BORIS_DRIVERS_INCLUDE_DIRS ${BORIS_DRIVERS_INCLUDE_DIRS})
else()
    SET(BORIS_DRIVERS_VERSION BorisDrivers_VERSION PARENT_SCOPE)
    SET(BORIS_DRIVERS_FOUND YES PARENT_SCOPE)
    SET(BORIS_DRIVERS_LIBRARIES ${BORIS_DRIVERS_LIBRARIES} PARENT_SCOPE)
    SET(BORIS_DRIVERS_INCLUDE_DIRS ${BORIS_DRIVERS_INCLUDE_DIRS} PARENT_SCOPE)
endif()

# Build Test
# if(ENABLE_TEST) 
#     add_subdirectory(Test)
# endif()