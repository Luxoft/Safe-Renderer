if(NOT DEFINED POPULUS_INITED)
    message(STATUS "Start set project options")

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(Common)
    include(Variables)
    include(Version)
    if(COVERAGE)
        include(Coverage)
    endif()
    include(Package)

    if(UNIT_TESTS)
        enable_testing()
    endif()

    add_definitions(-DPOPULUS_MEMORY_MODEL=1)
    message(STATUS "--> Using memory model: POPULUS_MEMORY_MODEL_STATIC")

    add_definitions(-DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})
    message(STATUS "--> Sizeof void* ${CMAKE_SIZEOF_VOID_P}")

    include(PlatformSpecific)

    message(STATUS "Init Project ${PROJECT_NAME} ver.${POPULUS_VERSION_MAJOR}.${POPULUS_VERSION_MINOR}.${POPULUS_VERSION_PATCH}")

    set(POPULUS_INITED ON)
endif()
