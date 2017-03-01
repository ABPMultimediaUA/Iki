#ifndef SHADER_H
#define SHADER_H

//#include <GL/gl.h>
//#include <GL\glew.h>





#include "TTransform.h"
#include "TCamara.h"

#include <TEntidad.h>





class Shader
{
public:
	Shader(const std::string& fileName);
	void Bind();
	void Update(const TTransform& transform, const TCamara& camera);
	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	Shader(const Shader& other) {}
	void operator = (const Shader& other) {}

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
