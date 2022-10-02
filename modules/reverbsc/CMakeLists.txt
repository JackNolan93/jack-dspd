set(REVERBSCSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/reverbsc~.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ReverbscWrapper.h
)

add_pd_external(reverbsc reverbsc~ "${REVERBSCSOURCE}")

SET_SOURCE_FILES_PROPERTIES (${CMAKE_CURRENT_SOURCE_DIR}/reverbsc~.c PROPERTIES LANGUAGE CXX)

target_link_libraries (reverbsc PRIVATE DaisySP)

set_target_properties(reverbsc PROPERTIES FOLDER modules)
