#include "TAG/TRecursoMalla.h"
#include "TAG/TGestorRecursos.h"
#include "TAG/TMalla.h"
#include "TAG/TMotorTAG.h"

#define INVALID_OGL_VALUE 0xffffffff


TRecursoMalla::MeshEntry::MeshEntry()
{

};

TRecursoMalla::MeshEntry::~MeshEntry()
{

}

void TRecursoMalla::MeshEntry::Init(const std::vector<Vertex>& Vertices,const std::vector<unsigned int>& Indices)
{
    NumIndices = Indices.size();

    glGenBuffers(1, &VB);
  	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

TRecursoMalla::TRecursoMalla()
{
}


TRecursoMalla::~TRecursoMalla()
{
    Clear();
}


void TRecursoMalla::Clear()
{

}



bool TRecursoMalla::LoadMesh(const string& FileName)
{
    // Release the previously loaded mesh (if it exists)
    Clear();

    bool Ret = false;
    Assimp::Importer Importer;

    const aiScene* pScene = Importer.ReadFile(FileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    if (pScene)
    {



        Ret = InitFromScene(pScene, FileName);
    }
    else
    {
        cout << "Error parsing: "+FileName+" "+Importer.GetErrorString();
    }

    return Ret;
}

bool TRecursoMalla::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
    m_Entries.resize(pScene->mNumMeshes);
    m_Textures.resize(pScene->mNumMaterials);
    m_material.resize(pScene->mNumMaterials);

    // Initialize the meshes in the scene one by one
    for (unsigned int i = 0 ; i < m_Entries.size() ; i++)
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];



        InitMesh(i, paiMesh);
    }
    return InitMaterials(pScene, Filename);
}

void TRecursoMalla::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
    m_Entries[Index].MaterialIndex = paiMesh->mMaterialIndex;

    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++)
    {
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = &(paiMesh->mNormals[i]);// : &Zero3D
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

        Vertex v(vec3(pPos->x, pPos->y, pPos->z),vec2(pTexCoord->x, pTexCoord->y),vec3(pNormal->x, pNormal->y, pNormal->z));

        Vertices.push_back(v);
    }

    for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++)
    {
        const aiFace& Face = paiMesh->mFaces[i];
        assert(Face.mNumIndices == 3);
        Indices.push_back(Face.mIndices[0]);
        Indices.push_back(Face.mIndices[1]);
        Indices.push_back(Face.mIndices[2]);
    }

    m_Entries[Index].Init(Vertices, Indices);
}

void TRecursoMalla::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0 ; i < m_Entries.size() ; i++) {
        glBindBuffer(GL_ARRAY_BUFFER, m_Entries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Entries[i].IB);

        const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

        if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex])
        {
            m_Textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

bool TRecursoMalla::InitMaterials(const aiScene* pScene, const std::string& FileName)
{

    bool Ret = false;

    std::string::size_type SlashIndex = FileName.find_last_of("/");
    std::string Dir;

    Dir = FileName.substr(0, SlashIndex);

    for (unsigned int i = 0 ; i < pScene->mNumMaterials ; i++)
    {
        const aiMaterial* pMaterial = pScene->mMaterials[i];

        //const aiMaterial* mat = pScene->mMaterials[m_Entries[i].MaterialIndex];
        m_material[i] = new TRecursoMaterial(pMaterial);

       // m_materials[i] = NULL;
      //  m_materials[i] = new TRecursoMaterial(pMaterial);
        //  m_Textures[i] = NULL;

        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString Path;

            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {

                std::string relativa = Path.data;

                std::string::size_type slashIndex2 = relativa.find_last_of("\\");
                std::string Dir2 = relativa.substr(slashIndex2+1,relativa.size()-slashIndex2);
                std::string FullPath = Dir + "/" + Dir2;

                m_Textures[i] = TGestorRecursos::getRecursoTextura(FullPath.c_str());

            }
        }
    }

    return Ret;
}



void TRecursoMalla::beginDraw()
{
    Render();
}

void TRecursoMalla::endDraw()
{

}

