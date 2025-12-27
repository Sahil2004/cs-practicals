#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

char terminalsArray[100] = {};
int nonTerminal_flag;

char non_terminalsArray[100] = {};
int no_nonTerminal;
char goto_tableArray[100][100];
char reduceArray[20][20];

char followCalculate[20][20];
char follow_count[20][20];
char firstCalculate[20][20];

struct stateStruct
{
    int prodCount;

    char prodArray[100][100] = {{}};
};

void add_dots(struct stateStruct *I) // augumentFed grammar

{

    for (int i = 0; i < I->prodCount; i++)
    {
        for (int j = 99; j > 3; j--)
            I->prodArray[i][j] = I->prodArray[i][j - 1];

        I->prodArray[i][3] = '.';
    }
}

void augumentF(struct stateStruct *S, struct stateStruct *I)
{
    if (I->prodArray[0][0] == 'S')
        strcpy(S->prodArray[0], "Z->.S");
    else
    {
        strcpy(S->prodArray[0], "S->.");

        S->prodArray[0][4] = I->prodArray[0][0];
    }

    S->prodCount++;
}

void get_prodsF(struct stateStruct *I) // user input

{

    cout << "SLR PARSING TABLE" << endl;

    cout << endl
         << "Directions: \n 1. Terminals must be single lettered. \n 2. Each production rule must contain only 1 rule.\n 3. The format of the prodcution rule is: S-> ABc " << endl;

    cout
        << endl
        << "Enter total no. of productions: ";
    cin >> I->prodCount;
    cout << endl
         << "Enter no. of non terminals: ";
    cin >> no_nonTerminal;
    cout << endl
         << "Enter non terminals: ";
    for (int i = 0; i < no_nonTerminal; i++)
        cin >> non_terminalsArray[i];
    cout << endl
         << "Enter no. of terminals: ";
    cin >> nonTerminal_flag;
    cout << endl
         << "Enter terminals: ";

    for (int i = 0; i < nonTerminal_flag; i++)
        cin >> terminalsArray[i];
    cout << endl
         << "Enter the production rules: ";
    for (int i = 0; i < I->prodCount; i++)
    {
        cin >> I->prodArray[i];
        cout << endl;
    }
}

bool is_nonTerminalF(char a)
{
    if (a >= 'A' && a <= 'Z')
        return true;
    else
        return false;
}

bool in_stateStruct(struct stateStruct *I, char *a)
{
    for (int i = 0; i < I->prodCount; i++)
    {
        if (!strcmp(I->prodArray[i], a))
            return true;
    }
    return false;
}

char char_after_dot(char a[100])
{
    char b;
    for (int i = 0; i < strlen(a);
         i++)

        if (a[i] == '.')
        {

            b = a[i + 1];
            return b;
        }
    return b;
}

// char *move_dot(char b[100], int len)
// {
//     char a[100] = {};
//     strcpy(a, b);

//     for (int i = 0; i < len; i++)
//     {
//         if (a[i] == '.')
//         {
//             swap(a[i], a[i + 1]);
//             break;
//         }
//     }

//     return &a[0];
// }

char* move_dot(char b[100], int len) {
    static char a[100];
    strcpy(a, b);
    for (int i = 0; i < len; i++) {
        if (a[i] == '.') {
            swap(a[i], a[i + 1]);
            break;
        }
    }
    return a;
}

bool same_stateStruct(struct stateStruct *I0, struct stateStruct *I)
{
    if (I0->prodCount != I->prodCount)
        return false;

    for (int i = 0; i < I0->prodCount; i++)

    {

        int flag = 0;

        for (int j = 0; j < I->prodCount; j++)

            if (strcmp(I0->prodArray[i], I->prodArray[j]) == 0)
                flag = 1;

        if (flag == 0)
            return false;
    }

    return true;
}

