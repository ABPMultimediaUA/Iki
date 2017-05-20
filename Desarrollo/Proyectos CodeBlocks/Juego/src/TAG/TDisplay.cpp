#include "TDisplay.h"

TDisplay::TDisplay(int width, int height, const std::string &title)
{

	m_window.create(sf::VideoMode(width, height), title/*, sf::Style::Fullscreen*/);

    running= true;

	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "Error al inicializar el display" << std::endl;
	}

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	clock.restart();
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
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape)
                running = false;
            else if(event.key.code == sf::Keyboard::F11)
                setModoVentana();

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

void TDisplay::Draw(sf::Sprite s)
{
    std::cout<<"Dibuja Sprite"<<std::endl;
    m_window.draw(s);

}


void TDisplay::setModoVentana()
{
    m_window.clear();
    m_window.create(sf::VideoMode(1280 , 720), "IKIGAI");

}

void TDisplay::setFullScreen()
{
   m_window.create(sf::VideoMode(1920 , 1080), "IKIGAI", sf::Style::Fullscreen);
}


sf::Time TDisplay::getTimer()
{
    return clock.getElapsedTime();
}





