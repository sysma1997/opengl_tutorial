#pragma once

#include <Engine.h>

class GamePostProcessing
{
private:
    unsigned int MSFBO, FBO;
    unsigned int RBO;
    unsigned int VAO;

    void initRenderData();

public:
    Shader shader;
    Texture texture;
    unsigned int width, height;

    bool chaos, confuse, shake;

    GamePostProcessing(Shader shader, unsigned int width, unsigned int height);

    void beginReder();
    void endRender();
    void render(float time);
};