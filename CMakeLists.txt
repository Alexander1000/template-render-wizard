cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(template-render-wizard)

set(TRW_SHARED_SOURCES
    src/trw/config.cpp
    src/trw/position.cpp
    src/trw/stream.cpp
    src/trw/tokens/token.cpp
    src/trw/tokens/open_tag_value.cpp
    src/trw/tokens/plain_text.cpp
    src/trw/tokens/close_tag_value.cpp
    src/trw/tokens/plain_value.cpp
    src/trw/tokens/open_control_tag.cpp
    src/trw/tokens/close_control_tag.cpp
    src/trw/tokens/keyword.cpp
    src/trw/tokens/round_bracket_open.cpp
    src/trw/tokens/round_bracket_close.cpp
    src/trw/tokens/compare.cpp
    src/trw/tokens/math_operation.cpp
    src/trw/tokens/expression_value.cpp
    src/trw/tokens/token_map.cpp
    src/trw/leaf_element.cpp
    src/trw/tree_parameters.cpp
    src/trw/render/construct.cpp
    src/trw/render/get_value_from_syntax_element.cpp
    src/trw/render/render.cpp
    src/trw/render/token_stack.cpp
    src/trw/render/get_value_from_token.cpp
    src/trw/render/calc_expr.cpp
    src/trw/render/to_buffer_plain_text.cpp
    src/trw/render/to_buffer_value.cpp
    src/trw/render/render_if_expression.cpp
    src/trw/value.cpp
    src/trw/value/cast_value_to_int.cpp
    src/trw/value/cast_value_to_bool.cpp
    src/trw/expression.cpp
    src/trw/utils/ctype_digits.cpp
    src/trw/syntax/syntax.cpp
)

set(TRW_SOURCES
    src/main.cpp
    ${TRW_SHARED_SOURCES}
)

include_directories(
    include
    /usr/local/include
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

#############
### TESTS ###
#############

project(template-render-wizard-test)

set(CMAKE_BUILD_TYPE Debug)

set(TRW_SOURCES_TEST
    tests/main.cpp
    ${TRW_SHARED_SOURCES}
)

include_directories(
    include
    /usr/local/include
)

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

add_executable(
    ${PROJECT_NAME} tests/main.cpp
    ${TRW_SOURCES_TEST}
)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
    ${YAML_PARSER}
    ${CPP_UNIT_TEST}
)
