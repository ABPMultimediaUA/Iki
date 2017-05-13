#include "TTextura.h"

TTextura::TTextura(const std::string& FileName)
{
    m_FileName = FileName;

     int width, height, numComponents;
	unsigned char* imageData = stbi_load((m_FileName).c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << m_FileName << std::endl;

	}

	glGenTextures(1,&m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width,height, 0, GL_RGBA, GL_UNSIGNED_BYTE,imageData);

	stbi_image_free(imageData);

	glBindTexture(GL_TEXTURE_2D, 0);

}

/*bool TTextura::Load()
{
    int width, height, numComponents;
	unsigned char* imageData = stbi_load((m_FileName).c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << m_FileName << std::endl;
		return false;
	}

	glGenTextures(1,&m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width,height, 0, GL_RGBA, GL_UNSIGNED_BYTE,imageData);

	stbi_image_free(imageData);

	return true;
}*/

TTextura::~TTextura()
{
    glDeleteTextures(1, &m_texture);
}

void TTextura::Bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

