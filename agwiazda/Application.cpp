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
	m_drawMenu = true;

	m_textMenu.setFont(Resource::GetInstance()->getFont());
	m_textMenu.setColor(sf::Color::White);

	m_textBackground.setFillColor(sf::Color(0,0,158,255));
	m_textBackground.setSize(sf::Vector2f(100,100));
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
			drawing_sprite = res->getSprite(Resource::SPR_START);
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
			m_level->tick(*m_window);	//calculating and moving A*
			m_pause = true;
		}

		m_level->draw(*m_window, (m_state == SET_COLLIDER) ? true : false);

		if (m_drawMenu)
		{
			drawMenu();
		}

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
	case sf::Keyboard::N:
		m_level->drawVisitedNodes(m_level->isDrawingVisitedNodes() ? false : true);
		break;
	case sf::Keyboard::S:
		m_level->drawVisitedSectors(m_level->isDrawingVisitedSectors() ? false : true);
		break;
	case sf::Keyboard::H:
		m_level->changeHeuristic();
		break;
	case sf::Keyboard::Space:
		//m_pause = (m_pause) ? false : true;
		m_pause = false;
		break;
	case sf::Keyboard::Tab:
		m_drawMenu = !m_drawMenu;
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

void Application::drawMenu()
{
	m_window->draw(m_textBackground);


	std::string _textHolder;


	_textHolder += "[R]eset level";
	_textHolder += "\nFind path [Space]";

	_textHolder += "\nDraw visited [N]odes:   ";
	if (m_level->isDrawingVisitedNodes())
		_textHolder += "Y";
	else
		_textHolder += "N";

	_textHolder += "\nDraw visited [S]ectors: ";
	if (m_level->isDrawingVisitedSectors())
		_textHolder += "Y";
	else
		_textHolder += "N";

	_textHolder += "\n[H]euristic: ";
	switch (m_level->getHeuristic())
	{
	case Level::Euclidian:
		_textHolder += "Euclidian";
		break;
	case Level::Manhattan:
		_textHolder += "Manhattan";
		break;
	case Level::Chebyshev:
		_textHolder += "Chebyshev";
		break;
	default:
		_textHolder += "UNKNOWN";
		break;
	}

	_textHolder += "\nCurrent state: ";
	switch (m_state)
	{
	case SET_START:
		_textHolder += "set start point";
		break;
	case SET_FINISH:
		_textHolder += "set end point";
		break;
	case SET_COLLIDER:
		if (m_addCollider)
			_textHolder += "[T] set colliders";
		else
			_textHolder += "[T] remove colliders";
		break;
	}

	_textHolder += "\nPath found in: ";
	std::ostringstream oss;
	oss << m_level->getCalculateTime().asSeconds() << "s" << "  " << m_level->getCalculateTime().asMilliseconds() << "ms";
	_textHolder += oss.str();

	_textHolder += "\nTOGGLE ME [Tab]";
	
	m_textMenu.setCharacterSize(20);
	m_textMenu.setString(_textHolder);
	m_textBackground.setSize(sf::Vector2f(m_textMenu.getGlobalBounds().width, m_textMenu.getGlobalBounds().height));
	m_window->draw(m_textMenu);
}