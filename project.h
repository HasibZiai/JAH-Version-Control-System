#ifndef _PROJECT_
#define _PROJECT_
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class project
{
public:
	project();
	~project();
	std::vector<fs::path> dir;
	std::vector<fs::path> files;
	void find_directories(std::string project_path);
	void find_files(std::string project_path);

private:
	int num_folders;
	int num_files;
};

#endif