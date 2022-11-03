message("-- Beginning Protofile Generation")
find_package(protobuf CONFIG REQUIRED)

file(GLOB PROTO_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.proto")
message("Generating proto files for: ${PROTO_FILES}")
PROTOBUF_GENERATE_CPP(PROTO_SOURCES PROTO_HEADERS ${PROTO_FILES})

add_library(messages STATIC ${PROTO_SOURCES} ${PROTO_HEADERS})
target_link_libraries(messages 
    PUBLIC
        protobuf::libprotoc 
        protobuf::libprotobuf
)
target_compile_features(messages
    PRIVATE
        cxx_std_17
)

message("-- Protofile Generation done")
