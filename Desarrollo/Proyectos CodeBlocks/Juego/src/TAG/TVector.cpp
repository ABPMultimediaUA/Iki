#include "TVector.h"

TVector::~TVector()
{
    //dtor
}

float dotProduct(TVector other){
    return X*other.X + Y*other.Y + Z*other.Z;
}
