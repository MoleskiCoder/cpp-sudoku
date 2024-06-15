#pragma once

#include <vector>
#include <cassert>

template<typename T> class Grid {
private:
	const int _width;
	const int _height;
	std::vector<T> _values;

public:
	Grid(const int gridWidth, const int gridHeight, const std::vector<T>& initial)
	: _width(gridWidth),
	  _height(gridHeight) {
		assert(_width == _height);
		assert(_width * _height == initial.size());
		_values.reserve(initial.size());
		for (const T value : initial)
			_values.push_back(value);
	}

	[[nodiscard]] constexpr int height() const noexcept { return _height; }
	[[nodiscard]] constexpr int width() const noexcept { return _width; }

	[[nodiscard]] constexpr auto offset(const int x, const int y) const noexcept {
		return x + y * width();
	}

	constexpr void set(const int offset, const T value) noexcept {
		_values[offset] = value;
	}

	constexpr void set(const int x, const int y, const T value) noexcept {
		set(offset(x, y), value);
	}


	[[nodiscard]] constexpr T get(const int x, const int y) const noexcept {
		return get(offset(x, y));
	}

	[[nodiscard]] constexpr T get(const int offset) const noexcept {
		return _values[offset];
	}
};
