cmake_minimum_required(VERSION 3.21)
project(combat_cpp VERSION 0.1.0 LANGUAGES CXX)
enable_testing()

#----------------------------------------------------------------
# Add messages library
#----------------------------------------------------------------
add_subdirectory(proto)

#----------------------------------------------------------------
# Add main library
#----------------------------------------------------------------
file(GLOB COMBAT_CPP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB COMBAT_CPP_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/combat_cpp/*.hpp")

add_library(${PROJECT_NAME} STATIC ${COMBAT_CPP_SOURCES} ${COMBAT_CPP_HEADERS})

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