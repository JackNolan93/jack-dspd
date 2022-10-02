set(OVERDRIVESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/overdrive~.c
    ${CMAKE_CURRENT_SOURCE_DIR}/OverdriveWrapper.h
)

add_pd_external(overdrive overdrive~ "${OVERDRIVESOURCE}")

SET_SOURCE_FILES_PROPERTIES (${CMAKE_CURRENT_SOURCE_DIR}/overdrive~.c PROPERTIES LANGUAGE CXX)

target_link_libraries (overdrive PRIVATE DaisySP)

set_target_properties(overdrive PROPERTIES FOLDER modules)
