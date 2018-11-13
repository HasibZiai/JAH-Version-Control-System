/*
Computer Science 362 - SWE Fundamentals - VCS Project #1
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

#include "checksum.h"
#include "checkout.h"

namespace fs = std::experimental::filesystem;


void create_repo()
{
	std::string sourcePath;
	std::string targetPath;

	std::cout << "Please enter the source path you want to copy: \n";

	std::getline(std::cin, sourcePath);											//get sourcePath, includes whitespace for Windows paths

																				/*
																				if (!fs::is_directory(sourcePath)) {
																				std::cout << "Not a valid path \n";
																				return 1;
																				}
																				*/

	std::cout << "Now enter the target path you want to create your repo: \n";

	std::getline(std::cin, targetPath);											//get targetPath, includes whitespace for Windows paths

																				/*
																				if (!fs::is_directory(targetPath)) {
																				std::cout << "Target path does not exist. \n";
																				std::cout << "Creating directory. \n";
																				fs::create_directory(targetPath);
																				}
																				*/

	time_t current_time = time(NULL);
	//array to take in the system time and date
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);


	// In this example we have two text files in a folder "mypt" within the source folder.
	// This code will copy contents of "mypt" to target folder "mypt_repo".

	int regular_files = 0;
	int n = 0;
	
	// Main code for copying files and directories along with all related subdirectories
	/*
	try {
		fs::copy(sourcePath, targetPath, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
	}
	catch (fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
		system("pause");
	}
	*/
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

void label() {

	std::string manifest_folder;
	std::string label;

	std::cout << "Enter the repository root path to find manifest file: \n";
	std::getline(std::cin, manifest_folder);
	std::cout << "Enter your label: ";
	std::getline(std::cin, label);

	std::ofstream manifest_file(manifest_folder);
	manifest_file.open(manifest_folder += "\\manifest.txt", std::ofstream::app);
	manifest_file << label;
	manifest_file.close();

}

int main() {

	std::string copy_path;
	std::string copy_source;
	//label();
	//create_repo();

	std::cout << "Please enter a file path to copy: ";
	std::getline(std::cin, copy_source);
	std::cout << "Please enter the path for the file to be copied to: ";
	std::getline(std::cin, copy_path);

	check_out(copy_source, copy_path);

	return 0;
}
