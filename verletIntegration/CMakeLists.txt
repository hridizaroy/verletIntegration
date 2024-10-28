# CMakeList.txt : CMake project for verletIntegration

include_directories(
	"${PROJECT_SOURCE_DIR}/SFML-2.6.1/include"
)

add_executable (verletIntegration "main.cpp" "Particle.h" "Particle.cpp" "Constraint.h" "Constraint.cpp")

target_link_libraries(verletIntegration
	"${PROJECT_SOURCE_DIR}/SFML-2.6.1/lib/sfml-main.lib"
	"${PROJECT_SOURCE_DIR}/SFML-2.6.1/lib/sfml-window.lib"
	"${PROJECT_SOURCE_DIR}/SFML-2.6.1/lib/sfml-graphics.lib"
	"${PROJECT_SOURCE_DIR}/SFML-2.6.1/lib/sfml-system.lib"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET verletIntegration PROPERTY CXX_STANDARD 20)
endif()
