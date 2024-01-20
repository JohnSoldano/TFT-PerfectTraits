cmake_minimum_required(VERSION 3.10)


# Set the project name and version
project(PerfectTraits VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# include(FetchContent)
# FetchContent_Declare(
#   json
#   GIT_REPOSITORY https://github.com/nlohmann/json.git
#   GIT_TAG v3.10.5 # Specify the commit hash or tag to fetch
# )

# FetchContent_MakeAvailable(json)


# Add strict compilation flags
# add_compile_options(-Wall -Wextra -Werror -pedantic -Wshadow -Wnon-virtual-dtor)
# Add strict compilation flags
# add_compile_options(
#     -Wall -Wextra -Werror
#     -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused 
#     -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation 
#     -Wduplicated-cond -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 
#     -pedantic-errors
# )

# if (CMAKE_COMPILER_IS_GNUCXX)
#     add_compile_options(-Weffc++)
# endif()

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
  src/UnitController.cpp

  src/Trait.cpp
  src/TraitController.cpp

  src/Team.cpp
  src/TeamController.cpp

  src/global.cpp
)

# target_link_libraries(PerfectTraits PRIVATE nlohmann_json::nlohmann_json)

# include necessary source files
# add_executable(
#   tests
#   tests/tests.cpp
#   src/FunTimer.cpp
  
#   # src/ParseCSV.cpp
#   # src/Unit.cpp
#   # src/Team.cpp
#   # src/global.cpp
#   # src/Trait.cpp
#   # src/CombController.cpp
# ) 