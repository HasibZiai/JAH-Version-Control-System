#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>
#include <ctime>
#include <stdio.h>



namespace fs = std::experimental::filesystem;

void check_out(std::string s_path, std::string source_path, std::string label )
{
	time_t current_time = time(NULL);
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);
	std::string label_name;
	std::string sp = source_path + "\\manifest.txt";
	
	if (source_path == s_path)
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
			if (p.substr(p.size() - 12, 12) == "manifest.txt")
			{
				std::ifstream f(p);
				if (f.is_open() == false)
				{
					std::cout << "Failed to open file." << std::endl;
				}
				while (std::getline(f,line))
				{
					std::getline(f,line);
					std::cout << line.substr(0,5) << std::endl;
					//stores the line that says label
					if (line.substr(0, 6) == "Label:")
					{
						c_label = line.substr(7, line.size() - 1);
					}
				}
				f.close();
				//if the labels match copy the file path to the folder
				if (c_label == label)
				{
					fs::copy(iter->path().parent_path(), source_path, fs::copy_options::recursive);
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
