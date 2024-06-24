#include "StarPointsSet.h"

void StarPointsSet::add(StarPoint point) {
	_data.push_back(point);
}

void StarPointsSet::setSetNumber(int setNumber) {
	_setNumber = setNumber;
}

int StarPointsSet::getSetNumber() {
	return _setNumber;
}

std::vector<StarPoint> StarPointsSet::getPoints() {
	return _data;
}