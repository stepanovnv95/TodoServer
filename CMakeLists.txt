cmake_minimum_required(VERSION 3.5)

project(TodoServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(proxygen CONFIG REQUIRED)

set(AppTarget TodoServer)
add_executable(${AppTarget}
    HelloHandler.cpp
    HelloHandler.h
    HelloHandlerFactory.cpp
    HelloHandlerFactory.h
    main.cpp
)

target_link_libraries(${AppTarget} PRIVATE proxygen::proxygen proxygen::proxygenhttpserver)
