#include "TDraw2D.h"

TDraw2D::TDraw2D(const std::string filename)
{
    if(!m_texture.loadFromFile(filename))
        std::cerr << "Error al inicializar" << filename <<std::endl;

    m_texture.loadFromFile(filename);


    m_sprite.setTexture(m_texture);
}

void TDraw2D::setPosition(float x, float y)
{
    m_sprite.setPosition(x, y);
}

sf::Sprite TDraw2D::getSprite()
{
    return m_sprite;
}

TDraw2D::~TDraw2D()
{
    //dtor
}