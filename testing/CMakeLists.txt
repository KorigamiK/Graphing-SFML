cmake_minimum_required(VERSION 3.14.0)

set(LOCAL_PROJECT_NAME        "MathS")
set(LOCAL_PROJECT_VERSION     "0.0.1")
set(LOCAL_PROJECT_DESCRIPTION "Description")

set (CMAKE_CXX_STANDARD 20)

project(
  ${LOCAL_PROJECT_NAME}
  VERSION ${LOCAL_PROJECT_VERSION}
  DESCRIPTION ${LOCAL_PROJECT_DESCRIPTION}
  LANGUAGES CXX
)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${LOCAL_PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${LOCAL_PROJECT_VERSION})

# Header files (relative to "include" directory)
set(HEADERS
    header.h
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
)

# Compiler definitions
set(DEFINES

)

# Compiler options
set(OPTIONS

)

list(TRANSFORM HEADERS PREPEND "include/")
list(TRANSFORM SOURCES PREPEND "src/")

SET( CMAKE_EXE_LINKER_FLAGS   "-L/usr/local/lib")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" -std=c++18)

add_executable(${LOCAL_PROJECT_NAME})

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)
find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
find_package(Eigen3 REQUIRED)

target_include_directories(${LOCAL_PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include 
  ${EIGEN3_INCLUDE_DIR}
  ${SFML_INCLUDE_DIR}
)

target_sources(${LOCAL_PROJECT_NAME} PUBLIC ${SOURCES} ${HEADERS})

target_link_directories(${LOCAL_PROJECT_NAME} PUBLIC
)

target_link_libraries(${LOCAL_PROJECT_NAME}
  ${OPENGL_LIBRARIES}
  ${SFML_LIBRARIES}
)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/")

target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

include(CPack)
