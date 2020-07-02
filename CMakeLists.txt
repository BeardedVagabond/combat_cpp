cmake_minimum_required(VERSION 3.10)
project(combat_cpp VERSION 0.1.0 LANGUAGES CXX)


#----------------------------------------------------------------
# Packages
#----------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DCMAKE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")


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

target_link_libraries(exampleMain
    PRIVATE      
)
