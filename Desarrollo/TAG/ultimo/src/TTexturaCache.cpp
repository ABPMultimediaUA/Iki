#include "TTexturaCache.h"

TTexturaCache::TTexturaCache()
{
    //ctor
}

TTexturaCache::~TTexturaCache()
{
    //dtor
}

TTextura* TTexturaCache::getRecursoTextura(const std::string& fileName)
{
    auto mit = m_MapaTextura.find(fileName);

		//check if its not in the map
		if (mit == m_MapaTextura.end())
        {
			//Load the texture
			TTextura* newTextura = new TTextura(fileName);
			//Insert the texture into the map
			m_MapaTextura.insert(make_pair(fileName, newTextura));

			return newTextura;
		}

		return mit->second;
}
