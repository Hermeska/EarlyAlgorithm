set(SOURCES Grammar.cpp InputPolicy.cpp ParserAlgo.cpp EarleyParser.cpp)

add_library(lib ${SOURCES})

if(TEST_COVERAGE)
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()