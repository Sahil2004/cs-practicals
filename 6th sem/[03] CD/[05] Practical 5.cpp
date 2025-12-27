#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

struct Grammar {
    char p[10]; // LHS of production
    char prod[10]; // RHS of production
} g[10];

// Util function
bool is_terminal(char symbol) {
    return !(symbol >= 'A' && symbol <= 'Z') && symbol != '#';
}

// LEADING computation
void compute_leading(map<char, vector<string>>& grammar, map<char, set<char>>& leading) {
    stack<pair<char, char>> stk;
    for (auto& rule : grammar) {
        char nt = rule.first;
        for (string prod : rule.second) {
            if (!prod.empty()) {
                char first = prod[0];
                if (is_terminal(first)) {
                    if (leading[nt].insert(first).second) {
                        stk.push({nt, first});
                    }
                } else if (prod.length() > 1 && is_terminal(prod[1])) {
                    if (leading[nt].insert(prod[1]).second) {
                        stk.push({nt, prod[1]});
                    }
                }
            }
        }
    }

    while (!stk.empty()) {
        pair<char, char> top = stk.top(); stk.pop();
        char B = top.first;
        char a = top.second;
        for (auto& rule : grammar) {
            char A = rule.first;
            for (string prod : rule.second) {
                if (!prod.empty() && prod[0] == B) {
                    if (leading[A].insert(a).second) {
                        stk.push({A, a});
                    }
                }
            }
        }
    }
}

// TRAILING computation
void compute_trailing(map<char, vector<string>>& grammar, map<char, set<char>>& trailing) {
    stack<pair<char, char>> stk;
    for (auto& rule : grammar) {
        char nt = rule.first;
        for (string prod : rule.second) {
            if (!prod.empty()) {
                char last = prod.back();
                if (is_terminal(last)) {
                    if (trailing[nt].insert(last).second) {
                        stk.push({nt, last});
                    }
                } else if (prod.length() > 1 && is_terminal(prod[prod.length() - 2])) {
                    if (trailing[nt].insert(prod[prod.length() - 2]).second) {
                        stk.push({nt, prod[prod.length() - 2]});
                    }
                }
            }
        }
    }

    while (!stk.empty()) {
        pair<char, char> top = stk.top(); stk.pop();
        char B = top.first;
        char a = top.second;
        for (auto& rule : grammar) {
            char A = rule.first;
            for (string prod : rule.second) {
                if (!prod.empty() && prod.back() == B) {
                    if (trailing[A].insert(a).second) {
                        stk.push({A, a});
                    }
                }
            }
        }
    }
}

// Precedence table generation
void compute_precedence_table(map<char, vector<string>>& grammar,
                              map<char, set<char>>& leading,
                              map<char, set<char>>& trailing,
                              set<char>& terminals,
                              char start_symbol,
                              map<char, map<char, char>>& table) {

    for (char a : terminals) {
        for (char b : terminals) {
            table[a][b] = '.';
        }
        table[a]['$'] = '.';
        table['$'][a] = '.';
    }
    table['$']['$'] = '.';

    for (auto& rule : grammar) {
        for (string prod : rule.second) {
            for (size_t i = 0; i < prod.length() - 1; ++i) {
                char a = prod[i], b = prod[i + 1];
                if (is_terminal(a) && is_terminal(b)) {
                    table[a][b] = '=';
                }
                if (is_terminal(a) && !is_terminal(b)) {
                    for (char lead : leading[b]) {
                        table[a][lead] = '<';
                    }
                }
                if (!is_terminal(a) && is_terminal(b)) {
                    for (char trail : trailing[a]) {
                        table[trail][b] = '>';
                    }
                }
            }
        }
    }

    for (char a : leading[start_symbol]) {
        table['$'][a] = '<';
    }
    for (char a : trailing[start_symbol]) {
        table[a]['$'] = '>';
    }
}

void print_table(map<char, map<char, char>>& table, set<char>& terminals) {
    cout << "\nOperator Precedence Table:\n\t";
    for (char t : terminals) cout << t << "\t";
    cout << "$\n";
    for (char row : terminals) {
        cout << row << "\t";
        for (char col : terminals) {
            cout << table[row][col] << "\t";
        }
        cout << table[row]['$'] << "\n";
    }
    cout << "$\t";
    for (char col : terminals) {
        cout << table['$'][col] << "\t";
    }
    cout << table['$']['$'] << "\n";
}

