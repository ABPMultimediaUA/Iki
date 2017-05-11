#include "TDisplay.h"

TDisplay::TDisplay(int width, int height, const std::string &title)
{

	m_window.create(sf::VideoMode(width, height), title);

    running= true;

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Error al inicializar el display" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

TDisplay::~TDisplay()
{

}

bool TDisplay::isOpen()
{
    return running;
}

void TDisplay::Update()
{
	sf::Event event;

    while(m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            running = false;

            break;

        }
    }
}

void TDisplay::Clear(float r,float g,float b,float a)
{
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void TDisplay::Display()
{
    m_window.display();
}
/*
void TDisplay::setModoVentana()
{
    SDL_SetWindowFullscreen(m_window, 0);
    SDL_SetWindowSize(m_window, 1360, 768);
}
/*
void TDisplay::setFullScreen()
{
   SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
}

Uint32 TDisplay::getTimer()
{
    return SDL_GetTicks();
}
*/





