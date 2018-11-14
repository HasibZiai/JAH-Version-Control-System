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



#include "Repo.h"


namespace fs = std::experimental::filesystem;


int main() {

	int userChoice = 0;
	std::string sPath;
	std::string tPath;
	std::string tempLabel;
	std::string tempManPath;

	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	std::cout << "        Welcome to JAH Version Control System\n\n\n";
	std::cout << "        Press 1 to Create a new repository\n";
	std::cout << "        Press 2 to add a Label to a manifest file\n";
	std::cout << "        Press 3 to Check Out files from an existing repository\n";
	std::cout << "        Press 4 to Check In files and update an existing repository\n\n";
	std::cout << "        Please select an action(q to quit):\n\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
	std::cin >> userChoice;
	std::cin.ignore();

	switch (userChoice) 
	{
		case 1:
			std::cout << "\n";
			std::cout << "Create Repo\n\n";
			std::cout << "Please enter the Source path:\n";
			std::getline(std::cin, sPath);
			std::cout << "Please enter the Target path:\n";
			std::getline(std::cin, tPath);
			create_repo(sPath, tPath);
			break;
		case 2: 
			std::cout << "\n";
			std::cout << "Add label\n\n";
			std::cout << "Please enter the path of the manifest file you want to label:\n";
			std::getline(std::cin, tempManPath);
			std::cout << "Please enter the label you want to add:\n";
			std::getline(std::cin, tempLabel);
			//label(tempManPath, tempLabel)
			break;
		case 3:
			std::cout << "\n";
			std::cout << "Check Out\n\n";
			std::cout << "Please enter the Source path:\n";
			std::getline(std::cin, sPath);
			std::cout << "Please enter the Target path:\n";
			std::getline(std::cin, tPath);
			//check_out(sPath, tPath);
			break;
		case 4:
			std::cout << "\n";
			std::cout << "Check In\n\n";
			std::cout << "Please enter the Source path:\n";
			std::getline(std::cin, sPath);
			std::cout << "Please enter the Target path:\n";
			std::getline(std::cin, tPath);
			check_in(sPath, tPath);
			break;
		default:
			std::cout << "Quitting...\n";
	}

	//label("mypt2_repo", "Fred");
	//create_repo("mypt2", "mypt2_repo");
	
	return 0;
}
