#include <iostream>
#include <fstream>
#define SIZE 80

using namespace std;

int main() {
	ofstream fout("country");
	fout << "United States of America\n";
	fout << "United Kingdom";
	fout.close();
	fout.open("capital");
	fout << "washington\n";
	fout << "london";
	fout.close();
	char line[SIZE];
	ifstream fin1("country"),  fin2("capital");
	for(int i = 0; i <= 10; i++) {
	    if (fin1.eof() != 0 || fin2.eof() != 0) {
	        fin1.close();
	        fin2.close();
            break;
        }
        fin1.getline(line, SIZE);
        cout << "Capital of " << line;
        fin2.getline(line, SIZE);
        cout << " is " << line << "\n";
    }
    return 0;
}
