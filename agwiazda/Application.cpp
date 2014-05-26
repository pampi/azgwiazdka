#include "headers.h"

Application::Application(int width, int height)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), "A* - 143370, 143313", sf::Style::Titlebar | sf::Style::Close);
	m_state = SET_START;
	m_level = new Level(width / SQUARE_SIZE, height / SQUARE_SIZE);
	m_width = width;
	m_height = height;
	m_pause = true;
	m_clicked = false;
	m_addCollider = true;
}

Application::~Application()
{
	delete m_window;
	delete m_level;
}

void Application::run()
{
	sf::Sprite drawing_sprite;
	sf::Vector2i mouse;
	Resource *res = Resource::GetInstance();
	while (m_window->isOpen())
	{
		while (m_window->pollEvent(m_event))
		{
			handleEvent();
		}

		m_window->clear();
		mouse = sf::Mouse::getPosition(*m_window);

		switch (m_state)
		{
		case SET_START:
			drawing_sprite = res->getSprite(Resource::SPR_PATH);
			drawing_sprite.setPosition((float)(mouse.x / SQUARE_SIZE) * SQUARE_SIZE, (float)(mouse.y / SQUARE_SIZE) * SQUARE_SIZE);
			m_window->draw(drawing_sprite);
			break;
		case SET_FINISH:
			drawing_sprite = res->getSprite(Resource::SPR_FINISH);
			drawing_sprite.setPosition((float)(mouse.x / SQUARE_SIZE) * SQUARE_SIZE, (float)(mouse.y / SQUARE_SIZE) * SQUARE_SIZE);
			m_window->draw(drawing_sprite);
			break;
		case SET_COLLIDER:
			drawing_sprite = res->getSprite(Resource::SPR_COLLIDER);
			drawing_sprite.setPosition((float)(mouse.x / SQUARE_SIZE) * SQUARE_SIZE, (float)(mouse.y / SQUARE_SIZE) * SQUARE_SIZE);
			m_window->draw(drawing_sprite);
		}

		if (!m_pause)
		{
			m_level->tick();	//calculating and moving A*
		}
		m_level->draw(*m_window, (m_state == SET_COLLIDER) ? true : false);
		m_window->display();

		sf::sleep(sf::milliseconds(10));
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
		m_clicked = true;
		handleMouseEvent();
		break;
	case sf::Event::MouseButtonReleased:
		m_clicked = false;
		break;
	case sf::Event::MouseMoved:
		if (m_clicked && m_state == SET_COLLIDER)
		{
			handleMouseEvent();
		}
		break;
	default:
		return;
	}
}

void Application::handleKeyEvent()
{
	switch (m_event.key.code)
	{
	case sf::Keyboard::Escape:
		m_window->close();
		break;
	case sf::Keyboard::R:
		m_state = SET_START;
		m_pause = true;
		m_clicked = false;
		m_addCollider = true;

		delete m_level;
		m_level = new Level(m_width / SQUARE_SIZE, m_height / SQUARE_SIZE);
		break;
	case sf::Keyboard::T:
		m_clicked = false;
		m_addCollider = (m_addCollider) ? false : true;
		break;
	case sf::Keyboard::Space:
		m_pause = (m_pause) ? false : true;
		break;
	default:
		break;
	}
}

void Application::handleMouseEvent()
{
	sf::Vector2i mouse = sf::Mouse::getPosition(*m_window);

	switch (m_state)
	{
	case SET_START:
		m_state = SET_FINISH;
		m_level->setStartPosition(mouse.x / SQUARE_SIZE, mouse.y / SQUARE_SIZE);
		break;
	case SET_FINISH:
		m_state = SET_COLLIDER;
		m_level->setFinishPosition(mouse.x / SQUARE_SIZE, mouse.y / SQUARE_SIZE);
		break;
	case SET_COLLIDER:
		if (m_addCollider)
			m_level->setCollider(mouse.x / SQUARE_SIZE, mouse.y / SQUARE_SIZE);
		else
			m_level->unsetCollider(mouse.x / SQUARE_SIZE, mouse.y / SQUARE_SIZE);
		break;
	default:
		break;
	}
}