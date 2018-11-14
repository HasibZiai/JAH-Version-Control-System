#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>


namespace fs = std::experimental::filesystem;

void check_out(std::string copy_path, std::string source_path)
{
	time_t current_time = time(NULL);
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);
	
	if (source_path == copy_path)
	{
		std::cout << "Error copied path cannot be the same as destination folder." << std::endl;
	}
	else
	{
		fs::copy(copy_path, source_path, fs::copy_options::recursive);		
		std::ofstream fileManifest(source_path);
		fileManifest.open(source_path += "\\manifest.txt", std::ofstream::trunc);
		fileManifest << "File created at:" << timeStr;
		
		std::cout << "Successfully copied file path." << std::endl;
	}
}
