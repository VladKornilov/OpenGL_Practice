#ifndef FIGURES_H
#define FIGURES_H

#include <glm.hpp>
#include "Vertex.h"

using namespace glm;

// данные о вершинах
//int triangleVertexCount = 3;
//Vertex triangleVertexes[] = {
//    //                ВЕРШИНА                   ЦВЕТ
//    Vertex(vec3( 0.0f,  1.0f,  0.0f),   vec3(0.5f, 0.8f, 0.5f)),
//    Vertex(vec3(-1.0f, -1.0f,  1.0f),   vec3(0.5f, 0.8f, 0.5f)),
//    Vertex(vec3( 1.0f, -1.0f,  1.0f),   vec3(0.5f, 0.8f, 0.5f)),
//};

int cubeVertexCount = 6 * 2 * 3;
Vertex cubeVertexes[] = {
    //front
    Vertex(vec3(-0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f,  0.5f)),

    Vertex(vec3(-0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),

    //right
    Vertex(vec3( 0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f,  0.5f)),

    Vertex(vec3( 0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),

    //back
    Vertex(vec3( 0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f,  0.5f)),

    Vertex(vec3( 0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),

    //left
    Vertex(vec3(-0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f,  0.5f)),

    Vertex(vec3(-0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),

    //top
    Vertex(vec3(-0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),
    Vertex(vec3(-0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f,  0.5f)),

    Vertex(vec3(-0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f, -0.5f)),
    Vertex(vec3( 0.5f,  0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),

    //bottom
    Vertex(vec3( 0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),
    Vertex(vec3(-0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f,  0.5f)),

    Vertex(vec3( 0.5f, -0.5f, -0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2(-0.5f, -0.5f)),
    Vertex(vec3( 0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f, -0.5f)),
    Vertex(vec3(-0.5f, -0.5f,  0.5f),   vec3(0.5f, 0.8f, 0.5f),   vec2( 0.5f,  0.5f)),

}

#endif
