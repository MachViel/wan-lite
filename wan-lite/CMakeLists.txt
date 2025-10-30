cmake_minimum_required(VERSION 3.16)
project(wan-lite C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WANLITE_BUILD_SHARED "Build shared library" OFF)

# 指向本机已有 ggml（无需耦合其他工程）
# 可通过 -DGGML_DIR=/abs/path/to/ggml 覆盖
set(GGML_DIR "/root/ggml/ggml" CACHE PATH "ggml root directory")

if (NOT EXISTS ${GGML_DIR})
    message(FATAL_ERROR "GGML_DIR not found: ${GGML_DIR}")
endif()

add_library(ggml STATIC
    ${GGML_DIR}/src/ggml.c
)

target_include_directories(ggml PUBLIC
    ${GGML_DIR}/include
)

add_executable(wan
    src/wan.cpp
    src/wan_api.cpp
    src/loader_gguf.cpp
    src/text_encoder_umt5.cpp
    src/diffusion_wan22.cpp
    src/vae.cpp
    src/sampler.cpp
)

target_include_directories(wan PRIVATE
    ${GGML_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(wan PRIVATE ggml)

if (UNIX AND NOT APPLE)
    target_link_libraries(wan PRIVATE pthread m)
endif()

# 轻量优化
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(wan PRIVATE NDEBUG)
endif()
