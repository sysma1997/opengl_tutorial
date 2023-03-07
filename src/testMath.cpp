#include "testMath.h"

#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

void coutTestMatrix(glm::mat4 myMatrix, glm::vec4 myVector, glm::vec4 transformedVector)
{
    std::cout << "Matrix " << glm::to_string(myMatrix) << std::endl;
    std::cout << "Vector " << glm::to_string(myVector) << std::endl;
    std::cout << "Transformed " << glm::to_string(transformedVector) << std::endl;
}

void testTranslationMatrix()
{
    glm::mat4 myMatrix(
        glm::vec4(1, 0, 0, 0),
        glm::vec4(0, 1, 0, 0),
        glm::vec4(0, 0, 1, 0),
        glm::vec4(10, 0, 0, 1));
    glm::vec4 myVector(10, 10, 10, 1);

    glm::vec4 transformedVector = myMatrix * myVector;

    coutTestMatrix(myMatrix, myVector, transformedVector);
}
void testIdentityMatrix()
{
    glm::mat4 myMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 0.0f, 0.0f));
    glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);

    glm::vec4 transformedVector = myMatrix * myVector;

    coutTestMatrix(myMatrix, myVector, transformedVector);
}
void testScalingMatrix()
{
    glm::mat4 myScalingMatrix = glm::scale(glm::vec3(2.0f, 2.0f, 2.0f));

    std::cout << "Scaling matrix: " << glm::to_string(myScalingMatrix) << std::endl;
}
void testRotationMatrix()
{
    glm::vec3 myRotationAxis(2.0f, 2.0f, 2.0f);
    // glm::rotate(glm::angle(45), myRotationAxis);

    std::cout << "Rotation axis " << glm::to_string(myRotationAxis) << std::endl;
    // std::cout << "Rotation matrix " << glm::to_string(myRotationMatrix) << std::endl;
}