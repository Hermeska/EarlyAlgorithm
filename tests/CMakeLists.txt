set(TestSources main_test.cpp grammar_test.cpp earley_tests.cpp)

find_package(GTest CONFIG)
if (GTest_FOUND)
    message("GTest found locally.\n")
    add_executable(CTest ${TestSources})
    target_link_libraries(CTest PUBLIC lib GTest::gtest GTest::gtest_main)
    target_link_libraries(CTest PUBLIC GTest::gmock GTest::gmock_main)
    include(GoogleTest)
    gtest_discover_tests(CTest)
else ()
    message("GTest not found locally. Downloading from repo ...\n")
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.11.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(CTest ${TestSources})
    target_link_libraries(CTest PUBLIC lib gtest gtest_main)
    target_link_libraries(CTest PUBLIC gmock gmock_main)
    include(GoogleTest)
    gtest_discover_tests(CTest)
endif ()

if (TEST_COVERAGE)
    message("Configuring coverage...\n")
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
    if (CMAKE_COMPILER_IS_GNUCXX)
        include(CodeCoverage)
        append_coverage_compiler_flags()
        setup_target_for_coverage_lcov(
                NAME coverage
                EXECUTABLE CTest
                EXCLUDE "${CMAKE_SOURCE_DIR}/tests/*"
                         "${CMAKE_SOURCE_DIR}/main.cpp"
                         "${CMAKE_SOURCE_DIR}/build/*"
                        "/usr/include/*"
        )
    endif ()
endif ()