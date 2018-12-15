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
#include "create.h"
#include "checksum.h"
#include "Label.h"
#include "checkout.h"
#include "merge.h"

namespace fs = std::experimental::filesystem;

int main() {

	//label("mypt2_repo", "Fred");
	create_repo("mypt2", "mypt3_repo");
	//check_out("mypt2_repo", "mypt2_checkout", "Fred");

	//	Three parameters:
	//	1. Path of T project
	//	2. Path of R project
	//	3. Path of G project
	//	Only testing for T project right now
	//merge("mypt2_checkout", "a", "b");
	
	return 0;
}