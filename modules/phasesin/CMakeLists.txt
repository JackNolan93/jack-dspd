set(PHASESINSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/phasesin~.c
)

add_pd_external(phasesin phasesin~ "${PHASESINSOURCE}")

set_target_properties(phasesin PROPERTIES FOLDER modules)