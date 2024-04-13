#include <iostream>

using namespace std;

struct Activity {
    int start_time, finish_time;
};

void selectActivities(Activity activities[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (activities[j].finish_time > activities[j + 1].finish_time) {
                swap(activities[j], activities[j + 1]);
            }
        }
    }

    cout << "Selected activity: " << 0 << ", start_time: " << activities[0].start_time << ", finish_time: " << activities[0].finish_time << endl;

    int lastSelected = 0;

    for (int i = 1; i < n; i++) {
        if (activities[i].start_time >= activities[lastSelected].finish_time) {
            cout << "Selected activity: " << i << ", start_time: " << activities[i].start_time << ", finish_time: " << activities[i].finish_time << endl;
            lastSelected = i;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of activities: ";
    cin >> n;

    Activity activities[n];
    
    for (int i = 0; i < n; i++) {
        cout << "Enter start_time time for activity " << i + 1 << ": ";
        cin >> activities[i].start_time;
        cout << "Enter finish_time time for activity " << i + 1 << ": ";
        cin >> activities[i].finish_time;
    }

    selectActivities(activities, n);

    return 0;
}