#pragma once

extern "C" __declspec(dllexport)void* SF_CalculateStarsLocation(const char* filename, int luminosityThreshold);
extern "C" __declspec(dllexport) int SF_CalcStarsLocation(const char* filename, const char* result, const char* clearImageName, int luminosityThreshold);
