cmake_minimum_required (VERSION 2.8.11)
project (ECS)

set(generation_src generation/simplex.cpp
                   generation/generator.cpp)

# -std=c++2a -ggdb -Wno-psabi -DGLM_ENABLE_EXPERIMENTAL -Wsuggest-override 
add_executable(ecs main.cpp ${generation_src})

target_include_directories(ecs PUBLIC ./)
target_compile_options(ecs PRIVATE "-ggdb")
target_compile_options(ecs PRIVATE "-DGLM_ENABLE_EXPERIMENTAL")
target_compile_options(ecs PRIVATE "-Wno-psabi")
target_compile_options(ecs PRIVATE "-std=c++17")

