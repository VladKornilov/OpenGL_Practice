#include "Shaders.h"
#include "Helpers.h"
#include <stdio.h>
#include <stdlib.h>


GLuint createShaderFromSources(const char* vertexShader, const char* fragmentShader){
    GLuint vs = glCreateShader (GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    CHECK_GL_ERRORS();

    GLuint fs = glCreateShader (GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    CHECK_GL_ERRORS();

    GLuint shaderProgram = glCreateProgram ();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);
    CHECK_GL_ERRORS();

    /*int infologLength = 0;
    glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
    if (infologLength > 0){
        GLchar* infoLog = (GLchar*)malloc(static_cast<size_t>(infologLength));
        if (infoLog == nullptr){
            printf("ERROR: Could not allocate InfoLog buffer");
            exit(1);
        }
        int charsWritten = 0;
        glGetShaderInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
        printf("Shader InfoLog:\n%s", infoLog );
        free(infoLog);
    }
    CHECK_GL_ERRORS();*/
    
    return shaderProgram;
}

GLuint createShader(){
    // Шейдер вершин
    const char* vertexShader = STRINGIFY_SHADER(
        // vertex attribute
        attribute vec3 aPos;
        attribute vec3 aNorm;
        attribute vec3 aColor;
        attribute vec2 aTexture;
        // uniforms
        uniform mat4 uModelViewProjMat;
        // output
        varying vec3 vColor;
        varying vec3 vNorm;
        varying vec2 vTexture;
        varying vec3 vFragPos;

        void main () {
            vec4 vertexVec4 = vec4(aPos, 1.0f);      // последняя компонента 1, тк это точка
            // вычисляем позицию точки в пространстве OpenGL
            gl_Position = uModelViewProjMat * vertexVec4;

            vNorm = mat3(uModelViewProjMat) * aNorm;
            //vNorm = aNorm;
            vFragPos = vec3(uModelViewProjMat * vec4(aPos, 1.0));

            // цвет и текстурные координаты просто пробрасываем для интерполяции
            vColor = aColor;
            vTexture = aTexture;
        }
    );

    const char* fragmentShader = STRINGIFY_SHADER(
        varying vec3 vColor;
        varying vec3 vNorm;
        varying vec2 vTexture;
        varying vec3 vFragPos;
        uniform sampler2D newTexture0;

        vec3 lightPos = vec3(0.0f, 0.0f, 0.0f);
        vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
        float ambientK = 0.4f;
        float diffuseK = 0.7f;

        void main () {
            vec3 ambient = ambientK * vec3(texture2D(newTexture0, vTexture));

            // diffuse
            vec3 norm = normalize(vNorm);
            vec3 lightDir = normalize(lightPos - vFragPos);

            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diffuseK * diff * lightColor;
            //vec3 diffuse = light.diffuse * diff * vec3(texture2D(newTexture0, vTexture));


            // attenuation
            float distance = length(lightPos - vFragPos);
            //float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

            //ambient *= attenuation;
            //diffuse *= attenuation;
            //specular *= attenuation;

            vec3 result = ambient + diffuse;
            float dist = sqrt(vFragPos.x * vFragPos.x + vFragPos.y * vFragPos.y + vFragPos.z * vFragPos.z);
            if (dist < 0.11f) result = ambient / ambientK;

            gl_FragColor = vec4(result * vColor, 1.0);
            //gl_FragColor = texture2D(newTexture0, vTexture + 0.5f) * vec4(result * vColor, 1.0);
//            int i;
//            int j;
//            for (i = -1; i <= 1; i++) {
//                for (j = -1; j <= 1; j++) {
//                    if (abs(i + j) == 1) {
//                        if (abs(vTexture.x + 0.2 * i) < 0.1 && abs(vTexture.y + 0.2 * j) < 0.1) {
//                            discard;
//                        }
//                    }
//                }
//            }

        }
    );

    GLuint shader = createShaderFromSources(vertexShader, fragmentShader);
    CHECK_GL_ERRORS();
    return shader;
}

