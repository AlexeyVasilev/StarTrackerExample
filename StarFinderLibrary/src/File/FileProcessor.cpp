#include "FileProcessor.h"

#include <fstream>
#include <iostream>

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

void FileProcessor::WriteDataToFile(std::string filename, const char* data, size_t dataSize) {
	if (filename.empty() || data == nullptr || dataSize == 0)
		return;

	std::ofstream fout;
	fout.open(filename, std::ios::binary | std::ios::out);
	fout.write(data, dataSize);
	fout.close();
}

