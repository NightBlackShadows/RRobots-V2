#include "Options.h"
#include <string>
#include <fstream>
#include <sstream>

Options::Options()
{
	filename = "options.ini";
	if (fileHandler.fileExicts(filename)) {
		loadOptions();
	}
	else {

		screenWidth = 800;
		screenHeight = 600;
		volume = 50;
		mute = false;
		fullscreen = false;
		saveOptions();
	}
}

bool Options::loadOptions()
{
	std::fstream filestream;
	filestream.open(filename, std::ios::in);
	std::string line;
	if (filestream.is_open()) {
		while (std::getline(filestream, line))
		{
			std::istringstream is_line(line);
			std::string key;
			if (std::getline(is_line, key, '='))
			{
				std::string value;
				if (std::getline(is_line, value))
					loadValues(key, value);
			}
		}
	}
	else {
		printf("Could not read config file");
		return false;
	}
	return true;
}

int Options::getVolume()
{
	return volume;
}

bool Options::getMute()
{
	return mute;
}

int Options::getWidth()
{
	return screenWidth;
}

int Options::getHeight()
{
	return screenHeight;
}

bool Options::getFullscreen()
{
	return fullscreen;
}

void Options::saveOptions()
{
	std::stringstream options;
	options << "[Game]\n";
	options << "ScreenWidth=" << std::to_string(screenWidth) << std::endl;
	options << "ScreenHeight=" << std::to_string(screenHeight) << std::endl;
	options << "Fullscreen=" << std::to_string(fullscreen) << std::endl;
	options << "Volume=" << std::to_string(volume) << std::endl;
	options << "Mute=" << std::to_string(mute) << std::endl;
	fileHandler.writeToFile(filename, options.str());
	options.clear();
}

Options::~Options()
{
}

void Options::loadValues(std::string key, std::string value)
{
	if (key == "ScreenWidth") {
		screenWidth = std::stoi(value);
	}
	else if (key == "ScreenHeight") {
		screenHeight = std::stoi(value);
	}
	else if (key == "Fullscreen") {
		fullscreen = std::stoi(value);
	}
	else if (key == "Volume") {
		volume = std::stoi(value);
	}
	else if (key == "Mute") {
		mute = std::stoi(value);
	}
}
