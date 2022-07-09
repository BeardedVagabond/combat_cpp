file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(bv_combat_core ${srcs})

target_include_directories(bv_combat_core 
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
