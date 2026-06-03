cmake_minimum_required(VERSION 3.10)
project(RinhaDeBackend2026)
SET(CMAKE_CXX_STANDARD 23)

# Habilitando otimizações de compilação por padrão
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(Rinha2026
        src/main.cpp
        src/kmknn.cpp
        src/vector.cpp
        src/network.cpp
        src/kmeanspp.cpp
        src/cluster.cpp
)


target_include_directories(Rinha2026
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

# Habilitando warnings adicionais
target_compile_options(Rinha2026 PRIVATE -Wall -Wextra -Wpedantic)
