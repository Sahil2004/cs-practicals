#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <cstdlib>
using namespace std;

int labelFlag[20];
int number = 0;

bool check_labelFlag(int k) {
    for (int i = 0; i < number; i++) {
        if (k == labelFlag[i]) return true;
    }
    return false;
}

bool isNumber(const string &s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {
    ifstream fileIn;
    ofstream fileOut;
    char op[10], operand1[8], operand2[8], result[8];
    int i = 0;
    string fileName;

    cout << "Enter the filename of intermediate code: ";
    cin >> fileName;

    fileIn.open(fileName);
    fileOut.open("target_textFile.txt");

    if (!fileIn || !fileOut) {
        cerr << "\nError opening the file." << endl;
        return 1;
    }

    while (!fileIn.eof()) {
        fileIn >> op;
        i++;
        if (check_labelFlag(i)) {
            fileOut << "\nlabelFlag#" << i;
        }

        if (strcmp(op, "print") == 0) {
            fileIn >> result;
            fileOut << "\n\tOUT " << result;
        } else if (strcmp(op, "goto") == 0) {
            fileIn >> operand1 >> operand2;
            if (isNumber(operand2))
                labelFlag[number++] = atoi(operand2);
        } else if (strcmp(op, "[]=") == 0) {
            fileIn >> operand1 >> operand2 >> result;
            fileOut << "\n\tSTORE " << operand1 << "[" << operand2 << "]," << result;
        } else if (strcmp(op, "uminus") == 0) {
            fileIn >> operand1 >> result;
            fileOut << "\n\tLOAD -" << operand1;
            fileOut << "\n\tSTORE R1," << result;
        } else {
            switch (op[0]) {
                case '*':
                    fileIn >> operand1 >> operand2 >> result;
                    fileOut << "\n\tLOAD " << operand1 << ",R0";
                    fileOut << "\n\tLOAD " << operand2 << ",R1";
                    fileOut << "\n\tMUL R1,R0";
                    fileOut << "\n\tSTORE R0," << result;
                    break;
                case '+':
                    fileIn >> operand1 >> operand2 >> result;
                    fileOut << "\n\tLOAD " << operand1 << ",R0";
                    fileOut << "\n\tLOAD " << operand2 << ",R1";
                    fileOut << "\n\tADD R1,R0";
                    fileOut << "\n\tSTORE R0," << result;
                    break;
                case '-':
                    fileIn >> operand1 >> operand2 >> result;
                    fileOut << "\n\tLOAD " << operand1 << ",R0";
                    fileOut << "\n\tLOAD " << operand2 << ",R1";
                    fileOut << "\n\tSUB R1,R0";
                    fileOut << "\n\tSTORE R0," << result;
                    break;
                case '/':
                    fileIn >> operand1 >> operand2 >> result;
                    fileOut << "\n\tLOAD " << operand1 << ",R0";
                    fileOut << "\n\tLOAD " << operand2 << ",R1";
                    fileOut << "\n\tDIV R1,R0";
                    fileOut << "\n\tSTORE R0," << result;
                    break;
                case '=':
                    fileIn >> operand1 >> result;
                    fileOut << "\n\tSTORE " << operand1 << "," << result;
                    break;
                case '>':
                    fileIn >> operand1 >> operand2 >> result;
                    fileOut << "\n\tLOAD " << operand1 << ",R0";
                    fileOut << "\n\tJGT " << operand2 << ",labelFlag#" << result;
                    if (isNumber(result))
                        labelFlag[number++] = atoi(result);
                    break;
                case '<':
                    fileIn >> operand1 >> operand2 >> result;
                    fileOut << "\n\tLOAD " << operand1 << ",R0";
                    fileOut << "\n\tJLT " << operand2 << ",labelFlag#" << result;
                    if (isNumber(result))
                        labelFlag[number++] = atoi(result);
                    break;
            }
        }
    }

    fileIn.close();
    fileOut.close();

    // Display the output file content
    ifstream display("target_textFile.txt");
    if (!display) {
        cerr << "Error opening output file." << endl;
        return 1;
    }
    char ch;
    while (display.get(ch)) {
        cout << ch;
    }
    display.close();

    return 0;
}
