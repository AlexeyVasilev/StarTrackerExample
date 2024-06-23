#include <windows.h>
#include <iostream>
#include <conio.h> 

//extern "C" __declspec(dllimport) int TestFunc();
typedef int(__stdcall* TestFunc)();
//typedef int(CALLBACK* TestFunc)();

int main()
{
    std::cout << "Hello World!\n";

    HINSTANCE hLib = LoadLibrary("StarFinderLibrary.dll");
    if (hLib == NULL)
    {
        std::cout << "Unable to load library!" << std::endl;
        //getch();

        //int var = TestFunc();
        //std::cout << "var = " << var;
        
    }

    if (!hLib) {
        std::cout << "could not load the dynamic library" << std::endl;
        return EXIT_FAILURE;
    }

    TestFunc testFunc = (TestFunc)GetProcAddress(hLib, "TestFunc");
    if (!testFunc) {
        std::cout << "could not locate the function" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "funci() returned " << testFunc() << std::endl;
    char ch;
    std::cin >> ch;

    return 0;
}
