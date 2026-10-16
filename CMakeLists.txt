cmake_minimum_required(VERSION 3.14)
project(HousingManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB_RECURSE MODEL_SOURCES
    src/model/entity/*.cpp
    src/model/repository/*.cpp
    src/model/service/*.cpp
    src/view/*.cpp
    src/controller/*.cpp
)

add_library(HousingManagementSystem_lib STATIC ${MODEL_SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(HousingManagementSystem_lib PRIVATE Threads::Threads)

add_executable(${PROJECT_NAME} app/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE HousingManagementSystem_lib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(tests)cmake_minimum_required(VERSION 3.14)
project(HousingManagementSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

file(GLOB_RECURSE MODEL_SOURCES
    src/model/entity/*.cpp
    src/model/repository/*.cpp
    src/model/service/*.cpp
    src/view/*.cpp
    src/controller/*.cpp
)

add_library(HousingManagementSystem_lib STATIC ${MODEL_SOURCES})

find_package(Threads REQUIRED)
target_link_libraries(HousingManagementSystem_lib PRIVATE Threads::Threads)

add_executable(${PROJECT_NAME} app/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE HousingManagementSystem_lib)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(tests)
