#ifndef NAVGRAPH
#define NAVGRAPH

#include <irrlicht.h>
#include <enemigo.h>

class Heuristic_Euclid
{
public:
Heuristic_Euclid(){}
//calculate the straight-line distance from node nd1 to node nd2
template <class graph_type>
static double Calculate(const graph_type& G, int nd1, int nd2)
{
return Vec2DDistance(G.GetNode(nd1).Position, G.GetNode(nd2).Position);
}
};
#endif // NAVGRAPH
