#include "Enemies/StateMachine/Percibir.h"
#include "Enemies/StateMachine/Investigar.h"
#include "Enemies/StateMachine/Revivir.h"
#include "Enemies/StateMachine/Alarma.h"
#include "Enemy.h"
#include "EntityManager.h"
#include "GameEntity.h"
#include "Enemies/Medico.h"

#include "Trigger.h"
#include "TriggerSystem.h"

Percibir* Percibir::Instance()
{
  static Percibir instance;

  return &instance;
}

void Percibir::Enter(Enemy* enemigo){
    entities = EntityMgr->getEntities();
    std::vector<Trigger*> triggers = TriggerSystem::getInstance()->GetTriggers();
    for(int i=0;i < triggers.size();i++){
        if(triggers[i]->isPuerta())
        entities.push_back(triggers[i]);
    }
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
                    case 3:
                        enemigo->GetFSM()->ChangeState(Alarma::Instance());

                }
            }
        }
        else if(entities[i]->isTrigger() && enemigo->getPosition().Distance(entities[i]->getPosition())<10){
                enemigo->actualizarMemoria(entities[i]);
               if(enemigo->getEstadoEntity(entities[i]) == 3){
                    std::cout<<"veo una puerta abierta locoooo"<<std::endl;//si la puerta esta abierta
                    //enemigo->GetFSM()->ChangeState(Investigar::Instance());
               }
               // std::cout<<"esto es un puto trigger"<<entities[i]->getPosition().X<<std::endl;
        }
    }
}
void Percibir::Exit(Enemy* enemigo){}
