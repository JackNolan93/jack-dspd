set(XFADESOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/xfade~.c
)

add_pd_external(xfade xfade~ "${XFADESOURCE}")

set_target_properties(xfade PROPERTIES FOLDER modules)