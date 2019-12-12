cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(minimesh
	LANGUAGES CXX
	VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

find_package(VTK REQUIRED)

if (NOT VTK_FOUND)
  message(FATAL_ERROR "Minimesh fatal error : ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()

message (STATUS "VTK_VERSION: ${VTK_VERSION}")
message (STATUS "VTK_DIR: ${VTK_DIR}")

set(EXE_SOURCES
  src/options.cpp
  src/viewer.cpp
  src/import.cpp
  src/concatenate.cpp
  src/job.cpp
  # Add other source files here, one by line
)

include_directories(
    ${PROJECT_SOURCE_DIR}/includes
    ${PROJECT_SOURCE_DIR}/external/cpptoml
    ${PROJECT_SOURCE_DIR}/tests
)

#set(VTK_LIBRARY_DIRS "C:/MyProjects/VTK-8.2.0/out/build/x64-Debug/bin")
#link_directories(${VTK_LIBRARY_DIRS})
#message (STATUS "VTK_LIBRARY_DIRS: ${VTK_LIBRARY_DIRS}")

if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(${PROJECT_NAME} src/main.cpp ${EXE_SOURCES})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(${PROJECT_NAME} src/main.cpp ${EXE_SOURCES})
  target_link_libraries(${PROJECT_NAME} PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS main
    MODULES ${VTK_LIBRARIES}
    )
endif () 
