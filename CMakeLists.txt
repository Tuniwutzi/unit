cmake_minimum_required(VERSION 3.15)

project(cpp-unit)

option(CONFIGURE_TESTS "Configure test target" On)

set(TARGET unit)

add_library(${TARGET} INTERFACE)
target_include_directories(
    ${TARGET}
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
    ${TARGET}
    PROPERTIES
        PUBLIC_HEADER "${CMAKE_CURRENT_SOURCE_DIR}/jb/unit.hpp"
)

target_compile_features(
    ${TARGET}
    INTERFACE
        cxx_std_17
)

if(${CONFIGURE_TESTS})
    add_subdirectory(tests)
endif()

install(TARGETS ${TARGET} PUBLIC_HEADER DESTINATION "include/jb")
