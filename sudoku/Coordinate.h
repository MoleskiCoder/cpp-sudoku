#pragma once

class Coordinate
{
private:
	int x;
	int y;

public:
	Coordinate();
	Coordinate(int xCoordinate, int yCoordinate);

	void set(int xCoordinate, int yCoordinate);

	int getX() const;
	void setX(int xCoordinate);

	int getY() const;
	void setY(int yCoordinate);
};
