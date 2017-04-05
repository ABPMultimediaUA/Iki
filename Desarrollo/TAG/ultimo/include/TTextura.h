#ifndef TTEXTURA_H
#define TTEXTURA_H

#define GLEW_STATIC
#include <glew.h>

#include <iostream>
#include "TEntidad.h"
#include "stb_image.h"

class TTextura
{
    public:
        TTextura(const std::string& FileName);
        virtual ~TTextura();

        //bool Load();
        void Bind(GLenum TextureUnit);

    protected:
    private:
        GLuint m_texture;
        std::string m_FileName;

};

#endif // TTEXTURA_H
