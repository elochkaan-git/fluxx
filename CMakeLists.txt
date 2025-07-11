cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Включение библиотеки для парсинга json-файлов
FetchContent_Declare(json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)


# Set properties that will be used while building TGUI
set(BUILD_SHARED_LIBS OFF)      # Determines whether TGUI build a static or dynamic/shared library
set(TGUI_BACKEND SFML_GRAPHICS)  # Sets which backend TGUI will use

FetchContent_Declare(
  TGUI
  GIT_REPOSITORY https://github.com/texus/TGUI
  GIT_TAG v1.10.0  # Change this to wanted version
)
FetchContent_MakeAvailable(TGUI)

# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
# )
# FetchContent_MakeAvailable(googletest)

    
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_executable(main ${SOURCES})
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics TGUI::TGUI nlohmann_json::nlohmann_json)

# enable_testing()
# add_executable(testing ${TEST_SOURCES})
# set_target_properties(testing PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests)
# target_link_libraries(testing GTest::gtest_main SFML::Graphics nlohmann_json::nlohmann_json)
# include(GoogleTest)
# gtest_discover_tests(testing)
