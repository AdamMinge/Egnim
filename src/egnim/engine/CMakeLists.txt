# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set files variable ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/src/egnim/engine)
set(include_root ${EGNIM_SOURCE_DIR}/include/egnim/engine)
set(resources_root ${EGNIM_SOURCE_DIR}/resources)

set(sources
        ${source_root}/core/context.cpp
        ${source_root}/core/state.cpp
        ${source_root}/core/state_stack.cpp
        ${source_root}/core/node.cpp
        ${source_root}/core/command_queue.cpp
        ${source_root}/core/component.cpp
        ${source_root}/core/component_container.cpp
        ${source_root}/core/sound_node.cpp
        ${source_root}/core/music_node.cpp
        ${source_root}/core/sprite_node.cpp
        ${source_root}/core/label_node.cpp
        ${source_root}/core/animated_sprite.cpp
        ${source_root}/core/animated_sprite_node.cpp
        ${source_root}/core/camera.cpp
        ${source_root}/core/scene_node.cpp)

set(includes
        ${include_root}/../config.h
        ${include_root}/export.h
        ${include_root}/core/context.h
        ${include_root}/core/lazy_unique_pointer.h
        ${include_root}/core/resource_holder.h
        ${include_root}/core/state.h
        ${include_root}/core/state_stack.h
        ${include_root}/core/node.h
        ${include_root}/core/command.h
        ${include_root}/core/command_queue.h
        ${include_root}/core/component.h
        ${include_root}/core/component_container.h
        ${include_root}/core/sound_node.h
        ${include_root}/core/music_node.h
        ${include_root}/core/sprite_node.h
        ${include_root}/core/label_node.h
        ${include_root}/core/animated_sprite.h
        ${include_root}/core/animated_sprite_node.h
        ${include_root}/core/camera.h
        ${include_root}/core/scene_node.h)

set(resources)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(SFML REQUIRED COMPONENTS graphics audio system network)
find_package(box2d REQUIRED)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_library(egnim-engine
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS sfml-graphics sfml-audio sfml-system sfml-network box2d)

set_target_properties(egnim-engine
        PROPERTIES CXX_STANDARD 20)
# -------------------------------------------------------------------------------------------------- #
