#include "FileProcessor.h"

#include <fstream>
#include <iostream>
#include <fstream>

char* FileProcessor::ReadFile(std::string filename, size_t& fileSize) {
	std::ifstream ifs(filename, std::ifstream::binary);
	ifs.seekg(0, ifs.end);
	int len = ifs.tellg();
	ifs.seekg(0, ifs.beg);

	//std::cout << "len = " << len << std::endl;
	if (len <= 0)
		return nullptr;

	char* bytes = new char[len];
	if (bytes == nullptr)
		return nullptr;

	ifs.read(bytes, len);
	ifs.close();
	fileSize = len;
	return bytes;
}

