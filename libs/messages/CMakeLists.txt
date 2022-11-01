message("-- Beginning Protofile Generation")
find_package(protobuf CONFIG REQUIRED)

file(GLOB ProtoFiles "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message("Generating proto files for: ${ProtoFiles}")
PROTOBUF_GENERATE_CPP(ProtoSources ProtoHeaders ${ProtoFiles})

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
target_compile_features(messages
    PRIVATE
        cxx_std_17
)

message("-- Protofile Generation done")
