if(NOT DEFINED LSR_VERSION_MAJOR)
    set(LSR_VERSION_MAJOR 0)
endif(NOT DEFINED LSR_VERSION_MAJOR)

if(NOT DEFINED LSR_VERSION_MINOR)
    set(LSR_VERSION_MINOR 4)
endif(NOT DEFINED LSR_VERSION_MINOR)

if(NOT DEFINED LSR_VERSION_PATCH)
    set(LSR_VERSION_PATCH 0)
endif(NOT DEFINED LSR_VERSION_PATCH)

if(NOT CMAKE_SCRIPT_MODE_FILE)
    add_definitions("-DLSR_VERSION_MAJOR=${LSR_VERSION_MAJOR}")
    add_definitions("-DLSR_VERSION_MINOR=${LSR_VERSION_MINOR}")
    add_definitions("-DLSR_VERSION_PATCH=${LSR_VERSION_PATCH}")
endif()
