cmake_minimum_required(VERSION 3.2)

project(key_myself)

include_directories(
    "./include/"
)

# add_executable(keysound src/main.cpp src/Audio.cpp)

set(PLATFORM_LIBS pthread ${CMAKE_DL_LIBS})
add_executable(test_ src/test.cpp)
target_link_libraries(test_  ${PLATFORM_LIBS})