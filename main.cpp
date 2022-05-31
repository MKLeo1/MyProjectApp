/*App for counting empty & non empty lines from specified directory that will handle recursive directories.
by M.K. 
*/
#include <boost/filesystem.hpp>
#include <conio.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

namespace fs = boost::filesystem;

std::string getpass();
void directory_check();
void counting_lines_from_files();
void number_of_files(std::string);

std::string pass = "";
std::string dir = "";
std::string line = "";

long files_number = { 0 };
long non_empty = { 0 };
long empty = { 0 };
bool check = true;

int main()
{
	getpass();
	if (pass != "1234") return 0;

	directory_check();
	std::cout << "Work in progress..." << "\n";

	auto start = std::chrono::steady_clock::now();

	std::thread t1(counting_lines_from_files);
	std::thread t2(number_of_files, dir);

	t1.join();
	t2.join();

	auto end = std::chrono::steady_clock::now();

	std::cout << "\n\n";
	std::cout << "Files number: " << files_number << "\n";
	std::cout << "In checked files there are " << empty << " empty lines and " << non_empty << " non empty lines." << "\n";
	std::cout << "Elapsed time in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << " s" << std::endl;
	std::cout << "\n" << "Done!";
	std::cin.get();
	return 0;
}

//unlock app
std::string getpass()
{
	std::cout << "Type password: ";

	char ch = _getch();

	while (ch != 13)
	{
		if (ch != 8)
		{
			pass.push_back(ch);
			std::cout << "*";
		}
		else if (pass.length() > 0)
		{
			pass.pop_back();
			std::cout << "\b \b";
		}
		ch = _getch();
	}
	return pass;
}

void directory_check() {
	do {
		system("cls");
		std::cout << "Enter directory: ";
		std::getline(std::cin, dir);
		fs::path directory(dir);
		if (fs::exists(directory) && fs::is_directory(directory)) {
			check = false;
		}
		else {
			system("cls");
			dir = "";
			std::cout << "Wrong directory. Try again.\n";
		}
	} while (check);
}

//read empty and non_empty lines from vector elements
void counting_lines_from_files() {
	for (fs::directory_entry& entry : fs::recursive_directory_iterator(dir)) { 
		fs::ifstream file(entry.path());
		while (std::getline(file, line)) {
			if (line.empty()) {
				empty++;
			}
			else {
				non_empty++;
			}
		}
	}
}

//count number of files and cout and paths
void number_of_files(std::string dir) {
	for (const auto& x : fs::recursive_directory_iterator(dir)) {
		files_number++;
		std::cout << files_number << ". " << x.path() << "\n";
	}
}