set(SAWSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/saw~.c
)

add_pd_external(saw saw~ "${SAWSOURCE}")

set_target_properties(saw PROPERTIES FOLDER modules)