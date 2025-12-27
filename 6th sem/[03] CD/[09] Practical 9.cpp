#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;

struct Action {
    string type;  // "s3", "r2", "acc", "err"
};

map<pair<int, char>, Action> ACTION;
map<pair<int, char>, int> GOTO;

struct Production {
    char lhs;
    string rhs;
};

vector<Production> productions = {
    {'E', "E+T"},  // 0
    {'E', "T"},    // 1
    {'T', "T*F"},  // 2
    {'T', "F"},    // 3
    {'F', "(E)"},  // 4
    {'F', "i"}     // 5
};

void setupTables() {
    ACTION[{0, 'i'}] = {"s5"};
    ACTION[{0, '('}] = {"s4"};
    ACTION[{1, '+'}] = {"s6"};
    ACTION[{1, '$'}] = {"acc"};
    ACTION[{2, '+'}] = {"r1"};
    ACTION[{2, '*'}] = {"s7"};
    ACTION[{2, ')'}] = {"r1"};
    ACTION[{2, '$'}] = {"r1"};
    ACTION[{3, '+'}] = {"r3"};
    ACTION[{3, '*'}] = {"r3"};
    ACTION[{3, ')'}] = {"r3"};
    ACTION[{3, '$'}] = {"r3"};
    ACTION[{4, 'i'}] = {"s5"};
    ACTION[{4, '('}] = {"s4"};
    ACTION[{5, '+'}] = {"r5"};
    ACTION[{5, '*'}] = {"r5"};
    ACTION[{5, ')'}] = {"r5"};
    ACTION[{5, '$'}] = {"r5"};
    ACTION[{6, 'i'}] = {"s5"};
    ACTION[{6, '('}] = {"s4"};
    ACTION[{7, 'i'}] = {"s5"};
    ACTION[{7, '('}] = {"s4"};
    ACTION[{8, '+'}] = {"s6"};
    ACTION[{8, ')'}] = {"s11"};
    ACTION[{9, '+'}] = {"r0"};
    ACTION[{9, '*'}] = {"s7"};
    ACTION[{9, ')'}] = {"r0"};
    ACTION[{9, '$'}] = {"r0"};
    ACTION[{10, '+'}] = {"r2"};
    ACTION[{10, '*'}] = {"r2"};
    ACTION[{10, ')'}] = {"r2"};
    ACTION[{10, '$'}] = {"r2"};
    ACTION[{11, '+'}] = {"r4"};
    ACTION[{11, '*'}] = {"r4"};
    ACTION[{11, ')'}] = {"r4"};
    ACTION[{11, '$'}] = {"r4"};

    GOTO[{0, 'E'}] = 1;
    GOTO[{0, 'T'}] = 2;
    GOTO[{0, 'F'}] = 3;
    GOTO[{4, 'E'}] = 8;
    GOTO[{4, 'T'}] = 2;
    GOTO[{4, 'F'}] = 3;
    GOTO[{6, 'T'}] = 9;
    GOTO[{6, 'F'}] = 3;
    GOTO[{7, 'F'}] = 10;
}

void printStack(stack<int> states, stack<char> symbols) {
    vector<int> stateList;
    vector<char> symList;
    while (!states.empty()) {
        stateList.push_back(states.top());
        states.pop();
    }
    while (!symbols.empty()) {
        symList.push_back(symbols.top());
        symbols.pop();
    }
    for (int i = stateList.size() - 1; i >= 0; --i) {
        cout << stateList[i];
        if (i < symList.size()) cout << symList[i];
        else cout << " ";
    }
    cout << setw(16 - stateList.size() * 2);
}

void parse(string input) {
    input += '$';
    stack<int> states;
    stack<char> symbols;
    states.push(0);
    int ip = 0;

    cout << left;
    cout << "\nStep\tStack\t\tInput\t\tAction\n";
    cout << "--------------------------------------------------------\n";

    int step = 1;

    while (true) {
        int state = states.top();
        char a = input[ip];

        auto act = ACTION.find({state, a});
        cout << step++ << "\t";
        printStack(states, symbols);
        cout << input.substr(ip) << "\t\t";

        if (act == ACTION.end()) {
            cout << "ERROR No action for (" << state << ", " << a << ")\n";
            return;
        }

        string action = act->second.type;
        if (action == "acc") {
            cout << "ACCEPTED\n";
            return;
        }

        if (action[0] == 's') {
            int nextState = stoi(action.substr(1));
            cout << "Shift " << a << ", push state " << nextState << "\n";
            symbols.push(a);
            states.push(nextState);
            ip++;
        } else if (action[0] == 'r') {
            int prodIndex = stoi(action.substr(1));
            string rhs = productions[prodIndex].rhs;
            char lhs = productions[prodIndex].lhs;
            cout << "Reduce using " << lhs << " --> " << rhs << "\n";

            for (int i = 0; i < rhs.size(); i++) {
                symbols.pop();
                states.pop();
            }

            symbols.push(lhs);
            int gotoState = GOTO[{states.top(), lhs}];
            states.push(gotoState);
        } else {
            cout << "ERROR Invalid action code: " << action << "\n";
            return;
        }
    }
}
int main() {
    setupTables();
    string input;
    cout << "Enter input string (e.g., i+i*i): ";
    cin >> input;
    parse(input);
    return 0;
}