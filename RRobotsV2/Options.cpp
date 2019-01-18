#include "Options.h"
#include <string>
#include <fstream>
#include <sstream>

//TODO: check if going to use anymore or change to toml

Options::Options()
{
	filename = "options.ini";
	if (fileHandler.fileExicts(filename)) {
		loadOptions();
	}
	else {

		screenWidth = 800;
		screenHeight = 600;
		musicVolume = 50;
		soundVolume = 50;
		fpsLock = 60;
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

int Options::getMusicVolume()
{
	return musicVolume;
}

int Options::getSoundVolume()
{
	return soundVolume;
}

bool Options::getMute()
{
	return mute;
}

std::string Options::getMuteString()
{
	switch (mute)
	{
	case true:
		return "true";
	default:
		return "false";
		break;
	}
	return "NaN";
}

int Options::getWidth()
{
	return screenWidth;
}

int Options::getHeight()
{
	return screenHeight;
}

int Options::getFPSLock()
{
	return fpsLock;
}

bool Options::getFullscreen()
{
	return fullscreen;
}

std::string Options::getFullscreenString()
{
	switch (fullscreen)
	{
	case true:
		return "true";
	default:
		return "false";
		break;
	}
	return "NaN";
}

void Options::setResolution(int w, int h)
{
	screenWidth = w;
	screenHeight = h;
}

void Options::setMusicVolume(int volume)
{
	musicVolume = volume;
}

void Options::setSoundVolume(int volume)
{
	soundVolume = volume;
}

void Options::setMute(bool state)
{
	mute = state;
}

void Options::setFullscreen(bool state)
{
	fullscreen = state;
}

void Options::setFPSLock(int lock)
{
	fpsLock = lock;
}

void Options::saveOptions()
{
	std::stringstream options;
	options << "[Game]\n";
	options << "ScreenWidth=" << std::to_string(screenWidth) << std::endl;
	options << "ScreenHeight=" << std::to_string(screenHeight) << std::endl;
	options << "Fullscreen=" << std::to_string(fullscreen) << std::endl;
	options << "FPSLock=" << std::to_string(fpsLock) << std::endl;
	options << "MusicVolume=" << std::to_string(musicVolume) << std::endl;
	options << "SoundVolume=" << std::to_string(soundVolume) << std::endl;
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
	else if (key == "FPSLock") {
		fpsLock = std::stoi(value);
	}
	else if (key == "MusicVolume") {
		musicVolume = std::stoi(value);
	}
	else if (key == "SoundVolume") {
		soundVolume = std::stoi(value);
	}
	else if (key == "Mute") {
		mute = std::stoi(value);
	}
}
