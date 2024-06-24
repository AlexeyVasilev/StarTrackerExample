#include <windows.h>
#include <iostream>
#include <conio.h> 
#include <list>

//extern "C" __declspec(dllimport) int TestFunc();
typedef int(__stdcall* TestFunc)();
//typedef int(CALLBACK* TestFunc)();

struct TestStruct {
    int a;
    std::list<int> l;
};

/*extern "C" {
    typedef  void* (__cdecl* SF_CalculateStarsLocation)(const char* filename, int luminosityThreshold);
}*/

extern "C" typedef  void* (__cdecl* SF_CalculateStarsLocation)(const char* filename, int luminosityThreshold);

int main()
{
    std::cout << "Hello World!\n";

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

    /*TestFunc testFunc = (TestFunc)GetProcAddress(hLib, "TestFunc");
    if (!testFunc) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "funci() returned " << testFunc() << std::endl;*/

    SF_CalculateStarsLocation findStarsFunc = (SF_CalculateStarsLocation)GetProcAddress(hLib, "SF_CalculateStarsLocation");
    if (!findStarsFunc) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    const int luminosityThreshold = 80;
    std::string filename{ "star_image_1.bmp" };
    void* ptr = findStarsFunc(filename.c_str(), luminosityThreshold);

    char ch;
    std::cin >> ch;

    return 0;
}
