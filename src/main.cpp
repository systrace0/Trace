#include "Window.h"
#include "Core.h"
#include "Logger.h"

#include "Shader.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <cstdio>
#include "glad/glad.h"

using namespace engine;

int main()
{
	Logger::init();

	F32 vertices[] = {
		//   position            color
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
	};

	U32 indices[] = {
		0, 1, 2
	};

	// Window owns everything
	Window window{ 1280, 720, "Engine" };

	Logger::info("Engine initialized successfully.");
	Logger::warn("Memory usage approaching limit: {} MB", 512);
	Logger::error("Failed to load texture: {}", "player.png");

	VertexArray vao; // Start "Recording"
	vao.bind();

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	IndexBuffer indexBuffer(indices, sizeof(indices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)0);					// Position
	glEnableVertexAttribArray(0);																// Enable slot 0
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(F32), (void*)(3 * sizeof(F32))); // Color - starts 12 bytes later
	glEnableVertexAttribArray(1);																// Enable slot 1

	vao.unbind(); // End "Recording" - Saves recipe

	ASSERT(vao.id() != 0, "VAO invalid before draw");
	ASSERT(vertexBuffer.id() != 0, "VBO invalid before draw");
	ASSERT(indexBuffer.id() != 0, "EBO invalid before draw");

	while (!window.shouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		vao.bind();

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}