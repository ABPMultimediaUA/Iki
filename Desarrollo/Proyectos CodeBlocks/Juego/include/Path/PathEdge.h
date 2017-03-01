#ifndef PATHEDGE
#define PATHEDGE

#include <irrlicht.h>
#include <enemigo.h>
#include <SparseGraph.h>

class PathEdge
{
    public:PathEdge(irr::core::vector3df Source,irr::core::vector3df Destination,int Behavior)
                    :desde(Source),
                     hasta(Destination),
                     behavior(Behavior){}

    irr::core::vector3df getDestination()const{return hasta;}
    void SetDestination(irr::core::vector3df NewDest){hasta=NewDest;}
    irr::core::vector3df getSource()const{return desde;}
    void SetSource(irr::core::vector3df NewSource){desde=NewSource;}
    int Behavior()const;


    protected:

    private:
        //positions of the source and destination nodes this edge connects
        irr::core::vector3df desde;
        irr::core::vector3df hasta;
        //the behavior associated with traversing this edge
        int behavior;
};

#endif // PATHEDGE
