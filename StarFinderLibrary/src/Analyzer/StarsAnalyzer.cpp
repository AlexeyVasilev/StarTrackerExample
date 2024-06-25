#include "StarsAnalyzer.h"
#include "../Data/StarPoint.h"

#include <iostream>

std::vector<StarInfo>* StarsAnalyzer::processBitmap(ImageBitmap* bitmap, int luminosityThreshold) {
	if (bitmap == nullptr)
		return nullptr;

	size_t max_x = bitmap->getWidth();
	size_t max_y = bitmap->getHeigth();

	for (size_t x = 0; x < max_x; x++) {
		for (size_t y = 0; y < max_y; y++) {
			ImagePoint point = bitmap->getPoint(x, y);
			if (isStarPoint(point, luminosityThreshold)) {
				StarPoint starPoint(point.redValue, point.greenValue, point.blueValue, x, y);
				processStarPoint(starPoint, bitmap, luminosityThreshold);
			}
		}
	}
	//printStarSets();

	std::vector<StarInfo>* starList = createStarList();
	return starList;
}

void StarsAnalyzer::processStarPoint(StarPoint starPoint, ImageBitmap* bitmap, int luminosityThreshold) {
	size_t max_x = bitmap->getWidth();
	size_t max_y = bitmap->getHeigth();

	std::vector<std::pair<size_t, size_t>> neighborPoints = getNeighborPoints(starPoint.x, starPoint.y, max_x, max_y);
	std::set<int> starSetsNumbers;
	for (auto p : neighborPoints) {
		ImagePoint neighborPoint = bitmap->getPoint(p.first, p.second);
		bool isNeighborStar = isStarPoint(neighborPoint, luminosityThreshold);
		if (isNeighborStar) {
			if (isPointInSet(neighborPoint)) {
				starSetsNumbers.insert(neighborPoint.starSetNumber);
			}
		}
	}

	int setNumber = -1;
	if (starSetsNumbers.size() > 1) {
		setNumber = mergeStarSets(starSetsNumbers, bitmap);
	}
	else if (starSetsNumbers.size() == 1) {
		setNumber = *starSetsNumbers.begin();
	}
	else if (starSetsNumbers.size() == 0) {
		setNumber = createNewSet();
	}
	addPointToSet(starPoint, setNumber);
	bitmap->updateSetNumber(starPoint.x, starPoint.y, setNumber);
}

bool StarsAnalyzer::isStarPoint(const ImagePoint& point, int luminosityThreshold) {
	if ((point.redValue >= luminosityThreshold) && (point.greenValue >= luminosityThreshold)
		&& (point.blueValue >= luminosityThreshold))
		return true;

	return false;
}

bool StarsAnalyzer::isPointInSet(const ImagePoint& point) {
	if (point.starSetNumber > 0)
		return true;
	return false;
}

//    A  B  C
//	  D  *  E
//    F  G  H
std::vector<std::pair<size_t, size_t>> StarsAnalyzer::getNeighborPoints(size_t x, size_t y, size_t max_x, size_t max_y) {
	std::vector<std::pair<size_t, size_t>> neighborPoints;
	if (x >= 1 && y >= 1) // A
		neighborPoints.push_back(std::make_pair(x - 1, y - 1));

	if (y >= 1)  // B
		neighborPoints.push_back(std::make_pair(x, y - 1));

	if (y >= 1 && x < (max_x - 1))  // C
		neighborPoints.push_back(std::make_pair(x + 1, y - 1));
	
	if (x >= 1) // D
		neighborPoints.push_back(std::make_pair(x - 1, y));

	if (x < (max_x - 1))  // E
		neighborPoints.push_back(std::make_pair(x + 1, y));

	if (x >= 1 && y < (max_y - 1))  // F
		neighborPoints.push_back(std::make_pair(x - 1, y + 1));

	if (y < (max_y - 1))  // G
		neighborPoints.push_back(std::make_pair(x, y + 1));

	if (x < (max_x - 1) && y < (max_y - 1))  // H
		neighborPoints.push_back(std::make_pair(x + 1, y + 1));

	return neighborPoints;
}

int StarsAnalyzer::createNewSet() {
	StarPointsSet set;
	set.setSetNumber(_lastSetNumber++);
	_starSets.push_back(set);
	return set.getSetNumber();
}

void StarsAnalyzer::addPointToSet(StarPoint starPoint, int setNumber) {
	for (auto& set : _starSets) {
		if (set.getSetNumber() == setNumber) {
			set.add(starPoint);
		}
	}
}

std::vector<StarInfo>* StarsAnalyzer::createStarList() {
	std::vector<StarInfo>* list = new std::vector<StarInfo>();
	int serial = 1;
	for (auto set : _starSets) {
		StarInfo star;
		star.serialNumber = serial++;
		std::vector<StarPoint> points = set.getPoints();
		for (auto p : points)
			star.points.push_back(p);
		calcCenterPoint(star);
		list->push_back(star);
	}
	return list;
}

void StarsAnalyzer::printStarSets() {
	for (auto set : _starSets) {
		std::cout << "set " << set.getSetNumber() << std::endl;
		std::vector<StarPoint> points = set.getPoints();
		for (auto p : points) {
			std::cout << "| x=" << p.x << " y=" << p.y
				<< " | r=" << p.redValue << " g=" << p.greenValue
				<< " b=" << p.blueValue << std::endl;
		}
	}
}

void StarsAnalyzer::calcCenterPoint(StarInfo& info) {
	double sum_x = 0;
	double sum_y = 0;
	for (auto p : info.points) {
		sum_x += p.x;
		sum_y += p.y;
	}
	size_t size = info.points.size();
	if (size > 0) {
		float x = sum_x / (double)size;
		float y = sum_y / (double)size;
		info.centerOfMass.x = (int)(x + 0.5);
		info.centerOfMass.y = (int)(y + 0.5);

		//std::cout << "center fx=" << x << " fy=" << y <<
		//	" x=" << info.centerOfMass.x << " y=" << info.centerOfMass.y << std::endl;
	}
}

int StarsAnalyzer::mergeStarSets(std::set<int> intersectingSetsNumbers, ImageBitmap* bitmap) {
	if (bitmap == nullptr)
		return -1;

	std::vector<StarPoint> commonPoints;
	for (std::vector<StarPointsSet>::iterator it = _starSets.begin(); it != _starSets.end();)
	{
		if (isintersectingSet(it->getSetNumber(), intersectingSetsNumbers)) {
			for (auto p : it->getPoints()) {
				commonPoints.push_back(p);
			}
			it = _starSets.erase(it);
		}
		else
			++it;
	}

	int newSetNumbr = createNewSet();
	for (auto p : commonPoints) {
		addPointToSet(p, newSetNumbr);
		bitmap->updateSetNumber(p.x, p.y, newSetNumbr);
	}
	
	return newSetNumbr;

}

bool StarsAnalyzer::isintersectingSet(int setNumber, std::set<int> intersectingSetsNumbers) {
	for (auto n : intersectingSetsNumbers) {
		if (setNumber == n)
			return true;
	}
	return false;
}