void closure(struct stateStruct *I, struct stateStruct *I0)
{
    char a = {};
    for (int i = 0; i < I0->prodCount; i++)
    {
        a = char_after_dot(I0->prodArray[i]);
        if (is_nonTerminalF(a))
        {
            for (int j = 0; j < I->prodCount; j++)
            {
                if (I->prodArray[j][0] == a)
                {
                    if (!in_stateStruct(I0, I->prodArray[j]))
                    {

                        strcpy(I0->prodArray[I0->prodCount], I->prodArray[j]);
                        I0->prodCount++;
                    }
                }
            }
        }
    }
}

void goto_stateStruct(struct stateStruct *I, struct stateStruct *S, char a)
{
    int time = 1;
    for (int i = 0; i < I->prodCount; i++)
    {

        if (char_after_dot(I->prodArray[i]) == a)
        {
            if (time == 1)
            {
                time++;
            }

            strcpy(S->prodArray[S->prodCount], move_dot(I->prodArray[i], strlen(I->prodArray[i])));
            S->prodCount++;
        }
    }
}

void print_prods(struct stateStruct *I)
{
    for (int i = 0; i < I->prodCount; i++)
        printf("%s\n", I->prodArray[i]);
    cout << endl;
}

bool in_array(char a[20], char b)
{
    for (int i = 0; i < strlen(a); i++)
        if (a[i] == b)
            return true;
    return false;
}

// char *chars_after_dots(struct stateStruct *I)
// {
//     char a[20] = {};
//     for (int i = 0; i < I->prodCount; i++)
//     {
//         if (!in_array(a, char_after_dot(I->prodArray[i])))
//         {

//             a[strlen(a)] = char_after_dot(I->prodArray[i]);
//         }
//     }

//     return &a[0];
// }

char chars_after_dot(char a[100]) {
    for (int i = 0; i < strlen(a); i++)
        if (a[i] == '.')
            return a[i + 1];
    return '\0';  // safe return
}

void cleanup_prods(struct stateStruct *I)
{
    char a[100] = {};
    for (int i = 0; i < I->prodCount; i++)
        strcpy(I->prodArray[i], a);
    I->prodCount = 0;
}

int return_index(char a)
{
    for (int i = 0; i < nonTerminal_flag; i++)
        if (terminalsArray[i] == a)
            return i;
    for (int i = 0; i < no_nonTerminal; i++)
        if (non_terminalsArray[i] == a)
            return nonTerminal_flag + i;
    return -1;
}

void print_shift_table(int stateStruct_count)
{
    cout << endl
         << "SHIFT ACTIONS" << endl
         << endl;
    cout << "\t";
    for (int i = 0; i < nonTerminal_flag; i++)
        cout << terminalsArray[i] << "\t";

    for (int i = 0; i < no_nonTerminal; i++)
        cout << non_terminalsArray[i] << "\t";
    cout << endl;

    for (int i = 0; i < stateStruct_count; i++)
    {
        int arr[no_nonTerminal + nonTerminal_flag];
        for (int idx = 0; idx < no_nonTerminal + nonTerminal_flag; idx++)
            arr[idx] = -1;
        for (int j = 0; j < stateStruct_count; j++)
        {
            if (goto_tableArray[i][j] != '~')
            {
                arr[return_index(goto_tableArray[i][j])] = j;
            }
        }

        cout << "I" << i << "\t";

        for (int j = 0; j < no_nonTerminal + nonTerminal_flag; j++)
        {
            if (i == 1 && j == nonTerminal_flag - 1)
                cout << "ACC"
                     << "\t";
            if (arr[j] == -1 || arr[j] == 0)
                cout << "\t";
            else
            {
                if (j < nonTerminal_flag)
                    cout << "S" << arr[j] << "\t";
                else
                    cout << arr[j] << "\t";
            }
        }

        cout << "\n";
    }
}

int get_index(char c, char *a)
{
    for (int i = 0; i < strlen(a); i++)
        if (a[i] == c)
            return i;
}

void add_dot_at_end(struct stateStruct *I)
{
    for (int i = 0; i < I->prodCount; i++)
    {
        strcat(I->prodArray[i], ".");
    }
}

void add_to_firstCalculate(int n, char b)
{
    for (int i = 0; i < strlen(firstCalculate[n]); i++)
        if (firstCalculate[n][i] == b)
            return;
    firstCalculate[n][strlen(firstCalculate[n])] = b;
}

