//
// Created by MTBLE on 20.01.2022.
//

#include "compile_shader.h"

GLuint ReadShader(const std::string &vertex, const std::string& fragment) {
    std::string VertexCode, FragmentCode;

    {
        std::ifstream VertexFile(vertex, std::ios::in);

        if (!VertexFile.is_open()) {
            std::cerr << "Unable to find file " << vertex << std::endl;
            return 0;
        }

        std::stringstream sstr;
        sstr << VertexFile.rdbuf();
        VertexCode = sstr.str();
        VertexFile.close();
    }

    {
        std::ifstream FragmentFile(fragment, std::ios::in);
        std::stringstream sstr;
        sstr << FragmentFile.rdbuf();
        FragmentCode = sstr.str();
        FragmentFile.close();
    }

    return CreateShader(VertexCode, FragmentCode);
}

GLuint CompileShader(const std::string &source, GLenum type) {
    GLuint result = glCreateShader(type);

    const char *src = source.c_str();

    glShaderSource(result, 1, &src, nullptr);
    glCompileShader(result);

    int status;
    glGetShaderiv(result, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetShaderiv(result, GL_INFO_LOG_LENGTH, &length);

        char *message = (char*) alloca(length);
        glGetShaderInfoLog(result, length, &length, message);

        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex\n" : "fragment\n");
        std::cerr << source << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(result);
        return 0;
    }

    return result;
}

GLuint CreateShader(const std::string &vertexShader, const std::string &fragmentShader) {
    GLuint ProgramID = glCreateProgram();

    GLuint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    GLuint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(ProgramID, vs);
    glAttachShader(ProgramID, fs);
    glLinkProgram(ProgramID);
    glValidateProgram(ProgramID);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return ProgramID;
}