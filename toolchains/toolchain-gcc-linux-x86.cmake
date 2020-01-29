
# C and C++ compiler
if (NOT DEFINED COMPILER_HOME)
    get_filename_component(COMPILER_HOME "/usr/bin" ABSOLUTE)
endif()

set(CMAKE_AR           "${COMPILER_HOME}/ar"      CACHE PATH "ar Program")
set(CMAKE_C_COMPILER   "${COMPILER_HOME}/gcc"     CACHE PATH "C Compiler Program")
set(CMAKE_CXX_COMPILER "${COMPILER_HOME}/g++"     CACHE PATH "C++ Compiler Program")
set(CMAKE_LINKER       "${COMPILER_HOME}/ld"      CACHE PATH "Linker Program")
set(CMAKE_NM           "${COMPILER_HOME}/nm"      CACHE PATH "nm Program")
set(CMAKE_OBJCOPY      "${COMPILER_HOME}/objcopy" CACHE PATH "objcopy Program")
set(CMAKE_OBJDUMP      "${COMPILER_HOME}/objdump" CACHE PATH "objdump Program")
set(CMAKE_RANLIB       "${COMPILER_HOME}/ranlib"  CACHE PATH "ranlib Program")
set(CMAKE_STRIP        "${COMPILER_HOME}/strip"   CACHE PATH "Strip Program")

# compiler/linker flags
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -m32 -DNDEBUG -O3" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -m32 -DDEBUG -g" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -m32 -DDEBUG -g -O3" CACHE INTERNAL "" FORCE)
set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -m32 -DNDEBUG" CACHE INTERNAL "" FORCE)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -m32 -DNDEBUG -O3 -fno-rtti -fno-exceptions -fno-non-call-exceptions" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -m32 -DDEBUG -g -fno-rtti -fno-exceptions -fno-non-call-exceptions" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -m32 -DDEBUG -g -O3 -fno-rtti -fno-exceptions -fno-non-call-exceptions" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL} -m32 -DNDEBUG -fno-rtti -fno-exceptions -fno-non-call-exceptions" CACHE INTERNAL "" FORCE)

# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS}" CACHE INTERNAL "" FORCE)
# set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS}" CACHE INTERNAL "" FORCE)

set(SYSTEM_LIBS)

# the name of the target operating system
set(CMAKE_SYSTEM_NAME "Linux")
set(CPACK_SYSTEM_NAME "x86")
