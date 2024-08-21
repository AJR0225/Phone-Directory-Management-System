#include <iostream>
#include <string>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

const int MAX_ENTRIES = 100;
int lastIndex = 0;

class Directory
{
public:
    long phoneno;
    string fname, lname;

    Directory(long phoneno = 0, string fname = "", string lname = "")
        : phoneno(phoneno), fname(fname), lname(lname) {}
};

void addDetail(Directory &d, int flag) // Add details
{
    string specific = "";
    if (flag)
        specific = " New";

    cout << "Enter" << specific << " First Name: ";
    cin >> d.fname;
    cout << "Enter" << specific << " Last Name: ";
    cin >> d.lname;
    cout << "Enter" << specific << " Phone No: ";
    cin >> d.phoneno;
}

void displayDetails(const Directory d[])
{
    cout << "\nFirstName\tLastName\tPhoneno\t\n";
    for (int i = 0; i < lastIndex; i++)
    {
        if (d[i].fname != "Deleted")
        {
            cout << d[i].fname << "\t\t" << d[i].lname << "\t\t" << d[i].phoneno << "\t\n";
        }
    }
}

void modifyDetail(Directory d[])
{
    string fname, lname;
    cout << "To Modify Details: \n\n";
    cout << "Enter First Name: ";
    cin >> fname;
    cout << "Enter Last Name: ";
    cin >> lname;

    bool found = false;
    for (int i = 0; i < lastIndex; i++)
    {
        if (d[i].fname == fname && d[i].lname == lname)
        {
            found = true;
            addDetail(d[i], 1);
            break;
        }
    }
    if (found)
        cout << "\nDetails Modified Successfully..\n\n";
    else
        cout << "\nNo Details Found..\n\n";
}

void deleteDetail(Directory d[])
{
    string fname, lname;
    cout << "To Delete Details: \n\n";
    cout << "Enter First Name: ";
    cin >> fname;
    cout << "Enter Last Name: ";
    cin >> lname;

    bool found = false;
    for (int i = 0; i < lastIndex; i++)
    {
        if (d[i].fname == fname && d[i].lname == lname)
        {
            found = true;
            d[i].fname = "Deleted";
            d[i].lname = "Deleted";
            d[i].phoneno = 0;
            break;
        }
    }
    if (found)
        cout << "\nDetails Deleted Successfully..\n\n";
    else
        cout << "\nNo Details Found..\n\n";
}

void listAllFiles(const string& path) {
    cout << "Files in Directory:\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << entry.path().filename().string() << endl;
    }
}

void listFilesByExtension(const string& path, const string& extension) {
    cout << "Listing Files with Extension: " << extension << endl;
    int count = 0;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry) && entry.path().extension() == extension) {
            cout << entry.path().filename().string() << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "No files found with extension " << extension << endl;
}

void listFilesByPattern(const string& path, const string& pattern) {
    cout << "Listing Files Matching Pattern: " << pattern << endl;
    int count = 0;
    for (const auto& entry : fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry) && entry.path().filename().string().find(pattern) != string::npos) {
            cout << entry.path().filename().string() << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "No files found matching pattern " << pattern << endl;
}

void createDirectory(const string& path) {
    if (fs::create_directory(path)) {
        cout << "Directory created successfully: " << path << endl;
    } else {
        cout << "Failed to create directory. It may already exist or there was an error." << endl;
    }
}

void changeDirectory(string& path) {
    int choice;
    cout << "Change Directory Options:\n";
    cout << "1. Move one step back (to the parent directory).\n";
    cout << "2. Move to the root directory.\n";
    cout << "3. Move to a specific directory provided by the user.\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            path = fs::current_path().parent_path().string();
            break;
        case 2:
            path = fs::path("/").string();
            break;
        case 3: {
            string newPath;
            cout << "Enter the path of the directory: ";
            cin >> newPath;
            if (fs::exists(newPath) && fs::is_directory(newPath)) {
                path = newPath;
            } else {
                cout << "Invalid path or directory does not exist." << endl;
            }
            break;
        }
        default:
            cout << "Invalid option!" << endl;
    }
    fs::current_path(path); // Update the current working directory
    cout << "Current directory changed to: " << fs::current_path() << endl;
}

int main() {
    Directory d[MAX_ENTRIES];
    string currentPath = fs::current_path().string();
    int ch;

    cout << "\nWelcome to Phone Directory and File Management System\n";
    do {
        cout << "\nMain Menu\n";
        cout << "_____________\n";
        cout << "1. Display List of Files\n";
        cout << "2. Create a New Directory\n";
        cout << "3. Change the Working Directory\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: {
                int subChoice;
                cout << "\nList Files Menu\n";
                cout << "1. List all files in the current directory.\n";
                cout << "2. List files based on a specific extension (e.g., .txt).\n";
                cout << "3. List files based on a pattern (e.g., moha*.*).\n";
                cout << "Enter your choice: ";
                cin >> subChoice;

                switch (subChoice) {
                    case 1:
                        listAllFiles(currentPath);
                        break;
                    case 2: {
                        string extension;
                        cout << "Enter the file extension (e.g., .txt): ";
                        cin >> extension;
                        listFilesByExtension(currentPath, extension);
                        break;
                    }
                    case 3: {
                        string pattern;
                        cout << "Enter the file name pattern (e.g., moha*.*): ";
                        cin >> pattern;
                        listFilesByPattern(currentPath, pattern);
                        break;
                    }
                    default:
                        cout << "Invalid option!" << endl;
                }
                break;
            }
            case 2: {
                string dirName;
                cout << "Enter the name of the directory to create: ";
                cin >> dirName;
                createDirectory(currentPath + "/" + dirName);
                break;
            }
            case 3:
                changeDirectory(currentPath);
                break;
            case 4:
                cout << "Thank you for using the system. Exiting...\n";
                return 0;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    } while (ch != 4);

    return 0;
}
