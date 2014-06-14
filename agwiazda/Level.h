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

	enum eHeuristic
	{
		Euclidian,
		Manhattan,
		Chebyshev,
	};

	Level(unsigned int width, unsigned int height);
	~Level();
	void draw(sf::RenderWindow& wnd, bool renderFinishTile);
	void tick(sf::RenderWindow& wnd);	//calculate new path

	void setStartPosition(int x, int y);
	void setFinishPosition(int x, int y);
	void setCollider(int x, int y);
	void unsetCollider(int x, int y);
	void drawVisitedNodes(bool enable);
	void drawVisitedSectors(bool enable);
	void changeHeuristic();
	void changeSectorFill();

	bool isDrawingVisitedNodes() const;
	bool isDrawingVisitedSectors() const;
	bool isFillingSectors() const;

	eHeuristic getHeuristic();

	sf::Time getCalculateTime();

	void reset();

private:
	sf::Vector2i m_startPosition;
	sf::Vector2i m_currentPosition;
	sf::Vector2i m_finishPosition;

	void removePathFromMap();

	// do the astar shake
	std::vector<sf::Vector2i> calculatePath(const int xStart, const int yStart, const int xFinish, const int yFinish, bool allowDiagMovement);
	void prepareNodeMapForAstar();

	void fillSector(int x, int y);
	void freeSector(int x, int y);

	std::vector<std::vector<char> > m_map;	//full resolution map

	std::vector< std::vector<class Node> > m_nodeMap;
	bool isValidLocation(int x, int y);

	bool m_drawVisitedNodes;
	bool m_drawVisitedSectors;
	bool m_fillsector;

	eHeuristic m_heuristic;
	sf::Clock m_timer;
	sf::Time m_calculateTime;

	class CQuadTree *qt;
};

#endif
