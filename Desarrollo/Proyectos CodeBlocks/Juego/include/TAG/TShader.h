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
        TShader(const std::string& FileName);
        void Bind();
        void DesBind();
        GLuint getShader(){return m_programa;};
        void Update(TCamara* camara);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
        std::string LoadShader(const std::string& fileName);
        GLuint CreateShader(const std::string& text, GLenum shaderType);
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
