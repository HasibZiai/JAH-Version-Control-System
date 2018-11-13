#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;

void check_out(std::string copy_path, std::string source_path)
{
	if (source_path == copy_path)
	{
		std::cout << "Error copied path cannot be the same as destination folder." << std::endl;
	}
	else
	{
		fs::copy(copy_path, source_path, fs::copy_options::recursive);
		std::cout << "Successfully copied file path." << std::endl;
	}
}
