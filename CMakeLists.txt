cmake_minimum_required(VERSION 3.10) 
project(OptiPrice) 

# Set the C++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

# Specify dirs for the source and include files 
include_directories(${PROJECT_SOURCE_DIR}/include) 
include_directories(/opt/homebrew/include)         # For pqxx
include_directories(/opt/homebrew/opt/libpq/include)  # For libpq

# Link directories for libraries 
link_directories(/opt/homebrew/lib)
link_directories(/opt/homebrew/opt/libpq/lib)    

# Find dependencies
find_package(PostgreSQL REQUIRED)

# List all source files
set(SOURCES 
    src/main.cpp
    src/option_pricer.cpp 
    src/user_auth.cpp)  

# Add the executable 
add_executable(OptiPrice ${SOURCES})

# Link libraries 
target_link_libraries(OptiPrice pqxx PostgreSQL::PostgreSQL)