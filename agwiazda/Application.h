#ifndef APPLICATION_H
#define APPLICATION_H

#include "headers.h"

class Level;

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

	unsigned int m_width;
	unsigned int m_height;
	bool m_pause;
	bool m_clicked;
	bool m_addCollider;

	STATE m_state;

	void handleEvent();
	void handleKeyEvent();
	void handleMouseEvent();

	Level *m_level;
};

#endif