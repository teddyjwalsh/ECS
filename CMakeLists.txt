cmake_minimum_required (VERSION 2.8.11)
project (ECSengine)

set(generation_src generation/simplex.cpp
                   generation/generator.cpp)

file(GLOB ecs_src "./*.h" "./*.cpp")
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
find_library(glfw glfw3 "./lib64")
add_executable(ecs ${ecs_src} ${generation_src} ${fnsd_src})


target_include_directories(ecs PUBLIC ./)
target_include_directories(ecs PUBLIC ./glad/include)
target_compile_options(ecs PRIVATE "-ggdb")
target_compile_options(ecs PRIVATE "-DGLM_ENABLE_EXPERIMENTAL")
set_property(TARGET ecs PROPERTY CXX_STANDARD 17)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ecs PRIVATE -Wno-psabi)
elseif( "\"${CMAKE_CXX_COMPILER_ID}\"" MATCHES MSVC )
    target_compile_definitions(ecs PUBLIC USE_GLFW)
    target_compile_definitions(ecs PUBLIC FNSD)
    target_link_libraries(ecs ${glfw})
endif()
target_compile_options(ecs PRIVATE "-std=c++17")

