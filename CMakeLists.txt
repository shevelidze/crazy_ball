cmake_minimum_required(VERSION 3.21)

project("SFMLTest")

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(main main.cpp Animation.hpp Animation.cpp SunAnimation.cpp SunAnimation.hpp)
target_link_libraries(main sfml-graphics)