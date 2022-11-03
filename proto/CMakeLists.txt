add_subdirectory(messages)

target_include_directories(messages 
    PUBLIC 
        INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
)