#include "../include/pandaGraphics/glfw.h"

#include <stdio.h>

#include <GLFW/glfw3.h>

int pgInit()
{
	return glfwInit();
}

static GLFWwindow * _pgCreateWindow(int width, int height, const char * title, int major, int minor)
{
	/* setup context hints */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* create the native window */
	GLFWwindow * native = glfwCreateWindow(width, height, title, NULL, NULL);

	if (native == NULL)
	{
		int err = glfwGetError(NULL);
		switch (err)
		{
		case GLFW_VERSION_UNAVAILABLE:
			fprintf(stderr, "OpenGL version %d.%d unavailable!\n", major, minor);
			break;

		default:
			fprintf(stderr, "Unrecognised error: 0x%08x\n", err);
			break;
		}
	}
	return native;
}

PGwindow * pgCreateWindow(int width, int height, const char * title)
{
	GLFWwindow * native = _pgCreateWindow(width, height, title, 3, 2);
	if (!native) return NULL;

	/* setup callbacks */
	//glfwSetWindowUserPointer(native, NULL);

	/* enable v-sync */
	glfwMakeContextCurrent(native);
	glfwSwapInterval(1);

	return (PGwindow *) native;
}

void pgPollEvents()
{
	glfwPollEvents();
}

int main()
{
	pgInit();
	pgCreateWindow(500, 500, "Hello, world!");
}