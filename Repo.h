#pragma once

#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <stdio.h>

namespace fs = std::experimental::filesystem;


std::string checksum(fs::path file_path)
{

	//ifstream to take in the file
	std::ifstream ifs(file_path);
	//Reads all of the input of the string
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	//Prints out the contents of the file
	//std::cout << "Contents of the text file are: " << content << std::endl;

	//Holds the eventual checksum filename
	std::string file_name;
	//Holds the numbers for checksum
	int checksum = 0;
	//Helps loop through the 5 pattern checksum
	int counter = 1;
	for (int i = 0; i < content.size(); i++)
	{
		if (counter == 1)
		{
			checksum += content[i];
			counter++;
		}
		else if (counter == 2)
		{
			checksum += content[i] * 3;
			counter++;
		}
		else if (counter == 3)
		{
			checksum += content[i] * 7;
			counter++;
		}
		else if (counter == 4)
		{
			checksum += content[i] * 11;
			counter++;
		}
		else if (counter == 5)
		{
			checksum += content[i] * 17;
			counter = 1;
		}

	}
	//Uses modulo on the number to cut down on number size
	file_name = std::to_string(checksum % 2147483647);
	//Adds -L to the end of the file
	file_name += "-L";
	//converts the size of the file into a string and then adds it to the file name
	std::string size = std::to_string(fs::file_size(file_path));
	std::cout << "Size of the file is: " << size << " bytes." << std::endl;
	file_name += size;


	std::cout << "Final string is: " << file_name << std::endl;
	return file_name;
}

std::string text_content(fs::path file_path)
{
	//ifstream to take in the file
	std::ifstream ifs(file_path);
	//Reads all of the input of the string
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	return content;
}

void create_repo(std::string sourcePath, std::string targetPath)
{

	time_t current_time = time(NULL);
	//array to take in the system time and date
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);


	// In this example we have two text files in a folder "mypt" within the source folder.
	// This code will copy contents of "mypt" to target folder "mypt_repo".

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

	fileManifest << "Create Repo\n";
	// Printout out the timestamp
	std::cout << timeStr << "\n";

	fileManifest << "The source path entered was: " << sourcePath << "\n";
	fileManifest << "The target path entered was: " << targetPath << "\n\n\n\n";


	// For loop that recursively iterates through all folders/sub-folders searching for files
	try {
		for (auto& p : fs::recursive_directory_iterator(targetPath))
			// For every file that is a regular file...
			if (fs::is_regular_file(p) && fs::path(p).filename() != "manifest.txt")
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
	regular_files++;
	std::cout << "There are " << regular_files << " files in the repository (including the manifest file)." << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";


	std::cout.rdbuf(backup);



	std::cout << "The operation is complete. Please check manifest file.\n";

}

void label(std::string manifest_path, std::string label_name) {

	std::string _manifest_path = manifest_path + "\\manifest.txt";
	std::string _label_name = manifest_path + "\\" + label_name + ".txt";
	char f;
	std::string new_name;

	std::cout << "Has the manifest filename been changed? <y/n> \n";
	f = std::getchar();
	if (f == 'y') {
		std::cout << "Enter the name of the manifest file you wish to change: \n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, new_name);
		_manifest_path = manifest_path + "\\" + new_name + ".txt";
	}

	std::cout << "Change filename? <y/n> \n";
	std::cin >> f;
	if (f == 'y') {
		std::rename(_manifest_path.c_str(), _label_name.c_str());
	}
	else if (f == 'n') {
		std::ofstream manifest_file;
		manifest_file.open(_manifest_path, std::ofstream::out | std::ofstream::app);
		manifest_file << "\n";
		manifest_file << "Label: " << label_name;
		manifest_file.close();
	}
	else {
		std::cout << "Invalid choice!";
	}
	system("pause");
}

