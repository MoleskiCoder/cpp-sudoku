#pragma once

#include "Coordinate.h"

#include <vector>
#include <assert.h>

template<typename T> class Grid
{
private:
	int width;
	int height;
	std::vector<T> values;

public:
	Grid(const int gridWidth, const int gridHeight, const std::vector<T>& initial)
	{
		width = gridWidth;
		height = gridHeight;
		assert(width == height);
		assert(width * height == initial.size());
		for each (T value in initial)
		{
			values.push_back(value);
		}
	}

	int getHeight() const
	{
		return height;
	}

	int getWidth() const
	{
		return width;
	}

	void set(const Coordinate& coordinate, const T value)
	{
		values[getOffset(coordinate)] = value;
	}

	void set(const int x, const int y, const T value)
	{
		values[getOffset(x, y)] = value;
	}

	T get(const Coordinate& coordinate) const
	{
		return values[getOffset(coordinate)];
	}

	T get(const int x, const int y) const
	{
		return values[getOffset(x, y)];
	}

	int getOffset(const Coordinate& coordinate) const
	{
		return getOffset(coordinate.getX(), coordinate.getY());
	}

	int getOffset(const int x, const int y) const
	{
		return x + y * width;
	}
};
