#include "headers.h"


int Node::estimate(int xDest, int yDest)
{
	int xd, yd, d;
	xd = xDest - xPos;
	yd = yDest - yPos;


	// Euclidian Distance
	d = static_cast<int>(sqrt(xd*xd + yd*yd));

	// Manhattan distance
	//d=abs(xd)+abs(yd);

	// Chebyshev distance
	//d=max(abs(xd), abs(yd));

	return d;
}

void Node::updateDistance()
{
	this->distance += 10;
}

void Node::updatePriority(const int xDest, const int yDest)
{
	this->priority = distance + estimate(xDest, yDest);
}

bool Node::hasParent()
{
	return (parent != nullptr);
}