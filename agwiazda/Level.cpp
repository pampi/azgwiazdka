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
	m_nodeMap = vector<vector<class Node> >(width, vector<class Node>(height));

	m_drawVisited = false;
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

void Level::drawVisitedNodes(bool enable)
{
	m_drawVisited = enable;
}

bool Level::isDrawingVisitedNodes() const
{
	return m_drawVisited;
}

void Level::tick()
{
	removePathFromMap();

	//A* tutaj
	std::vector<sf::Vector2i> path = calculatePath(m_startPosition.x, m_startPosition.y, m_finishPosition.x, m_finishPosition.y, false);
	//std::reverse(path.begin(), path.end());

	for (unsigned int i = 0; i < path.size(); i++)
	{
		m_map[path[i].x][path[i].y] = Resource::SPR_PATH;
	}

}

void Level::removePathFromMap()
{
	for (size_t x = 0; x < m_map.size(); x++)
	{
		for (size_t y = 0; y < m_map[x].size(); y++)
		{
			if (m_map[x][y] == Resource::SPR_PATH || m_map[x][y] == Resource::SPR_VISITED)
			{
				m_map[x][y] = Resource::NO_SPRITE;
			}
		}
	}
}

std::vector<sf::Vector2i> Level::calculatePath(const int xStart, const int yStart, const int xFinish, const int yFinish, bool allowDiagMovement)
{
	prepareNodeMapForAstar();
	std::vector<sf::Vector2i> path;

	// Define points to work with
	Node *start = &m_nodeMap[xStart][yStart];
	Node *end = &m_nodeMap[xFinish][yFinish];
	Node *current;
	Node *child;

	// Define the open and the close list
	std::priority_queue<Node*, std::vector<Node*>, Node> openQ;// , closedQ;


	// Add the start point to the openList
	openQ.push(start);
	start->opened = true;

	// iloœæ iteracji
	unsigned int n = 0;


	while (n == 0 || (current != end && n < 128*72) )
	{

		// Look for the smallest F value in the openList and make it the current point
		if (openQ.empty())
			break;

		current = openQ.top();

		// Stop if we reached the end
		if (current == end)
		{
			break;
		}

		// Remove the current point from the openList
		openQ.pop();
		current->opened = false;

		// Add the current point to the closedList
		//closedQ.push(current);
		current->closed = true;

		// Get all current's adjacent walkable points (inc diagonal)
		for (int x = -1; x < 2; x++)
		{
			for (int y = -1; y < 2; y++)
			{
				// If it's current point then pass
				if (x == 0 && y == 0)
				{
					continue;
				}

				// if we're not allowing diaganal movement then only one of x or y can be set
				if (!allowDiagMovement)
				{
					if ((x != 0) && (y != 0)) 
					{
						continue;
					}
				}


				// Get this point
				int xp = x + current->xPos;
				int yp = y + current->yPos;
			

				if (isValidLocation(xp, yp))
				{
					// Get this point
					child = &m_nodeMap[xp][yp];

					//oznaczamy ¿e odwiedziliœmy ten kawa³ek
					if (isDrawingVisitedNodes())
					{
						m_map[xp][yp] = Resource::SPR_VISITED;
					}

					// If it's closed or not walkable then pass
					if (child->closed || !child->walkable)
					{
						continue;
					}


					// If it's already in the openList
					if (child->opened)
					{
						// If it has a wroste g score than the one that pass through the current point
						// then its path is improved when it's parent is the current point
						if (child->g > child->getGScore(current))
						{
							// Change its parent and g score
							child->parent = current;
							child->computeScores(end);
						}
					}
					else
					{
						// Add it to the openList with current point as parent
						//openQ.push(child);
						child->opened = true;

						// Compute it's g, h and f score
						child->parent = current;
						child->computeScores(end);

						openQ.push(child);
					}

				} // if validLocation

			} // end for
		} // end for
		n++;
	} // end while

	while (current->hasParent() && current != start)
	{
		path.push_back(sf::Vector2i(current->xPos, current->yPos));
		current = current->parent;
		n++;
	}
	return path;
}

void Level::prepareNodeMapForAstar()
{

	for (size_t x = 0; x < m_map.size(); x++)
	{
		for (size_t y = 0; y < m_map[x].size(); y++)
		{
			m_nodeMap[x][y].xPos = x;
			m_nodeMap[x][y].yPos = y;

			switch ( m_map[x][y] )
			{
				case Resource::NO_SPRITE:
				{
					m_nodeMap[x][y].walkable = true;
					break;
				}
				case Resource::SPR_COLLIDER:
				{
					m_nodeMap[x][y].walkable = false;
					break;
				}
				case Resource::SPR_PATH:
				{
					m_nodeMap[x][y].walkable = true;
					break;
				}
				case Resource::SPR_START:
				{
					m_nodeMap[x][y].walkable = true;
					break;
				}
				case Resource::SPR_FINISH:
				{
					m_nodeMap[x][y].walkable = true;
					break;
				}
			}
		}
	}
}

bool Level::isValidLocation(int x, int y)
{
	// czy pozycja miesci sie w wymiarach mapy
	bool invalid = (x<0) || (y<0) || ((unsigned int)x >= m_map.size()) || ((unsigned int)y >= m_map[0].size());

	// jak sie miesci to sprawdz czy nie jest zablokowana pozycja
	if ((!invalid))
	{
		if (m_map[x][y] == Resource::SPR_COLLIDER)
		{
			invalid = true;
		}
	}

	return !invalid;
}

void Level::setStartPosition(int x, int y)
{
	m_startPosition.x = x;
	m_startPosition.y = y;
	m_map[x][y] = Resource::SPR_START;
}

void Level::setFinishPosition(int x, int y)
{
	m_finishPosition.x = x;
	m_finishPosition.y = y;
	m_map[x][y] = Resource::SPR_FINISH;
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
