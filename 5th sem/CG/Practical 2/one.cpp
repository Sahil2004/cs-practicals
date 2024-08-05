#include <graphics.h>
#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    float x, y;
};

bool isPointCloseToLine(const Point& p1, const Point& p2, const Point& userPoint) {
    float slope = (p2.y - p1.y) / (p2.x - p1.x);
    float intercept = p1.y - slope * p1.x;
    float lineY = slope * userPoint.x + intercept;
    return fabs(userPoint.y - lineY) < 1e-6;
}

bool isPointBelowLine(const Point& p1, const Point& p2, const Point& userPoint) {
    float slope = (p2.y - p1.y) / (p2.x - p1.x);
    float intercept = p1.y - slope * p1.x;
    float lineY = slope * userPoint.x + intercept;
    return userPoint.y > lineY;
}

int main() {
    Point p1, p2;
    cout << "Enter the coordinates of the first line point (x1 y1): ";
    cin >> p1.x >> p1.y;
    cout << "Enter the coordinates of the second line point (x2 y2): ";
    cin >> p2.x >> p2.y;

    int numPoints;
    cout << "How many points do you want to check? ";
    cin >> numPoints;

    int width = 800, height = 600;
    initwindow(width, height, "Line and Point Relation");
    setcolor(WHITE);
    line(p1.x, p1.y, p2.x, p2.y);

    for (int i = 0; i < numPoints; ++i) {
        Point userPoint;
        cout << "Enter the coordinates of point " << i + 1 << " (x y): ";
        cin >> userPoint.x >> userPoint.y;

        bool closeToLine = isPointCloseToLine(p1, p2, userPoint);
        bool belowLine = isPointBelowLine(p1, p2, userPoint);

        if (closeToLine) {
            setcolor(GREEN);
        } else if (belowLine) {
            setcolor(BLUE);
        } else {
            setcolor(RED);
        }

        fillellipse(userPoint.x, userPoint.y, 5, 5);
    }

    getch();
    closegraph();
    return 0;
}
