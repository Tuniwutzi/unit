########################### GTEST
# Enable ExternalProject CMake module
INCLUDE(ExternalProject)

set(INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/deps/gtest")

set(GTEST_LIBRARIES
${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtestd${CMAKE_STATIC_LIBRARY_SUFFIX}
${INSTALL_DIR}/lib/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_maind${CMAKE_STATIC_LIBRARY_SUFFIX})

# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
ExternalProject_Add(
    googletest_external
    GIT_REPOSITORY https://github.com/google/googletest.git
    UPDATE_COMMAND ""
    # TIMEOUT 10
    # # Force separate output paths for debug and release builds to allow easy
    # # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    # CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
    #            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
    #            -Dgtest_force_shared_crt=ON
    # Disable install step
    # INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}" "-Dgtest_force_shared_crt=On"
    BUILD_BYPRODUCTS ${GTEST_LIBRARIES}
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# Specify include dir
set(GTEST_INCLUDE_DIR ${INSTALL_DIR}/include)
message(STATUS "GTEST INCLUDE DIR ${GTEST_INCLUDE_DIR}")

# Library
message(STATUS "GTEST LIB PATH ${GTEST_LIBRARIES}")

set(GTEST_IMPORTED_LIBRARY gtest_imported)
add_library(${GTEST_IMPORTED_LIBRARY} STATIC IMPORTED GLOBAL)
set_property(TARGET ${GTEST_IMPORTED_LIBRARY} PROPERTY IMPORTED_LOCATION
                ${GTEST_LIBRARIES} )
add_dependencies(${GTEST_IMPORTED_LIBRARY} googletest_external)

set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} INTERFACE)
target_include_directories(${GTEST_LIBRARY} INTERFACE ${GTEST_INCLUDE_DIR})
target_link_libraries(${GTEST_LIBRARY} INTERFACE ${GTEST_LIBRARIES})
add_dependencies(${GTEST_LIBRARY} ${GTEST_IMPORTED_LIBRARY})
