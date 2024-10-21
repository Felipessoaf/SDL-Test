#pragma once

#include <vector>
#include <string>

class IOManager
{
public:
	static bool ReadFileToBuffer(std::string filePath,std::vector<char>& buffer);
};

