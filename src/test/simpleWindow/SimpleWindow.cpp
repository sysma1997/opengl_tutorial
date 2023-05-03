#include "./SimpleWindow.h"

void simpleWindow()
{
    Engine engine = Engine();
    engine.init("Simple window");

    while (engine.isClose())
    {
        engine.newFrame();

        engine.renderFrame();
    }

    engine.terminate();
}