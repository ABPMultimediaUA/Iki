#include "TAG/TRecursoMaterial.h"
#include "TAG/TMotorTAG.h"

//#include <glm/gtx/string_cast.hpp>


TRecursoMaterial::TRecursoMaterial(const aiMaterial* material)
{


		aiColor3D Ka;
		material->Get(AI_MATKEY_COLOR_AMBIENT, Ka);
		m_Ka.x = Ka.r;
		m_Ka.y = Ka.g;
		m_Ka.z = Ka.b;

		aiColor3D Kd;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, Kd);
		m_Kd.x = Kd.r;
		m_Kd.y = Kd.g;
		m_Kd.z = Kd.b;

		aiColor3D Ks;
		material->Get(AI_MATKEY_COLOR_SPECULAR, Ks);
		m_Ks.x = Ks.r;
		m_Ks.y = Ks.g;
		m_Ks.z = Ks.b;

		aiColor3D Ke;
		material->Get(AI_MATKEY_COLOR_EMISSIVE, Ke);
		m_Ke.x = Ke.r;
		m_Ke.y = Ke.g;
		m_Ke.z = Ke.b;


		material->Get(AI_MATKEY_REFRACTI, m_Ni);

		material->Get(AI_MATKEY_OPACITY, m_d);

		material->Get(AI_MATKEY_SHADING_MODEL, m_illum);

		material->Get(AI_MATKEY_SHININESS, m_Ns);

		//mostrarMaterial();
}

TRecursoMaterial::~TRecursoMaterial()
{
    //dtor
}

void TRecursoMaterial::update()
{
//    TMotorTAG::TAGShader.setUniform(TShader::Uniforms::SHININESS_U, m_Ns); //falta crear tagshader en la fachada.
//    TMotorTAG::TAGShader.setUniform(TShader::Uniforms::KA_U, m_Ka);
//    TMotorTAG::TAGShader.setUniform(TShader::Uniforms::KD_U, m_Kd);
//    TMotorTAG::TAGShader.setUniform(TShader::Uniforms::KS_U, m_Ks);
}

void TRecursoMaterial::mostrarMaterial()
{
        std::cout << "\n";
        std::cout << "ns: " << m_Ns << std::endl;
		std::cout << "ka: " << glm::to_string(m_Ka) << std::endl;
		std::cout << "kd: " << glm::to_string(m_Kd) << std::endl;
		std::cout << "ks: " << glm::to_string(m_Ks) << std::endl;
		std::cout << "ke: " << glm::to_string(m_Ke) << std::endl;
		std::cout << "Ni: " << m_Ni << std::endl;
		std::cout << "d: " << m_d << std::endl;
		std::cout << "illum: " << m_illum << std::endl;
		std::cout << "\n";
}


