# -------------------------------------------------------------------------------------------------- #
# -------------------------------------- Set CMake Version ----------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.11)
# -------------------------------------------------------------------------------------------------- #
# --------------------------- Generate headers and set files variable ------------------------------ #
# -------------------------------------------------------------------------------------------------- #
set(source_root ${EGNIM_SOURCE_DIR}/tests/engine/src)
set(include_root ${EGNIM_SOURCE_DIR}/tests/engine/include)

set(sources
    ${source_root}/main.cpp)

set(includes)
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------- Create application target ------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
egnim_add_application(egnim-core-test
        SOURCES ${sources} ${includes}
        DEPENDS egnim::egnim-engine GTest::gtest GTest::gmock)

target_include_directories(egnim-core-test
        PUBLIC $<BUILD_INTERFACE:${EGNIM_SOURCE_DIR}/tests/core/include>)

set_target_properties(egnim-core-test
        PROPERTIES CXX_STANDARD 20)
# -------------------------------------------------------------------------------------------------- #
