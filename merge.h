#pragma once
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <stdio.h>
#include <fstream>
#include <string>
#include "project.h"


namespace fs = std::experimental::filesystem;

void merge(std::string T_path, std::string source_path, std::string R) {

	//	Create object class PROJECT named T and call functions
	project T;
	std::vector<fs::path> T_list;
	std::vector<fs::path> R_list;
	//T.find_directories(T_path);
	//T.find_files(T_path);
	try {

		for (auto& p : fs::recursive_directory_iterator(T_path))

			// For every file that is a regular file...

			if (fs::is_directory(p))
			{
				T_list.push_back(fs::path(p).relative_path());
				// Created vector paths to store paths to regular files into
				//dir.push_back(fs::path(p).relative_path());
				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
				//num_folders++;
			}
			else if (fs::is_regular_file(p))
			{
				T_list.push_back(fs::path(p).relative_path());
				// Created vector paths to store paths to regular files into
				//T.file_add(p);
				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
				//num_files++;
			}
	}

	catch (fs::filesystem_error& e)			
	{
		std::cout << e.what() << '\n';
		//system("pause");
	}
	
	for (int i = 0; i < T_list.size(); i++)
	{
		std::cout << T_list[i] << std::endl;
	}

	//Path of all the branches
	fs::recursive_directory_iterator iter(source_path);
	fs::recursive_directory_iterator end;
	//Fstream variable to open the manifest
	std::fstream file;
	//Line handles the lines of the manifest
	//path is for the end of the directory path
	//c_label is the label of the manifest that we are checking against
	//rr_path is the path of the R branch
	std::string line, path, c_label, rr_path;
	//T_label is if they gave a label, T_Fname is if they gave a file name.
	bool T_label = false;
	bool T_Fname = false;

	
	//Check if the string given is a manifest name file or if it is a label
	//Check will change depending if label or manifest given. If label given, assume manifest is named manifest.txt
	if (R.substr(R.length() - 4, 4) == ".txt")
	{
		std::cout << "User has given file name instead of a label." << std::endl;
		std::cout << "File name is: " << R << std::endl;
		T_Fname = true;

	}
	else
	{
		std::cout << "User has given label instead of a file name." << std::endl;
		std::cout << "Label name is: " << R << std::endl;
		T_label = true;
	}




	//Grabs the Path of R and will throw it inside a vector
	while (iter != end)
	{
		std::string tpath = iter->path().string();
		//Grab the end of the file path in order to see which file is the manifest
		for (int i = tpath.length()-1; i > 0; i--)
		{
			if (tpath.at(i) == '\\')
			{
				path = tpath.substr(i + 1, (tpath.length()) - 1 - (i-1));
				std::cout << "End of path is : " << path << std::endl;
				break;
			}
		}
		if (T_label == true)
		{
			std::ifstream f(tpath);
			if (tpath.substr(tpath.size() - 12, 12) == "manifest.txt")
			{
				//Check to see if the file is open or not
				std::ifstream f(tpath);
				if (f.is_open() == false)
				{
					std::cout << "Failed to open file." << std::endl;
				}
				//Loops while there is still content inside of the file
				while (std::getline(f, line))
				{
					//Grabs each line of the text file one by one
					std::getline(f, line);
					std::cout << line.substr(0, 5) << std::endl;
					//Checks to see if the line is label
					//if it is label, take the rest of the line as the label
					if (line.substr(0, 6) == "Label:")
					{
						c_label = line.substr(7, line.size() - 1);
					}
				}
				f.close();
				//If the label inside the manifest matches the filename then the location of the manifest there is where the branch starts
				if (c_label == R)
				{
					rr_path = iter->path().parent_path().string();
					std::cout << "The parent path for the R branch is: " << rr_path << std::endl;
				}
			}
		}
		else if (T_Fname == true)
		{
			if (R == path)
			{
				rr_path = iter->path().parent_path().string();
				std::cout << "The parent path for the R branch is: " << rr_path <<  std::endl;
			}
		}		
		iter.operator++();
	}


	try {

		for (auto& p : fs::recursive_directory_iterator(rr_path))

			// For every file that is a regular file...

			if (fs::is_directory(p))
			{
				R_list.push_back(fs::path(p).relative_path());
				// Created vector paths to store paths to regular files into
				//dir.push_back(fs::path(p).relative_path());
				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
				//num_folders++;
			}
			else if (fs::is_regular_file(p))
			{
				R_list.push_back(fs::path(p).relative_path());
				// Created vector paths to store paths to regular files into
				//T.file_add(p);
				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
				//num_files++;
			}
	}

	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		//system("pause");
	}

	for (int i = 0; i < R_list.size(); i++)
	{
		std::cout << R_list[i] << std::endl;
	}


	
}
