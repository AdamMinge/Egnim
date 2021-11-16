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
        ${source_root}/qdialog/qdialogwithtoggleview.cpp
        ${source_root}/qdialog/qextendedfiledialog.cpp

        ${source_root}/qlineedit/qlineeditwithhistory.cpp

        ${source_root}/qdpi/qdpiinfo.cpp

        ${source_root}/qzip/qzipfile.cpp)

set(includes
        ${include_root}/export.h

        ${include_root}/qdialog/qdialogwithtoggleview.h
        ${include_root}/qdialog/qextendedfiledialog.h

        ${include_root}/qlineedit/qlineeditwithhistory.h

        ${include_root}/qview/qunselectableview.h

        ${include_root}/qdpi/qdpiinfo.h

        ${include_root}/qzip/qzipfile.h)

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
