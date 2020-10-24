cmake_minimum_required (VERSION 3.11)

project ("VisualCPPCodeSamples")

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(examples/arrays)
add_subdirectory(examples/classes)
add_subdirectory(examples/inheritance)
add_subdirectory(examples/strings)
add_subdirectory(examples/vector)
add_subdirectory(examples/wxWidgets/simpleFrame)
add_subdirectory(examples/raylib)

# Add source to this project's executable.
add_executable (VisualCPPCodeSamples "main.cpp")
