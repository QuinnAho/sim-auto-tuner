#
# <!-- Machine Summary Block -->
# {"file":"CMakeLists.txt","purpose":"Modernizes the SimulationAutoTuner root build to add presets-aware targets while preserving legacy Jet modules.","notes":["milestone_0_phase_3"]}
#
cmake_minimum_required(VERSION 3.25)

project(SimulationAutoTuner
    VERSION 0.1.0
    DESCRIPTION "Modern fluid simulation toolkit with AI-assisted tuning"
    LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external")
set(SAT_ENABLE_LEGACY_SRC ON CACHE BOOL "Build legacy Jet modules under src/")
option(SAT_ENABLE_PYTHON_BINDINGS "Build pybind11-based Python bindings" OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()

set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# NOTE: Only add include paths here that are needed globally for legacy Jet code
# New SAT code (sim/, app/) should use target_include_directories instead
include_directories(external)
include_directories(external/pybind11/include)
include_directories(external/Clara/include)
include_directories(external/tinyobj)
include_directories(src/examples)

# Disable -Werror for legacy Jet code (has warnings with modern compilers)
set(JET_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat warnings as errors in legacy code" FORCE)

include(cmake/TaskingSystemOptions.cmake)
include(cmake/CompileOptions.cmake)

option(BUILD_COVERAGE "Build code coverage" OFF)
if (CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage unit_tests coverage)
endif()

set(CMAKE_MACOSX_RPATH ON)

set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
set(RESOURCES_OBJS
        ${RESOURCES_DIR}/bunny.obj
        ${RESOURCES_DIR}/cube.obj
        ${RESOURCES_DIR}/cup.obj
        ${RESOURCES_DIR}/dragon.obj)
set(unzip_py ${CMAKE_CURRENT_SOURCE_DIR}/scripts/unzip.py)
add_custom_command(
        COMMAND python ${unzip_py} ${RESOURCES_DIR}/resources.zip ${RESOURCES_DIR}
        DEPENDS ${headers}
        OUTPUT ${RESOURCES_OBJS})
add_custom_target(unzip_py ALL
        DEPENDS ${RESOURCES_OBJS})

add_subdirectory(sim)
add_subdirectory(app)
add_subdirectory(tests)
add_subdirectory(bench)

if (SAT_ENABLE_LEGACY_SRC)
    set(BUILD_GTEST ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(gtest_disable_pthreads OFF CACHE BOOL "" FORCE)
    # Disable -Werror in googletest to avoid build failures with modern compilers
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/googletest/CMakeLists.txt")
        add_subdirectory(external/googletest EXCLUDE_FROM_ALL)
    else()
        message(WARNING "Skipping googletest (external/googletest missing or not initialized)")
    endif()
    if ((CMAKE_VERSION VERSION_EQUAL 3.3) OR (CMAKE_VERSION VERSION_GREATER 3.3))
        cmake_policy(SET CMP0063 NEW)
    endif()
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/googlebenchmark/CMakeLists.txt")
        add_subdirectory(external/googlebenchmark)
    else()
        message(WARNING "Skipping googlebenchmark (external/googlebenchmark missing or not initialized)")
    endif()
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
    # Add legacy Jet include path (only for legacy src/ code, not new SAT code)
    include_directories(include)
    foreach(_legacy_dir
            external/cnpy
            external/pystring
            src/jet
            src/tests/manual_tests
            src/tests/mem_perf_tests
            src/tests/time_perf_tests
            src/tests/unit_tests
            src/examples/hello_fluid_sim
            src/examples/hybrid_liquid_sim
            src/examples/level_set_liquid_sim
            src/examples/obj2sdf
            src/examples/particles2obj
            src/examples/particles2xml
            src/examples/smoke_sim
            src/examples/sph_sim
            src/examples/playground)
        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_legacy_dir}/CMakeLists.txt")
            add_subdirectory(${_legacy_dir})
        else()
            message(WARNING "Skipping ${_legacy_dir} (CMakeLists.txt missing)")
        endif()
    endforeach()

    if (SAT_ENABLE_PYTHON_BINDINGS)
        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/external/pybind11/CMakeLists.txt")
            add_subdirectory(external/pybind11)
            if (BUILD_FROM_PIP)
                set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY})
            endif()
            if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/python/CMakeLists.txt")
                add_subdirectory(src/python)
            else()
                message(WARNING "Skipping src/python (CMakeLists.txt missing)")
            endif()
        else()
            message(WARNING "Skipping pybind11 and python bindings (external/pybind11 missing)")
        endif()
    else()
        message(STATUS "SAT_ENABLE_PYTHON_BINDINGS=OFF; skipping pybind11/python targets")
    endif()
endif()
