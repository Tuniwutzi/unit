cmake_minimum_required(VERSION 3.15)

set(TARGET unit_tests)

set(SRC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(gtest)

add_executable(
    ${TARGET}
    "${SRC}/UnitBaseTests.cpp"
)

target_link_libraries(${TARGET} unit gtest)
