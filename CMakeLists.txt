cmake_minimum_required(VERSION 3.30)
project(ricerca_percorso)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

set(GTEST_DIR "${CMAKE_SOURCE_DIR}/googletest-main")
if(EXISTS "${GTEST_DIR}/CMakeLists.txt")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory("${GTEST_DIR}" "${CMAKE_BINARY_DIR}/googletest-build" EXCLUDE_FROM_ALL)
    message(STATUS "fatto: collegato gtest")
else()
    message(FATAL_ERROR "ERRORE CRITICO: Cartella GoogleTest non trovata in: ${GTEST_DIR}")
endif()

include_directories(include)
add_executable(main src/main.cpp
                    src/map.cpp
                    src/pg.cpp
                    src/pxcount.cpp
                    src/MapSearchNode.cpp)
add_executable(tests
        tests/test_main.cpp
        src/map.cpp
        src/pg.cpp
        src/pxcount.cpp
        src/MapSearchNode.cpp
        googletest-main/googletest/include/gtest/gtest.h
)



target_link_libraries(main PRIVATE SFML::Graphics)
target_include_directories(tests PRIVATE
        "${GTEST_DIR}/googletest/include"
        "${GTEST_DIR}/googlemock/include"
        "${CMAKE_SOURCE_DIR}"
)

target_link_libraries(tests
        PRIVATE
        gtest
        gtest_main
        SFML::Graphics
)
enable_testing()
add_test(NAME GameTest COMMAND tests)

target_compile_features(main PRIVATE cxx_std_17)
target_compile_features(tests PRIVATE cxx_std_17)