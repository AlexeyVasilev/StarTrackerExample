#include "StarPointsSet.h"

void StarPointsSet::add(size_t x, size_t y) {
	_data.push_back(std::make_pair(x, y));
}

void StarPointsSet::setSetNumber(int setNumber) {
	_setNumber = setNumber;
}

int StarPointsSet::getSetNumber() {
	return _setNumber;
}

std::vector<std::pair<size_t, size_t>> StarPointsSet::getPoints() {
	return _data;
}