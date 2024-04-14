#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main() {
    // Get a list of all block devices
    cout << "All the block devices on the system are:" << endl;
    system("lsblk -o NAME | grep -v NAME > devices.txt");
    ifstream file("devices.txt");
    if (!file.is_open()) {
      cout << "Error opening file" << endl;
      return 1;
    }
    string device;
    while (getline(file, device)) {
        cout << device << endl;
    }
    file.close();
    // Get the folders in root directory with the space of each
    cout << "All the root folders with their sizes:" << endl;
    system("du -sh /home/sahil/* | grep -v Permission > directories.txt");
    file.open("directories.txt");
    if (!file.is_open()) {
      cout << "Error opening file" << endl;
      return 1;
    }
    string directory;
    while (getline(file, directory)) {
        cout << directory << endl;
    }
    file.close();
    return 0;
}