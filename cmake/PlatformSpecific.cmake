message(STATUS "CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message(STATUS "CPACK_SYSTEM_NAME=${CPACK_SYSTEM_NAME}")
add_definitions(-DUNICODE -D_UNICODE)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include(platform_specific/Windows)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX ON CACHE INTERNAL "" FORCE)
    include(platform_specific/Linux)
endif()

include(CheckSymbolExists)

check_symbol_exists(errno_t "errno.h" HAVE_ERRNO_T)
if(HAVE_ERRNO_T)
    add_definitions(-DHAVE_ERRNO_T)
endif()

