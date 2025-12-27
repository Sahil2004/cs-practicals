#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    char TerminalOne, TerminalTwo;
    char nTerminalOne, nTerminalTwo;
    char tableArray[10][6][20] = {
        {"s3", "s4", "Error", "1", "2"},      // state 0
        {"Error", "Error", "ACCEPT", "Error", "Error"}, // state 1
        {"s6", "s7", "Error", "Error", "5"},  // state 2
        {"s3", "s4", "Error", "Error", "8"},  // state 3
        {"r3", "r3", "Error", "Error", "Error"}, // state 4
        {"Error", "Error", "r1", "Error", "Error"}, // state 5
        {"s6", "s7", "Error", "Error", "Error"},    // state 6
        {"Error", "Error", "r3", "Error", "Error"}, // state 7
        {"r2", "r2", "Error", "Error", "Error"},    // state 8
        {"Error", "Error", "r2", "Error", "Error"}}; // state 9

    char stack[40], iTemp[40];
    int topStack = 0;
    int columnCount = 0, rowCount = 0, popStack = 0, no = 0, lengthCount = 0;

    // terminals and non-terminals
    char terminal[5] = {'a', 'd', '$', 'S', 'A'};
    char ithrowCount[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    char rule[3][10] = {"S->AA", "A->aA", "A->d"};

    cout << "Enter the set of terminals: ";
    cin >> TerminalOne >> TerminalTwo;
    cout << "Enter the set of non-terminals: ";
    cin >> nTerminalOne >> nTerminalTwo;
    cout << "Productions are:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << rule[i] << "\n";
    }

    cout << "\nCLR PARSING TABLE:\n";
    for (int i = 0; i < 5; i++)
    {
        cout << "\t" << terminal[i];
    }
    for (int i = 0; i < 10; i++)
    {
        cout << "\n" << ithrowCount[i];
        for (int j = 0; j < 5; j++)
        {
            cout << "\t" << tableArray[i][j];
        }
    }

    stack[topStack++] = '$';
    stack[topStack++] = '0';

    cout << "\n\nSTACK IMPLEMENTATION";
    cout << "\nDirections: The input string must contain $ at the end.";
    cout << "\nEnter the input string: ";
    cin >> iTemp;

    cout << "\n\nSTACK\t\tINPUT STRING\t\tACTION\n";

    int i = 0;
    while (true)
    {
        // Print current stack
        for (int j = 0; j < topStack; j++)
        {
            cout << stack[j];
        }
        cout << "\t\t";

        // Print remaining input
        for (int j = i; j < strlen(iTemp); j++)
        {
            cout << iTemp[j];
        }
        cout << "\t\t";

        // Get current state from top of stack
        int state = stack[topStack - 1] - '0';

        // Find input symbol index
        int symbolIndex = -1;
        for (int j = 0; j < 5; j++)
        {
            if (iTemp[i] == terminal[j])
            {
                symbolIndex = j;
                break;
            }
        }

        if (symbolIndex == -1)
        {
            cout << "Invalid symbol in input!\n";
            break;
        }

        string action = tableArray[state][symbolIndex];

        if (action == "ACCEPT")
        {
            cout << "ACCEPT\n";
            break;
        }
        else if (action[0] == 's') // shift
        {
            stack[topStack++] = iTemp[i];         // push terminal
            stack[topStack++] = action[1];        // push state number
            cout << "Shift " << iTemp[i] << " " << action[1] << "\n";
            i++;
        }
        else if (action[0] == 'r') // reduce
        {
            int ruleNo = action[1] - '1';          // rule number (0-indexed)
            int rhsLen = strlen(rule[ruleNo]) - 3; // RHS length

            int symbolsToPop = rhsLen * 2;
            topStack -= symbolsToPop;

            char lhs = rule[ruleNo][0]; // LHS non-terminal
            int prevState = stack[topStack - 1] - '0';

            // Find goto column for LHS
            int lhsCol = -1;
            for (int j = 0; j < 5; j++)
            {
                if (terminal[j] == lhs)
                {
                    lhsCol = j;
                    break;
                }
            }

            stack[topStack++] = lhs;
            stack[topStack++] = tableArray[prevState][lhsCol][0]; // Push new state

            cout << "Reduce using rule " << ruleNo + 1 << ": " << rule[ruleNo] << "\n";
        }
        else
        {
            cout << "\nError\nSTRING REJECTED\n";
            break;
        }
    }

    return 0;
}
