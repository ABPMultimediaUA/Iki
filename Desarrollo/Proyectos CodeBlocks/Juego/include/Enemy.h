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
        virtual void inicializar_enemigo(Map* m)=0;
        virtual void update()=0;
        void init(Map* m);
        void SetID(int val);
        int getID()const{return id;}
        int getTipo(){return tipo;}
        void setPosition(Structs::TPosicion p);
        f32 getTiempo() { return tiempoEnEstado;}
        void resetTime() { tiempoEnEstado = 0;}
        void patrullar();
        void vigilar();
        enum message_type
        {
            Msg_NecesitoAyuda,
            Msg_Alarma,
            Msg_DameTuPosicion
        };

    protected:

        int tipo,direccion;
        PatrolRoute* ruta;
        PatrolPoint* pRuta;
        float sospecha,angulo,avMovement;
        Structs::TPosicion posinit,posaux;
        Map* Mapa;

        f32 tiempoEnEstado;


    private:

        static int m_iNextValidID;

};

#endif // ENEMIGO_H

