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

set (CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${LOCAL_PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${LOCAL_PROJECT_VERSION})

# Header files (relative to "include" directory)
set(HEADERS
    app.hpp
    drawUtil.hpp
    userInteraction.hpp
    Objects/TextBox.hpp
)

# Source files (relative to "src" directory)
set(SOURCES
    main.cpp
    app.cpp
    drawUtil.cpp
    userInteraction.cpp
    Objects/TextBox.cpp
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

add_executable(${LOCAL_PROJECT_NAME})

set(OpenGL_GL_PREFERENCE "GLVND")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

if (WIN32)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(SFML_DIR "C:\\msys64\\vcpkg\\user\\SFML-2.5.1\\lib\\cmake\\SFML")
  set(Eigen3_DIR "C:\\msys64\\vcpkg\\installed\\x64-mingw-static\\share\\eigen3")
  set(EXPRTK_INCLUDE_DIR "C:\\msys64\\vcpkg\\installed\\x64-mingw-static\\include")
  set(SFML_INCLUDE_DIR "C:\\msys64\\vcpkg\\user\\SFML-2.5.1\\include")
endif()

find_package(OpenGL REQUIRED)
find_package(SFML 2 COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Eigen3 REQUIRED)

if(NOT WIN32)
  find_package(ExprTk REQUIRED)
endif()


target_include_directories(${LOCAL_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
    ${EIGEN3_INCLUDE_DIR}
    ${SFML_INCLUDE_DIR}
    ${EXPRTK_INCLUDE_DIR}
)

target_sources(${LOCAL_PROJECT_NAME} PUBLIC ${SOURCES} ${HEADERS})

target_link_directories(${LOCAL_PROJECT_NAME} PUBLIC
)

target_link_libraries(${LOCAL_PROJECT_NAME}
  sfml-system
  sfml-graphics
  sfml-window
  ${OPENGL_LIBRARIES}
)

set_target_properties(${LOCAL_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "bin/")
file(COPY "res" DESTINATION "bin")


target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

target_compile_definitions(${LOCAL_PROJECT_NAME} PRIVATE ${DEFINES})
target_compile_options(${LOCAL_PROJECT_NAME} PRIVATE ${OPTIONS})

message(STATUS "SFML library status:")
message(STATUS "    version: ${SFML_VERSION}")
message(STATUS "    version: ${SFML_LIB_DIR}")


include(CPack)
