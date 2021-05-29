#ifndef SPACEBODY_H
#define SPACEBODY_H
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "PngLoader.h"
using namespace glm;

class SpaceBody
{
private:
    // матрица модель-вид-проекция
    mat4 MVPMatrix;
    float distance;
    float rotateSpeed;
    float moveSpeed;
    float scale;
    vec3 rot;
    ImageData *image;
public:
    SpaceBody(int id, float dist, float rotate, float moveSpeed, float scale = 0.2);
    mat4 getMVP() { return MVPMatrix; }
    ImageData *getImage() { return image; }


    void translateAndRotate(double time);
};

#endif // SPACEBODY_H
