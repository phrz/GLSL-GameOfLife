cmake_minimum_required (VERSION 3.8)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project (lifefade)

include_directories("${PROJECT_BINARY_DIR}")

set(EXECUTABLE_NAME "lifefade")
add_executable(${EXECUTABLE_NAME} src/main.cpp src/ColorMapper.cpp src/ImageFader.cpp src/LifeIterator.cpp src/Shaders.cpp)

target_compile_features(lifefade PRIVATE cxx_std_17)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 REQUIRED graphics window system) 

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# fmtlib/fmt
# http://fmtlib.net/latest/usage.html
add_subdirectory(lib/fmt EXCLUDE_FROM_ALL)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE fmt::fmt-header-only)


install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