void add_to_firstCalculate(int m, int n)
{
    for (int i = 0; i < strlen(firstCalculate[n]); i++)
    {
        int flag = 0;

        for (int j = 0; j < strlen(firstCalculate[m]); j++)
        {
            if (firstCalculate[n][i] == firstCalculate[m][j])
                flag = 1;
        }

        if (flag == 0)
            add_to_firstCalculate(m, firstCalculate[n][i]);
    }
}

void add_to_followCalculate(int n, char b)
{
    for (int i = 0; i < strlen(followCalculate[n]); i++)
        if (followCalculate[n][i] == b)
            return;
    followCalculate[n][strlen(followCalculate[n])] = b;
}

void add_to_followCalculate(int m, int n)
{
    for (int i = 0; i < strlen(followCalculate[n]); i++)
    {
        int flag = 0;

        for (int j = 0; j < strlen(followCalculate[m]); j++)
        {
            if (followCalculate[n][i] == followCalculate[m][j])
                flag = 1;
        }

        if (flag == 0)
            add_to_followCalculate(m, followCalculate[n][i]);
    }
}

void add_to_followCalculate_firstCalculate(int m, int n)
{
    for (int i = 0; i < strlen(firstCalculate[n]); i++)
    {

        int flag = 0;

        for (int j = 0; j < strlen(followCalculate[m]); j++)
        {
            if (firstCalculate[n][i] == followCalculate[m][j])
                flag = 1;
        }

        if (flag == 0)
            add_to_followCalculate(m, firstCalculate[n][i]);
    }
}

void find_firstCalculate(struct stateStruct *I)
{
    for (int i = 0; i < no_nonTerminal; i++)
    {
        for (int j = 0; j < I->prodCount; j++)
        {

            if (I->prodArray[j][0] == non_terminalsArray[i])
            {
                if (!is_nonTerminalF(I->prodArray[j][3]))
                {
                    add_to_firstCalculate(i, I->prodArray[j][3]);
                }
            }
        }
    }
}

void find_followCalculate(struct stateStruct *I)
{
    for (int i = 0; i < no_nonTerminal; i++)
    {
        for (int j = 0; j < I->prodCount; j++)
        {
            for (int k = 3; k < strlen(I->prodArray[j]); k++)
            {

                if (I->prodArray[j][k] == non_terminalsArray[i])
                {
                    if (I->prodArray[j][k + 1] != '\0')
                    {
                        if (!is_nonTerminalF(I->prodArray[j][k + 1]))
                        {
                            add_to_followCalculate(i, I->prodArray[j][k + 1]);
                        }
                    }
                }
            }
        }
    }
}

int get_index(int *arr, int n)
{
    for (int i = 0; i < nonTerminal_flag; i++)
    {
        if (arr[i] == n)
            return i;
    }

    return -1;
}

void print_reduceArray_table(int stateStruct_count, int *no_re, struct stateStruct *temp1)
{
    cout << "REDUCE ACTIONS" << endl
         << endl;
    cout << "\t";

    int arr[temp1->prodCount][nonTerminal_flag];
    memset(arr, -1, sizeof(arr));
    for (int i = 0; i < nonTerminal_flag; i++)
    {
        cout << terminalsArray[i] << "\t";
    }

    cout << endl;

    for (int i = 0; i < temp1->prodCount; i++)
    {
        int n = no_re[i];
        for (int j = 0; j < strlen(followCalculate[return_index(temp1->prodArray[i][0]) - nonTerminal_flag]); j++)
        {
            for (int k = 0; k < nonTerminal_flag; k++)
            {
                if (followCalculate[return_index(temp1->prodArray[i][0]) - nonTerminal_flag][j] == terminalsArray[k])
                    arr[i][k] = i + 1;
            }
        }

        cout << "I" << n << "\t";
        for (int j = 0; j < nonTerminal_flag; j++)
        {
            if (arr[i][j] != -1 && arr[i][j] != 0 && arr[i][j] < stateStruct_count)
                cout << "R" << arr[i][j] << "\t";
            else
                cout << "\t";
        }

        cout << endl;
    }
}

