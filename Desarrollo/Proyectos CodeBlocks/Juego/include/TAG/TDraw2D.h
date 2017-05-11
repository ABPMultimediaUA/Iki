#ifndef TDRAW2D_H
#define TDRAW2D_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class TDraw2D
{
    public:
        TDraw2D(const std::string filename);
        virtual ~TDraw2D();

        sf::Sprite getSprite();
        void setPosition(float x, float y);

    protected:

    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;

};

#endif // TDRAW2D_H
