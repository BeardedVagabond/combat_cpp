message("-- Configuring applications")
add_executable(main_game
    main.cpp
)

target_compile_features(main_game
    PRIVATE
        cxx_std_17
)

target_link_libraries(main_game
    PRIVATE
        combat_cpp
)

message("-- DONE configuring application")