// Operator Precedence Parsing Logic (with stack implementation)
void operator_precedence_parse(map<char, map<char, char>>& table, set<char>& terminals) {
    string input;
    cout << "\nEnter input string for operator precedence parser: ";
    cin >> input;
    input.push_back('$');

    stack<char> stk;
    stk.push('$');
    int i = 0;

    cout << "\n\nStack\tInput\tAction";
    while (true) {
        cout << "\n";
        // Print Stack
        stack<char> temp = stk;
        vector<char> print_stack;
        while (!temp.empty()) {
            print_stack.push_back(temp.top());
            temp.pop();
        }
        reverse(print_stack.begin(), print_stack.end());
        for (char c : print_stack) cout << c;
        cout << "\t";

        // Print Input
        for (int j = i; j < input.length(); ++j) cout << input[j];
        cout << "\t";

        char top = stk.top();
        char curr = input[i];

        if (top == '$' && curr == '$') {
            cout << "Accepted";
            break;
        }

        char relation = table[top][curr];

        if (relation == '<' || relation == '=') {
            cout << "Shift";
            stk.push(curr);
            i++;
        } else if (relation == '>') {
            cout << "Reduce";
            stk.pop();
        } else {
            cout << "Error!";
            break;
        }
    }
}

// Shift-Reduce Parsing Logic (with improved stack print)
void bottomUpParsing() {
    int i, stpos, k, l, m, r, np, tspos;
    char sc, ts[10];

    cout << "\nEnter total number of productions: ";
    cin >> np;

    cout << "\nEnter the set of productions (e.g., S->aS):\n";
    for (i = 0; i < np; i++) {
        cin >> ts;
        strncpy(g[i].p, ts, 1);
        strcpy(g[i].prod, &ts[3]);
    }

    char ip[20];
    cout << "\nEnter input string: ";
    cin >> ip;

    int lip = strlen(ip);
    char stack[40] = {'\0'};
    stpos = 0;
    i = 0;

    cout << "\n\nStack\tInput\tAction";
    do {
        r = 1;
        while (r != 0) {
            cout << "\n";
            for (int p = 0; p < stpos; p++) cout << stack[p];
            cout << "\t";
            for (int p = i; p < lip; p++) cout << ip[p];
            if (r == 2) cout << "\tReduced";
            else cout << "\tShifted";
            r = 0;

            for (k = 0; k < stpos; k++) {
                memset(ts, '\0', sizeof(ts));
                tspos = 0;
                for (l = k; l < stpos; l++) {
                    ts[tspos] = stack[l];
                    tspos++;
                }
                for (m = 0; m < np; m++) {
                    if (strcmp(ts, g[m].prod) == 0) {
                        for (l = k; l < stpos; l++) stack[l] = '\0';
                        stpos = k;
                        strcat(stack, g[m].p);
                        stpos++;
                        r = 2;
                    }
                }
            }
        }
        if (i < lip) {
            sc = ip[i];
            stack[stpos] = sc;
            i++;
            stpos++;
        }
    } while (strlen(stack) != 1 || i < lip);

    if (strlen(stack) == 1 && i == lip) cout << "\n\nString Accepted";
    else cout << "\n\nString Rejected";
}

int main() {
    map<char, vector<string>> grammar;
    set<char> terminals;
    map<char, set<char>> leading, trailing;
    map<char, map<char, char>> table;
    char choice;
    do {
        int task;
        cout << "\nChoose an option:\n";
        cout << "1. Operator Precedence Parser\n";
        cout << "2. Shift Reduce Parsing\n";
        cout << "Enter your choice: ";
        cin >> task;
        cin.ignore();

        switch (task) {
            case 1: {
                cout << "Enter grammar productions (e.g., E->E+T|T) and type 'end' to finish:\n";
                string input;
                grammar.clear();
                terminals.clear();
                table.clear();
                leading.clear();
                trailing.clear();

                while (true) {
                    getline(cin, input);
                    if (input == "end") break;
                    size_t arrow = input.find("->");
                    char lhs = input[0];
                    string rhs = input.substr(arrow + 2);
                    size_t pos = 0;
                    while ((pos = rhs.find('|')) != string::npos) {
                        grammar[lhs].push_back(rhs.substr(0, pos));
                        rhs.erase(0, pos + 1);
                    }
                    grammar[lhs].push_back(rhs);
                }

                char start_symbol = grammar.begin()->first;

                for (auto& rule : grammar) {
                    for (string prod : rule.second) {
                        for (char ch : prod) {
                            if (is_terminal(ch)) terminals.insert(ch);
                        }
                    }
                }

                compute_leading(grammar, leading);
                compute_trailing(grammar, trailing);

                cout << "\nLEADING sets:\n";
                for (auto& l : leading) {
                    cout << "LEADING(" << l.first << ") = { ";
                    for (char ch : l.second) cout << ch << " ";
                    cout << "}\n";
                }

                cout << "\nTRAILING sets:\n";
                for (auto& t : trailing) {
                    cout << "TRAILING(" << t.first << ") = { ";
                    for (char ch : t.second) cout << ch << " ";
                    cout << "}\n";
                }

                compute_precedence_table(grammar, leading, trailing, terminals, start_symbol, table);
                print_table(table, terminals);
                operator_precedence_parse(table, terminals);
                break;
            }
            case 2:
                bottomUpParsing();
                break;
            default:
                cout << "Invalid choice!";
        }
        cout << "\nDo you want to continue? (Y/N): ";
        cin >> choice;

    } while (choice == 'Y' || choice == 'y');
    return 0;
}