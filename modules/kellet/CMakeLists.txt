set(KELLETSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/kellet~.c
)

add_pd_external(kellet kellet~ "${KELLETSOURCE}")

set_target_properties(kellet PROPERTIES FOLDER modules)