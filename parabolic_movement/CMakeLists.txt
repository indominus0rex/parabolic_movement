set(SDL3_DIR "C:/SDKs/SDL3-3.4.4/x86_64-w64-mingw32/lib/cmake/SDL3")
set(SDL3_image_DIR "C:/SDKs/SDL3_image-3.4.2/x86_64-w64-mingw32/lib/cmake/SDL3_image")

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

add_executable(${PROJECT_NAME} main.cpp particle.cpp button.cpp)

######################## fmt #######################

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        e69e5f977d458f2650bb346dadf2ad30c5320281) # 10.2.1
FetchContent_MakeAvailable(fmt)

######################## SDL3dll ###################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "C:/SDKs/SDL3-3.4.4/x86_64-w64-mingw32/bin/SDL3.dll"
  $<TARGET_FILE_DIR:${PROJECT_NAME}>)


####################### SDL3_image dll #####################

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
   "C:/SDKs/SDL3_image-3.4.2/x86_64-w64-mingw32/bin/SDL3_image.dll"
  $<TARGET_FILE_DIR:${PROJECT_NAME}>)

set(CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image fmt::fmt)