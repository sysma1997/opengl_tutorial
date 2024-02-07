#pragma once

#include <iostream>
#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Texture/Texture.h>
#include <Shader/Shader.h>
#include <ResourceManager/ResourceManager.h>

struct GameCharacter {
	unsigned int id;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class TextRenderer {
private:
	unsigned int VAO, VBO;
public:
	std::map<char, GameCharacter> characters;
	Shader textShader;

	TextRenderer(unsigned int width, unsigned int height);

	void load(std::string font, unsigned int fontSize);
	void render(std::string text, float x, float y, float scale,
		glm::vec3 color = glm::vec3{ 1.0f });
};