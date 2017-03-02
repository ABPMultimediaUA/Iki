#pragma once

#define GLEW_STATIC
#include <glew.h>

#include <SDL2\SDL.h>
#include <string>
#include <iostream>


class TDisplay
{

public:
	TDisplay(int width,int height,const std::string &title);
	void Clear(float r,float g,float b,float a);
	void Update();
	bool IsClosed();
	virtual ~TDisplay();
protected:
private:
	TDisplay(const TDisplay &other) {}
	TDisplay &operator = (const TDisplay &other) {}

	SDL_Window *m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

