cmake_minimum_required(VERSION 3.22)
#cmake_policy(VERSION <min>[...<max>])
project(http) 

find_package(Poco REQUIRED Net Foundation) 

add_executable(http poco_request.cpp)

target_link_libraries(http PUBLIC
  Poco::Net
)


set_target_properties(
       http PROPERTIES
       CXX_STANDARD 17
       CXX_STANDARD_REQUIRED ON
)
