#ifndef TRECURSOMALLA_H
#define TRECURSOMALLA_H

#define GLEW_STATIC
#include <glew.h>

#include <glm\glm.hpp>
#include <TAG/TEntidad.h>
#include <TAG/TTextura.h>
#include "TRecursoMaterial.h"

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

using namespace std;
using namespace glm;




class Vertex
{
public:
	Vertex(const vec3& pos, const vec2& texCoord, const vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	inline glm::vec3* getPos() { return &pos; }
	inline glm::vec3* getNormal() { return &normal; }
	inline glm::vec2* getTexCoord() { return &texCoord; }

protected:
private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};


class TRecursoMalla : public TEntidad
{
    public:
        TRecursoMalla();
        virtual ~TRecursoMalla();
        bool LoadMesh(const std::string& FileName);
        void Render();


        void beginDraw();
        void endDraw();

    protected:

    private:
        bool InitFromScene(const aiScene* pScene, const std::string& Filename);
        void InitMesh(unsigned int Index, const aiMesh* paiMesh);
        bool InitMaterials(const aiScene* pScene, const std::string& Filename);
        void Clear();

#define INVALID_MATERIAL 0xFFFFFFFF

    struct MeshEntry{

            MeshEntry();

            ~MeshEntry();

            void Init(const vector<Vertex>& Vertices,const vector<unsigned int>& Indices);


            GLuint VB;
            GLuint IB;
            unsigned int NumIndices;
            unsigned int MaterialIndex;
    };

    vector<MeshEntry> m_Entries;
    vector<TRecursoMaterial*> m_material;
    vector<TTextura*> m_Textures; // sustituir tipo -> texturs

};

#endif // TMALLA_H

