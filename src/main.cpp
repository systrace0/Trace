#include <cstddef>

#include "Window.h"
#include "Core.h"
#include "Logger.h"

#include "Shader.h"
#include "Mesh.h"

#include "imgui/ImGuiManager.h"
#include "imgui/panels/DebugPanel.h"
#include "imgui/panels/LogPanel.h"

#include "glad/glad.h"

using namespace trace;

int main()
{
	Logger::init();

	std::vector<Vertex> vertices = {
		//		Position			Color
		{{ 0.0f,  0.5f, 0.0f}, {1.0f, 0.0f, 0.0 }},
		{{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}
	};

	std::vector<U32> indices = {
		0, 1, 2
	};

	// Window owns everything
	Window window{ 1280, 720, "TRACE Engine" };

	Logger::info("Engine initialized successfully.");

	ImGuiManager gui{ window };
	gui.registerDefaultPanels();

	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	Mesh mesh(vertices, indices);

	while (!window.shouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		mesh.draw();

		gui.beginFrame();
		// Panels
		gui.endFrame();

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}