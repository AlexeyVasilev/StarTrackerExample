#pragma once

#include <iostream>
#include <list>

struct TestStruct {
	int a;
	std::list<int> l;
};

extern "C" __declspec(dllexport)void* TestFunc_2();

extern "C" __declspec(dllexport)void* SF_CalculateStarsLocation(const char* filename, int luminosityThreshold);
extern "C" __declspec(dllexport) int SF_CalcStarsLocation(const char* filename, const char* result, const char* clearImageName, int luminosityThreshold);
//__declspec(dllexport)void* __stdcall SF_CalculateStarsLocation(const char* filename, int luminosityThreshold);
