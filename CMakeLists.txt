cmake_minimum_required(VERSION 3.5)

project(QDevTool VERSION 0.1 LANGUAGES CXX)

file(GLOB_RECURSE RESOURCES resources)
file(GLOB_RECURSE RESOURCES config)

file(COPY config/ DESTINATION ${PROJECT_BINARY_DIR}/bin/config)

add_subdirectory(src ${PROJECT_BINARY_DIR}/bin)
#install(PROGRAMS )
install(DIRECTORY ./resources ./config DESTINATION ${CMAKE_INSTALL_PREFIX}/)
