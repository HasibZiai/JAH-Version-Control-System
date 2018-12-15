#ifndef _MERGE_
#define _MERGE_
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <stdio.h>
#include "project.h"


namespace fs = std::experimental::filesystem;

void merge(std::string T_path, std::string R_path, std::string G_path) {

	//	Create object class PROJECT named T and call functions
	project T;
	T.find_directories(T_path);
	T.find_files(T_path);

}
#endif