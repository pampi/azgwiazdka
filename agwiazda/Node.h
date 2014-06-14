#ifndef NODE_H
#define NODE_H

#include "headers.h"

class Node
{
public:
	Node() : 
		xPos(0), 
		yPos(0), 
		parent(nullptr), 
		closed(false), 
		opened(false),
		walkable(false)
	{
		g = h = f = 0;
	}

	Node(int x, int y, int distance, int priority, bool walkable) : 
		xPos(x), 
		yPos(y), 
		parent(nullptr), 
		closed(false), 
		opened(false), 
		walkable(walkable)
	{
		g = h = f = 0;
	}

	bool hasParent()
	{
		return (parent != nullptr);
	}

	//koszt przejœcia drogi
	int getGScore(Node *p)
	{
		//return p->g + ((xPos == p->xPos || yPos == p->yPos) ? 10 : 14);
		return 10;
	}

	//koszt dojœcia do celu wed³ug heurystyki
	int getHScore(Node *p, Level::eHeuristic _heuristic)
	{
		int xd, yd, d=0;
		xd = p->xPos - xPos;
		yd = p->yPos - yPos;


		// Euclidian Distance
		if (_heuristic == Level::Euclidian)
			d = static_cast<int>(sqrt(xd*xd + yd*yd));

		// Manhattan distance
		if (_heuristic == Level::Manhattan)
			d=abs(xd)+abs(yd);

		// Chebyshev distance
		if (_heuristic == Level::Chebyshev)
			d=max(abs(xd), abs(yd));

		//return (abs(p->xPos - xPos) + abs(p->yPos - yPos)) * 10;
		return d;
	}

	void computeScores(Node *end, Level::eHeuristic _heuristic)
	{
		g = getGScore(parent);
		h = getHScore(end, _heuristic);
		f = g + h;
	}

	int g, h, f;

	bool operator()(const Node *lhs, const Node *rhs) const
	{
		return (lhs->f > rhs->f) ? true : false;
	}


	// current position
	int xPos, yPos;

	Node *parent;

	bool walkable, closed, opened;

};
#endif