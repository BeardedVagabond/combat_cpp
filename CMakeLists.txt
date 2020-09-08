cmake_minimum_required(VERSION 3.10)
project(combat_cpp VERSION 0.1.0 LANGUAGES CXX)


#----------------------------------------------------------------
# Packages
#----------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DCMAKE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")


#----------------------------------------------------------------
# GTest External Project (from gtest documentation)
# https://bit.ly/3g8iXeM
#----------------------------------------------------------------

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()


#----------------------------------------------------------------
# Main Sources
#----------------------------------------------------------------
set(ser_includes
    include/Die.hpp
    include/Combatant.hpp
    include/Utility.hpp
)

set(ser_sources
    src/Die.cpp
    src/Combatant.cpp
)

set(all_sources
    ${ser_includes}
    ${ser_sources}
)


#----------------------------------------------------------------
# Executables
#----------------------------------------------------------------
add_executable(exampleMain
    src/main.cpp
    ${all_sources}
)

target_compile_features(exampleMain
    PRIVATE
        cxx_std_17
)

target_include_directories(exampleMain
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(runAllTests
    src/runAllTests.cpp
    ${all_sources}
)

target_compile_features(runAllTests
    PRIVATE
        cxx_std_17
)

target_include_directories(runAllTests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(runAllTests
    gtest_main
)

