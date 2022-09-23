cmake_minimum_required(VERSION 3.2)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_MACOSX_RPATH Off)
set(CMAKE_OSX_DEPLOYMENT_TARGET 11.6)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/lib/pd.build/pd.cmake)

project(jackdspd)

set_pd_sources(${CMAKE_CURRENT_SOURCE_DIR}/lib/pure-data/src)
set_pd_external_path(${CMAKE_CURRENT_SOURCE_DIR}/bin/)

add_pd_external(helloworld helloworld ${CMAKE_CURRENT_SOURCE_DIR}/src/helloworld.c)
add_pd_external(folder folder~ ${CMAKE_CURRENT_SOURCE_DIR}/src/folder~.c)
add_pd_external(kellet kellet~ ${CMAKE_CURRENT_SOURCE_DIR}/src/kellet~.c)
add_pd_external(klp24 klp24~ ${CMAKE_CURRENT_SOURCE_DIR}/src/klp24~.c)
add_pd_external(saw saw~ ${CMAKE_CURRENT_SOURCE_DIR}/src/saw~.c)
add_pd_external(sawblep sawblep~ ${CMAKE_CURRENT_SOURCE_DIR}/src/sawblep~.c)
add_pd_external(square square~ ${CMAKE_CURRENT_SOURCE_DIR}/src/square~.c)
add_pd_external(squareblep squareblep~ ${CMAKE_CURRENT_SOURCE_DIR}/src/squareblep~.c)
add_pd_external(xfade xfade~ ${CMAKE_CURRENT_SOURCE_DIR}/src/xfade~.c)
