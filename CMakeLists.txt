cmake_minimum_required(VERSION 3.22)
project(WeatherStatistics)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
include_directories(src)

set(SRC
    src/WeatherStatistics.cpp
)

set(FLAGS
    -Wall
    -pedantic
    -Wconversion
    -Wextra
)

add_library(${PROJECT_NAME}-lib STATIC ${SRC})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})