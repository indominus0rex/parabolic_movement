set(SDL3_DIR "C:/SDKs/SDL3-3.4.4/x86_64-w64-mingw32/lib/cmake/SDL3")

find_package(SDL3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "C:/SDKs/SDL3-3.4.4/x86_64-w64-mingw32/bin/SDL3.dll"
  $<TARGET_FILE_DIR:${PROJECT_NAME}>)

set(CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)