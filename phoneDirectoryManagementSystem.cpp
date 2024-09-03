#include <iostream>
#include <direct.h>
#include <string>
using namespace std;

void display_files();
void create_directory();
void modify_directory();

	int main() {
	int selection;
		while (true) {
	cout << " Main Menu: " << endl;
	cout << "--------------------------------\n";
	cout << "1. Show List of Files\n";
	cout << "2. Create New Folder\n";
	cout << "3. Change Current Directory\n";
	cout << "4. Exit Application\n";
	cout << "Select Option: ";
	cin >> selection;

	switch (selection) {
		case 1:
			display_files();
				break;
		case 2:
			create_directory();
				break;
		case 3:
			modify_directory();
				break;
		case 4:
		
		return 0;
	default:
		cout << "Invalid selection. Please try again.\n";
		}	
	}
	return 0;
	}

void display_files() {
	int option;
	cout << " FILE LIST DETAILS:" << endl;
	cout << "--------------------------------------\n" << endl;
	cout << "1. Show All Files\n";
	cout << "2. Show Files by Extension\n";
	cout << "3. Show Files by Name\n";
	cout << "Select Option: ";
	cin >> option;

	switch (option) {
		case 1:
			cout << "Listing all files:\n";
			system("dir");
			break;
		case 2: {
			string extension;
			cout << "Enter file extension: ";
			cin >> extension;
			system(("dir *." + extension).c_str());
			break;
			}
		case 3: {
			string name_pattern;
			cout << "Enter file name pattern: ";
			cin >> name_pattern;
			system(("dir " + name_pattern).c_str());
			break;
		}
			default:
			cout << "Invalid selection. Please try again.\n";
		}
	}


void createDirectory(const string& path) { 
    if (fs::create_directory(path)) {
        cout << "Directory Successfully Created: " << path << endl;
    } else {
        cout << "Error creating directory." << endl;
    }
}

void create_directory() {

	string folder_name;
		cout << "Folder name: ";
		cin >> folder_name;

	if (_mkdir(folder_name.c_str()) == 0) {
		cout << "Folder created successfully." << endl;
			} else {
		cout << "Error creating folder. It may already exist or be invalid." << endl;
		}
	}

void modify_directory() {

	int action;
		cout << "Change Directory Options:" << endl;
		cout << "1. Go one level up." << endl;
		cout << "2. Go to the root directory." << endl;
		cout << "3. Go to a specific directory provided by the user." << endl;
		cout << "Select your option: ";
		cin >> action;

		switch (action) {
			case 1:
				if (_chdir("..") == 0) {
				cout << "Moved to parent directory." << endl;
			} else {
		cout << "Error moving to parent directory." << endl;
		}
		break;
			case 2:
				if (_chdir("\\") == 0) {
				cout << "Moved to root directory." << endl;
			} else {
				cout << "Error moving to root directory." << endl;
			}
		break;
			case 3: {
				string target_dir;
				cout << "Directory name: ";
				cin >> target_dir;
				if (_chdir(target_dir.c_str()) == 0) {
				cout << "Directory changed successfully." << endl;
		} else {
				cout << "Error changing directory. It may not exist." << endl;
		}
		break;
		}
		default:
				cout << "Invalid selection. Please try again." << endl;
		}
	}
