set(SAWBLEPSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/sawblep~.c
)

add_pd_external(sawblep sawblep~ "${SAWBLEPSOURCE}")

set_target_properties(sawblep PROPERTIES FOLDER modules)