#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

map<char, vector<string>> productions;
map<char, set<char>> firstSet, followSet;
map<pair<char, char>, string> parseTable;
set<char> terminals, nonTerminals;
char startSymbol;

string input;
int pos = 0;

bool isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

void computeFirst(char symbol) {
    if (isTerminal(symbol)) {
        firstSet[symbol].insert(symbol);
        return;
    }

    for (string prod : productions[symbol]) {
        bool nullable = true;
        for (char c : prod) {
            if (c == '#') {
                firstSet[symbol].insert('#');
                nullable = false;
                break;
            }
            computeFirst(c);
            for (char x : firstSet[c]) {
                if (x != '#')
                    firstSet[symbol].insert(x);
            }
            if (firstSet[c].find('#') == firstSet[c].end()) {
                nullable = false;
                break;
            }
        }
        if (nullable)
            firstSet[symbol].insert('#');
    }
}

// ----------- FOLLOW computation -----------

void computeFollow() {
    followSet[startSymbol].insert('$');
    bool changed = true;

    while (changed) {
        changed = false;

        for (auto &rule : productions) {
            char A = rule.first;
            for (string prod : rule.second) {
                for (size_t i = 0; i < prod.size(); i++) {
                    char B = prod[i];
                    if (nonTerminals.count(B)) {
                        bool nullable = true;

                        // Lookahead beta = prod[i+1]
                        for (size_t j = i + 1; j < prod.size(); j++) {
                            char beta = prod[j];

                            if (isTerminal(beta)) {
                                // Direct terminal after B
                                if (followSet[B].insert(beta).second)
                                    changed = true;
                                nullable = false;
                                break;
                            } else {
                                // Non-terminal beta
                                for (char f : firstSet[beta]) {
                                    if (f != '#') {
                                        if (followSet[B].insert(f).second)
                                            changed = true;
                                    }
                                }
                                if (firstSet[beta].find('#') == firstSet[beta].end()) {
                                    nullable = false;
                                    break;
                                }
                            }
                        }

                        // If nullable beta or end of production, FOLLOW(A) → FOLLOW(B)
                        if (nullable) {
                            for (char f : followSet[A]) {
                                if (followSet[B].insert(f).second)
                                    changed = true;
                            }
                        }
                    }
                }
            }
        }
    }
}


// ----------- Parse Table -----------

void buildParseTable() {
    for (auto &rule : productions) {
        char A = rule.first;
        for (string prod : rule.second) {
            set<char> tempSet;
            if (prod == "#") {
                tempSet = followSet[A];
            } else {
                bool nullable = true;
                for (char c : prod) {
                    if (isTerminal(c)) {
                        tempSet.insert(c);
                        nullable = false;
                        break;
                    } else {
                        for (char f : firstSet[c]) {
                            if (f != '#') tempSet.insert(f);
                        }
                        if (firstSet[c].find('#') == firstSet[c].end()) {
                            nullable = false;
                            break;
                        }
                    }
                }
                if (nullable) {
                    for (char f : followSet[A])
                        tempSet.insert(f);
                }
            }
            for (char t : tempSet) {
                parseTable[{A, t}] = prod;
            }
        }
    }
}

// ----------- Predictive Parse -----------

void predictiveParse() {
    vector<char> stack;
    stack.push_back('$');
    stack.push_back(startSymbol);
    input += '$';
    pos = 0;

    cout << "\nParsing steps:\n";
    cout << left << setw(20) << "STACK" << setw(20) << "INPUT" << "ACTION" << endl;
    cout << string(50, '-') << endl;

    while (!stack.empty()) {
        // Show stack contents
        string stk;
        for (auto it = stack.rbegin(); it != stack.rend(); ++it) stk += *it;
        cout << left << setw(20) << stk << setw(20) << input.substr(pos);

        char top = stack.back();
        char curr = input[pos];

        if (top == curr && top == '$') {
            cout << "ACCEPTED" << endl;
            return;
        } else if (top == curr) {
            cout << "Match '" << curr << "'" << endl;
            stack.pop_back();
            pos++;
        } else if (isTerminal(top)) {
            cout << "REJECTED (Unexpected Terminal)" << endl;
            return;
        } else {
            auto it = parseTable.find({top, curr});
            if (it != parseTable.end()) {
                stack.pop_back();
                string prod = it->second;
                if (prod != "#") {
                    for (int i = prod.size() - 1; i >= 0; i--) {
                        stack.push_back(prod[i]);
                    }
                }
                cout << "Apply " << top << " -> " << prod << endl;
            } else {
                cout << "REJECTED (No production)" << endl;
                return;
            }
        }
    }
}

