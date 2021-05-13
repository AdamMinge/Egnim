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
        ${source_root}/main_window.cpp
        ${source_root}/document.cpp
        ${source_root}/editor.cpp
        ${source_root}/no_editor_widget.cpp
        ${source_root}/document_manager.cpp
        ${source_root}/language_manager.cpp
        ${source_root}/style_manager.cpp

        ${source_root}/widgets/dialog_with_toggle_view.cpp)

set(includes
        ${include_root}/meta_types.h
        ${include_root}/main_window.h
        ${include_root}/document.h
        ${include_root}/editor.h
        ${include_root}/no_editor_widget.h
        ${include_root}/document_manager.h
        ${include_root}/language_manager.h
        ${include_root}/style_manager.h

        ${include_root}/widgets/dialog_with_toggle_view.h)

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
