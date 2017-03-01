#ifndef PATROLROUTE_H
#define PATROLROUTE_H

class PatrolPoint;

class PatrolRoute
{
    public:
        PatrolRoute(PatrolPoint*);
        virtual ~PatrolRoute();

        void setInicial(PatrolPoint* p);
        void setFinal(PatrolPoint* p);


        PatrolPoint* getInicial(){ return inicial; };
        int          getEnemigo(){ return enemigo; };

    protected:

    private:

        int enemigo;

        PatrolPoint* inicial;

};

#endif // PATROLROUTE_H
