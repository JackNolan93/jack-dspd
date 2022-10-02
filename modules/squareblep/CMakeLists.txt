set(SQUAREBLEPSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/squareblep~.c
)

add_pd_external(squareblep squareblep~ "${SQUAREBLEPSOURCE}")

set_target_properties(squareblep PROPERTIES FOLDER modules)