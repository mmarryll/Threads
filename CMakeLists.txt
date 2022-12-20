cmake_minimum_required(VERSION 3.13)
project(cmkpr)
set(SOURCES main.cpp solver.cpp ThreadSafeStack.cpp)
set(HEADERS solver.h ThreadSafeStack.h)
add_executable(cmkpr ${SOURCES} ${HEADERS})
 #add_executeble(cmkpr main.cpp solver.cpp ThreadSafeStack.cpp)
set_target_properties(
       cmkpr PROPERTIES
       CXX_STANDARD 17
       CXX_STANDARD_REQUIRED ON
)