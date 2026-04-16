#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>

int main()
{
	if (!glfwInit())
	{
		std::printf("Failed to initialize GLFW\n");
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Engine", nullptr, nullptr);
	if (!window)
	{
		std::printf("Failed to create Window!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::printf("Failed to initialize GLAD\n");
		return 1;
	}

	std::printf("OpenGL %s\n", (const char*)glGetString(GL_VERSION));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window); // Present the rendered frame
		glfwPollEvents();		 // Process Keyboard / mouse / window events
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}