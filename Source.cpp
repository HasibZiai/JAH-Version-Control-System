/*
	Computer Science 362 - SWE Fundamentals - VCS Project #3
	Team Name: JAH
	Authors :
		Aaron Gumabong - aarongumabong@gmail.com
		Joe Vanacore - joevanacore@gmail.com
		Hasib Ziai - hasibziai@csu.fullerton.edu

	Description: This program, that requires no initial invocation or function calls, executes from main to create a repository for a Version Control System.
					Refactor to function call createRepo is possible. User will be prompted to enter a source path, containing files and their associated directories
					along with the target path; the directory where the repository will be created. This program assumes all of the project guideline assumptions, but 
					we have created some directory exist checks for sanity. 
*/
#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <stdio.h>

#include "checksum.h"
#include "Label.h"
#include "checkout.h"
#include "merge.h"

namespace fs = std::experimental::filesystem;

	// create_repo has two paramters: 
	// 1. Source path of project folder you want to create a repo of
	// 2. Target path of newly created repo
void create_repo(std::string sourcePath, std::string targetPath)
{

	time_t current_time = time(NULL);
	//array to take in the system time and date
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);
	int regular_files = 0;
	int n = 0;
	// Main code for copying files and directories along with all related subdirectories
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
	std::string checksum_value;

	std::vector<fs::path> full_filename;

	//Create a manifest file
	std::streambuf *psbuf, *backup;
	std::ofstream fileManifest(targetPath);
	fileManifest.open(targetPath += "\\manifest.txt", std::ofstream::trunc);

	backup = std::cout.rdbuf();

	psbuf = fileManifest.rdbuf();
	std::cout.rdbuf(psbuf);

	targetPath = targetPath.substr(0, targetPath.size() - 13);

	fileManifest << "The source path entered was: " << sourcePath << "\n";
	fileManifest << "The target path entered was: " << targetPath << "\n\n\n\n";

	// For loop that recursively iterates through all folders/sub-folders searching for files
	try {
		for (auto& p : fs::recursive_directory_iterator(targetPath))
			// For every file that is a regular file...
			if (fs::is_regular_file(p))
			{
				// Increment counter for # of files within repo
				regular_files++;

				// Created vector paths to store paths to regular files into
				paths.push_back(fs::path(p).parent_path());

				// Created vector filenames without extension to hold names of files within subfolders for Checksum calculation
				filenames.push_back(fs::path(p).stem());

				// Created vector that contains the name of the file being copied along with its extension
				full_filename.push_back(fs::path(p).filename());

				// Create directories and subdirectories
				fs::create_directories(paths[n] / filenames[n]);

				// Iterate through folders and find the checksum values of all text files found
				checksum_value = checksum(fs::path(p));

				// Push all artifact directories that will be created into a vector
				artifact_path.push_back(paths[n] / filenames[n] / checksum_value += ".txt");

				// Create new text files using artifact directories found above by iteration
				std::ofstream outfile(artifact_path[n]);

				// Writing the contents of the original files to the Artifact files
				outfile << text_content(fs::path(p));

				std::cout << "The relative path is: " << fs::path(p).relative_path() << "\n\n\n";

				// Close ofstream to prevent memory leak
				outfile.close();
				n++;
			}
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}

	// Cleanup leftover artifact creation of manifest text file.
	fs::remove_all(targetPath + "/manifest");

	// Create iterator to go through target folder and delete original files that were copied.
		for (int i = 0; i < full_filename.size(); i++)
		{
			try
			{
				/* In our design, manifest.txt is added  in full_filename vector but since the fs::remove function
					cannot find manifest.txt within the current directory, it will print an error. This if statement is a 
					rudimentary workaround.
				*/
				if (full_filename[i].string() == "manifest.txt")
				{
					i++;
				}
				fs::remove(paths[i] / full_filename[i]);
			}
			catch (fs::filesystem_error &p)
			{
				std::cout << p.what() << "\n";
			}
		}

	std::cout << "There are " << regular_files << " files in the repository (including the manifest.txt file)." << "\n";
	std::cout.rdbuf(backup);
	// Printout out the timestamp
	std::cout << timeStr;
	std::cout << "The operation is complete. Please check manifest file.\n";
}



int main() {

	//label("mypt2_repo", "Fred");
	//create_repo("mypt2", "mypt3_repo");
	//check_out("mypt2_repo", "mypt2_checkout", "Fred");

	//	Three parameters:
	//	1. Path of T project
	//	2. Path of R project
	//	3. Path of G project
	//	Only testing for T project right now
	merge("mypt2_checkout", "a", "b");
	
	return 0;
}