#ifndef EDGE
#define EDGE

#include <irrlicht.h>


class Edge
{
    public:
        Edge(int desde, int hacia):from(desde),to(hacia),cost(1.0){}
        Edge(int desde, int hacia, float coste):from(desde),to(hacia),cost(coste){}
        Edge(float coste):from(-1.0),to(-1.0),cost(coste){}
        Edge(){}
        virtual ~Edge(){}

        int From()const;
        void setFrom(int newIndex);

        int To()const;
        void setTo(int newIndex);

        float Cost()const;
        void setCost(float newCost);

        enum BehaviorType
        {
            normal = 1 << 0,
            tippy_toe = 1 << 1,
            swim = 1 << 2,
            crawl = 1 << 3,
            creep = 1 << 4
        };

    protected:
        //un edge conecta dos nodos, from y to siempre positivos
        int from;
        int to;
        float cost;//coste entre los nodos
        //the behavior associated with traversing this edge
        BehaviorType behavior;

    private:
        irr::core::vector3df posicion;
        //extra_info extra_info; si queremos que el nodo represente un pickup como armadura, vida, etc y luego poder buscarlo en el grafo
};

#endif // EDGE
