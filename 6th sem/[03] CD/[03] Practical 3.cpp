#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>
#include <sstream>
#include <tuple>
using namespace std;

vector<string> read_code() {
    string choice;
    cout << "Enter '1' to provide a filename or '2' to enter code manually: ";
    getline(cin, choice);

    vector<string> lines;
    if (choice == "1") {
        string filename;
        cout << "Enter the filename: ";
        getline(cin, filename);
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }
    } else if (choice == "2") {
        cout << "Enter your code below. Press Enter on an empty line to finish:\n";
        string line;
        while (true) {
            getline(cin, line);
            if (line.empty()) break;
            lines.push_back(line);
        }
    } else {
        cout << "Invalid choice. Please restart the program.\n";
        exit(0);
    }
    return lines;
}

tuple<vector<tuple<int, int, string>>, int, int> extract_comments(const vector<string>& lines) {
    regex single_line_pattern("//(.*)");
    bool in_multiline = false;
    vector<tuple<int, int, string>> comments;
    int single_count = 0, multi_count = 0;
    int start_line = -1;
    string multi_comment;

    for (size_t i = 0; i < lines.size(); ++i) {
        string line = lines[i];
        if (in_multiline) {
            multi_comment += line + "\n";
            if (line.find("*/") != string::npos) {
                in_multiline = false;
                comments.push_back(make_tuple(start_line, static_cast<int>(i + 1), multi_comment));
                multi_count++;
                multi_comment.clear();
            }
            continue;
        }

        size_t start = line.find("/*");
        if (start != string::npos) {
            start_line = i + 1;
            in_multiline = true;
            multi_comment = line + "\n";
            if (line.find("*/") != string::npos) {
                in_multiline = false;
                comments.push_back(make_tuple(start_line, static_cast<int>(i + 1), multi_comment));
                multi_count++;
                multi_comment.clear();
            }
            continue;
        }

        smatch match;
        if (regex_search(line, match, single_line_pattern)) {
            comments.push_back(make_tuple(static_cast<int>(i + 1), static_cast<int>(i + 1), match[1].str()));
            single_count++;
        }
    }
    return make_tuple(comments, single_count, multi_count);
}

void print_comments_table(const vector<tuple<int, int, string>>& comments, int single_count, int multi_count) {
    cout << "\nComment Table:\n";
    cout << "+------------+------------+----------------------------------------------+\n";
    cout << "| Start Line | End Line   | Comment                                      |\n";
    cout << "+------------+------------+----------------------------------------------+\n";

    for (size_t i = 0; i < comments.size(); ++i) {
        int start = get<0>(comments[i]);
        int end = get<1>(comments[i]);
        string comment = get<2>(comments[i]);
        istringstream iss(comment);
        string line;
        bool first = true;
        while (getline(iss, line)) {
            if (first) {
                cout << "| " << setw(10) << start << " | " << setw(10) << end << " | " << left << setw(45) << line.substr(0, 45) << " |\n";
                first = false;
            } else {
                cout << "| " << setw(10) << " " << " | " << setw(10) << " " << " | " << left << setw(45) << line.substr(0, 45) << " |\n";
            }
        }
    }

    cout << "+------------+------------+----------------------------------------------+\n";
    cout << "Total Single Line Comments: " << single_count << endl;
    cout << "Total Multi Line Comments: " << multi_count << endl;
}

int main() {
    vector<string> lines = read_code();
    auto result = extract_comments(lines);
    vector<tuple<int, int, string>> comments = get<0>(result);
    int single_count = get<1>(result);
    int multi_count = get<2>(result);
    print_comments_table(comments, single_count, multi_count);
    return 0;
}
