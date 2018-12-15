/*
	Computer Science 362 - SWE Fundamentals - VCS Project #1
	Team Name: JAH
	Authors :
		Aaron Gumabong - aarongumabong@gmail.com
		Joe Vanacore - joevanacore@gmail.com
		Hasib Ziai - hasibziai@csu.fullerton.edu

	Description: This header function takes in a file and converts it into a weighted checksum of the characters in the
			file. Returns a string that is a converted checksum version of the original file name. Additionally, returns the contents
			of the original files to be output to Artifacts.

*/
#ifndef _CHECKSUM_
#define _CHECKSUM_
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>


namespace fs = std::experimental::filesystem;



std::string checksum(fs::path file_path)
{

	//ifstream to take in the file
	std::ifstream ifs(file_path);
	//Reads all of the input of the string
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	//Prints out the contents of the file
	//std::cout << "Contents of the text file are: " << content << std::endl;

	//Holds the eventual checksum filename
	std::string file_name;
	//Holds the numbers for checksum
	int checksum = 0;
	//Helps loop through the 5 pattern checksum
	int counter = 1;
	for (int i = 0; i < content.size(); i++)
	{
		if (counter == 1)
		{
			checksum += content[i];
			counter++;
		}
		else if (counter == 2)
		{
			checksum += content[i] * 3;
			counter++;
		}
		else if (counter == 3)
		{
			checksum += content[i] * 7;
			counter++;
		}
		else if (counter == 4)
		{
			checksum += content[i] * 11;
			counter++;
		}
		else if (counter == 5)
		{
			checksum += content[i] * 17;
			counter = 1;
		}

	}
	//Uses modulo on the number to cut down on number size
	file_name = std::to_string(checksum % 2147483647);
	//Adds -L to the end of the file
	file_name += "-L";
	//converts the size of the file into a string and then adds it to the file name
	std::string size = std::to_string(fs::file_size(file_path));
	std::cout << "Size of the file is: " << size << std::endl;
	file_name += size;


	std::cout << "Final string is: " << file_name << std::endl;
	return file_name;
}

std::string text_content(fs::path file_path)
{
	//ifstream to take in the file
	std::ifstream ifs(file_path);
	//Reads all of the input of the string
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	return content;
}
#endif