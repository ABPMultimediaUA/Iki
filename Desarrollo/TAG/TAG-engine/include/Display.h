#pragma once

#define GLEW_STATIC
#include <glew.h>

#include <SDL2\SDL.h>
#include <string>
#include <iostream>


class Display
{

public:
	Display(int width,int height,const std::string &title);
	void Clear(float r,float g,float b,float a);
	void Update();
	bool IsClosed();
	virtual ~Display();
protected:
private:
	Display(const Display &other) {}
	Display &operator = (const Display &other) {}

	SDL_Window *m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};