void check_out(std::string s_path, std::string source_path, std::string label)
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
				while (std::getline(f, line))
				{
					std::getline(f, line);
					std::cout << line.substr(0, 5) << std::endl;
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





void check_in(std::string sourcePath, std::string targetPath) {

	time_t current_time = time(NULL);
	//array to take in the system time and date
	char timeStr[26];
	char cur_time = ctime_s(timeStr, sizeof timeStr, &current_time);


	int regular_files = 0;
	int new_files = 0;
	int n = 0;

	// Holds copies of the above files and subdirectories
	// Overwrites existing files while adding newly added ones

	std::vector<fs::path> paths;
	std::vector<fs::path> filenames;
	std::vector<fs::path> artifact_path;
	std::string checksum_value;

	std::vector<fs::path> full_filename;

	//Open the manifest file
	std::streambuf *psbuf, *backup;
	std::ofstream fileManifest;

	fileManifest.open(targetPath += "\\manifest.txt", std::ios_base::app);

	//std::ofstream fileManifest(targetPath);
	//fileManifest.open(targetPath += "\\check_in_manifest.txt", std::ofstream::trunc);

	//redirecting std::out to file
	backup = std::cout.rdbuf();

	psbuf = fileManifest.rdbuf();
	std::cout.rdbuf(psbuf);

	//removing "\manifest.txt" for output in manifest
	targetPath = targetPath.substr(0, targetPath.size() - 13);

	fileManifest << "\n";
	fileManifest << "Check In\n";
	// Printout out the timestamp
	std::cout << timeStr << "\n";

	fileManifest << "The source path entered was: " << sourcePath << "\n";
	fileManifest << "The target path entered was: " << targetPath << "\n\n\n\n";


	// For loop that recursively iterates through all folders/sub-folders searching for files
	try {
		for (auto& targetFile : fs::recursive_directory_iterator(targetPath))

			// For every file that is a regular file...
			if (fs::is_regular_file(targetFile))
			{
				//std::cout << "Is the target file a regular file?\n";
				for (auto& sourceFile : fs::recursive_directory_iterator(sourcePath)) {
					if (fs::is_regular_file(sourceFile)) {
						

						//Check if current directory in Target is the same as current directory in Source
						std::string targetParentDir = fs::path(targetFile).parent_path().string();
						std::string sourceParentDir = fs::path(sourceFile).parent_path().string();

						//Get Parent Directory by removing Target Path
						std::string::size_type i = targetParentDir.find(targetPath);
						if (i != std::string::npos) {
							targetParentDir.erase(i, targetPath.length());
						}

						//Get Parent Directory by removing Source Path
						std::string::size_type j = sourceParentDir.find(sourcePath);
						if (j != std::string::npos) {
							sourceParentDir.erase(j, sourcePath.length());
						}

						if (targetParentDir == sourceParentDir) {
							
							

							if (fs::is_regular_file(sourceFile) && fs::is_regular_file(targetFile)) {
								if (fs::path(targetFile).filename() == fs::path(sourceFile).filename() && fs::path(targetFile).filename().string() != "manifest.txt") {

									//If filenames are same, increment regular files
									regular_files++;
								}
								if (fs::path(targetFile).filename() != fs::path(sourceFile).filename()) {

									// Increment counter for # of files within repo
									regular_files++;

									// calculate new Checksum Value
									checksum_value = checksum(fs::path(sourceFile));

									std::string copySource = fs::absolute(sourceFile).string();
									std::string copyTarget = fs::path(targetFile).parent_path().string();
									
									//Copy new file to target Repo directory
									try {
										fs::copy(copySource, copyTarget);
										//std::cout << "File copied successfully\n";
									}
									catch (std::exception & e) {
										std::cout << e.what() << "\n";
									}
									
									
									std::string newFileDir = fs::path(targetFile).parent_path().string();
									std::string newFileName = newFileDir + "\\" + checksum_value + ".txt";
									
									//Iterator finds new file and renames it with Checksum name
									for (auto& newFile : fs::directory_iterator(newFileDir)) {
										if (fs::path(newFile).filename() == fs::path(sourceFile).filename()) {
											//std::string newRelativePath = fs::path(newFile).relative_path().string();
											std::string tempFilePath = fs::absolute(newFile).string();
											//std::cout << "new Temp File Path: " << tempFilePath << "\n";

											fs::rename(tempFilePath, newFileName);
											//std::cout << "GRRRRRRRRRRRRRRRRRRRRRRREEEEEEEEEEEEEAAAT!!!!!!!!!!\n";
											std::cout << "The path of the checked-in file is: " << fs::path(newFile).parent_path().string() + "\\" + checksum_value + ".txt" << "\n\n\n";
											
											//Increment new file counter
											new_files++;
										}
									}
									
								}

							}
							

						}

					}
				}
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
	std::cout << "There are " << new_files << " new files checked-in to the repository." << "\n";

	regular_files++;
	std::cout << "There are " << regular_files << " files in the repository (including the manifest file)." << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";


	std::cout.rdbuf(backup);



	std::cout << "The operation is complete. Please check manifest file.\n";


}
