cmake_minimum_required(VERSION 3.19)

project(tictactoe VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
if (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=13.0")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

find_package(SFML COMPONENTS system window graphics network audio CONFIG REQUIRED)
set(SFML_LIBRARIES sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

include(cmake/SourcesAndHeaders.cmake)
include(cmake/StandardSettings.cmake)


## build executable

add_executable(${PROJECT_NAME} ${exe_sources})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES})

file(COPY ${CMAKE_SOURCE_DIR}/resource
        DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

## build library
add_library(${PROJECT_NAME}_LIB ${headers} ${sources})
target_include_directories(${PROJECT_NAME}_LIB PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME}_LIB PRIVATE ${SFML_LIBRARIES})

if (${CMAKE_PROJECT_NAME}_ENABLE_CODE_COVERAGE AND NOT WIN32)
  include(CTest)
  target_compile_options(${CMAKE_PROJECT_NAME}_LIB PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(${CMAKE_PROJECT_NAME}_LIB PUBLIC -fprofile-arcs -ftest-coverage)
  message(STATUS "Code coverage is enabled.")
endif()
if(${PROJECT_NAME}_ENABLE_UNIT_TESTING)
  enable_testing()
  message(STATUS "Build unit tests for the project. Tests should always be found in the test folder\n")
  add_subdirectory(test)
endif()

### INSTALL
include(GNUInstallDirs)
install(
  TARGETS
  ${PROJECT_NAME}
  EXPORT
  ${PROJECT_NAME}Targets
  LIBRARY DESTINATION
  ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION
  ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION
  ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}
  PUBLIC_HEADER DESTINATION
  include
)

install(
  EXPORT
  ${PROJECT_NAME}Targets
  FILE
  ${PROJECT_NAME}Targets.cmake
  NAMESPACE
  ${PROJECT_NAME}::
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)