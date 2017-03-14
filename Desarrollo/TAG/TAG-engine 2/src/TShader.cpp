#include "TShader.h"

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

	glLinkProgram(m_programa);
	CheckShaderError(m_programa, GL_LINK_STATUS,true,"Error: Program linking failed");

	glValidateProgram(m_programa);
	CheckShaderError(m_programa, GL_VALIDATE_STATUS, true, "Error: Program is invalid");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_programa, "transform");
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

void TShader::Update(const TTransform& transform, const TCamara& camera)
{
	//glm::mat4 model = camera.getViewProjection() * transform.GetModel();  // falta transform.
    glm::mat4 model = camera.getViewProjection() * transform.GetModel();  // falta transform.

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
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
