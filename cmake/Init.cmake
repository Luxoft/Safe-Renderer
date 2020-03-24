if(NOT DEFINED LSR_INITED)
    message(STATUS "Start set project ${PROJECT_NAME} options")

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(Common)
    include(Variables)

    include(Version)
    message(STATUS "--> ${PROJECT_NAME} version is ${LSR_VERSION_MAJOR}.${LSR_VERSION_MINOR}.${LSR_VERSION_PATCH}")

    include(GitRevision)
    getGitRevision(
        REVISION_VAR "GIT_LSR_REVISION"
        SHORT_REVISION_VAR "GIT_LSR_REVISION_SHORT"
    )
    message(STATUS "git revision is ${GIT_LSR_REVISION}; short revision is ${GIT_LSR_REVISION_SHORT}")

    if(LSR_PACKAGE_INIT)
        include(Package)
        setPackageName(
            MAJOR "${LSR_VERSION_MAJOR}"
            MINOR "${LSR_VERSION_MINOR}"
            PATCH "${LSR_VERSION_PATCH}"
            DEV_BUILD "${DEVELOPMENT_BUILD}"
            UNIT_TESTS "${UNIT_TESTS}"
        )
    endif()

    if(COVERAGE)
        include(Coverage)
    endif()

    if(UNIT_TESTS)
        enable_testing()
    endif()

    add_definitions(-DLSR_MEMORY_MODEL=1)
    message(STATUS "--> Using memory model: LSR_MEMORY_MODEL_STATIC")

    add_definitions(-DSIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P})
    message(STATUS "--> Sizeof void* ${CMAKE_SIZEOF_VOID_P}")

    include(PlatformSpecific)

    set(LSR_INITED ON)
endif()
