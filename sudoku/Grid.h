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
		set(getOffset(coordinate), value);
	}

	void set(const int x, const int y, const T value)
	{
		set(getOffset(x, y), value);
	}

	void set(const int offset, const T value)
	{
		values[offset] = value;
	}

	T get(const Coordinate& coordinate) const
	{
		return get(getOffset(coordinate));
	}

	T get(const int x, const int y) const
	{
		return get(getOffset(x, y));
	}

	T get(const int offset) const
	{
		return values[offset];
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
