#ifndef NODE_H
#define NODE_H

#include "headers.h"

class Node
{
public:
	Node() : xPos(0), yPos(0), distance(0), priority(0), parent(nullptr), closed(false), opened(false) 
	{
		g = h = f = 0;
	}

	Node(int x, int y, int distance, int priority, bool walkable) : xPos(x), yPos(y), distance(distance), priority(priority), 
		parent(nullptr), closed(false), opened(false), walkable(walkable)
	{
		g = h = f = 0;
	}


	// Estimation function for the remaining distance to the goal.
	// hscore
	int estimate(int xDest, int yDest);

	void updatePriority(const int xDest, const int yDest);

	void updateDistance();

	bool hasParent();

	//koszt przejœcia drogi
	int getGScore(Node *p)
	{
		//return p->g + ((xPos == p->xPos || yPos == p->yPos) ? 10 : 14);
		return 10;
	}

	//koszt dojœcia do celu wed³ug heurystyki
	int getHScore(Node *p)
	{
		int xd, yd, d=0;
		xd = p->xPos - xPos;
		yd = p->yPos - yPos;


		// Euclidian Distance
		d = static_cast<int>(sqrt(xd*xd + yd*yd));

		// Manhattan distance
		//d=abs(xd)+abs(yd);

		// Chebyshev distance
		//d=max(abs(xd), abs(yd));

		//return (abs(p->xPos - xPos) + abs(p->yPos - yPos)) * 10;
		return d;
	}

	void computeScores(Node *end)
	{
		g = getGScore(parent);
		h = getHScore(end);
		f = g + h;
	}

	int g, h, f;

	bool operator()(const Node *lhs, const Node *rhs) const
	{
		return (lhs->f > rhs->f) ? true : false;
	}


	// current position
	int xPos, yPos;

	// total distance already travelled to reach the node
	// gscore
	int distance; 

	// priority=level+remaining distance estimate
	// fscore
	int priority; // smaller: higher priority

	Node *parent;

	bool walkable, closed, opened;

};
#endif