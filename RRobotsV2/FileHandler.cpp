#include "FileHandler.h"
#include <sys/stat.h>
#include <fstream>
#include <iostream>

FileHandler::FileHandler()
{
}

//Check if file excists
bool FileHandler::fileExicts(const std::string& name)
{
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

//Write file
bool FileHandler::writeToFile(std::string filename, std::string text)
{
  std::fstream fileStream;
  fileStream.open(filename, std::ios::out);
	
  if (fileStream.is_open())
    {
      fileStream << text;
      fileStream.close();
      return true;
    }
  return false;
}

/*
  std::fstream FileHandler::readFromFile(std::string filename)
  {
  std::fstream fileStream;
  std::string shit;

  fileStream.open(filename, std::ios::in);

  if (fileStream.is_open())
  {
  return fileStream;
  }
  else throw ("Unable to open file:" + filename);
  }*/



FileHandler::~FileHandler()
{
}
