#include "TVector.h"

TVector::TVector(T x1, T y1, T z1)
{
    x = x1;
    y = y1;
    z = z1;
}

TVector::~TVector()
{
    //dtor
}

T dotProduct(TVector other){
    return x*other.x + y*other.y + z*other.z;
}
