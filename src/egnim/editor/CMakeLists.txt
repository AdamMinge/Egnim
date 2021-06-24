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
        ${source_root}/language_manager.cpp
        ${source_root}/style_manager.cpp
        ${source_root}/action_manager.cpp
        ${source_root}/preferences_manager.cpp
        ${source_root}/about_dialog.cpp
        ${source_root}/settings_dialog.cpp

        ${source_root}/document/document.cpp
        ${source_root}/document/document_manager.cpp
        ${source_root}/document/document_editor.cpp
        ${source_root}/document/scene_document.cpp
        ${source_root}/document/scene_editor.cpp
        ${source_root}/document/new_document_dialog.cpp
        ${source_root}/document/inspector_dock.cpp
        ${source_root}/document/scene_dock.cpp
        ${source_root}/document/no_document_widget.cpp
        ${source_root}/document/document_serializer.cpp
        ${source_root}/document/priv/document_serializer_impl.h
        ${source_root}/document/priv/document_serializer_impl.cpp
        ${source_root}/document/priv/json_document_serializer_impl.h
        ${source_root}/document/priv/json_document_serializer_impl.cpp

        ${source_root}/project/project.cpp
        ${source_root}/project/project_editor.cpp
        ${source_root}/project/no_project_widget.cpp
        ${source_root}/project/project_manager.cpp
        ${source_root}/project/game_project.cpp
        ${source_root}/project/game_editor.cpp
        ${source_root}/project/new_project_dialog.cpp
        ${source_root}/project/open_documents_widget.cpp
        ${source_root}/project/file_system_dock.cpp
        ${source_root}/project/undo_dock.cpp
        ${source_root}/project/project_serializer.cpp
        ${source_root}/project/priv/project_serializer_impl.h
        ${source_root}/project/priv/project_serializer_impl.cpp
        ${source_root}/project/priv/json_project_serializer_impl.h
        ${source_root}/project/priv/json_project_serializer_impl.cpp

        ${source_root}/commands/command.cpp
        ${source_root}/commands/group_command.cpp
        ${source_root}/commands/add_remove_document.cpp

        ${source_root}/widgets/dialog_with_toggle_view.cpp)

set(includes
        ${include_root}/meta_types.h
        ${include_root}/main_window.h
        ${include_root}/language_manager.h
        ${include_root}/style_manager.h
        ${include_root}/action_manager.h
        ${include_root}/preferences_manager.h
        ${include_root}/about_dialog.h
        ${include_root}/settings_dialog.h

        ${include_root}/document/document.h
        ${include_root}/document/document_manager.h
        ${include_root}/document/document_editor.h
        ${include_root}/document/scene_document.h
        ${include_root}/document/scene_editor.h
        ${include_root}/document/new_document_dialog.h
        ${include_root}/document/inspector_dock.h
        ${include_root}/document/scene_dock.h
        ${include_root}/document/no_document_widget.h
        ${include_root}/document/document_serializer.h

        ${include_root}/project/project.h
        ${include_root}/project/project_editor.h
        ${include_root}/project/no_project_widget.h
        ${include_root}/project/project_manager.h
        ${include_root}/project/game_project.h
        ${include_root}/project/game_editor.h
        ${include_root}/project/new_project_dialog.h
        ${include_root}/project/open_documents_widget.h
        ${include_root}/project/file_system_dock.h
        ${include_root}/project/undo_dock.h
        ${include_root}/project/project_serializer.h

        ${include_root}/commands/command.h
        ${include_root}/commands/group_command.h
        ${include_root}/commands/add_remove_document.h

        ${include_root}/widgets/dialog_with_toggle_view.h)

set(resources)

set(uis
        ${uis_root}/main_window.ui
        ${uis_root}/about_dialog.ui
        ${uis_root}/settings_dialog.ui

        ${uis_root}/document/no_document_widget.ui
        ${uis_root}/document/new_scene_document_dialog.ui

        ${uis_root}/project/no_project_widget.ui
        ${uis_root}/project/new_game_project_dialog.ui)
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

target_include_directories(egnim-editor
        PUBLIC $<BUILD_INTERFACE:${EGNIM_SOURCE_DIR}/include/egnim/editor>
        PRIVATE ${PROJECT_SOURCE_DIR}/src)

set_target_properties(egnim-editor
        PROPERTIES CXX_STANDARD 20)

target_compile_definitions(egnim-editor
        PUBLIC QT_NO_KEYWORDS)
# -------------------------------------------------------------------------------------------------- #
