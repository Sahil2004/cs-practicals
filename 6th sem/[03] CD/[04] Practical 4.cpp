#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
using namespace std;

struct TokenType {
    string token;
    string pattern;
    string category;
};

vector<TokenType> tokenTypes = {
    {"int", "\\bint\\b", "Keyword"}, {"float", "\\bfloat\\b", "Keyword"},
    {"char", "\\bchar\\b", "Keyword"}, {"if", "\\bif\\b", "Keyword"},
    {"else", "\\belse\\b", "Keyword"}, {"while", "\\bwhile\\b", "Keyword"},
    {"return", "\\breturn\\b", "Keyword"}, {"void", "\\bvoid\\b", "Keyword"},
    {"Constant", "\\b\\d+(\\.\\d+)?\\b", "Constant"},
    {"<", "<", "Relational Operator"}, {"<=", "<=", "Relational Operator"},
    {"==", "==", "Relational Operator"}, {">", ">", "Relational Operator"},
    {">=", ">=", "Relational Operator"}, {"!=", "!=", "Relational Operator"},
    {"=", "=", "Assignment Operator"},
    {"+", "\\+", "Addition Operator"}, {"-", "-", "Subtraction Operator"},
    {"*", "\\*", "Multiplication Operator"}, {"/", "/", "Division Operator"}
};

struct SymbolEntry {
    int address;
    string var_type;
    string value_type;
    string value;
};

struct TokenStats {
    int Total = 0;
    int Constant = 0;
    int Identifier = 0;
    int Operator = 0;
    int Keyword = 0;
};

void tokenize(const string& code, vector<pair<string, string>>& tokens, map<string, SymbolEntry>& symbolTable, TokenStats& stats) {
    regex wordRegex("\\b\\w+\\b|[<>]=?|!=|==|[=+\\-*/]");
    auto words_begin = sregex_iterator(code.begin(), code.end(), wordRegex);
    auto words_end = sregex_iterator();

    int address = 1000;

    for (auto i = words_begin; i != words_end; ++i) {
        string word = i->str();
        string token_category = "Identifier";
        string token_type = "Identifier";

        for (const auto& token : tokenTypes) {
            if (regex_match(word, regex(token.pattern))) {
                token_category = token.category;
                token_type = token.token;
                break;
            }
        }

        tokens.push_back({word, token_category});
        stats.Total++;

        if (token_category == "Constant") {
            string value_type = regex_match(word, regex("\\d+")) ? "int" : "real";
            if (symbolTable.find(word) == symbolTable.end()) {
                symbolTable[word] = {address, "constant", value_type, "value=" + word};
            }
            stats.Constant++;
        } else if (token_category == "Identifier") {
            if (symbolTable.find(word) == symbolTable.end()) {
                symbolTable[word] = {address, "variable", "real", "value=" + word};
            }
            stats.Identifier++;
        } else if (token_category.find("Operator") != string::npos) {
            stats.Operator++;
        } else if (token_category == "Keyword") {
            if (symbolTable.find(word) == symbolTable.end()) {
                symbolTable[word] = {address, "keyword", "N/A", "value=" + word};
            }
            stats.Keyword++;
        }

        address += 20;
    }
}

int main() {
    string choice;
    cout << "Enter '1' for console input or '2' for file input: ";
    cin >> choice;
    cin.ignore();

    string code;
    if (choice == "1") {
        cout << "Enter the code (end with an empty line):\n";
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            code += line + "\n";
        }
    } else if (choice == "2") {
        string file_path;
        cout << "Enter the file path: ";
        getline(cin, file_path);
        ifstream file(file_path);
        if (!file.is_open()) {
            cout << "File not found.\n";
            return 0;
        }
        string line;
        while (getline(file, line)) {
            code += line + "\n";
        }
        file.close();
    } else {
        cout << "Invalid choice.\n";
        return 0;
    }

    vector<pair<string, string>> tokens;
    map<string, SymbolEntry> symbolTable;
    TokenStats stats;

    tokenize(code, tokens, symbolTable, stats);

    cout << "\nS. No. | Lexime    | Token\n";
    cout << "------------------------------\n";
    for (size_t i = 0; i < tokens.size(); ++i) {
        cout << i + 1 << "      | " << tokens[i].first << "        | " << tokens[i].second << "\n";
    }

    cout << "\nTotal Tokens: " << stats.Total << "\n";
    cout << "Total Constants: " << stats.Constant << "\n";
    cout << "Total Identifiers: " << stats.Identifier << "\n";
    cout << "Total Operators: " << stats.Operator << "\n";
    cout << "Total Keywords: " << stats.Keyword << "\n";

    cout << "\nSymbol Table:\n";
    cout << "Address | Type     | Value Type | Value\n";
    cout << "---------------------------------------------\n";
    for (const auto& [lexeme, entry] : symbolTable) {
        cout << entry.address << "     | " << entry.var_type << "   | " << entry.value_type << "     | " << entry.value << "\n";
    }

    return 0;
}