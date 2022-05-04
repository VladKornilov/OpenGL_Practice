// TODO: надо ли?
// #define GLFW_INCLUDE_GLCOREARB 1 // Tell GLFW to include the OpenGL core profile header
#define GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GL3
#define GLFW_INCLUDE_GLEXT
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>        // для поддержки расширений, шейдеров и так далее
#include <GLFW/glfw3.h>     // Непосредственно сам GLFW
#include <glm.hpp>          // библиотека графической математики
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include "PngLoader.h"
#include "Helpers.h"
#include "Vertex.h"
#include "Figures.h"
#include "Shaders.h"
#include "ObjLoader.h"
#include "SpaceBody.h"

// Документация
// https://www.opengl.org/sdk/docs/man/html/

using namespace std;
using namespace glm;

#define MATH_PI 3.14159265

// Текущие переменные для модели
bool leftButtonPressed = false;
bool rightPressed = false;
double lastCursorPosX = 0.0;
double lastCursorPosY = 0.0;

void glfwErrorCallback(int error, const char* description) {
    printf("OpenGL error = %d\n description = %s\n\n", error, description);
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Выходим по нажатию Escape
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    }
    // по пробелу включаем или выключаем вращение автоматом
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
    }
}

void glfwMouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
    // обработка левой кнопки
    if(button == GLFW_MOUSE_BUTTON_1){
        if(state == GLFW_PRESS){
            leftButtonPressed = true;
        }else{
            leftButtonPressed = false;
        }
    }
    // обработка правой кнопки
    if(button == GLFW_MOUSE_BUTTON_2){
        if(state == GLFW_PRESS){
            rightPressed = true;
        }else{
            rightPressed = false;
        }
    }
}

void glfwCursorCallback(GLFWwindow* window, double x, double y) {
    // при нажатой левой кнопки - вращаем по X и Y
    if(leftButtonPressed){
    }

    // при нажатой левой кнопки - перемещаем по X Y
    if(rightPressed){
    }

    lastCursorPosX = x;
    lastCursorPosY = y;
}

void glfwScrollCallback(GLFWwindow* window, double scrollByX, double scrollByY) {
}

