# <!-- Machine Summary Block -->
# {"file":"sim/CMakeLists.txt","purpose":"Holds core simulation library target configuration."}

cmake_minimum_required(VERSION 3.23)

set(SAT_SIM_TARGET sat_sim_core)
set(SAT_SIM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/logging.cpp
)

add_library(${SAT_SIM_TARGET} ${SAT_SIM_SOURCES})
add_library(sat::sim ALIAS ${SAT_SIM_TARGET})

target_include_directories(${SAT_SIM_TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

target_link_libraries(${SAT_SIM_TARGET}
    PUBLIC
        spdlog::spdlog
        fmt::fmt
)
