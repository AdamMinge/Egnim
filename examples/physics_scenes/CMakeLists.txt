# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# --------------------------- Generate headers and set files variable ------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/examples/physics_scenes/src)
set(include_root ${EGNIM_SOURCE_DIR}/examples/physics_scenes/include)

set(sources
    ${source_root}/main.cpp
    ${source_root}/example_game.cpp
    ${source_root}/boxes_state.cpp)

set(includes
    ${include_root}/example_game.h
    ${include_root}/boxes_state.h)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_application(egnim-example-physics_scenes
        SOURCES ${sources} ${includes}
        DEPENDS egnim::egnim-engine)

target_include_directories(egnim-example-physics_scenes
        PUBLIC $<BUILD_INTERFACE:${EGNIM_SOURCE_DIR}/examples/physics_scenes/include>)

set_target_properties(egnim-example-physics_scenes
        PROPERTIES CXX_STANDARD 20)
# -------------------------------------------------------------------------------------------------- #
