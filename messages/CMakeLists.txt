cmake_minimum_required(VERSION 3.10)

# REF: https://stackoverflow.com/a/20825093

message("-- Beginning Protofile Generation")

file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message("Generating proto files for: ${ProtoFiles}")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})
message("Generated ProtoHeaders: ${ProtoHeaders}")
message("Generated ProtoSources: ${ProtoSources}")

add_library(messages STATIC ${ProtoSources} ${ProtoHeaders})
target_link_libraries(messages 
    PUBLIC
        protobuf::libprotoc 
        protobuf::libprotobuf
)
target_include_directories(messages 
    PUBLIC 
        INTERFACE ${CMAKE_CURRENT_BINARY_DIR}
)

message("-- Protofile Generation done")
