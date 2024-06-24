#pragma once

#include "Data/StarInfo.h"
#include "Data/ImageBitmap.h"

#include <string>
#include <vector>

class ClearImageCreator {
	static void create(std::string filename, std::vector<StarInfo> starList, ImageBitmap* bitmap);
};