project(tetris)

## In most cases better set in the CMake cache
set(SFML_DIR "D:/StorageHome/workspace_Clion/SFML/output")

# Copy the DLLs to the binary directory
file(GLOB ALL_REQUIRED_DLL "${SFML_DIR}/lib/Debug/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy the content of the resources folder
file(GLOB ALL_REQUIRED_RESOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "images/*.png")
file(COPY ${ALL_REQUIRED_RESOURCES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/images)


find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
