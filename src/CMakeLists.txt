target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	Window.cpp
	Shader.cpp
	VertexArray.cpp
	VertexBuffer.cpp
	IndexBuffer.cpp
	Logger.cpp)

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/external/glad/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	glad
	glfw
)

