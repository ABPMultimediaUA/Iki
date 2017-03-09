#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <GameEntity.h>


class PatrolRoute;
class PatrolPoint;

class Enemy : public GameEntity
{
    public:
        Enemy(){}
        ~Enemy(){}
        virtual void inicializar_enemigo()=0;
        virtual void update()=0;
        void SetID(int val);
        int getID()const{return id;}
        int getTipo(){return tipo;}
        virtual void setPosition(Structs::TPosicion p) {
            body->SetTransform(b2Vec2(p.X, p.Z), 0);
            modelo->setPosition(Structs::TPosicion{body->GetPosition().x, 0, body->GetPosition().y});
            modelo->setRotation(body->GetAngle());
            }
        void patrullar();
        void vigilar();

    protected:
        int id,tipo, direccion;
        PatrolRoute* ruta;
        PatrolPoint* pRuta;
        float sospecha,angulo,avMovement;
        Structs::TPosicion posinit,posaux;

        f32 tiempoEnEstado;


    private:

        static int m_iNextValidID;



        /*PatrolRoute ruta;
        PatrolPoint* pRuta;*/

};

#endif // ENEMIGO_H

