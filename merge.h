#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <stdio.h>


namespace fs = std::experimental::filesystem;

//	Function to find all folders within specified path
std::vector<fs::path> find_dir(std::string _dir) {

	std::vector<fs::path> _paths;
	// For loop that recursively iterates through all folders/sub-folders searching for files in project T
	try {
		for (auto& p : fs::recursive_directory_iterator(_dir))
			// For every file that is a regular file...
			if (fs::is_directory(p))
			{
				// Increment counter for # of directories within repo

				// Created vector paths to store paths to regular files into
				_paths.push_back(fs::path(p).relative_path());

				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";
			}
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}
	std::cout << "Number of directories in T: " << _paths.size();
	return _paths;
	system("pause");
}


void merge(std::string T_path, std::string R_path, std::string G_path) {

	std::vector<fs::path> T = find_dir(T_path);
	std::vector<fs::path> R = find_dir(R_path);
	std::vector<fs::path> G = find_dir(G_path);

}