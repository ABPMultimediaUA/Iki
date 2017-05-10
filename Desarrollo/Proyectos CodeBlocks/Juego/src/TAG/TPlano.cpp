#include "TPlano.h"

TPlano::~TPlano()
{
    //dtor
}

void TPlano::recalculateD(const TVector& MPoint){
    Distance = - Normal.dotProduct(MPoint);
}

bool TPlano::getIntersectionWithLine(const TVector& linePoint, const TVector& lineVect, TVector& outIntersection){
    float t2 = Normal.dotProduct(lineVect);
    if (t2 == 0)
        return false;

    float t =- (Normal.dotProduct(linePoint) + Distance) / t2;
    outIntersection = linePoint + (lineVect * t);
    return true;
}
