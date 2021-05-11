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
        ${source_root}/core/main_loop.cpp

        ${source_root}/graphics/animated_sprite.cpp
        ${source_root}/graphics/cell.cpp
        ${source_root}/graphics/chunk.cpp
        ${source_root}/graphics/tile.cpp
        ${source_root}/graphics/tile_map.cpp
        ${source_root}/graphics/layer.cpp
        ${source_root}/graphics/tile_layer.cpp
        ${source_root}/graphics/tile_layer_iterator.cpp
        ${source_root}/graphics/group_layer_iterator.cpp
        ${source_root}/graphics/group_layer.cpp
        ${source_root}/graphics/tileset.cpp
        ${source_root}/graphics/priv/tile_map_impl.h
        ${source_root}/graphics/priv/tile_map_impl.cpp
        ${source_root}/graphics/priv/isometric_tile_map_impl.h
        ${source_root}/graphics/priv/isometric_tile_map_impl.cpp
        ${source_root}/graphics/priv/orthogonal_tile_map_impl.h
        ${source_root}/graphics/priv/orthogonal_tile_map_impl.cpp

        ${source_root}/scene/component.cpp
        ${source_root}/scene/component_container.cpp
        ${source_root}/scene/node.cpp
        ${source_root}/scene/sound_node.cpp
        ${source_root}/scene/music_node.cpp
        ${source_root}/scene/sprite_node.cpp
        ${source_root}/scene/label_node.cpp
        ${source_root}/scene/animated_sprite_node.cpp
        ${source_root}/scene/scene_node.cpp
        ${source_root}/scene/node_factory.cpp
        ${source_root}/scene/node_iterator.cpp
        ${source_root}/scene/camera_node.cpp
        ${source_root}/scene/camera_manager.cpp
        ${source_root}/scene/tile_map_node.cpp
        ${source_root}/scene/scene_state.cpp
        ${source_root}/scene/scene_serializer.cpp
        ${source_root}/scene/priv/scene_serializer_impl.h
        ${source_root}/scene/priv/json_scene_serializer_impl.h
        ${source_root}/scene/priv/json_scene_serializer_impl.cpp

        ${source_root}/physics/physics_world.cpp
        ${source_root}/physics/physics_body.cpp
        ${source_root}/physics/physics_shape.cpp
        ${source_root}/physics/physics_joint.cpp
        ${source_root}/physics/physics_contact_impulse.cpp
        ${source_root}/physics/physics_manifold.cpp
        ${source_root}/physics/physics_manifold_point.cpp
        ${source_root}/physics/physics_contact.cpp
        ${source_root}/physics/physics_material.cpp
        ${source_root}/physics/physics_aabb.cpp
        ${source_root}/physics/priv/b2_physics_casters.h
        ${source_root}/physics/priv/b2_physics_casters.cpp
        ${source_root}/physics/priv/b2_physics_world_callbacks.h
        ${source_root}/physics/priv/b2_physics_world_callbacks.cpp

        ${source_root}/events/event_dispatcher.cpp
        ${source_root}/events/event.cpp
        ${source_root}/events/contact_event.cpp
        ${source_root}/events/mouse_event.cpp
        ${source_root}/events/keyboard_event.cpp
        ${source_root}/events/window_event.cpp
        ${source_root}/events/joystick_event.cpp
        ${source_root}/events/event_listener.cpp
        ${source_root}/events/contact_event_listener.cpp
        ${source_root}/events/mouse_event_listener.cpp
        ${source_root}/events/keyboard_event_listener.cpp
        ${source_root}/events/window_event_listener.cpp
        ${source_root}/events/joystick_event_listener.cpp
        ${source_root}/events/state_event.cpp
        ${source_root}/events/state_event_listener.cpp
        ${source_root}/events/priv/event_listener_vector.h
        ${source_root}/events/priv/event_listener_vector.cpp

        ${source_root}/actions/action.cpp
        ${source_root}/actions/action_manager.cpp)

set(includes
        ${include_root}/../config.h
        ${include_root}/export.h

        ${include_root}/core/object.h
        ${include_root}/core/context.h
        ${include_root}/core/lazy_unique_pointer.h
        ${include_root}/core/unique_pointer.h
        ${include_root}/core/resource_holder.h
        ${include_root}/core/state.h
        ${include_root}/core/state_stack.h
        ${include_root}/core/main_loop.h

        ${include_root}/graphics/animated_sprite.h
        ${include_root}/graphics/cell.h
        ${include_root}/graphics/chunk.h
        ${include_root}/graphics/tile.h
        ${include_root}/graphics/tile_map.h
        ${include_root}/graphics/layer.h
        ${include_root}/graphics/tile_layer.h
        ${include_root}/graphics/tile_layer_iterator.h
        ${include_root}/graphics/group_layer_iterator.h
        ${include_root}/graphics/group_layer.h
        ${include_root}/graphics/tileset.h

        ${include_root}/scene/component.h
        ${include_root}/scene/component_container.h
        ${include_root}/scene/node.h
        ${include_root}/scene/sound_node.h
        ${include_root}/scene/music_node.h
        ${include_root}/scene/sprite_node.h
        ${include_root}/scene/label_node.h
        ${include_root}/scene/animated_sprite_node.h
        ${include_root}/scene/scene_node.h
        ${include_root}/scene/node_factory.h
        ${include_root}/scene/node_iterator.h
        ${include_root}/scene/camera_node.h
        ${include_root}/scene/camera_manager.h
        ${include_root}/scene/tile_map_node.h
        ${include_root}/scene/scene_state.h
        ${include_root}/scene/scene_visitor.h
        ${include_root}/scene/scene_serializer.h

        ${include_root}/physics/physics_world.h
        ${include_root}/physics/physics_body.h
        ${include_root}/physics/physics_shape.h
        ${include_root}/physics/physics_joint.h
        ${include_root}/physics/physics_contact_impulse.h
        ${include_root}/physics/physics_manifold.h
        ${include_root}/physics/physics_manifold_point.h
        ${include_root}/physics/physics_contact.h
        ${include_root}/physics/physics_material.h
        ${include_root}/physics/physics_aabb.h

        ${include_root}/events/event_dispatcher.h
        ${include_root}/events/event.h
        ${include_root}/events/contact_event.h
        ${include_root}/events/mouse_event.h
        ${include_root}/events/keyboard_event.h
        ${include_root}/events/window_event.h
        ${include_root}/events/joystick_event
        ${include_root}/events/event_listener.h
        ${include_root}/events/contact_event_listener.h
        ${include_root}/events/mouse_event_listener.h
        ${include_root}/events/keyboard_event_listener.h
        ${include_root}/events/window_event_listener.h
        ${include_root}/events/joystick_event_listener.h
        ${include_root}/events/state_event.h
        ${include_root}/events/state_event_listener.h

        ${include_root}/actions/action.h
        ${include_root}/actions/action_manager.h)

set(resources)
# -------------------------------------------------------------------------------------------------- #
# ----------------------------------- Find external libraries -------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
find_package(SFML REQUIRED COMPONENTS graphics audio system network)
find_package(box2d REQUIRED)
find_package(nlohmann_json REQUIRED)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_library(egnim-engine
        SOURCES ${sources} ${includes} ${resources}
        DEPENDS sfml-graphics sfml-audio sfml-system
                box2d nlohmann_json::nlohmann_json)

set_target_properties(egnim-engine
        PROPERTIES CXX_STANDARD 20)
# -------------------------------------------------------------------------------------------------- #
