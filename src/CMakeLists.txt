cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -fsanitize=address,leak,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# ==== Compiler Flags ====
include(CheckCXXCompilerFlag)

# Enable march=native if available
check_cxx_compiler_flag(-march=native HAS_MARCH_NATIVE)
if (HAS_MARCH_NATIVE)
  target_compile_options(${PROJECT_NAME} INTERFACE -march=native)
endif()

# Non compatible compile flags
check_cxx_compiler_flag(-static-libsan HAS_LIBSAN)
if (HAS_LIBSAN)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -static-libsan")
else()
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -static-libasan")
endif()

# ==== Example target ====
add_executable(finedex_example example.cpp)

# Add intel mkl
find_package(MKL CONFIG REQUIRED)
target_compile_options(finedex_example PUBLIC $<TARGET_PROPERTY:MKL::MKL,INTERFACE_COMPILE_OPTIONS>)
target_link_libraries(finedex_example ${PROJECT_NAME} $<LINK_ONLY:MKL::MKL>)