int main()
{

    struct stateStruct init;

    struct stateStruct temp;
    struct stateStruct temp1;
    int stateStruct_count = 1;

    get_prodsF(&init);
    temp = init;
    temp1 = temp;
    add_dots(&init);
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            goto_tableArray[i][j] = '~';
    struct stateStruct I[50];
    augumentF(&I[0], &init);
    closure(&init, &I[0]);
    cout << "\nI0:\n";
    print_prods(&I[0]);
    char characters[20] = {};
    for (int i = 0; i < stateStruct_count; i++)
    {
        char characters[20] = {};
        for (int z = 0; z < I[i].prodCount; z++)
            if (!in_array(characters, char_after_dot(I[i].prodArray[z])))
                characters[strlen(characters)] = char_after_dot(I[i].prodArray[z]);
        for (int j = 0; j < strlen(characters); j++)
        {
            goto_stateStruct(&I[i], &I[stateStruct_count], characters[j]);
            closure(&init, &I[stateStruct_count]);
            int flag = 0;

            for (int k = 0; k < stateStruct_count - 1; k++)
            {
                if (same_stateStruct(&I[k], &I[stateStruct_count]))
                {

                    cleanup_prods(&I[stateStruct_count]);
                    flag = 1;

                    cout << "I" << i << " on reading the symbol " << characters[j] << " goes to I" << k << ".\n";
                    goto_tableArray[i][k] = characters[j];
                    ;
                    break;
                }
            }

            if (flag == 0)
            {
                stateStruct_count++;
                cout << "I" << i << " on reading the symbol " << characters[j] << " goes to I" << stateStruct_count - 1 << ":\n";
                goto_tableArray[i][stateStruct_count - 1] = characters[j];
                print_prods(&I[stateStruct_count - 1]);
            }
        }
    }

    int no_re[temp.prodCount];
    for (int i = 0; i < temp.prodCount; ++i)
        no_re[i] = -1;
    terminalsArray[nonTerminal_flag] = '$';
    nonTerminal_flag++;
    add_dot_at_end(&temp1);
    for (int i = 0; i < stateStruct_count; i++)
    {
        for (int j = 0; j < I[i].prodCount; j++)
            for (int k = 0; k < temp1.prodCount; k++)
                if (in_stateStruct(&I[i], temp1.prodArray[k]))
                    no_re[k] = i;
    }

    find_firstCalculate(&temp);
    for (int l = 0; l < no_nonTerminal; l++)
    {
        for (int i = 0; i < temp.prodCount; i++)
        {
            if (is_nonTerminalF(temp.prodArray[i][3]))
            {
                add_to_firstCalculate(return_index(temp.prodArray[i][0]) - nonTerminal_flag, return_index(temp.prodArray[i][3]) - nonTerminal_flag);
            }
        }
    }

    find_followCalculate(&temp);
    add_to_followCalculate(0, '$');
    for (int l = 0; l < no_nonTerminal; l++)
    {
        for (int i = 0; i < temp.prodCount; i++)
        {
            for (int k = 3; k < strlen(temp.prodArray[i]); k++)
            {
                if (temp.prodArray[i][k] == non_terminalsArray[l])
                {
                    if (is_nonTerminalF(temp.prodArray[i][k + 1]))
                    {
                        add_to_followCalculate_firstCalculate(l, return_index(temp.prodArray[i][k + 1]) - nonTerminal_flag);
                    }
                    if (temp.prodArray[i][k + 1] == '\0')
                        add_to_followCalculate(l, return_index(temp.prodArray[i][0]) - nonTerminal_flag);
                }
            }
        }
    }

    print_shift_table(stateStruct_count);
    cout << endl
         << endl;
    print_reduceArray_table(stateStruct_count, &no_re[0], &temp1);

    cout << "The above two tables combined generate the SLR Parsing Table \n";
    cout << "*For error entries->cells where both shift and reduce actions are present";
    return 0;
}
