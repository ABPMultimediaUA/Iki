#include "TMalla.h"
#include "TTransform.h"


#include "TGestorRecursos.h"
#include "TMotorTAG.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>



TMalla::~TMalla()
{
    //dtor
}

void TMalla::beginDraw()
{
		/*	m_MV = TCamara::viewMatrix * TTransform::pila.top();
			m_MVP = TCamara::viewProjectionMatrix * TTransform::pila.top();
			m_NormalMatrix = glm::transpose(glm::inverse(m_MV));

            printMatrices();

			TMotorTAG::TAGShader.setUniform(TShader::Uniforms::MV_U, m_MV);
			TMotorTAG::TAGShader.setUniform(TShader::Uniforms::MVP_U, m_MVP);
			TMotorTAG::TAGShader.setUniform(TShader::Uniforms::NORMAL_U, m_NormalMatrix);*/

			m_RecursoMalla->beginDraw();
}

void TMalla::endDraw()
{

}

void TMalla::loadMesh(const std::string& fileName)
{
    m_RecursoMalla = TGestorRecursos::getRecursoMalla(fileName);
}


const bool& TMalla::getView() const
{
    return m_view;
}


void TMalla::setView(const bool& view)
{
    m_view = view;
}

void TMalla::printMatrices() {

		std::cout << "\n m_MVP:\n";
		glm::vec4 fil1_MVP(m_MVP[0][0], m_MVP[0][1], m_MVP[0][2], m_MVP[0][3]);
		glm::vec4 fil2_MVP(m_MVP[1][0], m_MVP[1][1], m_MVP[1][2], m_MVP[1][3]);
		glm::vec4 fil3_MVP(m_MVP[2][0], m_MVP[2][1], m_MVP[2][2], m_MVP[2][3]);
		glm::vec4 fil4_MVP(m_MVP[3][0], m_MVP[3][1], m_MVP[3][2], m_MVP[3][3]);

		std::cout << glm::to_string(fil1_MVP) << std::endl;
		std::cout << glm::to_string(fil2_MVP) << std::endl;
		std::cout << glm::to_string(fil3_MVP) << std::endl;
		std::cout << glm::to_string(fil4_MVP) << std::endl;

		std::cout << "\nm_NormalMatrix:\n";
		glm::vec4 fil1_N(m_NormalMatrix[0][0], m_NormalMatrix[0][1], m_NormalMatrix[0][2], m_NormalMatrix[0][3]);
		glm::vec4 fil2_N(m_NormalMatrix[1][0], m_NormalMatrix[1][1], m_NormalMatrix[1][2], m_NormalMatrix[1][3]);
		glm::vec4 fil3_N(m_NormalMatrix[2][0], m_NormalMatrix[2][1], m_NormalMatrix[2][2], m_NormalMatrix[2][3]);
		glm::vec4 fil4_N(m_NormalMatrix[3][0], m_NormalMatrix[3][1], m_NormalMatrix[3][2], m_NormalMatrix[3][3]);

		std::cout << glm::to_string(fil1_N) << std::endl;
		std::cout << glm::to_string(fil2_N) << std::endl;
		std::cout << glm::to_string(fil3_N) << std::endl;
		std::cout << glm::to_string(fil4_N) << std::endl;

		std::cout << std::endl;


}
