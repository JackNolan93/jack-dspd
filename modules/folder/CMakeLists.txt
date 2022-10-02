set(FOLDERSOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/folder~.c
)

add_pd_external(folder folder~ "${FOLDERSOURCE}")

set_target_properties(folder PROPERTIES FOLDER modules)