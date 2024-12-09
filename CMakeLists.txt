cmake_minimum_required(VERSION 3.10)
project(chat)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

find_package(Threads REQUIRED)

add_executable(server server.cpp)
add_executable(client client.cpp)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
  message("On Windows")
  target_link_libraries(server PRIVATE ssl crypto wsock32 ws2_32)
  target_link_libraries(client PRIVATE ssl crypto wsock32 ws2_32)
else()
  message("On Linux")
  target_link_libraries(server PRIVATE ssl crypto pthread)
  target_link_libraries(client PRIVATE ssl crypto pthread)
endif()
