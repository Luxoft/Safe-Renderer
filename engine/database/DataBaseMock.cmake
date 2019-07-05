cmake_minimum_required(VERSION 2.8.12)

include_directories(
    ${LSRROOT}/pil/api
    ${LSRENGINE}/common/api
    ${DATABASE_BASE}/api
    ${DATABASE_BASE}/api/gen
    ${DATABASE_BASE}/src
)

set(DATABASEMOCK_HEADERS
    ${DATABASE_HEADERS}
    ${DATABASE_BASE}/test/DatabaseAccessor.h
)

set(DATABASEMOCK_SOURCES
    ${DATABASE_BASE}/src/Area.cpp
    ${DATABASE_BASE}/src/BitmapAccess.cpp
    ${DATABASE_BASE}/src/FonBinReader.cpp
    ${DATABASE_BASE}/src/LsrImage.cpp
    ${DATABASE_BASE}/src/StaticBitmap.cpp
    ${DATABASE_BASE}/src/gen/DDHType.cpp
    ${DATABASE_BASE}/test/DatabaseMock.cpp
)
