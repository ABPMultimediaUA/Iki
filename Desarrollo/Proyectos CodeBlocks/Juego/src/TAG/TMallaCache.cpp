#include "TMallaCache.h"

TMallaCache::TMallaCache()
{
    //ctor
}

TMallaCache::~TMallaCache()
{
    //dtor
}

TRecursoMalla* TMallaCache::getRecursoMalla(const std::string& fileName)
{
		//lookup the mesh and see if its in the map
		auto mit = m_MapaMalla.find(fileName);

		//check if its not in the map
		if (mit == m_MapaMalla.end())
        {
			//Load the mesh
			TRecursoMalla* newMalla = new TRecursoMalla();
			newMalla->LoadMesh(fileName);
			//Insert the mesh into the map
			m_MapaMalla.insert(make_pair(fileName, newMalla));

			return newMalla;
		}

		return mit->second;
}
