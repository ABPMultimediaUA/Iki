#include "Enemies/StateMachine/Percibir.h"
#include "Enemies/StateMachine/Investigar.h"
#include "Enemies/StateMachine/Revivir.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "GameEntity.h"
#include "Enemies/Medico.h"

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
        if( enemigo->ID() != entities[i]->ID() && enemigo->getPosition().Distance(entities[i]->getPosition())<10
                                                            && enemigo->isEnemySeeing(entities[i]->getPosition())){
            //std::cout << "soy " << enemigo->ID() << "y estoy viendo a: " << entities[i]->ID()<< "su vida es: "<<entities[i]->getVida()<<std::endl;
            enemigo->actualizarMemoria(entities[i]); //crea un recuerdo,si ya esta creado lo actualiza
            if(enemigo->getEstadoEntity(entities[i]) == 2 ){ //si el estado del enemigo es muerto
                enemigo->setPosicionInteres(entities[i]->getPosition());
                switch(enemigo->getTipo()){
                    case 1:
                        enemigo->GetFSM()->ChangeState(Investigar::Instance());
                        break;
                    case 2:
                        static_cast<Medico*>(enemigo)->setProtegido(static_cast<Enemy*>(entities[i]));
                        enemigo->GetFSM()->ChangeState(Revivir::Instance());
                        break;

                }
            }
        }
    }

}
void Percibir::Exit(Enemy* enemigo){}
