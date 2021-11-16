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
        ${source_root}/qtpropertybrowser/qtbuttonpropertybrowser.cpp
        ${source_root}/qtpropertybrowser/qteditorfactory.cpp
        ${source_root}/qtpropertybrowser/qtgroupboxpropertybrowser.cpp
        ${source_root}/qtpropertybrowser/qtpropertybrowser.cpp
        ${source_root}/qtpropertybrowser/qtpropertybrowserutils.cpp
        ${source_root}/qtpropertybrowser/qtpropertymanager.cpp
        ${source_root}/qtpropertybrowser/qttreepropertybrowser.cpp
        ${source_root}/qtpropertybrowser/qtvariantproperty.cpp
        ${source_root}/qtpropertybrowser/priv/qtpropertybrowserutils_p.h

        ${source_root}/qtdialog/qtdialogwithtoggleview.cpp
        ${source_root}/qtdialog/qtextendedfiledialog.cpp

        ${source_root}/qtlineedit/qtlineeditwithhistory.cpp

        ${source_root}/qtdpi/qtdpiinfo.cpp

        ${source_root}/qtzip/qtzipfile.cpp)

set(includes
        ${include_root}/export.h

        ${include_root}/qtpropertybrowser/qtbuttonpropertybrowser.h
        ${include_root}/qtpropertybrowser/qteditorfactory.h
        ${include_root}/qtpropertybrowser/qtgroupboxpropertybrowser.h
        ${include_root}/qtpropertybrowser/qtpropertybrowser.h
        ${include_root}/qtpropertybrowser/qtpropertymanager.h
        ${include_root}/qtpropertybrowser/qttreepropertybrowser.h
        ${include_root}/qtpropertybrowser/qtvariantproperty.h

        ${include_root}/qtdialog/qtdialogwithtoggleview.h
        ${include_root}/qtdialog/qtextendedfiledialog.h

        ${include_root}/qtlineedit/qtlineeditwithhistory.h

        ${include_root}/qtview/qtunselectableview.h

        ${include_root}/qtdpi/qtdpiinfo.h

        ${include_root}/qtzip/qtzipfile.h)

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