int main(int argc, char *argv[]) {

    // окно
    GLFWwindow* window = 0;

    // обработчик ошибок
    glfwSetErrorCallback(glfwErrorCallback);

    // инициализация GLFW
    if (!glfwInit()){
        exit(EXIT_FAILURE);
    }

    // создание окна
#ifdef __APPLE__
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#else
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(700, 650, "Cuuube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);        // вертикальная синхронизация
    CHECK_GL_ERRORS();

    // Обработка клавиш и прочего
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(window, glfwCursorCallback);
    glfwSetScrollCallback(window, glfwScrollCallback);

    // инициализация расширений
    glewExperimental = GL_TRUE;
    glewInit();
    CHECK_GL_ERRORS();
    
    // инициализация расширений
    glewExperimental = GL_TRUE;
    glewInit();
    CHECK_GL_ERRORS();

    // Инициализация отладки
    if(glDebugMessageCallback){
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // Коллбек ошибок OpenGL
        glDebugMessageCallback((GLDEBUGPROC)glDebugOut, 0);

        // Более высокий уровень отладки
        // GLuint unusedIds = 0;
        // glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
    }
    CHECK_GL_ERRORS();
    
    const unsigned char* version = glGetString(GL_VERSION);
    printf("OpenGL version = %s\n", version);

    // cоотношение сторон
    int width = 0;
    int height = 0;
    // Размер буффера кадра
    glfwGetFramebufferSize(window, &width, &height);
    CHECK_GL_ERRORS();
    
    // задаем отображение
    glViewport(0, 0, width, height);
    CHECK_GL_ERRORS();

    // Шейдеры
    GLuint shaderProgram = createShader();
    CHECK_GL_ERRORS();

    // аттрибуты вершин шейдера
    int posAttribLocation = glGetAttribLocation(shaderProgram, "aPos");
    int normAttribLocation = glGetAttribLocation(shaderProgram, "aNorm");
    int colorAttribLocation = glGetAttribLocation(shaderProgram, "aColor");
    int textureAttribLocation = glGetAttribLocation(shaderProgram, "aTexture");
    CHECK_GL_ERRORS();

    // юниформы шейдера
    int MVPMatrixLocation = glGetUniformLocation(shaderProgram, "uModelViewProjMat");
    CHECK_GL_ERRORS();

    // VBO, данные о вершинах
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, triangleVertexCount * sizeof(Vertex), triangleVertexes, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, cubeVertexCount * sizeof(Vertex), cubeVertexes, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sphereVertexCount * sizeof(Vertex), sphereVertexes, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    CHECK_GL_ERRORS();
    
    // отключаем отображение задней части полигонов
    //glEnable(GL_CULL_FACE);
    // отбрасываться будут задние грани
    //glCullFace(GL_BACK);
    // Определяем, в каком направлении должный обходиться вершины, для передней части (против часовой стрелки?)
    // задняя часть будет отбрасываться
    glFrontFace(GL_CCW);
    CHECK_GL_ERRORS();

    // проверка глубины
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    CHECK_GL_ERRORS();

    // текущее время
    double time = glfwGetTime();


    bool realSystem = 1;
    int numOfPlanets = 9;

    float pixel = 1. / std::min(width, height);





    float realSizes[9] = { 69630, 2439, 6050, 6371, 3389, 69911, 58232, 25362, 24622 };
    float realSolarR = 0.1;
    float divisor = realSizes[0] / realSolarR;
    for (int i = 0; i < 9; i++) {
        realSizes[i] /= divisor;
        if (realSizes[i] < pixel)
            realSizes[i] = pixel;
    }

    float distances[numOfPlanets];
    distances[0] = 0;

    float minR = 0.2, maxR = 0.97;
    float deltDist = (maxR - minR) / numOfPlanets;
    for (int i = 1; i < numOfPlanets; i++) {
        distances[i] = minR + i * deltDist;
    }

    float realDistances[9] = { 0, 0.387, 0.72, 1, 1.52, 5.2, 9.55, 19.2, 30.1 };
    float maxRealR = realDistances[numOfPlanets-1] * 1.2;
    for (int i = 1; i < 9; i++) {
        realDistances[i] /= maxRealR;
        realDistances[i] += realSolarR;
        //if (realDistances[i] < realSolarR)
        //    realDistances[i] = 1.2 * realSolarR + pixel * i;
    }

    float realSpeeds[9] = { 0, 47.87, 35.02, 29.76, 24.13, 13.07, 9.67, 6.84, 5.48 };
    float speedMultiply = 0.02;
    for (int i = 0; i < 9; i++)
        realSpeeds[i] *= speedMultiply;

    SpaceBody *planets[numOfPlanets];
    if (realSystem)
        planets[0] = new SpaceBody(0, realDistances[0], 30, realSpeeds[0], realSizes[0]);
    else
        planets[0] = new SpaceBody(0, 0.0, 30, 0, realSizes[0]);

    for (int i = 1; i < numOfPlanets; i++) {
        if (realSystem)
            planets[i] = new SpaceBody(i, realDistances[i], 30, realSpeeds[i], realSizes[i]);
        else
            planets[i] = new SpaceBody(i, distances[i], 30, realSpeeds[i], deltDist / 2.1);
    }

    // Загрузка текстуры
//    ImageData info = *loadPngImage("/home/vlad/GraphicalSystems/OpenGL_Practice/res/earth2048.png");
//    GLuint textureId = 0;
//    if(info.loaded){
//        glGenTextures(1, &textureId);
//        glBindTexture(GL_TEXTURE_2D, textureId);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,              // формат внутри OpenGL
//                     info.width, info.height, 0,            // ширина, высота, границы
//                     info.withAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, info.data); // формат входных данных
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//        CHECK_GL_ERRORS();
//    }

    GLuint planetTextures[numOfPlanets];
    glGenTextures(numOfPlanets, planetTextures);
    for (int i = 0; i < numOfPlanets; i++) {
        ImageData *im = planets[i]->getImage();
        if (im->loaded) {
            glBindTexture(GL_TEXTURE_2D, planetTextures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                         im->width, im->height, 0,
                         im->withAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, im->data);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            CHECK_GL_ERRORS();
        }
    }

    while (!glfwWindowShouldClose(window)){
        // приращение времени
        double newTime = glfwGetTime();
        //double timeDelta = newTime - time;
        time = newTime;

        // wipe the drawing surface clear
        glClearColor(0.0, 0.0, 0.0, 1.0);
        //glEnable(GL_DEPTH_TEST);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glUseProgram (shaderProgram);

        for (int i = 0; i < numOfPlanets; i++) {

            glBindTexture(GL_TEXTURE_2D, planetTextures[i]);

            planets[i]->translateAndRotate(time);
            // выставляем матрицу трансформации в пространство OpenGL
            //glUniformMatrix4fv(MVPMatrixLocation, 1, false, glm::value_ptr(modelViewTransformMatrix));
            glUniformMatrix4fv(MVPMatrixLocation, 1, false, glm::value_ptr(planets[i]->getMVP()));

            // sizeof(Vertex) - размер блока данных о вершине
            // OFFSETOF(Vertex, color) - смещение от начала
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            // Позиции
            glEnableVertexAttribArray(posAttribLocation);
            glVertexAttribPointer(posAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, pos));
            // Нормали
            glEnableVertexAttribArray(normAttribLocation);
            glVertexAttribPointer(normAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, normal));
            // Цвет вершины
            glEnableVertexAttribArray(colorAttribLocation);
            glVertexAttribPointer(colorAttribLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, color));
            // Текстура вершины
            glEnableVertexAttribArray(textureAttribLocation);
            glVertexAttribPointer(textureAttribLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), OFFSETOF(Vertex, texture));
            CHECK_GL_ERRORS();



            // рисуем
            //glDrawArrays(GL_TRIANGLES, 0, cubeVertexCount); // draw points 0-3 from the currently bound VAO with current in-use shader
            //glDrawArrays(GL_TRIANGLES, 0, sphereVertexCount);
            glDrawElements(GL_TRIANGLES,
                           sp.getIndexCount(),
                           GL_UNSIGNED_INT,
                           sp.getIndices());
            // VBO off
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &VBO);

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
