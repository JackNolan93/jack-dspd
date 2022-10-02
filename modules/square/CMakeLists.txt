set(SQUARESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/square~.c
)

add_pd_external(square square~ "${SQUARESOURCE}")

set_target_properties(square PROPERTIES FOLDER modules)