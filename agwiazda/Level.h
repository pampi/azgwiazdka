#ifndef LEVEL_H
#define LEVEL_H

#include "headers.h"

class Level
{
public:
	enum FieldStaate
	{
		CLEAR,
		PATH,
		COLLIDER,
		FINISH,
	};

	Level(unsigned int width, unsigned int height);
	~Level();
	void draw(sf::RenderWindow& wnd, bool renderFinishTile);
	void tick();	//calculate new path

	void setStartPosition(int x, int y);
	void setFinishPosition(int x, int y);
	void setCollider(int x, int y);
	void unsetCollider(int x, int y);

private:
	sf::Vector2i m_startPosition;
	sf::Vector2i m_currentPosition;
	sf::Vector2i m_finishPosition;

	vector<vector<char> > m_map;	//full resolution map
};

#endif
