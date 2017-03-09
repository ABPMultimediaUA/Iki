#include "Path/Edge.h"


float Edge::Cost() const{
    return cost;
}
void Edge::setCost(float newCost){
    cost=newCost;
}
int Edge::From() const{
    return from;
}
void Edge::setFrom(int newFrom){
    from= newFrom;
}
int Edge::To() const{
    return to;
}
void Edge::setTo(int newTo){
    to=newTo;
}
