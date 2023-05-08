#include "./Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../libs/stb_image.h"

void Texture::init()
{
    stbi_set_flip_vertically_on_load(true);
}
GLuint Texture::loadTexture(const char *path, bool rgba)
{
    GLuint id;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannel;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannel, 0);
    if (!data)
    {
        std::cout << "Failed to load texture: " << path << std::endl;

        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (rgba) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return id;
}