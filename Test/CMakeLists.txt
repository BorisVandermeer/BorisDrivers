if(NOT BORIS_PNC_COMMON_FOUND)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty)
        execute_process(COMMAND mkdir ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty)
    endif()
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty/BorisPNCCommon)
        execute_process(COMMAND git clone git@github.com:BorisVandermeer/BorisPNCCommon.git --depth=1
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/SecondParty)
    endif()

    add_subdirectory(SecondParty/BorisPNCCommon)
endif()


add_subdirectory(Drivers)