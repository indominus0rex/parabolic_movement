add_executable(${PROJECT_NAME} 
  main.cpp 
  particle.cpp 
  button.cpp 
  window.cpp 
  object.cpp
  slingshot.cpp
  interaction.cpp
  collisionManager.cpp
)

include (FetchContent)

#fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 12.1.0      
)
FetchContent_MakeAvailable(fmt)

#glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

#sdl3
FetchContent_Declare(
  SDL3
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG release-3.4.8
) # 10.2.1
FetchContent_MakeAvailable(SDL3)

set(CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  SDL3::SDL3 
  fmt::fmt 
  glm::glm
)

#dlls
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
  $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
)