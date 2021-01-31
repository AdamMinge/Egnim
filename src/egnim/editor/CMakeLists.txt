# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/src/egnim/editor)
set(include_root ${EGNIM_SOURCE_DIR}/include/egnim/editor)
set(uis_root ${EGNIM_SOURCE_DIR}/uis/egnim/editor)
set(resources_root ${EGNIM_SOURCE_DIR}/resources)

set(sources
        ${source_root}/meta_types.cpp
        ${source_root}/main.cpp
        ${source_root}/main_window.cpp)

set(includes
        ${include_root}/meta_types.h
        ${include_root}/main_window.h)

set(resources)

set(uis)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Qt libraries configuration ------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${uis_root})
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(Qt6 REQUIRED COMPONENTS Widgets)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_application(egnim-editor
        SOURCES ${sources} ${includes} ${uis} ${resources}
        DEPENDS Qt6::Widgets egnim::egnim-engine)

target_include_directories(egnim-editor PUBLIC
        $<BUILD_INTERFACE:${EGNIM_SOURCE_DIR}/include/egnim/editor>)

set_target_properties(egnim-editor
        PROPERTIES CXX_STANDARD 20)

target_compile_definitions(egnim-editor
        PUBLIC QT_NO_KEYWORDS)
# -------------------------------------------------------------------------------------------------- #
