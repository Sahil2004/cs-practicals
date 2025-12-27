#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class OperatorClass {
public:
    string l;  // Changed from char to string
    string r;
} original[10], optimized[10];

int main() {
    int n;
    cout << "Enter the Number of Expressions: ";
    cin >> n;

    // Input expressions
    for (int i = 0; i < n; i++) {
        cout << "Left: ";
        cin >> original[i].l;
        cout << "Right: ";
        cin >> original[i].r;
    }

    cout << "\n--- Intermediate Code ---\n";
    for (int i = 0; i < n; i++) {
        cout << original[i].l << " = " << original[i].r << endl;
    }

    // Dead Code Elimination
    int z = 0;
    for (int i = 0; i < n - 1; i++) {
        string target = original[i].l;
        bool used = false;
        for (int j = 0; j < n; j++) {
            if (original[j].r.find(target) != string::npos) {
                used = true;
                break;
            }
        }
        if (used) {
            optimized[z++] = original[i];
        }
    }
    // Always include last expression
    optimized[z++] = original[n - 1];

    cout << "\n--- After Dead Code Elimination ---\n";
    for (int i = 0; i < z; i++) {
        cout << optimized[i].l << " = " << optimized[i].r << endl;
    }

    // Common Subexpression Elimination
    for (int i = 0; i < z; i++) {
        for (int j = i + 1; j < z; j++) {
            if (optimized[i].r == optimized[j].r) {
                string oldVar = optimized[j].l;
                string newVar = optimized[i].l;
                optimized[j].l = newVar;
                for (int k = 0; k < z; k++) {
                    size_t pos;
                    while ((pos = optimized[k].r.find(oldVar)) != string::npos) {
                        optimized[k].r.replace(pos, oldVar.length(), newVar);
                    }
                }
            }
        }
    }

    cout << "\n--- Optimized Code ---\n";
    unordered_set<string> printed;
    for (int i = 0; i < z; i++) {
        if (!printed.count(optimized[i].l)) {
            cout << optimized[i].l << " = " << optimized[i].r << endl;
            printed.insert(optimized[i].l);
        }
    }

    return 0;
}
