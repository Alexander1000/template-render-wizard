cmake_minimum_required(VERSION 3.7)

project(template-render-wizard)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(TRW_SHARED_SOURCES
    src/trw/config.cpp
    src/trw/position.cpp
    src/trw/lexer/lexer.cpp
    src/trw/lexer/char_stack.cpp
    src/trw/lexer/get_next_token_include_mode.cpp
    src/trw/lexer/get_next_token_include_with_mode.cpp
    src/trw/lexer/get_next_token_include_with_value_mode.cpp
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
    src/trw/tokens/comma.cpp
    src/trw/tokens/math_operation_high_priority.cpp
    src/trw/tokens/file_path.cpp
    src/trw/tokens/double_dot.cpp
    src/trw/tokens/open_brace.cpp
    src/trw/tokens/close_brace.cpp
    src/trw/tokens/include_with_key.cpp
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
    src/trw/render/to_buffer_tree.cpp
    src/trw/render/render_tree.cpp
    src/trw/render/calc_bool_expr.cpp
    src/trw/render/render_tree_include.cpp
    src/trw/render/calc_expr_tree_term.cpp
    src/trw/render/calc_expr_tree_factor.cpp
    src/trw/render/create_context_for_include_stmt.cpp
    src/trw/value.cpp
    src/trw/value/cast_value_to_int.cpp
    src/trw/value/cast_value_to_bool.cpp
    src/trw/expression.cpp
    src/trw/utils/ctype_digits.cpp
    src/trw/utils/explode_string.cpp
    src/trw/utils/file_exists.cpp
    src/trw/utils/merge_buffers.cpp
    src/trw/utils/merge_context.cpp
    src/trw/syntax/syntax.cpp
    src/trw/syntax/tree.cpp
    src/trw/syntax/parse.cpp
    src/trw/context.cpp
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

find_library(SYNTAX_TREE_LIB libsyntax-tree-lib.a)
message(STATUS "Found syntax-tree library: ${SYNTAX_TREE_LIB}")

add_executable(
    ${PROJECT_NAME} src/main.cpp
    ${TRW_SOURCES}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
    ${YAML_PARSER}
    ${SYNTAX_TREE_LIB}
)

#############
### TESTS ###
#############

project(template-render-wizard-test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(TRW_SOURCES_TEST
    tests/src/main.cpp
    ${TRW_SHARED_SOURCES}
    tests/src/helpers.cpp
    tests/src/asserts.cpp
    tests/src/test-suites/render-tests.cpp
    tests/src/test-suites/parse-token-template.cpp
    tests/src/test-suites/explode-string.cpp
    tests/src/test-suites/tree-tests.cpp
    tests/src/test-suites/check-changelog-version.cpp
)

include_directories(
    include
    tests/include
    /usr/local/include
)

find_library(CPP_UNIT_TEST libcpp-unit-test.a)
message(STATUS "Found cpp-unit-test: ${CPP_UNIT_TEST}")

add_executable(
    ${PROJECT_NAME} tests/src/main.cpp
    ${TRW_SOURCES_TEST}
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    ${IO_BUFFER}
    ${YAML_PARSER}
    ${CPP_UNIT_TEST}
    ${SYNTAX_TREE_LIB}
)
