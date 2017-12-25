add_definitions(
    /D "_CRT_SECURE_NO_DEPRECATE"
    /D "_CRT_SECURE_NO_WARNINGS"
    /GF
    /FD
    /EHsc
    /c
    /wd4800
    /D "NOMINMAX"
)
set_linker_flags("/ignore:4199")

if(FORCE_LINKER_INCREMENTAL_LINKING)
    set_linker_flags("/INCREMENTAL /OPT:NOREF /OPT:NOICF")
else()
    set_linker_flags("/INCREMENTAL:NO /OPT:REF /OPT:ICF")
endif()
