#include "./TextRendering.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace glm;

bool textRendering_pause = false;
bool textRendering_inverted_mouse = false;

std::map<char, Character> characters;

void textRenderingKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        textRendering_pause = !textRendering_pause;
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
        textRendering_inverted_mouse = !textRendering_inverted_mouse;
}
void renderText(Shader &shader, std::string text,
                float x, float y, float scale, vec3 color,
                unsigned int VAO, unsigned int VBO)
{
    shader.use();
    glUniform3f(glGetUniformLocation(shader.id, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = characters[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};

        glBindTexture(GL_TEXTURE_2D, ch.textureId);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void textRendering()
{
    Engine engine{};

    engine.init("Text Rendering");
    Texture::Init();

    engine.setKeyCallback(textRenderingKeyCallback);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Shader shader{"./shaders/textRendering/textRendering.vert", "./shaders/textRendering/textRendering.frag"};
    mat4 projection = ortho(0.0f, 800.0f, 0.0f, 600.0f);
    shader.use();
    glUniformMatrix4fv(glGetUniformLocation(shader.id, "projection"), 1, GL_FALSE, value_ptr(projection));

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "TEXTRENDERING::FREETYPE::Error: Could not init FreeType Library\n";
        getch();
        engine.terminate();
        return;
    }
    FT_Face face;
    if (FT_New_Face(ft, "./assets/fonts/arial.ttf", 0, &face))
    {
        std::cout << "TEXTRENDERING::FREETYPE::Error: Failed to load font\n";
        getch();
        engine.terminate();
        return;
    }
    FT_Set_Pixel_Sizes(face, 0, 48);
    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    {
        std::cout << "TEXTRENDERING::FREETYPE::Error: Failed to load Glyph\n";
        getch();
        engine.terminate();
        return;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "TEXTURERENDERING::FREETYPE::Error: Failed to load Glyph\n";
            getch();
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                     face->glyph->bitmap.width,
                     face->glyph->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)};
        characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    while (engine.isClose())
    {
        engine.newFrame();

        renderText(shader,
                   "This is sample text",
                   25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f),
                   VAO, VBO);
        renderText(shader,
                   "(C) LearnOpenGL.com",
                   540.0f, 570.0f, 0.5f, glm::vec3(0.3, 0.7f, 0.9f),
                   VAO, VBO);

        engine.renderFrame();
    }

    engine.terminate();
}