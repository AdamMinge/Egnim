# -------------------------------------------------------------------------------------------------- #
# ------------------------ Define a macro that helps defining an option ---------------------------- #
# -------------------------------------------------------------------------------------------------- #
macro(egnim_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------------- Detect the OS ------------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(EGNIM_OS_WINDOWS TRUE)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(EGNIM_OS_LINUX TRUE)
else()
    message(FATAL_ERROR "Unsupported operating system or environment")
endif()
# -------------------------------------------------------------------------------------------------- #
# ---------------------------------------- Define options ------------------------------------------ #
# -------------------------------------------------------------------------------------------------- #
egnim_set_option(BUILD_SHARED_LIBS TRUE BOOL "TRUE to build EGNIM dependencies as shared libraries, FALSE to build it as static libraries")
egnim_set_option(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EGNIM_BINARY_DIR}" PATH "set global directory for output runtime")
egnim_set_option(EGNIM_DEPRECATED_WARNINGS TRUE BOOL "FALSE to disable deprecated warning, TRUE to enable depracated warning")
egnim_set_option(EGNIM_BUILD_TEST TRUE BOOL "TRUE to build the egnim-tests, FALSE to ignore them")
egnim_set_option(EGNIM_BUILD_EXAMPLES TRUE BOOL "TRUE to build the egnim-examples, FALSE to ignore them")
egnim_set_option(EGNIM_BUILD_DOCUMENTATION TRUE BOOL "TRUE to build the documentation, FALSE to ignore them")
# -------------------------------------------------------------------------------------------------- #
# --------------------------------------- Set other options ---------------------------------------- #
# -------------------------------------------------------------------------------------------------- #
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${EGNIM_SOURCE_DIR}/cmake/modules)
# -------------------------------------------------------------------------------------------------- #
