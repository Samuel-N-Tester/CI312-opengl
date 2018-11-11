# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (GLTutorials)


find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)


include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	.
)


set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

#FILE(GLOB SRC_FILES "source/*.hlsl")

set_source_files_properties(${SRC_FILES} PROPERTIES VS_TOOL_OVERRIDE "None")

# Example 1
add_executable(Main 
	${SRC_FILES}		
	source/Main/Main.cpp
	source/Main/Viewer.cpp
	source/Main/Model.cpp
	source/Main/Controller.cpp
	source/Shapes/Shape.cpp
	source/Shapes/Tetrahedron.cpp
	source/Shaders/SimpleFragmentShader.hlsl
	source/Shaders/SimpleVertexShader.hlsl
	common/objloader.cpp
	common/objloader.hpp
	common/controls.cpp
	common/controls.hpp
	common/shader.cpp
	common/shader.hpp
	common/texture.cpp
	common/texture.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
)

# working directories
set_target_properties(Main PROPERTIES COMPILE_DEFINITIONS "USE_ASSIMP")
target_link_libraries(Main
	${ALL_LIBS}
	assimp
)

set_target_properties(Main PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/Main/")

#message(${CMAKE_GENERATOR})
if(NOT ${CMAKE_GENERATOR} STREQUAL "Xcode")
add_custom_command(
   TARGET Main POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Main${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/source/Main/"
    COMMENT "Copying Main files..."

)
endif()






SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*hlsl*" )