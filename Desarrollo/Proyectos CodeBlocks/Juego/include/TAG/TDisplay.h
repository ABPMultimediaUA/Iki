#pragma once

#define GLEW_STATIC
#include <glew.h>

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class TDisplay
{

public:
	TDisplay(int width,int height,const std::string &title);
	bool isOpen();
	void Display();
    void setStyle(sf::Window window, sf::Uint32 style);
	void Clear(float r,float g,float b,float a);
	void Update();
	void Draw(sf::Sprite s);
	void Draw2(){m_window.pushGLStates();};
	void Draw3(){m_window.popGLStates();};
    void setModoVentana();
	void setFullScreen();
	sf::Time getTimer();
	~TDisplay();

	int getWidth() { return m_window.getSize().x; }
	int getHeigth(){ return m_window.getSize().y; }

	//bool Evented();

protected:


private:
	sf::RenderWindow m_window;
    sf::Context m_glContext;
    sf::Clock clock;
    bool running;
	sf::View* view;
	sf::Vector2f* tam;
	sf::Vector2f* centro;
	bool full = true;

};

