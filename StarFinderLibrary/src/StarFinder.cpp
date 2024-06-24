#include "../pch.h"

#include "StarFinder.h"
#include "Data/StarInfo.h"
#include "File/FileProcessor.h"
#include "File/BmpProcessor.h"
#include "Analyzer/StarsAnalyzer.h"

#include <fstream>
#include <iostream>
#include <iomanip>

void writeResultToFile(std::string resultFileName, std::vector<StarInfo>* starInfo);

static std::vector<StarInfo>* CalculateStarsLocation(const char* filename, std::string clearImageFile, int luminosityThreshold) {
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

	if (!clearImageFile.empty()) {
		bitmap->clearNonStarPoints();
		BmpProcessor bmpClearProc(data, fileSize);
		bmpClearProc.UpdateBmpData(bitmap);
		FileProcessor::WriteDataToFile(clearImageFile, data, fileSize);
	}

	if (bitmap)
		delete bitmap;
	if (data)
		delete[] data;
	return starList;
}

extern "C" __declspec(dllexport) void* SF_CalculateStarsLocation(const char* filename, int luminosityThreshold) {
	std::string clearImageFile = "clear_image.bmp";
	return static_cast<void*>(CalculateStarsLocation(filename, clearImageFile, luminosityThreshold));
}

extern "C" __declspec(dllexport) int SF_CalcStarsLocation(const char* filename, const char* resultFile, const char* clearImageName, int luminosityThreshold) {
	std::vector<StarInfo>* starInfo = nullptr;
	int result = -1;
	try {
		starInfo = CalculateStarsLocation(filename, std::string(clearImageName), luminosityThreshold);

		writeResultToFile(std::string(resultFile), starInfo);

		if (starInfo != nullptr) {
			delete starInfo;
			result = 0;
		}
	}
	catch (std::exception ex) {
		std::ofstream fout;
		fout.open("library_err_log.txt", std::ios::out);
		fout << ex.what() << std::endl;
		fout.close();

	}
	
	return result;
}

static void writeResultToFile(std::string resultFileName, std::vector<StarInfo>* starInfo) {
	if (resultFileName.empty() || starInfo == nullptr)
		return;

	std::ofstream fout;
	fout.open(resultFileName, std::ios::out);
	
	fout << " " << starInfo->size() << "  stars found." << std::endl;
	for (auto s : *starInfo) {
		fout << "Star #" << s.serialNumber << std::endl;
		fout << "   Points:" << std::endl;
		size_t pNumber = 1;
		for (auto p : s.points) {
			fout << "   " << std::setw(2) << pNumber++ << ": ["
				<< p.x << ", " << p.y << "] "
				<< "R(" << p.redValue << "), G(" << p.greenValue
				<< "), B(" << p.blueValue << ")" << std::endl;
		}
		fout << std::endl;
	}
	fout.close();
}

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
