#ifndef APPLICATION_H
#define APPLICATION_H

#include "headers.h"

class Application
{
public:
	enum STATE {
		SET_START,
		SET_FINISH,
		SET_COLLIDER
	};

	Application(int width = 1280, int height = 720);
	~Application();
	void run();

private:
	sf::RenderWindow *m_window;
	sf::Event m_event;

	STATE m_state;

	void handleEvent();
	void handleKeyEvent();
	void handleMouseEvent();
};

#endif