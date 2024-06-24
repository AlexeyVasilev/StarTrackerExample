#include "../pch.h"

#include "StarFinder.h"
#include "Data/StarInfo.h"
#include "File/FileProcessor.h"
#include "File/BmpProcessor.h"
#include "Analyzer/StarsAnalyzer.h"

extern "C" __declspec(dllexport) void* TestFunc_2() {
	TestStruct* value = new TestStruct();
	value->a = 43;
	std::list<int> l = { 1,2,3 };
	value->l = l;
	return static_cast<void*>(value);
}

std::vector<StarInfo>* CalculateStarsLocation(const char* filename, int luminosityThreshold) {
	if (filename == nullptr || luminosityThreshold <= 0)
		return nullptr;

	std::string imageName(filename);
	size_t fileSize = 0;
	const char* data = FileProcessor::ReadFile(imageName, fileSize);
	if (!data)
		std::cout << "problem with file reading, file=" << imageName << std::endl;

	BmpProcessor bmpProc(data, fileSize);
	ImageBitmap* bitmap = bmpProc.ReadBmpData();

	if (!bitmap)
		std::cout << "problem with bmp file processing" << std::endl;

	StarsAnalyzer starsAnalyzer;
	std::vector<StarInfo>* starList = starsAnalyzer.processBitmap(bitmap, luminosityThreshold);

	bitmap->clearNonStarPoints();
	BmpProcessor bmpClearProc(data, fileSize);
	bmpClearProc.UpdateBmpData(bitmap);
	std::string clearImageName = "clearImage.bmp";
	FileProcessor::WriteDataToFile(clearImageName, data, fileSize);


	delete bitmap;
	delete[] data;
	return starList;
}

extern "C" __declspec(dllexport) void* SF_CalculateStarsLocation(const char* filename, int luminosityThreshold) {
	return static_cast<void*>(CalculateStarsLocation(filename, luminosityThreshold));
}

#include <fstream>
#include <iostream>

extern "C" __declspec(dllexport) int TestFunc_3(char* aStr, char* bStr) {
	std::string a(aStr);
	std::string b(bStr);
	std::cout << "a=" << a << " b=" << b << std::endl;


	std::ofstream fout;
	fout.open("log.txt", std::ios::out);
	fout << "a=" << a << " b=" << b << std::endl;
	fout.close();
	return 4849;
}
