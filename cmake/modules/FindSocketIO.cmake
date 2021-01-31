# Find SocketIO Client C++ Library and header file
# Sets
#   SocketIO_ROOT                  root box2d directory
#   SocketIO_FOUND                 to 0 or 1 depending on the result
# If SocketIO_FIND_REQUIRED is defined, then a fatal error message will be generated if isn't found something
# Returns
#   SocketIO::SocketIO             socketio target library

function(socketio_dependency)
    cmake_parse_arguments(THIS "" "TARGET;FRIENDLY_NAME" "SEARCH_NAMES" ${ARGN})
    if (THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when
        calling socketio_dependency:${THIS_UNPARSED_ARGUMENTS}")
    endif()

    find_library(${THIS_FRIENDLY_NAME}_LIB NAMES ${THIS_SEARCH_NAMES}
            PATHS
            ${SocketIO_ROOT}
            /usr/lib/x86_64-linux-gnu/
            /usr/local
            /usr
            /sw
            /opt/local
            /opt/csw
            /opt
            PATH_SUFFIXES lib NO_SYSTEM_ENVIRONMENT_PATH)

    if(${THIS_FRIENDLY_NAME}_LIB)
        set_property(TARGET ${THIS_TARGET} APPEND PROPERTY
                INTERFACE_LINK_LIBRARIES "${${THIS_FRIENDLY_NAME}_LIB}")
    else()
        set(FIND_SocketIO_DEPENDENCIES_NOTFOUND
                "${FIND_SocketIO_DEPENDENCIES_NOTFOUND} ${THIS_FRIENDLY_NAME}" PARENT_SCOPE)
    endif()
endfunction()

function(socketio_headers_dependency)
    cmake_parse_arguments(THIS "" "TARGET;FRIENDLY_NAME" "SEARCH_NAMES" ${ARGN})
    if (THIS_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Unknown arguments when
        calling socketio_headers_dependency:${THIS_UNPARSED_ARGUMENTS}")
    endif()

    find_path(${THIS_FRIENDLY_NAME}_HEADERS NAMES ${THIS_SEARCH_NAMES}
            PATHS
            ${SocketIO_ROOT}
            /usr/lib/x86_64-linux-gnu/
            /usr/local
            /usr
            /sw
            /opt/local
            /opt/csw
            /opt
            PATH_SUFFIXES include NO_SYSTEM_ENVIRONMENT_PATH)

    if(${THIS_FRIENDLY_NAME}_HEADERS)
        set_property(TARGET ${THIS_TARGET} APPEND PROPERTY
                INTERFACE_INCLUDE_DIRECTORIES "${${THIS_FRIENDLY_NAME}_HEADERS}")
    else()
        set(FIND_SocketIO_DEPENDENCIES_NOTFOUND
                "${FIND_SocketIO_DEPENDENCIES_NOTFOUND} ${THIS_FRIENDLY_NAME}" PARENT_SCOPE)
    endif()
endfunction()

find_library(SocketIO_LIBRARIES
        NAMES sioclient libsioclient
        PATHS
        ${SocketIO_ROOT}
        /usr/local
        /usr
        PATH_SUFFIXES
        lib)

find_path(SocketIO_INCLUDE_DIRECTORIES
        NAMES sio_client.h
        PATHS
        ${SocketIO_ROOT}
        /usr/local
        /usr
        PATH_SUFFIXES
        include)

add_library(Boost::random INTERFACE IMPORTED)
add_library(Boost::date_time INTERFACE IMPORTED)
add_library(Boost::system INTERFACE IMPORTED)
add_library(websocketpp INTERFACE IMPORTED)
add_library(rapidjson INTERFACE IMPORTED)

socketio_dependency(TARGET Boost::random FRIENDLY_NAME "boost-random" SEARCH_NAMES "libboost_random.a")
socketio_dependency(TARGET Boost::date_time FRIENDLY_NAME "boost-date_time" SEARCH_NAMES "libboost_date_time")
socketio_dependency(TARGET Boost::system FRIENDLY_NAME "boost-system" SEARCH_NAMES "libboost_system")
socketio_headers_dependency(TARGET websocketpp FRIENDLY_NAME "websocketpp" SEARCH_NAMES "websocketpp")
socketio_headers_dependency(TARGET rapidjson FRIENDLY_NAME "rapidjson" SEARCH_NAMES "rapidjson")

if(NOT SocketIO_INCLUDE_DIRECTORIES OR NOT SocketIO_LIBRARIES OR FIND_SocketIO_DEPENDENCIES_NOTFOUND)
    if(SocketIO_FIND_REQUIRED)
        if(NOT SocketIO_INCLUDE_DIRECTORIES OR NOT SocketIO_LIBRARIES)
            message(FATAL_ERROR "Not found SocketIO. Set SocketIO_ROOT or CMAKE_PREFIX_PATH" )
        endif()
        if(FIND_SocketIO_DEPENDENCIES_NOTFOUND)
            message(FATAL_ERROR "SocketIO found but some of its \
            dependencies are missing (${FIND_SocketIO_DEPENDENCIES_NOTFOUND})")
        endif()
    endif()
else()
    set(SocketIO_FOUND TRUE)
endif()

if(SocketIO_FOUND AND NOT TARGET SocketIO::SocketIO)
    add_library(SocketIO::SocketIO STATIC IMPORTED)
    set_target_properties(SocketIO::SocketIO PROPERTIES
            IMPORTED_LOCATION ${SocketIO_LIBRARIES}
            INTERFACE_INCLUDE_DIRECTORIES "${SocketIO_INCLUDE_DIRECTORIES}"
            INTERFACE_LINK_LIBRARIES "$<LINK_ONLY:Boost::random>;$<LINK_ONLY:Boost::date_time>;$<LINK_ONLY:Boost::system>;$<LINK_ONLY:websocketpp>;$<LINK_ONLY:rapidjson>")
endif()