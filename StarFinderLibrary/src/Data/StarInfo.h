#pragma once

#include "StarPoint.h"

#include <vector>

struct StarInfo {
	int serialNumber{ -1 };
	std::vector<StarPoint> points;
	StarPoint centerOfMass;
};