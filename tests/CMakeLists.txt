add_executable(TraceTests
    LoggerTests.cpp
)

target_link_libraries(TraceTests PRIVATE
    gtest_main
    TraceCore
)

target_include_directories(TraceTests PRIVATE
    ${CMAKE_SOURCE_DIR}/Core/src
)

include(GoogleTest)
gtest_discover_tests(TraceTests)