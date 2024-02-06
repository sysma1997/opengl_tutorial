#include "SimpleWindow.h"

void simpleWindow() {
	Engine* engine{ new Engine{400, 400} };
	engine->init("Simple windows");

	while (engine->isClose()) {
		engine->newFrame();

		engine->renderFrame();
	}

	engine->terminate();
}