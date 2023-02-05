# CMakeList.txt : CMake project for Volterra.Matrix, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (Volterra.Matrix "Volterra.Matrix.cpp" "Volterra.Matrix.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Volterra.Matrix PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
