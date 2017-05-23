#ifndef TSHADER_H
#define TSHADER_H

#define GLEW_STATIC
#include <glew.h>

#include "TTransform.h"
#include "TCamara.h"

#include <iostream>
#include <fstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

class TShader
{
    public:
        enum Uniforms {
            PROJECTION_MTX,             //PROJECTION MATRIX
            VIEW_MTX,				    //VIEW MATRIX
            MODEL_VIEW_MTX,             //MODEL_PROJECTION_MATRIX
            NORMAL_MTX,			        //NORMAL MATRIX

            LIGHT_POSITION,	            //LIGHT POSITION IN VIEW_SPACE
            LIGHT_INTESITY,	            //LIGHT INTENSITY COMPONENT
            LIGHT_COLOR,                //LIGHT COLOR

            KD_U,				        //MATERIAL DIFFUSE COMPONENT
            KA_U,				        //MATERIAL AMBIENT COMPONENT
            KS_U,				        //MATERIAL SPECULAR COMPONENT
            SHININESS_U,		        //MATERIAL SHININESS COMPONENT

            SAMPLER_U,		            //SAMPLER FOR TEXTURE
            TRANSFORM_U,
            NUM_UNIFORMS
        };

        TShader(const string& FileName);
        void Bind();
        void DesBind();
        GLuint getShader(){return m_programa;};
        void Update(TCamara* camara);
        void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
        string LoadShader(const string& fileName);
        GLuint CreateShader(const string& text, GLenum shaderType);
        virtual ~TShader();

        static glm::mat4 viewMatrix;

        void setUniform(const GLuint& id, float x, float y, float z);
        void setUniform(const GLuint& id, const glm::vec3& v);
        void setUniform(const GLuint& id, const glm::vec4& v);
        void setUniform(const GLuint& id, const glm::mat3& m);
        void setUniform(const GLuint& id, const glm::mat4& m);
        void setUniform(const GLuint& id, float val);
        void setUniform(const GLuint& id, int val);

    protected:

    private:
        static const unsigned int NUM_SHADERS = 2;

        GLuint m_programa;
        GLuint m_shaders[NUM_SHADERS];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // TSHADER_H
