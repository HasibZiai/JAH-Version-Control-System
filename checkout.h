#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <stdio.h>



namespace fs = std::experimental::filesystem;

void check_out(std::string s_path, std::string copy_path, std::string label )
{
	time_t current_time = time(NULL);
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);
	std::string label_name;
	std::string sp = copy_path + "\\manifest.txt";
	
	if (copy_path == s_path)
	{
		std::cout << "Error, copied path cannot be the same as destination folder." << std::endl;
	}
	else
	{
		fs::recursive_directory_iterator iter(s_path);
		fs::recursive_directory_iterator end;
		std::fstream file;
		std::string line;
		std::string c_label;
		//iterates through the whole filesystem and looks for all manifest files
		while (iter != end)
		{
			std::string p = iter->path().string();
			//if a file is the manifest it will open it and check what the label says
			//does this by taking the last 12 characters of the filepath and check that its "manifest.txt"
			if (p.substr(p.size() - 12, 12) == "manifest.txt")
			{
				//Check to see if the file is open or not
				std::ifstream f(p);
				if (f.is_open() == false)
				{
					std::cout << "Failed to open file." << std::endl;
				}
				//Loops while there is still content inside of the file
				while (std::getline(f,line))
				{
					//Grabs each line of the text file one by one
					std::getline(f,line);
					std::cout << line.substr(0,5) << std::endl;
					//Checks to see if the line is label
					//if it is label, take the rest of the line as the label
					if (line.substr(0, 6) == "Label:")
					{
						c_label = line.substr(7, line.size() - 1);
					}
				}
				f.close();
				//if the labels match copy the file path to the folder
				if (c_label == label)
				{
					fs::copy(iter->path().parent_path(), copy_path, fs::copy_options::recursive);
				}
				
			}
			iter.operator++();
		}	

		//std::ofstream fileManifest(source_path);
		//std::cout << label << std::endl;
		//label_name.insert(0, "\\");
		//const char * label2 = label_name.c_str();
		//fileManifest.open(label2, std::ofstream::trunc);
		//fileManifest << "File created at:" << timeStr;
	
		
		std::cout << "Successfully copied file path." << std::endl;
	}
}
