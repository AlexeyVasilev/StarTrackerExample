#include "../pch.h"

#include "StarFinder.h"
#include "Data/StarInfo.h"
#include "File/FileProcessor.h"
#include "File/BmpProcessor.h"
#include "Analyzer/StarsAnalyzer.h"

void processBitmap(ImageBitmap* bitmap, int luminosityThreshold);

extern "C" __declspec(dllexport) void* TestFunc_2() {
	TestStruct* value = new TestStruct();
	value->a = 43;
	std::list<int> l = { 1,2,3 };
	value->l = l;
	return static_cast<void*>(value);
}

StarInfo* CalculateStarsLocation(const char* filename, int luminosityThreshold) {
	if (filename == nullptr || luminosityThreshold <= 0)
		return nullptr;

	std::string imageName(filename);
	size_t fileSize = 0;
	char* data = FileProcessor::ReadFile(imageName, fileSize);
	if (!data)
		std::cout << "problem with file reading" << std::endl;

	BmpProcessor bmpProc(data, fileSize);
	ImageBitmap* bitmap = bmpProc.ReadBmpData();

	if (!bitmap)
		std::cout << "problem with bmp file processing" << std::endl;

	StarsAnalyzer starsAnalyzer;
	starsAnalyzer.processBitmap(bitmap, luminosityThreshold);

	//processBitmap(bitmap, luminosityThreshold);

	delete bitmap;
	return nullptr;// new StarInfo();
}

void processBitmap(ImageBitmap* bitmap, int luminosityThreshold) {
	if (!bitmap)
		return;

	size_t max_x = bitmap->getWidth();
	size_t max_y = bitmap->getHeigth();

	/*for (size_t x = 0; x < max_x; x++) {
		for (size_t y = 0; y < max_y; y++) {
			//printf("%d %d %d\n", rgb[i][j].rgbRed, rgb[i][j].rgbGreen, rgb[i][j].rgbBlue);
			ImagePoint point = bitmap->getPoint(x, y);
			printf("%d %d %d\n", point.redValue, point.greenValue, point.blueValue);
		}
		printf("\n");
	}*/
	for (size_t x = 0; x < max_x; x++) {
		for (size_t y = 0; y < max_y; y++) {
			//printf("%d %d %d\n", rgb[i][j].rgbRed, rgb[i][j].rgbGreen, rgb[i][j].rgbBlue);
			ImagePoint point = bitmap->getPoint(x, y);
			printf("%d %d %d\n", point.redValue, point.greenValue, point.blueValue);
		}
		printf("\n");
	}
}

extern "C" __declspec(dllexport) void* SF_CalculateStarsLocation(const char* filename, int luminosityThreshold) {
	//__declspec(dllexport)  void* __stdcall SF_CalculateStarsLocation(const char* filename, int luminosityThreshold) {
		//return nullptr;
	return static_cast<void*>(CalculateStarsLocation(filename, luminosityThreshold));
}