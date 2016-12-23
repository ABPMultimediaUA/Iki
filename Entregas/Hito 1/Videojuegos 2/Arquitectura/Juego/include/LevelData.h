#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>

#include <irrlicht.h>
#include <Box2D/Box2D.h>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de vídeo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;


class LevelData
{
    public:

        LevelData();
        virtual ~LevelData();
        int getNivel();
        int getNumEnemigos();
        std::vector<vector3df> getEnemPosiciones();

    protected:

    private:
        int nivel;
        int n_enemigos;
        //float tam_X;
        //float tam_Y;
        std::vector<vector3df> pos_enemigos;
};

#endif // LEVELDATA_H
