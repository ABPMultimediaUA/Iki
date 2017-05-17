#include "Enemies/StateMachine/Percibir.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "GameEntity.h"

Percibir* Percibir::Instance()
{
  static Percibir instance;

  return &instance;
}

void Percibir::Enter(Enemy* enemigo){
    entities = EntityMgr->getEntities();
    enter = true;
}

void Percibir::Execute(Enemy* enemigo){
    if(!enter)
        Enter(enemigo);
    for(int i=0; i < entities.size(); i++){
        if( enemigo->ID() != entities[i]->ID() && entities[i]->isEnemy() && enemigo->getPosition().Distance(entities[i]->getPosition())<10 && enemigo->isEnemySeeing(entities[i]->getPosition())){
               // std::cout<<"vida:"<<entities[i]->getVida()<<std::endl;
                if(entities[i]->getVida() == 0.0)
                    std::cout<<"Esta muertooo locoooo"<<std::endl;
        }
    }

}
void Percibir::Exit(Enemy* enemigo){}
