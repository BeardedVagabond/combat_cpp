cmake_minimum_required(VERSION 3.21)
project(combat_cpp VERSION 0.1.0 LANGUAGES CXX)
enable_testing()

#----------------------------------------------------------------
# Set compiler flags 
# (modified from fmtlib: https://github.com/fmtlib/fmt/blob/master/CMakeLists.txt)
#----------------------------------------------------------------
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(PEDANTIC_COMPILE_FLAGS -pedantic-errors -Wall -Wextra -pedantic
      -Wold-style-cast -Wundef
      -Wredundant-decls -Wwrite-strings -Wpointer-arith
      -Wcast-qual -Wformat=2 -Wmissing-include-dirs
      -Wcast-align
      -Wctor-dtor-privacy -Wdisabled-optimization
      -Winvalid-pch -Woverloaded-virtual
      -Wconversion -Wundef
      -Wno-ctor-dtor-privacy -Wno-format-nonliteral)
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.6)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
         -Wno-dangling-else -Wno-unused-local-typedefs)
  endif ()
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.0)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wdouble-promotion
          -Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast
          -Wvector-operation-performance -Wsized-deallocation -Wshadow)
  endif ()
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.0)
      set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS} -Wshift-overflow=2
          -Wnull-dereference -Wduplicated-cond)
  endif ()
endif ()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(PEDANTIC_COMPILE_FLAGS -Wall -Wextra -pedantic -Wconversion -Wundef
      -Wdeprecated -Wweak-vtables -Wshadow
      -Wno-gnu-zero-variadic-macro-arguments)
  check_cxx_compiler_flag(-Wzero-as-null-pointer-constant HAS_NULLPTR_WARNING)
  if (HAS_NULLPTR_WARNING)
    set(PEDANTIC_COMPILE_FLAGS ${PEDANTIC_COMPILE_FLAGS}
        -Wzero-as-null-pointer-constant)
  endif ()
endif ()

if (MSVC)
    set(PEDANTIC_COMPILE_FLAGS /W3)
endif ()

#----------------------------------------------------------------
# Add messages library
#----------------------------------------------------------------
add_subdirectory(proto)

#----------------------------------------------------------------
# Add main library
#----------------------------------------------------------------
file(GLOB COMBAT_CPP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB COMBAT_CPP_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/combat_cpp/*.hpp")

add_library(${PROJECT_NAME} ${COMBAT_CPP_SOURCES} ${COMBAT_CPP_HEADERS})

target_include_directories(${PROJECT_NAME}  
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_17
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${PEDANTIC_COMPILE_FLAGS}
)

#----------------------------------------------------------------
# Add Apps
#----------------------------------------------------------------
add_subdirectory(app)

#----------------------------------------------------------------
# Add Tests
#----------------------------------------------------------------
add_subdirectory(test)