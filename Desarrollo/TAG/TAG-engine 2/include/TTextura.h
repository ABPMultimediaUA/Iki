//#ifndef TTEXTURA_H
//#define TTEXTURA_H

#include <string>


#include <GL/glew.h>
#include <ImageMagick-6/Magick++.h>

//using namespace std;

class TTextura
{
    public:
    TTextura(GLenum TextureTarget, const std::string& FileName);

    bool Load();

    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
    Magick::Image m_image;
    Magick::Blob m_blob;
};

//#endif // TTEXTURA_H