// ----------- Parse Table -----------

void buildTable() {
    for (auto &rule : productions) {
        char A = rule.first;
        for (string prod : rule.second) {
            set<char> tempSet;
            if (prod == "#") {
                tempSet = followSet[A];
            } else {
                bool nullable = true;
                for (char c : prod) {
                    if (isTerminal(c)) {
                        tempSet.insert(c);
                        nullable = false;
                        break;
                    } else {
                        for (char f : firstSet[c]) {
                            if (f != '#') tempSet.insert(f);
                        }
                        if (firstSet[c].find('#') == firstSet[c].end()) {
                            nullable = false;
                            break;
                        }
                    }
                }
                if (nullable) {
                    for (char f : followSet[A])
                        tempSet.insert(f);
                }
            }
            for (char t : tempSet) {
                parseTable[{A, t}] = prod;
            }
        }
    }
}

void printTable() {
    cout << "\nPredictive Parsing Table:\n";
    cout << setw(10) << "NT \\ T";
    for (char t : terminals) {
        cout << setw(10) << t;
    }
    cout << setw(10) << "$\n";
    cout << string(10 * (terminals.size() + 2), '-') << "\n";

    bool isLL1 = true;
    map<pair<char, char>, string> seen;
    for (char nt : nonTerminals) {
        cout << setw(10) << nt;
        for (char t : terminals) {
            string production = parseTable[{nt, t}];
            cout << setw(10) << (production.empty() ? "-" : production);
            if (!production.empty()) {
                if (!seen[{nt, t}].empty() && seen[{nt, t}] != production) {
                    isLL1 = false;
                    cout << " [Conflict: " << seen[{nt, t}] << " & " << production << "]";
                } else {
                    seen[{nt, t}] = production;
                }
            }
        }
        string production = parseTable[{nt, '$'}];
        cout << setw(10) << (production.empty() ? "-" : production) << "\n";
    }
    cout << (isLL1 ? "\nThe grammar is LL(1)\n" : "\nThe grammar is NOT LL(1)\n");
}


// ----------- Main -----------

int main() {
    cout << "Enter number of productions: ";
    int n;
    cin >> n;

    cout << "Enter productions (e.g. E->TE'): \n";
    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;
        char lhs = prod[0];
        if (i == 0) startSymbol = lhs; // first production is start symbol
        string rhs = prod.substr(3);
        productions[lhs].push_back(rhs);

        nonTerminals.insert(lhs);
        for (char c : rhs) {
            if (isTerminal(c) && c != '#')
                terminals.insert(c);
        }
    }

    for (char nt : nonTerminals) {
        computeFirst(nt);
    }

    computeFollow();

    cout << "\nFIRST sets:\n";
    for (char nt : nonTerminals) {
        cout << "FIRST(" << nt << "): { ";
        for (char c : firstSet[nt]) cout << c << " ";
        cout << "}\n";
    }

    cout << "\nFOLLOW sets:\n";
    for (char nt : nonTerminals) {
        cout << "FOLLOW(" << nt << "): { ";
        for (char c : followSet[nt]) cout << c << " ";
        cout << "}\n";
    }

    buildParseTable();

    cout << "\nEnter input string (use i for id, no spaces): ";
    cin >> input;
    predictiveParse();

    buildTable();
    printTable();

    return 0;
}
