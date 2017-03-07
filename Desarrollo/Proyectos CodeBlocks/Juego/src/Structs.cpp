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
    return (sqrt( pow(p1.Y-p2.Y, 2) + pow(p1.X-p2.Y, 2) ));
}
