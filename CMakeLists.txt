cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(template-render-wizard)

set(TRW_SOURCES
    src/main.cpp
)

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

find_library(YAML_PARSER libyaml-parser.a)
message(STATUS "Found yaml-parser library: ${YAML_PARSER}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${TRW_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
    ${YAML_PARSER}
)
