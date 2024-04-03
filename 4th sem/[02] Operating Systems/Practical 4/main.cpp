#include <iostream>
#include <fstream>

using namespace std;

int main() {
  // Open the FAT file
  ifstream fatFile("fat.bin");

  // Check if the file is open
  if (!fatFile.is_open()) {
    cout << "Error opening FAT file" << endl;
    return 1;
  }

  // Read the FAT file
  char fat[1024];
  fatFile.read(fat, sizeof(fat));

  // Close the FAT file
  fatFile.close();

  // Print the FAT file
  for (int i = 0; i < 1024; i++) {
    cout << fat[i] << " ";
  }

  cout << endl;

  return 0;
}