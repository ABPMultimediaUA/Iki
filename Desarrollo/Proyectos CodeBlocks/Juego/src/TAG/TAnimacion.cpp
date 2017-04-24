#include "TAnimacion.h"
#define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
#include <sstream>


TAnimacion::TAnimacion(const unsigned int& length)
{
    m_longitud = length;
}

TAnimacion::~TAnimacion()
{
    for(unsigned int i=0;i<m_longitud;i++)
    {
        SAFE_DELETE(animacion[i]);
    }
}

void TAnimacion::cargarAnimacion(const std::string& fileName)
{
        std::string finalPath;
        string Result;//string which will contain the result
        ostringstream convert; // stringstream used for the conversion


		for (int i = 0; i <= m_longitud; i++)
        {
            int u = i;
            Result = static_cast<ostringstream*>( &(ostringstream() << u) )->str();


			if (i <= 9)
			{
				finalPath = fileName + "00000" + Result + ".obj";

			}
			else if (i <= 99)
			{
				finalPath = fileName + "0000" + Result + ".obj";
			}
			else
            {
				finalPath = fileName + "000" + Result + ".obj";
			}

			//cout << "Animacion: " << finalPath << endl;

			TMalla* malla = new TMalla();
			malla->loadMesh(finalPath);
			animacion[i] = malla;
		}
		cout << "Animacion cargada" <<endl;

}

void TAnimacion::beginDraw()
{
    animacion[frames]->beginDraw();
}

void TAnimacion::endDraw()
{
    animacion[frames]->endDraw();
    frames++;

    if(frames >= m_longitud)
    {
        frames = 0;
    }
}
