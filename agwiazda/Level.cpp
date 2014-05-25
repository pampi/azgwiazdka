#include "headers.h"

Level::Level(unsigned int width, unsigned int height)
{
	m_startPosition.x = 0;
	m_startPosition.y = 0;

	m_currentPosition.x = 0;
	m_currentPosition.y = 0;

	m_finishPosition.x = 0;
	m_finishPosition.y = 0;

	m_map = vector<vector<char> >(width, vector<char>(height,Resource::NO_SPRITE));
}

Level::~Level()
{
	m_map.clear();
}

void Level::draw(sf::RenderWindow& wnd, bool renderFinish)
{
	Resource *res = Resource::GetInstance();
	sf::Sprite sprite_to_draw = res->getSprite(Resource::SPR_FINISH);

	if (renderFinish)
	{
		sprite_to_draw.setPosition((float)m_finishPosition.x * SQUARE_SIZE, (float)m_finishPosition.y * SQUARE_SIZE);
		wnd.draw(sprite_to_draw);
	}

	for (size_t x = 0; x < m_map.size(); x++)
		for (size_t y = 0; y < m_map[x].size(); y++)
		{
			if (m_map[x][y] != Resource::NO_SPRITE)
			{
				sprite_to_draw = res->getSprite((Resource::SPRITES)m_map[x][y]);
				sprite_to_draw.setPosition((float)x * SQUARE_SIZE, (float)y * SQUARE_SIZE);

				wnd.draw(sprite_to_draw);
			}
		}
}

void Level::tick()
{
	//A* tutaj
}

void Level::setStartPosition(int x, int y)
{
	m_startPosition.x = x;
	m_startPosition.y = y;
	m_map[x][y] = Resource::SPR_PATH;
}

void Level::setFinishPosition(int x, int y)
{
	m_finishPosition.x = x;
	m_finishPosition.y = y;
}

void Level::setCollider(int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)m_map.size() || y >= (int)m_map[x].size()) return;

	if (m_map[x][y] == Resource::NO_SPRITE && (x != m_finishPosition.x || y != m_finishPosition.y))
		m_map[x][y] = Resource::SPR_COLLIDER;
}

void Level::unsetCollider(int x, int y)
{
	if (x < 0 || y < 0 || x >= (int)m_map.size() || y >= (int)m_map[x].size()) return;

	if (m_map[x][y] == Resource::SPR_COLLIDER && (x != m_finishPosition.x || y != m_finishPosition.y))
		m_map[x][y] = Resource::NO_SPRITE;
}
