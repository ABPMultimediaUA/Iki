#include "TDraw2D.h"

TDraw2D::TDraw2D(const std::string filename, sf::Vector2i rectam)
{
    sf::IntRect rectangulo(sf::Vector2i(0, 0), rectam);
    m_rectangle = rectangulo;



    if(!m_texture.loadFromFile(filename))
        std::cerr << "Error al inicializar" << filename <<std::endl;


    m_texture.loadFromFile(filename, m_rectangle);

    sf::Sprite sprite(m_texture, m_rectangle);

    m_sprite = sprite;

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
