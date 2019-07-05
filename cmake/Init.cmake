if(NOT DEFINED LSR_INITED)
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

    add_definitions(-DLSR_MEMORY_MODEL=1)
    message(STATUS "--> Using memory model: LSR_MEMORY_MODEL_STATIC")

    add_definitions(-DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})
    message(STATUS "--> Sizeof void* ${CMAKE_SIZEOF_VOID_P}")

    include(PlatformSpecific)

    message(STATUS "Init Project ${PROJECT_NAME} ver.${LSR_VERSION_MAJOR}.${LSR_VERSION_MINOR}.${LSR_VERSION_PATCH}")

    set(LSR_INITED ON)
endif()
