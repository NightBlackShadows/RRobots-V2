#pragma once
#include <string>>
class FileHandler
{
public:
	FileHandler();
	bool fileExicts(const std::string& name);
	bool writeToFile(std::string filename, std::string text);
	std::fstream readFromFile(std::string filename);
	~FileHandler(); 
private:
};

