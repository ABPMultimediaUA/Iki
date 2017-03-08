#include "Structs.h"
#include <math.h>

Structs::Structs()
{
    //ctor
}

Structs::~Structs()
{
    //dtor
}

float Structs::distance (TPosicion p1, TPosicion p2)
{
    return (sqrt( pow(p1.Z-p2.Z, 2) + pow(p1.X-p2.X, 2) ));
}
