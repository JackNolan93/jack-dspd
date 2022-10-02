set(KLP24SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/klp24~.c
)

add_pd_external(klp24 klp24~ "${KLP24SOURCE}")

set_target_properties(klp24 PROPERTIES FOLDER modules)

