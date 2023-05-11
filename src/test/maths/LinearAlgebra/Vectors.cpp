#include "../Maths.h"

using namespace glm;

vec3 sum(vec3 vector1, vec3 vector2)
{
    return vector1 + vector2;
}
vec3 difference(vec3 vector1, vec3 vector2)
{
    return vector1 - vector2;
}
vec3 scale(vec3 vector1, vec3 vector2)
{
    return vector1 * vector2;
}
vec2 unit(vec2 vector)
{
    float hypotenuse = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    std::cout << std::endl
              << "Hypotenuse: " << hypotenuse << std::endl;

    return vec2(vector.x / hypotenuse, vector.y / hypotenuse);
}
vec3 unit(vec3 vector)
{
    float hypotenuse = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
    std::cout << "Hypotenuse: " << hypotenuse << std::endl;

    return vec3(vector.x / hypotenuse, vector.y / hypotenuse, vector.z / hypotenuse);
}

void vectors()
{
    vec3 vector1{2.5, 3, 7};
    vec3 vector2{1, 5.6, 9};

    std::cout << "Vector1: " << glm::to_string(vector1) << std::endl;
    std::cout << "Vector2: " << glm::to_string(vector2) << std::endl;
    std::cout << std::endl;
    std::cout << "Sum:                " << glm::to_string(sum(vector1, vector2)) << std::endl;
    std::cout << "Difference:         " << glm::to_string(difference(vector1, vector2)) << std::endl;
    std::cout << "Scale:              " << glm::to_string(scale(vector1, vector2)) << std::endl;
    std::cout << "Unit/Normalization: " << glm::to_string(unit(vec2(-1, -7))) << std::endl;
}