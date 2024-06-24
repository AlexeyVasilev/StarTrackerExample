#pragma once
#include <cstddef>
#include <string>

class FileProcessor {
public:
	static char* ReadFile(std::string filename, size_t& fileSize);
};