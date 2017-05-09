#include "TPlano.h"

TPlano::~TPlano()
{
    //dtor
}

void recalculateD(const TVector& MPoint){
    Distance = - MPoint.dotProduct(Normal);
}

bool getIntersectionWithPlane(const TVector& linePoint, const TVector& lineVect, TVector& outIntersection){
    T t2 = Normal.dotProduct(lineVect);
    if (t2 == 0)
        return false;

    T t =- (Normal.dotProduct(linePoint) + D) / t2;
    outIntersection = linePoint + (lineVect * t);
    return true;
}
