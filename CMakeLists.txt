cmake_minimum_required(VERSION 3.1)
project(cpp-async VERSION 1.0.0)

find_package (Threads REQUIRED)

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
    main.cpp
    CurlGet.cpp)

target_link_libraries(${PROJECT_NAME}
    Threads::Threads
    ${CURL_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CURL_INCLUDE_DIR})
