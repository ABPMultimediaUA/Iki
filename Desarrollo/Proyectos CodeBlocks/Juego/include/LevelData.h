#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>

class LevelData
{
    public:
        typedef struct{
            float X;
            float Y;
            float Z;
            int tipo;
        } TPosicion;

        LevelData();
        virtual ~LevelData();
        int getNivel();
        int getNumEnemigos();
        std::vector<TPosicion> getEnemPosiciones();

    protected:

    private:
        int nivel;
        int n_enemigos;
        //float tam_X;
        //float tam_Y;
        std::vector<TPosicion> pos_enemigos;
};

#endif // LEVELDATA_H
