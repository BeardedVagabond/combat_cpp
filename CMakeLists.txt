cmake_minimum_required(VERSION 3.21)
project(combat_cpp VERSION 0.1.0 LANGUAGES CXX)

#----------------------------------------------------------------
# Packages
#----------------------------------------------------------------
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-DCMAKE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

#----------------------------------------------------------------
# GTest 
#----------------------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY    https://github.com/google/googletest.git
    GIT_TAG           main
)
FetchContent_MakeAvailable(gtest)

#----------------------------------------------------------------
# Protobuf Messages
#----------------------------------------------------------------
add_subdirectory(messages)

#----------------------------------------------------------------
# Create A Library
#----------------------------------------------------------------
file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} SHARED ${sources})

target_include_directories(${PROJECT_NAME}  
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

#----------------------------------------------------------------
# Add Apps
#----------------------------------------------------------------
add_subdirectory(app)

#----------------------------------------------------------------
# Add Tests
#----------------------------------------------------------------
add_subdirectory(test)