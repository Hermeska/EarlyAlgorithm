cmake_minimum_required(VERSION 3.21)
project(Parsing)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Wextra -gdwarf-4")

option(ENABLE_TESTING "enable google tests" ON)
option(TEST_COVERAGE "generate coverage files" ON)

set(SOURCES main.cpp)

add_executable(main ${SOURCES})

include_directories(include)

add_subdirectory(src)

target_link_libraries(main lib)

if(TEST_COVERAGE)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
    if(CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        append_coverage_compiler_flags()
    endif()
endif()

if(ENABLE_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

