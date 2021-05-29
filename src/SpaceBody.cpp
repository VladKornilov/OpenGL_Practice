#include "SpaceBody.h"
#include <iostream>
using namespace std;

string planetNames[] = {
    "sun2048.png",
    "mercury2048.png",
    "venus2048.png",
    "earth2048.png",
    "mars2048.png",
    "jupiter2048.png",
    "saturn2048.png",
    "uran2048.png",
    "neptune2048.png"
};

SpaceBody::SpaceBody(int id, float dist, float rotate, float moveSpeed, float scale)
{
    MVPMatrix = mat4(1.0);
    distance = dist;
    rotateSpeed = rotate;
    this->moveSpeed = moveSpeed;
    this->scale = scale;
    string path = "/home/vlad/GraphicalSystems/OpenGL_Practice/res/" + planetNames[id];

    image = loadPngImage(path.c_str());
}

void SpaceBody::translateAndRotate(double time)
{
    MVPMatrix = mat4(1.0);
    vec3 translate = vec3(distance, 0, 0) * sin((float)time * moveSpeed);
    translate += vec3(0, distance, 0) * cos((float)time * moveSpeed);
    //translate.z = 1.0 * rand() / RAND_MAX;
    //translate.z = 0.2;

    MVPMatrix = glm::translate(MVPMatrix, translate);

    glm::vec3 scaleVec = glm::vec3(scale);
    MVPMatrix = glm::scale(MVPMatrix, scaleVec);

    MVPMatrix = glm::rotate(MVPMatrix, glm::radians(90.f), vec3(1, 0, 0));
    MVPMatrix = glm::rotate(MVPMatrix, (float)time * glm::radians(rotateSpeed), vec3(0, 0, 1));
}
