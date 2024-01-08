#include <iostream>
#include <cstdio>
#include <string>
#include <malloc.h>

using namespace std;

struct sahil_NODE {
    int sahil_node_number;
    char sahil_name;
    sahil_NODE *sahil_next;
};

typedef sahil_NODE sahil_ND;

string getVerifString() {
    string str;
    char ch;
    fflush(stdin);
    cin.ignore();
    while (ch != '\n') {
        ch = getchar();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '.') {
            str.push_back(ch);
            fflush(stdin);
        }
    }
    return str;
}

char getVerifChar() {
    cout << "Input a character: ";
    char sahil_ch = getchar();
    if ((sahil_ch >= 'A' && sahil_ch <= 'Z') || (sahil_ch >= 'a' && sahil_ch <= 'z') || sahil_ch == '.') {
        return sahil_ch;
    }
    cout << "That was a wrong character.\n";
    return getVerifChar();
}

void insertCompleteName(sahil_ND *sahil_ptr) {
    if (sahil_ptr != NULL) {
        sahil_ND *sahil_prev;
        while (sahil_ptr != NULL) {
            sahil_prev = sahil_ptr;
            sahil_ptr = sahil_ptr->sahil_next;
            free(sahil_prev);
        }
    }
    sahil_ptr = (sahil_ND *)malloc(sizeof(sahil_ND));
    if (sahil_ptr == NULL) {
        cout << "No memory space left.\n";
        return;
    }
    sahil_ptr->sahil_next = NULL;
    char sahil_choice;
    cout << "Do you want to continue(y/n)?";
    cin >> sahil_choice;
    if (sahil_choice == 'n' || sahil_choice == 'N') {
        free(sahil_ptr);
        return;
    }
    string sahil_name = getVerifString();
    for (int i = 0; i < sahil_name.length(); i++) {
        sahil_ptr->sahil_name = sahil_name[i];
        sahil_ptr->sahil_node_number = i;
        sahil_ptr->sahil_next = (sahil_ND *)malloc(sizeof(sahil_ND));
        if (sahil_ptr->sahil_next == NULL) {
            cout << "No memory space left\n";
            return;
        }
        sahil_ptr->sahil_next->sahil_next = NULL;
        cout << "Do you want to continue(y/n)?";
        cin >> sahil_choice;
        if (sahil_choice == 'n' || sahil_choice == 'N') {
            free(sahil_ptr->sahil_next);
            return;
        }
        sahil_ptr = sahil_ptr->sahil_next;
    }
}

void insertCharAtEnd(sahil_ND *sahil_ptr) {
    char ch;
    cout << "Enter character to insert at last: ";
    ch = getVerifChar();
    if (sahil_ptr == NULL) {
        sahil_ptr = (sahil_ND *)malloc(sizeof(sahil_ND));
        if (sahil_ptr == NULL) {
            cout << "No space left on system";
            free(sahil_ptr);
            return;
        }
        sahil_ptr->sahil_next = NULL;
        sahil_ptr->sahil_name = ch;
        sahil_ptr->sahil_node_number = 0;
    } else {
        while (sahil_ptr->sahil_next != NULL) {
            sahil_ptr = sahil_ptr->sahil_next;
        }
        sahil_ptr->sahil_next = (sahil_ND *)malloc(sizeof(sahil_ND));
        if (sahil_ptr->sahil_next == NULL) {
            cout << "There is no more space on system.";
            free(sahil_ptr);
            return;
        }
        int lastNodeIndex = sahil_ptr->sahil_node_number;
        sahil_ptr = sahil_ptr->sahil_next;
        sahil_ptr->sahil_next = NULL;
        sahil_ptr->sahil_node_number = lastNodeIndex + 1;
        sahil_ptr->sahil_name = ch;
    }
    return;
}

void update(sahil_ND *sahil_ptr) {
    cout << "Enter a character which you want to replace: ";
    char sahil_query = getVerifChar();
    cout << "Enter a character with which you want to change it: ";
    char sahil_newChar = getVerifChar();
    if (sahil_ptr == NULL) {
        cout << "List is empty. Please fill the list before attempting to update it.";
        return;
    }
    while (sahil_ptr != NULL) {
        if (sahil_ptr->sahil_name == sahil_query) {
            sahil_ptr->sahil_name = sahil_newChar;
            cout << "Updated successfully.";
            return;
        }
        sahil_ptr = sahil_ptr->sahil_next;
    }
    cout << "No match was found.";
    return;
}

void search(sahil_ND *sahil_ptr) {
    if (sahil_ptr == NULL) {
        cout << "list is empty.";
        return;
    }
    cout << "For which character do you want to search for?\n";
    char sahil_query = getVerifChar();
    while (sahil_ptr != NULL) {
        if (sahil_ptr->sahil_name == sahil_query) {
            cout << "Query position: " << sahil_ptr->sahil_node_number;
            return;
        }
        sahil_ptr = sahil_ptr->sahil_next;
    }
    cout << "No match found.";
    return;
}

sahil_ND * deleteNode(sahil_ND *sahil_ptr) {
    if (sahil_ptr == NULL) {
        cout << "List is empty. Hence, nothing to delete.";
        return NULL;
    }
    cout << "Enter delete query: ";
    char sahil_query = getVerifChar();
    sahil_ND *sahil_start = sahil_ptr;
    sahil_ND *sahil_prev = sahil_ptr;
    sahil_ND *sahil_next;
    while (sahil_ptr != NULL) {
        if (sahil_ptr->sahil_name == sahil_query) {
            if (sahil_prev == sahil_ptr) {
                sahil_next = sahil_ptr->sahil_next;
                free(sahil_ptr);
                sahil_ptr = sahil_next;
                return sahil_ptr;
            }
            free(sahil_ptr);
            sahil_prev->sahil_next = sahil_ptr->sahil_next;
        }
        sahil_prev = sahil_ptr;
    }
    return sahil_start;
}

void display(sahil_ND *sahil_ptr) {
    string str;
    while(sahil_ptr != NULL) {
        str += sahil_ptr->sahil_name;
        sahil_ptr = sahil_ptr->sahil_next;
    }
    cout << "Name: " << str;
}

int main() {
    sahil_ND *sahil_start = NULL;

    int sahil_choice;
    while (true) {
        cout << "Here is the menu:\n";
        cout << "1. Insert your name or update your complete name\n"; // Sahil
        cout << "2. Insert a character at the end of your name\n";
        cout << "3. Update your name\n"; // updates a character in the name
        cout << "4. Search a character from your name\n";
        cout << "5. Delete a character from your name\n"; // Shaurya
        cout << "6. Display your name\n"; // Concatenates your name and displays // Samar
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> sahil_choice;
        switch (sahil_choice) {
            case 1:
                insertCompleteName(sahil_start);
                break;
            case 2:
                insertCharAtEnd(sahil_start);
                break;
            case 3:
                update(sahil_start);
                break;
            case 4:
                search(sahil_start);
                break;
            case 5:
                sahil_start = deleteNode(sahil_start);
                break;
            case 6:
                display(sahil_start);
                break;
            default:
                return 0;
        }
    }
    return 0;
}