# -------------------------------------------------------------------------------------------------- #
# ------------------------ Define a macro that helps defining an option ---------------------------- #
# -------------------------------------------------------------------------------------------------- #
macro(egnim_add_library target)

    cmake_parse_arguments(THIS "" "" "SOURCES;DEPENDS" ${ARGN})
    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling egnim_add_library: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    add_library(${target} ${THIS_SOURCES})
    add_library(egnim::${target} ALIAS ${target})

    if(THIS_DEPENDS)
        target_link_libraries(${target} ${THIS_DEPENDS})

        foreach(target_depends ${THIS_DEPENDS})
            install(TARGETS ${target_depends} EXPORT ${target}ConfigExport)
        endforeach()
    endif()

    string(REPLACE "-" "_" NAME_UPPER "${target}")
    string(TOUPPER "${NAME_UPPER}" NAME_UPPER)
    set_target_properties(${target} PROPERTIES DEFINE_SYMBOL ${NAME_UPPER}_EXPORTS)

    if(BUILD_SHARED_LIBS)
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)
    else()
        set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -s-d)
        set_target_properties(${target} PROPERTIES RELEASE_POSTFIX -s)
    endif()

    set_target_properties(${target} PROPERTIES COMPILE_FEATURES cxx_std_20)

    install(TARGETS ${target} EXPORT ${target}ConfigExport
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib)

    target_include_directories(${target}
                               PUBLIC $<BUILD_INTERFACE:${EGNIM_SOURCE_DIR}/include>
                               INTERFACE $<INSTALL_INTERFACE:include>
                               PRIVATE ${PROJECT_SOURCE_DIR}/src)

    if(NOT BUILD_SHARED_LIBS)
        target_compile_definitions(${target} PUBLIC "EGNIM_STATIC")
    endif()

endmacro()
# -------------------------------------------------------------------------------------------------- #
# -------------------------- Define a macro that helps export targets ------------------------------ #
# -------------------------------------------------------------------------------------------------- #
function(egnim_export_targets target)

    if (BUILD_SHARED_LIBS)
        set(config_name "shared")
    else()
        set(config_name "static")
    endif()

    set(current_dir "${EGNIM_SOURCE_DIR}/cmake")
    set(targets_config_filename "egnim-${config_name}-targets.cmake")
    set(config_package_location lib/cmake/egnim)

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/egnim-config-version.cmake"
                                     VERSION ${EGNIM_VERSION_MAJOR}.${EGNIM_VERSION_MINOR}
                                     COMPATIBILITY SameMajorVersion)

    export(EXPORT ${target}ConfigExport
           FILE "${CMAKE_CURRENT_BINARY_DIR}/${targets_config_filename}")

    configure_package_config_file("${current_dir}/egnim-config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/egnim-config.cmake"
                                    INSTALL_DESTINATION "${config_package_location}")
    configure_package_config_file("${current_dir}/egnim-config-dependencies.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/egnim-config-dependencies.cmake"
                                    INSTALL_DESTINATION "${config_package_location}")

    install(EXPORT ${target}ConfigExport
            FILE ${targets_config_filename}
            NAMESPACE egnim::
            DESTINATION ${config_package_location})

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/egnim-config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/egnim-config-dependencies.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/egnim-config-version.cmake
            DESTINATION ${config_package_location})

endfunction()
# -------------------------------------------------------------------------------------------------- #
# ----------------------- Define a macro that helps create application ----------------------------- #
# -------------------------------------------------------------------------------------------------- #
macro(egnim_add_application target)

    cmake_parse_arguments(THIS "" "RESOURCES_DIR" "SOURCES;DEPENDS" ${ARGN})
    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling egnim_add_application: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    add_executable(${target} ${THIS_SOURCES})
    set_target_properties(${target} PROPERTIES DEBUG_POSTFIX -d)

    if(THIS_DEPENDS)
        target_link_libraries(${target} PRIVATE ${THIS_DEPENDS})
    endif()

    install(TARGETS ${target}
            RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${target})

    if (THIS_RESOURCES_DIR)
        get_filename_component(THIS_RESOURCES_DIR "${THIS_RESOURCES_DIR}" ABSOLUTE)

        if(NOT EXISTS "${THIS_RESOURCES_DIR}")
            message(FATAL_ERROR "Given resources directory to install does not exist: ${THIS_RESOURCES_DIR}")
        endif()
        install(DIRECTORY ${THIS_RESOURCES_DIR}
                DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${target})
    endif()

endmacro()
# -------------------------------------------------------------------------------------------------- #
# ------------------------- Define a macro that generate documentation ----------------------------- #
# -------------------------------------------------------------------------------------------------- #
function(egnim_generate_documentation)
    find_package(Doxygen REQUIRED)
    set(DOXYGEN_IN ${EGNIM_SOURCE_DIR}/docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(docs_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
endfunction()
# -------------------------------------------------------------------------------------------------- #
# -------------------------- Define a macro that install documentation ----------------------------- #
# -------------------------------------------------------------------------------------------------- #
function(egnim_install_documentation)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/
            DESTINATION docs)
endfunction()
# -------------------------------------------------------------------------------------------------- #
# ----------------------- Define a macro that helps defining translations -------------------------- #
# -------------------------------------------------------------------------------------------------- #
macro(egnim_add_translations target)

    cmake_parse_arguments(THIS "" "QM_DIR" "TS_FILES;SOURCES;INCLUDES" ${ARGN})
    if (NOT "${THIS_UNPARSED_ARGUMENTS}" STREQUAL "")
        message(FATAL_ERROR "Extra unparsed arguments when calling egnim_add_translations: ${THIS_UNPARSED_ARGUMENTS}")
    endif()

    add_custom_target(update_all_ts_files ALL)
    add_custom_target(create_all_qm_files ALL)

    find_file(LUPDATE_PATH lupdate)
    find_file(LRELEASE_PATH lrelease)

    foreach(TS_FILE ${THIS_TS_FILES})

        get_filename_component(I18N_NAME ${TS_FILE} NAME_WE)
        set(TS_TARGET_NAME "update_ts_file_${I18N_NAME}")

        if (THIS_INCLUDES)
            add_custom_target(${TS_TARGET_NAME}
                    COMMAND ${LUPDATE_PATH} -I ${THIS_INCLUDES} ${THIS_SOURCES} -ts ${TS_FILE}
                    VERBATIM)
        else()
            add_custom_target(${TS_TARGET_NAME}
                    COMMAND ${LUPDATE_PATH} ${THIS_SOURCES} -ts ${TS_FILE}
                    VERBATIM)
        endif()

        add_dependencies(update_all_ts_files ${TS_TARGET_NAME})
        set(QM_TARGET_NAME "create_qm_file_${I18N_NAME}")
        set(QM_FILE "${THIS_QM_DIR}/${I18N_NAME}.qm")
        add_custom_target(${QM_TARGET_NAME}
                COMMAND ${LRELEASE_PATH} ${TS_FILE} -qm ${QM_FILE}
                VERBATIM)

        add_dependencies(${QM_TARGET_NAME} ${TS_TARGET_NAME})
        add_dependencies(create_all_qm_files ${QM_TARGET_NAME})
    endforeach()

    add_dependencies(${target} create_all_qm_files)

endmacro()
# -------------------------------------------------------------------------------------------------- #
