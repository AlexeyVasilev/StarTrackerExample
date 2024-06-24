#pragma once

#include "../Data/ImagePoint.h"

#include <vector>

class StarPointsSet {
public:
	StarPointsSet() = default;

	void add(size_t x, size_t y);
	void setSetNumber(int setNumber);
	int getSetNumber();
	std::vector<std::pair<size_t, size_t>> getPoints();

private:
	std::vector<std::pair<size_t, size_t>> _data;
	int _setNumber{ -1 };
};
