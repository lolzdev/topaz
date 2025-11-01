#include "gl.h"
#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#include "../rgfw.h"

int platform_run(int argc, char **argv)
{

	RGFW_glHints* hints = RGFW_getGlobalHints_OpenGL();
	hints->major = 3;
	hints->minor = 3;
	RGFW_setGlobalHints_OpenGL(hints);

	RGFW_window* win = RGFW_createWindow("Topaz", 0, 0, 800, 600, RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowHide);
	RGFW_window_createContext_OpenGL(win, hints);

	int glad_version = gladLoadGL(RGFW_getProcAddress_OpenGL);
	if (glad_version == 0) {
		printf("Failed to initialize OpenGL context.\n");
		return -1;
	}

	RGFW_window_show(win);

	RGFW_window_setExitKey(win, RGFW_escape);

	const GLubyte *version = glGetString(GL_VERSION);
	printf("OpenGL Version: %s\n", version);
	printf("GLAD Version: %d.%d\n", GLAD_VERSION_MAJOR(glad_version), GLAD_VERSION_MINOR(glad_version));


	while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
		RGFW_event event;
		while (RGFW_window_checkEvent(win, &event));

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		RGFW_window_swapBuffers_OpenGL(win);
	}

	RGFW_window_close(win);
	return 0;
}
