cmake_minimum_required(VERSION 3.2)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_MACOSX_RPATH Off)
set(CMAKE_OSX_DEPLOYMENT_TARGET 11.6)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(CXX_STANDARD 11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/lib/pd.build/pd.cmake)

project(jackdspd)

set_pd_sources(${CMAKE_CURRENT_SOURCE_DIR}/lib/pure-data/src)
set_pd_external_path(${CMAKE_CURRENT_SOURCE_DIR}/bin/)

# libs
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/lib/DaisySP)
set_target_properties(DaisySP PROPERTIES FOLDER lib)

# modules
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/kellet)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/klp24)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/folder)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/helloworld)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/reverbsc)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/saw)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/sawblep)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/square)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/squareblep)
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/modules/xfade)