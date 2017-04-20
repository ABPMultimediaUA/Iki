#ifndef TRECURSOMATERIAL_H
#define TRECURSOMATERIAL_H

#include <string>
#include <glm\glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <assimp\scene.h>

class TRecursoMaterial
{
    public:
        TRecursoMaterial(const aiMaterial* material);
        virtual ~TRecursoMaterial();
        void update();
        void mostrarMaterial();
    protected:
    private:
        float m_Ns;
		glm::vec3 m_Ka;
		glm::vec3 m_Kd;
		glm::vec3 m_Ks;
		glm::vec3 m_Ke;
		float m_Ni;
		float m_d;
		int m_illum;
};

#endif // TRECURSOMATERIAL_H
