cmake_minimum_required(VERSION 3.10)


# Set the project name and version
project(PerfectTraits VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/tests
  ${PROJECT_SOURCE_DIR}/src
  )

# Add the executable
add_executable(
  PerfectTraits
  src/main.cpp
  src/ParseCSV.cpp
  src/Unit.cpp
  src/Team.cpp
  src/global.cpp
  src/Trait.cpp
  src/CombController.cpp
)

# include necessary source files
add_executable(
  tests
  tests/tests.cpp
  src/ParseCSV.cpp
  src/Unit.cpp
  src/Team.cpp
  src/global.cpp
  src/Trait.cpp
  src/CombController.cpp
) 