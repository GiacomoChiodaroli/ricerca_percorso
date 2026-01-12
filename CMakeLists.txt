cmake_minimum_required(VERSION 3.30)
project(ricerca_percorso)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(include)
add_executable(main src/main.cpp
                    src/map.cpp
                    src/pg.cpp
                    src/pxcount.cpp
                    src/MapSearchNode.cpp)



target_link_libraries(main PRIVATE SFML::Graphics)
target_compile_features(main PRIVATE cxx_std_17)