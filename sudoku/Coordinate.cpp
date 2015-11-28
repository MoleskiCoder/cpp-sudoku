#include "stdafx.h"
#include "Coordinate.h"

#include <assert.h>

Coordinate::Coordinate()
:	x(-1),
	y(-1)
{
}

Coordinate::Coordinate(const int xCoordinate, const int yCoordinate)
{
	set(xCoordinate, yCoordinate);
}

void Coordinate::set(const int xCoordinate, const int yCoordinate)
{
	x = xCoordinate;
	y = yCoordinate;
}

int Coordinate::getX() const
{
	assert(x != -1);
	return x;
}

void Coordinate::setX(const int xCoordinate)
{
	x = xCoordinate;
}

int Coordinate::getY() const
{
	assert(y != -1);
	return y;
}

void Coordinate::setY(const int yCoordinate)
{
	y = yCoordinate;
}
