#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct PGwindow PGwindow;

	// Library initialisation
	int pgInit();

	// Window creation
	PGwindow * pgCreateWindow(int width, int height, const char * title);

	// Window context management
	void pgMakeWindowCurrent(PGwindow *);

	// Window event management
	void pgPollEvents();

#ifdef __cplusplus
}
#endif