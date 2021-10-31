# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# ------------------------------------- Initialize submodule --------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
function(initialize_submodule DIRECTORY)
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}/.git)
        find_package(Git QUIET REQUIRED)
        message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}/.git does not exist. Initializing ${DIRECTORY} submodule ...")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init ${DIRECTORY}
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_EXIT_CODE)
        if(NOT GIT_EXIT_CODE EQUAL "0")
            message(FATAL_ERROR "${GIT_EXECUTABLE} submodule update --init dependencies/${DIRECTORY} failed with exit code ${GIT_EXIT_CODE}, please checkout submodules")
        endif()
    endif()
endfunction(initialize_submodule)

initialize_submodule(box2d)
initialize_submodule(gtest)
initialize_submodule(json)
initialize_submodule(sfml)
initialize_submodule(zip)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Add subdirectories ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
add_subdirectory(box2d EXCLUDE_FROM_ALL)
add_subdirectory(gtest EXCLUDE_FROM_ALL)
add_subdirectory(json EXCLUDE_FROM_ALL)
add_subdirectory(sfml EXCLUDE_FROM_ALL)
add_subdirectory(zip EXCLUDE_FROM_ALL)
# -------------------------------------------------------------------------------------------------- #
