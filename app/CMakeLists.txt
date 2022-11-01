message("-- Configuring applications")
add_executable(exampleMain
    main.cpp
)

target_compile_features(exampleMain
    PRIVATE
        cxx_std_17
)

target_link_libraries(exampleMain
    PUBLIC
        messages
        combat_cpp
)

message("-- DONE configuring application")
