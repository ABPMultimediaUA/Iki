#include "LevelData.h"

LevelData::LevelData()
{
    nivel = 0;
    n_enemigos = 2;
    for(int i = 0; i < n_enemigos; i++){
        pos_enemigos.push_back(vector3df(30.f, 0.f, (float)i * 30.f));
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

std::vector<vector3df> LevelData::getEnemPosiciones(){
    return pos_enemigos;
}
