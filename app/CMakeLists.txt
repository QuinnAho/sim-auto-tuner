# <!-- Machine Summary Block -->
# {"file":"app/CMakeLists.txt","purpose":"Defines CMake targets for SimulationAutoTuner application entry points."}

cmake_minimum_required(VERSION 3.23)

set(SAT_APP_TARGET sat_app)
set(SAT_APP_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(${SAT_APP_TARGET} ${SAT_APP_SOURCES})
set_target_properties(${SAT_APP_TARGET} PROPERTIES OUTPUT_NAME "sat_app")

target_link_libraries(${SAT_APP_TARGET}
    PRIVATE
        sat::sim
)

# CLI Test Executable
set(SAT_CLI_TEST_TARGET sat_cli_test)
set(SAT_CLI_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/cli_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/cli_config.cpp
)

find_package(CLI11 CONFIG REQUIRED)

add_executable(${SAT_CLI_TEST_TARGET} ${SAT_CLI_TEST_SOURCES})
set_target_properties(${SAT_CLI_TEST_TARGET} PROPERTIES OUTPUT_NAME "sat_cli_test")

target_link_libraries(${SAT_CLI_TEST_TARGET}
    PRIVATE
        sat::sim
        CLI11::CLI11
)
