#pragma once

#include "../Data/StarPoint.h"

#include <vector>

class StarPointsSet {
public:
	StarPointsSet() = default;

	void add(StarPoint point);
	void setSetNumber(int setNumber);
	int getSetNumber();
	std::vector<StarPoint> getPoints();

private:
	std::vector<StarPoint> _data;
	int _setNumber{ -1 };
};
