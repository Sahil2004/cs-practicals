#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

// Function to read input NFA
void input_nfa(int &nfa_states, vector<char> &input_symbols, map<pair<int, char>, set<int>> &nfa_transitions,
               set<int> &start_state, set<int> &final_states) {
    cout << "Enter number of NFA states: ";
    cin >> nfa_states;
    int symbols;
    cout << "Enter number of input symbols: ";
    cin >> symbols;

    cout << "Enter input symbols: " << endl;
    input_symbols.clear();
    for (int i = 0; i < symbols; ++i) {
        char sym;
        cin >> sym;
        input_symbols.push_back(sym);
    }

    int num_transitions;
    cout << "Enter number of transitions: ";
    cin >> num_transitions;
    cout << "Enter transitions (state input next_state):" << endl;
    cout << "(Use 'e' for epsilon transitions)" << endl;

    for (int i = 0; i < num_transitions; ++i) {
        int state, next_state;
        char inp;
        cin >> state >> inp >> next_state;
        nfa_transitions[make_pair(state, inp)].insert(next_state);
    }

    int start;
    cout << "Enter start state: ";
    cin >> start;
    start_state.insert(start);

    int final_count;
    cout << "Enter number of final states: ";
    cin >> final_count;
    cout << "Enter final states: " << endl;
    final_states.clear();
    for (int i = 0; i < final_count; ++i) {
        int fs;
        cin >> fs;
        final_states.insert(fs);
    }
}

// Helper function to find epsilon closure of a state
set<int> find_epsilon_closure(int state, map<pair<int, char>, set<int>> &nfa_transitions,
                             map<int, set<int>> &epsilon_closure) {
    if (epsilon_closure.find(state) != epsilon_closure.end()) {
        return epsilon_closure[state];
    }

    set<int> closure;
    queue<int> q;
    closure.insert(state);
    q.push(state);

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        auto key = make_pair(current, 'e');
        if (nfa_transitions.find(key) != nfa_transitions.end()) {
            for (int next_state : nfa_transitions[key]) {
                if (closure.find(next_state) == closure.end()) {
                    closure.insert(next_state);
                    q.push(next_state);
                }
            }
        }
    }

    epsilon_closure[state] = closure;
    return closure;
}

// Compute epsilon closures for all states
void compute_epsilon_closures(int nfa_states, map<pair<int, char>, set<int>> &nfa_transitions,
                              map<int, set<int>> &epsilon_closure) {
    for (int state = 0; state < nfa_states; ++state) {
        find_epsilon_closure(state, nfa_transitions, epsilon_closure);
    }
}

// Move function for a set of states and a symbol
set<int> move(const set<int> &states, char symbol, map<pair<int, char>, set<int>> &nfa_transitions,
              map<int, set<int>> &epsilon_closure) {
    set<int> result;
    for (int state : states) {
        auto key = make_pair(state, symbol);
        if (nfa_transitions.find(key) != nfa_transitions.end()) {
            for (int next_state : nfa_transitions[key]) {
                set<int> closure = find_epsilon_closure(next_state, nfa_transitions, epsilon_closure);
                result.insert(closure.begin(), closure.end());
            }
        }
    }
    return result;
}

// Convert NFA to DFA
void convert_to_dfa(int nfa_states, vector<char> &input_symbols, map<pair<int, char>, set<int>> &nfa_transitions,
                    set<int> &start_state, set<int> &final_states,
                    map<set<int>, int> &dfa_state_mapping,
                    map<set<int>, map<char, set<int>>> &dfa_transitions,
                    set<set<int>> &dfa_final_states) {
    map<int, set<int>> epsilon_closure;
    compute_epsilon_closures(nfa_states, nfa_transitions, epsilon_closure);

    // Start closure
    int start_single = *start_state.begin();
    set<int> start_closure = find_epsilon_closure(start_single, nfa_transitions, epsilon_closure);

    queue<set<int>> state_queue;
    state_queue.push(start_closure);
    dfa_state_mapping[start_closure] = 0;
    int dfa_state_count = 0;

    while (!state_queue.empty()) {
        set<int> current_state = state_queue.front();
        state_queue.pop();

        dfa_transitions[current_state] = map<char, set<int>>();

        for (char symbol : input_symbols) {
            set<int> new_state = move(current_state, symbol, nfa_transitions, epsilon_closure);
            if (!new_state.empty()) {
                if (dfa_state_mapping.find(new_state) == dfa_state_mapping.end()) {
                    dfa_state_count++;
                    dfa_state_mapping[new_state] = dfa_state_count;
                    state_queue.push(new_state);
                }
                dfa_transitions[current_state][symbol] = new_state;
            } else {
                dfa_transitions[current_state][symbol] = set<int>(); // empty set means no transition
            }
        }
    }

    for (const auto &pair : dfa_state_mapping) {
        const set<int> &state_set = pair.first;
        bool is_final = false;
        for (int s : state_set) {
            if (final_states.find(s) != final_states.end()) {
                is_final = true;
                break;
            }
        }
        if (is_final) {
            dfa_final_states.insert(state_set);
        }
    }
}

// Print DFA transition table
void print_dfa_transition_table(map<set<int>, map<char, set<int>>> &dfa_transitions,
                                map<set<int>, int> &dfa_state_mapping,
                                set<set<int>> &dfa_final_states,
                                vector<char> &input_symbols) {
    cout << "\nDFA Transition Table:" << endl;
    cout << "State\t";
    for (char sym : input_symbols) {
        cout << sym << "\t";
    }
    cout << "Final" << endl;

    for (const auto &pair : dfa_state_mapping) {
        const set<int> &state_set = pair.first;
        int state_id = pair.second;

        // State representation
        cout << "Q" << state_id << " (";
        bool first = true;
        for (int s : state_set) {
            if (!first) cout << " ";
            cout << s;
            first = false;
        }
        cout << ")\t";

        for (char sym : input_symbols) {
            auto it = dfa_transitions.find(state_set);
            if (it != dfa_transitions.end()) {
                auto sym_it = it->second.find(sym);
                if (sym_it != it->second.end() && !sym_it->second.empty()) {
                    int next_id = dfa_state_mapping[sym_it->second];
                    cout << "Q" << next_id << "\t";
                } else {
                    cout << "{}\t";
                }
            } else {
                cout << "{}\t";
            }
        }

        cout << (dfa_final_states.find(state_set) != dfa_final_states.end() ? "Yes" : "No") << endl;
    }
}

int main() {
    int nfa_states;
    vector<char> input_symbols;
    map<pair<int, char>, set<int>> nfa_transitions;
    set<int> start_state;
    set<int> final_states;

    input_nfa(nfa_states, input_symbols, nfa_transitions, start_state, final_states);

    map<set<int>, int> dfa_state_mapping;
    map<set<int>, map<char, set<int>>> dfa_transitions;
    set<set<int>> dfa_final_states;

    convert_to_dfa(nfa_states, input_symbols, nfa_transitions, start_state, final_states,
                   dfa_state_mapping, dfa_transitions, dfa_final_states);

    print_dfa_transition_table(dfa_transitions, dfa_state_mapping, dfa_final_states, input_symbols);

    return 0;
}