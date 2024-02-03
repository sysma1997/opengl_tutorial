#include <iostream>

#include "Engine.h"

int main() {
	Engine* engine{ new Engine(400, 400) };
	engine->init("Test");

	while (engine->isClose()) {
		engine->newFrame();

		engine->renderFrame();
	}

	engine->terminate();

	return 0;
}