#include "LevelData.h"

LevelData::LevelData()
{
    nivel = 0;
    n_enemigos = 2;
    for(int i = 0; i < n_enemigos; i++){
        TPosicion posicion_enem{30.0f, 0.0f, (float)i * 30};
        pos_enemigos.push_back(posicion_enem);
    }
}

LevelData::~LevelData()
{
    //dtor
}

int LevelData::getNivel(){
    return nivel;
}

int LevelData::getNumEnemigos(){
    return n_enemigos;
}

std::vector<LevelData::TPosicion> LevelData::getEnemPosiciones(){
    return pos_enemigos;
}
