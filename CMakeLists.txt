cmake_minimum_required(VERSION 3.13)

project(cmkpr) 

set(SOURCES main.cpp solver/solver.cpp)
set(HEADERS solver/solver.h)
add_subdirectory(stack)

add_executable(cmkpr ${SOURCES} ${HEADERS})

 #add_executeble(cmkpr main.cpp solver.cpp ThreadSafeStack.cpp)
 
set_target_properties(
       cmkpr PROPERTIES
       CXX_STANDARD 17
       CXX_STANDARD_REQUIRED ON
)
target_include_directories( 
       cmkpr
       PRIVATE
       ${CMAKE_CURRENT_SOURCE_DIR}/../stack
)

target_link_libraries(cmkpr lib)