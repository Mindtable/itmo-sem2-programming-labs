//
// Created by MTBLE on 20.01.2022.
//

#include "../src/BasicOpenglObj/dependences.h"

#ifndef GLUT_TEST_COMPILE_SHADER_H
#define GLUT_TEST_COMPILE_SHADER_H

GLuint ReadShader(const std::string &vertex, const std::string& fragment);
GLuint CompileShader(const std::string &source, GLenum type);
GLuint CreateShader(const std::string &vertexShader, const std::string &fragmentShader);

#endif //GLUT_TEST_COMPILE_SHADER_H
