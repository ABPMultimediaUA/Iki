#ifndef PATROLROUTE_H
#define PATROLROUTE_H

#include "PatrolPoint.h"

class PatrolRoute
{
    public:
        PatrolRoute();
        virtual ~PatrolRoute();

        void setInicial(PatrolPoint* p);
        void setFinal(PatrolPoint* p);
        PatrolPoint* getInicial();
        PatrolPoint* getFinal();

        void changeOcupada();
        bool isOcupada();


    protected:

    private:
        bool ocupada;

        //class PatrolPoint* puntoObjetivo;
        class PatrolPoint* inicial;
        class PatrolPoint* final;

};

#endif // PATROLROUTE_H
