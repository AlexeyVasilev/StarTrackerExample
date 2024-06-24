#pragma once

#include "../Data/ImageBitmap.h"
#include "StarPointsSet.h"
#include "../Data/StarInfo.h"

class StarsAnalyzer {
public:
	StarsAnalyzer() = default;

	std::vector<StarInfo>* processBitmap(ImageBitmap* bitmap, int luminosityThreshold);

private:
	static bool isStarPoint(const ImagePoint& point, int luminosityThreshold);
	void processStarPoint(StarPoint starPoint, ImageBitmap* bitmap, int luminosityThreshold);
	static std::vector<std::pair<size_t, size_t>> getNeighborPoints(size_t x, size_t y, size_t max_x, size_t max_y);
	static bool isPointInSet(const ImagePoint& point);

	int createNewSet();
	void addPointToSet(StarPoint starPoint, int setNumber);
	void printStarSets();
	std::vector<StarInfo>* createStarList();

private:
	std::vector<StarPointsSet> _starSets;
	int _lastSetNumber{ 1 };
};