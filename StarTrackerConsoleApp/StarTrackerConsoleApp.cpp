#include <windows.h>
#include <iostream>
#include <conio.h> 
#include <list>
#include <vector>
#include <iomanip>

#include "StarInfo.h"

void printStarsInfo(std::vector<StarInfo>* info);

extern "C" typedef  void* (__cdecl* SF_CalculateStarsLocation)(const char* filename, int luminosityThreshold);

int main()
{
    std::cout << "Start tracker console application\n\n";

    HINSTANCE hLib = LoadLibrary("StarFinderLibrary.dll");
    if (hLib == NULL)
    {
        std::cout << "Unable to load library!" << std::endl;
        return EXIT_FAILURE;
    }

    if (!hLib) {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    SF_CalculateStarsLocation findStarsFunc = (SF_CalculateStarsLocation)GetProcAddress(hLib, "SF_CalculateStarsLocation");
    if (!findStarsFunc) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    const int luminosityThreshold = 100;
    std::string filename{ "star_image_1.bmp" };
    void* ptr = findStarsFunc(filename.c_str(), luminosityThreshold);

    std::vector<StarInfo>* info = static_cast<std::vector<StarInfo>*>(ptr);
    printStarsInfo(info);

    char ch;
    std::cin >> ch;

    return 0;
}

void printStarsInfo(std::vector<StarInfo>* info) {
    if (!info) {
        std::cout << "no data from dll" << std::endl;
        return;
    }

    for (auto s : *info) {
        std::cout << "Star #" << s.serialNumber << std::endl;
        std::cout << "   Points:" << std::endl;
        size_t pNumber = 1;
        for (auto p : s.points) {
            std::cout << "   " << std::setw(2) << pNumber++ << ": ["
                << p.x << ", " << p.y << "] " 
                << "R(" << p.redValue << "), G(" << p.greenValue 
                << "), B(" << p.blueValue << ")" << std::endl;
        }
        std::cout << std::endl;
    }
}
