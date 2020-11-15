project(tetris)

## In most cases better set in the CMake cache
set(SFML_DIR "D:/StorageHome/workspace_Clion/SFML/output")
set(SFML_HOME "D:/StorageHome/workspace_Clion/SFML")

# Copy the DLLs to the binary directory
file(GLOB ALL_REQUIRED_DLL "${SFML_DIR}/lib/Debug/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy external DLLs to the binary directory
file(GLOB ALL_REQUIRED_EXT_DLL "${SFML_HOME}/extlibs/bin/x64/openal32.dll")
file(COPY ${ALL_REQUIRED_EXT_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

# Copy the content of the images folder
file(GLOB ALL_REQUIRED_IMAGES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "images/*.png")
file(COPY ${ALL_REQUIRED_IMAGES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)

# Copy the content of the sounds folder
file(GLOB ALL_REQUIRED_SOUNDS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "sounds/*.*")
file(COPY ${ALL_REQUIRED_SOUNDS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/sounds)

find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)
add_executable(${PROJECT_NAME} "main.cpp" "Game.cpp" "Game.h")
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
