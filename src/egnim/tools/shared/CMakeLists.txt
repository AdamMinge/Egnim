# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/src/egnim/tools/shared)
set(include_root ${EGNIM_SOURCE_DIR}/include/egnim/tools/shared)
set(uis_root ${EGNIM_SOURCE_DIR}/uis/egnim/tools/shared)
set(resources_root ${EGNIM_SOURCE_DIR}/resources)

set(sources
        ${source_root}/dialog_with_toggle_view.cpp
        ${source_root}/line_edit_with_history.cpp
        ${source_root}/extended_file_dialog.cpp
        ${source_root}/dpi_info.cpp
        ${source_root}/zip_file.cpp)

set(includes
        ${include_root}/export.h
        ${include_root}/dialog_with_toggle_view.h
        ${include_root}/line_edit_with_history.h
        ${include_root}/unselectable_view.h
        ${include_root}/extended_file_dialog.h
        ${include_root}/dpi_info.h
        ${include_root}/zip_file.h)

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
# ------------------------------------ Create tool shared lib -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_tool_lib(tools-shared
        SOURCES ${sources} ${includes} ${uis} ${resources}
        DEPENDS Qt6::Widgets
        DEPENDS_PRIVATE zip::zip)
# -------------------------------------------------------------------------------------------------- #
