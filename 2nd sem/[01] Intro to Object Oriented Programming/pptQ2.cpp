#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const char * filename = "BINARY";

int main() {
    float height[4] = {175.5, 153.0, 167.25, 160.70};

    ofstream outfile(filename);
    outfile.write((char *) & height, sizeof(height));
    outfile.close();

    for(int i = 0; i < 4; i++)
        height[i] = 0;
    ifstream infile(filename);
    infile.read((char *) & height, sizeof(height));
    for (int i = 0; i < 4; i++) {
        cout << setw(10) << height[i];
    }
    cout << endl;
    infile.close();
    return 0;
}

