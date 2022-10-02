set(HELLOWORLDSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/helloworld.c
)

add_pd_external(helloworld helloworld "${HELLOWORLDSOURCE}")

set_target_properties(helloworld PROPERTIES FOLDER modules)