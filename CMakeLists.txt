cmake_minimum_required(VERSION 3.21)

project("SFMLTest")
FILE(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/images"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)


# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
add_executable(main main.cpp App.hpp App.cpp Objects.hpp Objects.cpp)
target_link_libraries(main sfml-graphics)
