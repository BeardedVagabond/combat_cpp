#----------------------------------------------------------------
# Protobuf Messages
#----------------------------------------------------------------
add_subdirectory(messages)

#----------------------------------------------------------------
# Main Sources
#----------------------------------------------------------------
set(common_includes
    include/Combatant.hpp
    include/States.hpp
    include/GameLogic.hpp
)

set(common_sources
    src/Combatant.cpp
    src/GameLogic.cpp
)

#----------------------------------------------------------------
# Executables
#----------------------------------------------------------------
add_executable(solo_combat
    src/main.cpp
    ${common_sources}
)

target_compile_features(solo_combat
    PRIVATE
        cxx_std_17
)

target_include_directories(solo_combat
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(solo_combat
    PUBLIC
        messages
        bv_combat_core
)

add_executable(solo_combat_tests
    src/all_tests.cpp
    ${common_sources}
)

target_compile_features(solo_combat_tests
    PRIVATE
        cxx_std_17
)

target_include_directories(solo_combat_tests
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(solo_combat_tests
    PUBLIC
        gtest_main
        messages
        bv_combat_core
)

enable_testing()
add_test(GTest solo_combat_tests)
