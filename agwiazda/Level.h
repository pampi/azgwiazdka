#ifndef LEVEL_H
#define LEVEL_H

#include "headers.h"

class Level
{
public:
	enum FieldState
	{
		CLEAR,
		PATH,
		COLLIDER,
		FINISH,
	};

	Level(unsigned int width, unsigned int height, unsigned int depth = 0);
	~Level();
	void draw(sf::RenderWindow& wnd, bool renderFinishTile);
	void tick();	//calculate new path

	void setStartPosition(int x, int y);
	void setFinishPosition(int x, int y);
	void setCollider(int x, int y);
	void unsetCollider(int x, int y);
	void drawVisitedNodes(bool enable);

	bool isDrawingVisitedNodes() const;

	void depthRebuild(std::vector< std::vector<char> >& map);

private:
	sf::Vector2i m_startPosition;
	sf::Vector2i m_currentPosition;
	sf::Vector2i m_finishPosition;

	void removePathFromMap();

	// do the astar shake
	std::vector<sf::Vector2i> calculatePath(const int xStart, const int yStart, const int xFinish, const int yFinish, bool allowDiagMovement);
	void prepareNodeMapForAstar();

	std::vector<std::vector<char> > m_map;	//full resolution map

	std::vector< std::vector<class Node> > m_nodeMap;
	bool isValidLocation(int x, int y);

	bool m_drawVisited;

	class CQuadTree *qt;
	Level *m_subLevel;
	unsigned int m_depth;
};

#endif
