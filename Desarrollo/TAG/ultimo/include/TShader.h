#ifndef TSHADER_H
#define TSHADER_H

#define GLEW_STATIC
#include <glew.h>

#include "TTransform.h"
#include "TCamara.h"


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class TShader
{
    public:
        TShader(const string& FileName);
        void Bind();
        void Update(TCamara* camara);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
        string LoadShader(const string& fileName);
        GLuint CreateShader(const string& text, GLenum shaderType);
        virtual ~TShader();
        static mat4 viewMatrix;

    protected:

    private:
        static const unsigned int NUM_SHADERS = 2;

        enum
        {
            TRANSFORM_U,
            NUM_UNIFORMS
        };

        GLuint m_programa;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // TSHADER_H
