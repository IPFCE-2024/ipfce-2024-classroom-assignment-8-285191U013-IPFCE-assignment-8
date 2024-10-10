cmake_minimum_required(VERSION 3.16)
project(assignment-8 VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20) # Needed to use designated initializers in ./tests/tests.cpp
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  		GIT_TAG        v3.6.0 # Newest release as of 12-10-2024
)

FetchContent_MakeAvailable(Catch2)

add_library(insertion_sort STATIC insertion_sort.c)
add_library(queue STATIC queue.c)

set(libs insertion_sort queue)

foreach(lib ${libs})
	target_compile_definitions(${lib} PUBLIC -DTEST)
	target_compile_options(${lib}
		PUBLIC
		$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall -Wpedantic>
	)
endforeach()

add_executable(unit-tests tests/tests.cpp)
target_include_directories(unit-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(unit-tests ${libs})
target_link_libraries(unit-tests Catch2::Catch2WithMain)
