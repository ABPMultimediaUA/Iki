#include "TCamara.h"

TCamara::TCamara()
{
    esPerspectiva= false;

    vec.push_back(0);
    vec.push_back(0);

    vec2.push_back(0);
    vec2.push_back(0);
}

TCamara::~TCamara()
{
    //dtor
}

void TCamara::setPerspectiva(float x, float y)
{
    vec.at(0)= x;
    vec.at(1)= y;
}
void TCamara::setParalela(float x, float y)
{
    vec2.at(0)= x;
    vec2.at(1)= y;
}
void TCamara::beginDraw()
{
    std::cout << "camara draw()" <<std::endl;
}
void TCamara::endDraw()
{
    //cout << "Desapilamos camara" << endl;
}
