#include <iostream>
#include <cstring>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

int tempVarCount = 1;
int labelCount = 100;

// Helper to generate a new temporary variable name
string newTemp() {
    return "t" + to_string(tempVarCount++);
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix
string infixToPostfix(string infix) {
    stack<char> opStack;
    string postfix = "";
    stringstream operand;

    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else {
            if (operand.str() != "") {
                postfix += operand.str();
                operand.str("");  // Clear the stringstream
            }
            if (c == '(') {
                opStack.push(c);
            } else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.pop(); // pop '('
            } else {
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                    postfix += opStack.top();
                    opStack.pop();
                }
                opStack.push(c);
            }
        }
    }

    if (operand.str() != "") {
        postfix += operand.str();  // Add any remaining operand
    }

    while (!opStack.empty()) {
        postfix += opStack.top();
        opStack.pop();
    }

    return postfix;
}

// Three Address Code for assignment
void handleAssignment(const string& expr) {
    size_t eqPos = expr.find('=');
    if (eqPos == string::npos || eqPos == 0 || eqPos == expr.size() - 1) {
        cout << "Invalid assignment expression\n";
        return;
    }

    string lhs = expr.substr(0, eqPos);
    string rhs = expr.substr(eqPos + 1);

    // Convert the right-hand side to postfix
    string postfixExpr = infixToPostfix(rhs);
    string t1 = newTemp();
    
    cout << t1 << " = " << postfixExpr << endl;
    cout << lhs << " = " << t1 << endl;
}

// Three Address Code for arithmetic expression only
void handleArithmetic(const string& expr) {
    string t1, t2;

    // Convert expression to postfix and generate TAC
    string postfixExpr = infixToPostfix(expr);
    t1 = newTemp();
    cout << t1 << " = " << postfixExpr << endl;
}

// Three Address Code for relational expression
void handleRelational(const string& id1, const string& op, const string& id2) {
    string trueLabel = to_string(labelCount + 3);
    cout << labelCount++ << "\tif " << id1 << " " << op << " " << id2 << " goto " << trueLabel << endl;
    cout << labelCount++ << "\tT := 0" << endl;
    cout << labelCount++ << "\tgoto " << labelCount + 1 << endl;
    cout << labelCount++ << "\tT := 1" << endl;
}

int main() {
    int choice;
    string expr, id1, id2, op;

    while (true) {
        cout << "1. Assignment Expression\n";
        cout << "2. Relational Expression\n";
        cout << "3. Arithmetic Expression\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter assignment expression (e.g., x=a+b): ";
            cin >> expr;
            handleAssignment(expr);
            break;

        case 2:
            cout << "Enter relational expression (e.g., a < b):\n";
            cin >> id1 >> op >> id2;
            if (op != "<" && op != ">" && op != "<=" && op != ">=" && op != "==" && op != "!=") {
                cout << "Invalid relational operator!\n";
            } else {
                handleRelational(id1, op, id2);
            }
            break;

        case 3:
            cout << "Enter arithmetic expression (e.g., a+b or a*b): ";
            cin >> expr;
            handleArithmetic(expr);
            break;

        case 4:
            return 0;

        default:
            cout << "Invalid choice\n";
        }
    }

    return 0;
}