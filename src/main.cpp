#include "Window.h"
#include "glad/glad.h"
#include "Core.h"

#include <cstdio>

int main()
{
	// Window owns everything
	engine::Window window{ 1280, 720, "Engine" };

	while (!window.shouldClose())
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.swapBuffers();
		window.pollEvents();
	}

	return 0;
}