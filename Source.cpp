#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#include "newChecksum.h"
#include "date.h"
#include "tz.h"


namespace fs = std::experimental::filesystem;


int main()
{
	std::string sourcePath;
	std::string targetPath;

	std::cout << "Please enter the source path you want to copy: \n";

	std::getline(std::cin, sourcePath);											//get sourcePath, includes whitespace for Windows paths

	if (!fs::is_directory(sourcePath)) {										//checks if sourcePath is valid dir
		std::cout << "Not a valid path \n";
		return 1;
	}

	std::cout << "Now enter the target path you want to create your repo: \n";

	std::getline(std::cin, targetPath);											//get targetPath, includes whitespace for Windows paths

	if (!fs::is_directory(targetPath)) {										//checks if targetPath is valid dir
		std::cout << "Target path does not exist. \n";
		std::cout << "Creating directory. \n";										//creates new directory if it does not exist

		fs::create_directory(targetPath);

	}

	// In this example I have two text files in a folder "mypt" within the source folder.
	// This code will copy contents of "mypt" to target folder "mypt_repo".

	int regular_files = 0;
	int n = 0;
	// Main code for copying files
	try {
		fs::copy(sourcePath, targetPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}
	// Holds copies of the above files and subdirectories
	// Overwrites existing files while adding newly added ones

	std::vector<fs::path> paths;
	std::vector<fs::path> filenames;
	std::vector<fs::path> artifact_path;
	std::string target = targetPath;
	std::string checksum_value;

	//Create a manifest file
	std::streambuf *psbuf, *backup;
	std::ofstream fileManifest(targetPath);
	fileManifest.open(targetPath += "\\manifest.txt", std::ofstream::out | std::ofstream::trunc);
	
	backup = std::cout.rdbuf();

	psbuf = fileManifest.rdbuf();
	std::cout.rdbuf(psbuf);

	//Error getting date and time here!! 
	/**********************************/
	//std::cout << "The current time is: " << date::make_zoned(date::current_zone(), std::chrono::system_clock::now()) << '\n';
	
	targetPath = targetPath.substr(0, targetPath.size() - 13);

	//fileManifest << "The time is: " << date::make_zoned(date::current_zone(), std::chrono::system_clock::now()) << '\n';

	fileManifest << "The source path entered was: " << sourcePath << "\n";
	fileManifest << "The target path entered was: " << targetPath << "\n\n\n\n";


	// For loop that recursively iterates through all folders/sub-folders searching for files
	try {
		for (auto& p : fs::recursive_directory_iterator(target))
			if (fs::is_regular_file(p))
			{
				regular_files++;

				// Created vector paths to store paths to regular files into
				paths.push_back(fs::path(p).parent_path());

				// Created vector filenames without extension to hold names of files within subfolders for Checksum calculation
				filenames.push_back(fs::path(p).stem());

				// Create directories and subdirectories
				fs::create_directories(paths[n] / filenames[n]);

				// Iterate through folders and find the checksum values of all text files found
				checksum_value = checksum(fs::path(p));

				// Push all artifact directories that will be created into a vector
				artifact_path.push_back(paths[n] / filenames[n] / checksum_value += ".txt");

				// Create new text files using artifact directories found above by iteration
				std::ofstream outfile(artifact_path[n]);


				outfile << text_content(fs::path(p));

				

				//std::cout << checksum(fs::path(p)) << "\n";
				//std::cout << fs::path(p) << "\n";
				//std::cout << fs::path(p).parent_path() << "\n";

				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";

				outfile.close();

				n++;
			}
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}
	std::cout << "There are " << regular_files << " files in the repository (including the manifest.txt file)." << "\n";
	
	
	std::cout.rdbuf(backup);

	fileManifest.close();

	std::cout << "The operation is complete. Please check manifest file.\n";

	system("pause");

	return 0;
}

