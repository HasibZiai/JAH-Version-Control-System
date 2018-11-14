#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <stdio.h>

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