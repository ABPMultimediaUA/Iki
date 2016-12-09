#include "World.h"

World::World()
{
    datos_nivel = new LevelData;
}

World::~World()
{
    datos_nivel = nullptr;
}

void inicializar_mundo(){
    mapa->inicializar_mapa(datos_nivel->getNivel());
    std::vector<TPosicion> posiciones = datos_nivel->getEnemPosiciones();
    for(std::vector<TPosicion>::iterator it = posiciones.begin(); it != posiciones.end(); ++it){
        Enemy *enemigo = new Enemy;
        enemigo->inicializar_enem(it.X, it.Y, it.Z, it.tipo);
        enemigos.push_back(enemigo);
    }
}

void update_mundo(){
    for(std::vector<Enemy*>::iterator it = enemigos.begin(); it != posiciones.end(); ++it){
        it->update_enem();
    }
    mapa->update_mapa();
}
