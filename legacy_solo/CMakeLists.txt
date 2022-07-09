#----------------------------------------------------------------
# Protobuf Messages
#----------------------------------------------------------------
add_subdirectory(messages)

#----------------------------------------------------------------
# Main Sources
#----------------------------------------------------------------
set(ser_includes
    include/Die.hpp
    include/Combatant.hpp
    include/Utility.hpp
    include/Item.hpp
    include/Weapon.hpp
    include/Armour.hpp
    include/States.hpp
    include/GameLogic.hpp
)

set(ser_sources
    src/Die.cpp
    src/Combatant.cpp
    src/Utility.cpp
    src/Weapon.cpp
    src/Armour.cpp
    src/GameLogic.cpp
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
    PUBLIC
        messages
)

add_executable(runAllTests
    src/all_tests.cpp
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
    PUBLIC
        gtest_main
        messages
)

enable_testing()
add_test(GTest runAllTests)
