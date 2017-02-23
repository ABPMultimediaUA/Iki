#ifndef TCAMARA_H
#define TCAMARA_H

//#include <iostream>
//#include <vector>

#include <TEntidad.h>

//#include <glm\glm.hpp>
//#include <glm\gtx\transform.hpp>


class TCamara : TEntidad
{
public:
	TCamara(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);


    virtual ~TCamara();
    void setPerspectiva(float sup, float inf, float izq, float dch, float cer, float lej);
    void setParalela(float sup, float inf, float izq, float dch, float cer, float lej);

	inline glm::mat4 getViewProjection() const
	{
		return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
	}

	void beginDraw();
    void endDraw();

protected:
private:
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	bool esPerspectiva;
    float superior, inferior, izquierda, derecha, cercano, lejano;
};

#endif // TCAMARA_H
