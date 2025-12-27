#include <iostream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

pair<map<string, map<char, string>>, string> construct_dfa(const string& pattern, const string& mode) {
    int num_of_states = pattern.length() + 1;
    set<char> symbol_set(pattern.begin(), pattern.end());
    vector<char> inp_symbols(symbol_set.begin(), symbol_set.end());

    map<string, map<char, string>> transition_table;
    for (int i = 0; i < num_of_states; ++i) {
        string state = "q" + to_string(i);
        for (char symbol : inp_symbols) {
            transition_table[state][symbol] = "q0";
        }
    }

    if (mode == "suffix" || mode == "prefix" || mode == "substring") {
        for (int i = 0; i < pattern.length(); ++i) {
            transition_table["q" + to_string(i)][pattern[i]] = "q" + to_string(i + 1);
        }

        if (mode == "prefix") {
            for (int state = 0; state < num_of_states - 1; ++state) {
                for (char symbol : inp_symbols) {
                    if (symbol != pattern[state]) {
                        transition_table["q" + to_string(state)][symbol] = "q" + to_string(num_of_states - 1);
                    }
                }
            }
        }
    }

    string final_state = "q" + to_string(pattern.length());
    return {transition_table, final_state};
}

bool process_string(const map<string, map<char, string>>& dfa, const string& final_state, const string& test_string) {
    string curr_state = "q0";
    for (char ch : test_string) {
        if (dfa.at(curr_state).count(ch)) {
            curr_state = dfa.at(curr_state).at(ch);
        } else {
            curr_state = "q0";
        }
    }
    return curr_state == final_state;
}

int main() {
    while (true) {
        cout << "\nDFA Constructor" << endl;
        cout << "1. DFA with Suffix String" << endl;
        cout << "2. DFA with Prefix String" << endl;
        cout << "3. DFA with Substring" << endl;
        cout << "4. Exit" << endl;
        cout << "Your Choice: ";
        string choice;
        cin >> choice;

        if (choice == "4") {
            return 0;
        }

        cout << "Enter the pattern string: ";
        string pattern;
        cin >> pattern;

        string mode = (choice == "1") ? "suffix" : (choice == "2") ? "prefix" : "substring";
        auto [dfa, final_state] = construct_dfa(pattern, mode);

        cout << "\nTransition Table:\nState\t";
        for (const auto& pair : dfa.at("q0")) {
            cout << pair.first << "\t";
        }
        cout << "\n--------------------------------------\n";
        for (const auto& [state, transitions] : dfa) {
            string state_marker = (state == "q0") ? "->" : (state == final_state) ? "* " : "  ";
            cout << state_marker << state << "\t";
            for (const auto& [symbol, target_state] : transitions) {
                cout << target_state << "\t";
            }
            cout << endl;
        }

        cout << "\n'->' represents initial state and '*' represents final state.\n";

        while (true) {
            cout << "\nDo you want to process a string? (y/n): ";
            string ans;
            cin >> ans;
            if (ans != "y" && ans != "Y") break;

            cout << "Enter the string to be recognized: ";
            string test_string;
            cin >> test_string;

            if (process_string(dfa, final_state, test_string)) {
                cout << "The string is accepted.\n";
            } else {
                cout << "The string is not accepted.\n";
            }
        }
    }

    return 0;
}
