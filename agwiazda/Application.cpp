#include "headers.h"

Application::Application(int width, int height)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), "A* - 143370, 143313");
	m_state = SET_START;
}

Application::~Application()
{
	delete m_window;
}

void Application::run()
{
	while (m_window->isOpen())
	{
		while (m_window->pollEvent(m_event))
		{
			handleEvent();
		}

		m_window->clear();
		//draw - TO DO
		m_window->display();

		Sleep(10);
	}
}

void Application::handleEvent()
{
	switch (m_event.type)
	{
	case sf::Event::Closed:
		m_window->close();
		break;
	case sf::Event::KeyPressed:
		handleKeyEvent();
		break;
	case sf::Event::MouseButtonPressed:
		handleMouseEvent();
		break;
	default:
		return;
	}
}

void Application::handleKeyEvent()
{
	//TO DO
	switch (m_event.key.code)
	{
	case sf::Keyboard::Escape:
		m_window->close();
		break;
	case sf::Keyboard::R:
		//TO DO - Reset
		m_state = SET_START;
		break;
	case sf::Keyboard::T:
		//TO DO - Prze³¹czaj pomiêdzy dodawaniem/usuwaniem przeszkód przez myszkê
		break;
	case sf::Keyboard::Space:
		//TO DO - pauza/start poruszania siê
		break;
	default:
		break;
	}
}

void Application::handleMouseEvent()
{
	//TO DO
	switch (m_state)
	{
	case SET_START:
		//TO DO - ustaw na mapie pocz¹tek trast
		m_state = SET_FINISH;
		break;
	case SET_FINISH:
		//TO DO - ustaw na mapie koniec trasy
		m_state = SET_COLLIDER;
		break;
	case SET_COLLIDER:
		//TO DO - dodaj przeszkodê
		break;
	default:
		break;
	}
}