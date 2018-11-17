#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <stdio.h>


namespace fs = std::experimental::filesystem;

void check_out(std::string copy_path, std::string source_path, std::string label_name)
{
	time_t current_time = time(NULL);
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);
	//Need 2 steps here: 
	//1) Combine the source path and the original manifest name into a string, do the same with source path and label
	//2) Convert both into const char * for the rename function 
	std::string sp = source_path + "\\manifest.txt";
	const char *sp2 = sp.c_str();
	std::string label2 = source_path + "\\" + label_name;
	std::cout << label2 << std::endl;
	
	//check to see if the source path is the same as copy path because this will lead to a large error
	if (source_path == copy_path)
	{
		std::cout << "Error, copied path cannot be the same as destination folder." << std::endl;
	}
	else
	{
		//copy the files to the target destination
		fs::copy(copy_path, source_path, fs::copy_options::recursive);		
		
		std::ofstream fileManifest(source_path);
		const char * label = label2.c_str()
		//rename the file 
		bool rename_success = rename(sp2, label);
		if (rename_success == true)
		{
			std::cout << "Sucessfully renamed file." << std::endl;
		}
		else
			std::cout << "Error in renaming file." << std::endl;
		
		//Note when the file was created
		fileManifest.open(label2, std::ofstream::trunc);
		fileManifest << "File created at:" << timeStr;
	
		
		std::cout << "Successfully copied file path." << std::endl;
	}
}
