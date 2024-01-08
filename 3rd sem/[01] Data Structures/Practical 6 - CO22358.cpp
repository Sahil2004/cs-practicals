#include <iostream>
#include <cstring>
#define MAX_ARRAY_SIZE 10000
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

using namespace std;

void enterPara(char *para) {
    int i = 0;
    char ch;
    cin >> ch;
    while (ch != '\n') {
        para[i++] = ch;
        ch = cin.get();
    }
    para[i] = '\0';
}

int getSentencesLength(char *para) {
    int i = 0;
    int sentenceCount = 0;
    while (para[i] != '\0') {
        if (para[i] == '.') sentenceCount++;
        if (para[i + 1] == '\0' && para[i] != '.') sentenceCount++;
        i++;
    }
    return sentenceCount;
}

int getWordLength(char *para) {
    int i = 0, words = 0;
    while (para[i] != '\0') {
        if (para[i] == ' ' || (para[i] == '.' && para[i + 1] != ' ')) words++;
        if (para[i + 1] == '\0' && (para[i] != ' ' && para[i] != '.')) words++;
        i++;
    }
    return words;
}

int getCharLength(char *para) {
    int i = 0, chars = 0;
    while (para[i] != '\0') {
        chars++;
        i++;
    }
    return chars;
}

int searchPattern(char* text, char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);
    for (int i = 0; i <= textLength - patternLength; ++i) {
        int j;
        for (j = 0; j < patternLength; ++j) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == patternLength) {
            return i;
        }
    }
    return -1;
}

void getFreqOfWords(char* para) {
    int freq[256] = {0};
    for (int i = 0; para[i] != '\0'; i++) {
        freq[para[i]]++;
    }

    // printing the frequencies
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            cout << "The frequency of " << char(i) << " is " << freq[i] << endl;
        }
    }
}

int main() {
    int choice, index;
    char *para = new char[MAX_ARRAY_SIZE];
    char *query = new char[1000];
    while (true) {
        cout << "Menu:\n";
        cout << "1. Enter a paragraph\n";
        cout << "2. Count the number of sentences\n";
        cout << "3. Count the number of words\n";
        cout << "4. Count the number of characters\n";
        cout << "5: Search for a pattern or word\n";
        cout << "6. Get the frequency of each word\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                enterPara(para);
                break;
            case 2:
                cout << "Number of sentences: " << getSentencesLength(para) << endl;
                break;
            case 3:
                cout << "Number of words: " << getWordLength(para) << endl;
                break;
            case 4:
                cout << "Number of characters: " << getCharLength(para) << endl;
                break;
            case 5:
                cin >> query;
                index = searchPattern(para, query);
                if (index != -1) cout << "Pattern found at index: " << index << endl;
                else cout << "Pattern not found\n";
                break;
            case 6:
                getFreqOfWords(para);
                break;
            case 7:
                return 0;
            default:
                cout << "Entered choice is wrong. Please enter a correct choice to continue.\n";
                break;
        }
    }
    return 0;
}