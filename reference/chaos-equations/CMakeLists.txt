cmake_minimum_required(VERSION 3.14.0)

set(LOCAL_PROJECT_NAME        "chaos-equations")
set(LOCAL_PROJECT_VERSION     "0.0.1")
set(LOCAL_PROJECT_DESCRIPTION "Description")

set (CMAKE_CXX_STANDARD 20)

project(
  ${LOCAL_PROJECT_NAME}
  VERSION ${LOCAL_PROJECT_VERSION}
  DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
  LANGUAGES CXX
)

# Compiler definitions
set(DEFINES
)

# Compiler options
set(OPTIONS
)

set (CMAKE_CXX_STANDARD 20)

add_executable(${LOCAL_PROJECT_NAME} Main.cpp)

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS graphics window system)

target_include_directories(${LOCAL_PROJECT_NAME} PUBLIC
  ${SFML_INCLUDE_DIR}
)

target_link_directories(${LOCAL_PROJECT_NAME} PUBLIC
)

target_link_libraries(${LOCAL_PROJECT_NAME}
  sfml-graphics
  sfml-system
  sfml-window
  ${OPENGL_LIBRARIES}
)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/")

target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Roboto-Regular.ttf
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

message(STATUS "SFML library status:")
message(STATUS "    version: ${SFML_VERSION}")
message(STATUS "    libraries:   ${SFML_LIBRARIES}")
message(STATUS "    include path: ${SFML_INCLUDE_DIR}")

