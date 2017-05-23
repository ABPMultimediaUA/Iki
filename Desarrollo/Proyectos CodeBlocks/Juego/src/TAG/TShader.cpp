#include "TShader.h"

glm::mat4 TShader::viewMatrix;

TShader::TShader(const string& FileName)
{
    m_programa = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(FileName + ".vs"),GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(FileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i=0;i < NUM_SHADERS;i++)
	{
		glAttachShader(m_programa,m_shaders[i]);
	}

	glBindAttribLocation(m_programa, 0, "position");
	glBindAttribLocation(m_programa, 1, "texCoord");
	glBindAttribLocation(m_programa, 2, "normal");


    std::cout<<glGetError()<<std::endl;
	glLinkProgram(m_programa);
	CheckShaderError(m_programa, GL_LINK_STATUS,true,"Error: Program linking failed");

	glValidateProgram(m_programa);
	CheckShaderError(m_programa, GL_VALIDATE_STATUS, true, "Error: Program is invalid");
/*
    //Pasamos la matriz de proyeccion
    m_uniforms[PROJECTION_MTX] = glGetUniformLocation(m_programa,  "projection");
    glUniformMatrix4fv(m_uniforms[PROJECTION_MTX], 1, GL_FALSE, camera->getMatrizProyeccion());
*/
	//Pasamos la matriz view
	m_uniforms[VIEW_MTX] = glGetUniformLocation(m_programa, "view");
	glUniformMatrix4fv(m_uniforms[VIEW_MTX], 1, GL_FALSE, glm::value_ptr(TShader::viewMatrix));
/*
	//Pasamos la matriz model
    m_uniforms[MODEL_VIEW_MTX] = glGetUniformLocation(m_programa, "model");
    glUniformMatrix4fv(m_uniforms[MODEL_VIEW_MTX], 1, GL_FALSE, ms_gmatriz);

*/
    //Pasamos el vector posicion de la luz
    m_uniforms[LIGHT_POSITION] = glGetUniformLocation(m_programa, "lightPos");
    glUniform3f(m_uniforms[LIGHT_POSITION], 0, 0, 0);

    //Pasamos el color de la luz
    m_uniforms[LIGHT_COLOR] = glGetUniformLocation(m_programa, "lightColor");
    glUniform3f(m_uniforms[LIGHT_COLOR], 1.f, 1.f, 1.f);


	//m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_programa, "transform");
	std::cout<<"Shader cargado"<<std::endl;
}

TShader::~TShader()
{
    for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_programa, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_programa);
}

void TShader::Bind()
{
	glUseProgram(m_programa);
}



void TShader::Update(TCamara* camera)
{
    glUniformMatrix4fv(m_uniforms[VIEW_MTX], 1, GL_FALSE, glm::value_ptr(TShader::viewMatrix));
    glUniformMatrix4fv(m_uniforms[PROJECTION_MTX], 1, GL_FALSE, glm::value_ptr(camera->getMatrizProyeccion()));
    //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(ms_gmatriz));

 	glUseProgram(0);
}

void TShader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader,flag,&success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader,sizeof(error),NULL,error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": " << error << "'" << std::endl;
	}
}

string TShader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file,line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader" << fileName << std::endl;
	}

	return output;
}

GLuint TShader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1,shaderSourceStrings,shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed");


	return shader;
}

void TShader::setUniform(const GLuint& id, float x, float y, float z)
{
	glUniform3f(m_uniforms[id], x, y, z);
}

void TShader::setUniform(const GLuint& id, const glm::vec3& v)
{
	glUniform3fv(m_uniforms[id], 1, &v[0]);
}

void TShader::setUniform(const GLuint& id, const glm::vec4& v)
{
	glUniform4fv(m_uniforms[id], 1, &v[0]);
}

void TShader::setUniform(const GLuint& id, const glm::mat4& m)
{
	glUniformMatrix4fv(m_uniforms[id], 1, GL_FALSE, glm::value_ptr(m));
}

void TShader::setUniform(const GLuint& id, const glm::mat3& m)
{
	glUniformMatrix3fv(m_uniforms[id], 1, GL_FALSE, glm::value_ptr(m));

}
void TShader::setUniform(const GLuint& id, float val)
{
	glUniform1f(m_uniforms[id], val);
}

void TShader::setUniform(const GLuint& id, int val)
{
	glUniform1i(m_uniforms[id], val);
}
