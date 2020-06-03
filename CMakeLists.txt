cmake_minimum_required (VERSION 2.8.11)
project (ECSengine)

set(generation_src generation/simplex.cpp
                   generation/generator.cpp)

file(GLOB ecs_src "./*.h" "./*.cpp")
set(glad_src "./glad/src/glad.c")
set(fnsd_src)

if( "\"${CMAKE_CXX_COMPILER_ID}\"" MATCHES MSVC )
	set(fnsd_src generation/FastNoiseSIMD/FastNoiseSIMD.cpp
			 generation/FastNoiseSIMD/FastNoiseSIMD_avx2.cpp
			 generation/FastNoiseSIMD/FastNoiseSIMD_internal.cpp
			 generation/FastNoiseSIMD/FastNoiseSIMD_neon.cpp
			 generation/FastNoiseSIMD/FastNoiseSIMD_sse2.cpp
			 generation/FastNoiseSIMD/FastNoiseSIMD_sse41.cpp)
endif()

link_directories("./lib64")
add_executable(ecs ${ecs_src} ${generation_src} ${fnsd_src} ${glad_src})


target_include_directories(ecs PUBLIC ./)
target_include_directories(ecs PUBLIC ./ugli/include)
target_include_directories(ecs PUBLIC ./glad/include)
target_compile_options(ecs PRIVATE "-ggdb")
target_compile_options(ecs PRIVATE "-DGLM_ENABLE_EXPERIMENTAL")
target_compile_options(ecs PRIVATE "-DLOADBMP_IMPLEMENTATION")
set_property(TARGET ecs PROPERTY CXX_STANDARD 17)
target_compile_definitions(ecs PUBLIC USE_GLFW)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ecs PRIVATE -Wno-psabi)
    find_library(glfw glfw)
    target_link_libraries(ecs ${glfw})
    find_library(dl dl)
    target_link_libraries(ecs ${dl})
elseif( "\"${CMAKE_CXX_COMPILER_ID}\"" MATCHES MSVC )
    find_library(glfw glfw3 "./lib64")
    target_compile_definitions(ecs PUBLIC FNSD)
    target_link_libraries(ecs ${glfw})
endif()
target_compile_options(ecs PRIVATE "-std=c++17")

