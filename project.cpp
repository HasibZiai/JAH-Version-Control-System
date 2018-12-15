#include "project.h"
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <stdio.h>

namespace fs = std::experimental::filesystem;

project::project()
{
	num_folders = 0;
	num_files = 0;
}


project::~project()
{
}

void project::find_directories(std::string project_root) {

	try {
		for (auto& p : fs::recursive_directory_iterator(project_root))
			// For every file that is a regular file...
			if (fs::is_directory(p))
			{
				// Created vector paths to store paths to regular files into
				dir.push_back(fs::path(p).relative_path());
				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
				num_folders++;
			}
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}
	std::cout << "Number of directories in T: " << dir.size();
	system("pause");
}

void project::find_files(std::string project_root)
{
	try {
		for (auto& p : fs::recursive_directory_iterator(project_root))
			// For every file that is a regular file...
			if (fs::is_regular_file(p))
			{
				// Created vector paths to store paths to regular files into
				files.push_back(fs::path(p).relative_path());
				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
				num_files++;
			}
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}
	std::cout << "Number of directories in T: " << files.size();
	system("pause");
}