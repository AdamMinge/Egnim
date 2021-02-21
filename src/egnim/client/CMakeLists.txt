# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/src/egnim/client)
set(include_root ${EGNIM_SOURCE_DIR}/include/egnim/client)

set(sources
        ${source_root}/main.cpp)

set(includes)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_application(egnim-client
        SOURCES ${sources} ${includes}
        DEPENDS egnim::egnim-engine)

target_include_directories(egnim-client PUBLIC
        $<BUILD_INTERFACE:${EGNIM_SOURCE_DIR}/include/egnim/client>)

set_target_properties(egnim-client
        PROPERTIES CXX_STANDARD 20)

target_compile_definitions(egnim-client
        PUBLIC QT_NO_KEYWORDS)
# -------------------------------------------------------------------------------------------------- #
