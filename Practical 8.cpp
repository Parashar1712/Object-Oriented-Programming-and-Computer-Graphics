#include <graphics.h>
#include <iostream>
#include <algorithm>
using namespace std;

class PolygonShape {
protected:
    int n;
    int x[20];
    int y[20];

public:
    void readVertices() {
        cout << "Enter number of vertices: ";
        cin >> n;

        int i = 0;
        while (i < n) {
            cout << "Enter x and y for vertex " << (i + 1) << ": ";
            cin >> x[i] >> y[i];
            i = i + 1;
        }
        x[n] = x[0];
        y[n] = y[0];
    }
};

class ScanFill : public PolygonShape {
public:
    void fillPolygon() {
        int i = 0;
        while (i < n) {
            line(x[i], y[i], x[i + 1], y[i + 1]);
            i = i + 1;
        }

        int ymin = y[0];
        int ymax = y[0];

        i = 0;
        while (i < n) {
            if (y[i] < ymin) {
                ymin = y[i];
            }
            if (y[i] > ymax) {
                ymax = y[i];
            }
            i = i + 1;
        }

        int scan = ymin;
        while (scan <= ymax) {
            int interX[20];
            int count = 0;

            i = 0;
            while (i < n) {
                if ((y[i] <= scan && y[i + 1] > scan) || (y[i] > scan && y[i + 1] <= scan)) {
                    interX[count] = x[i] + (scan - y[i]) * (x[i + 1] - x[i]) / (y[i + 1] - y[i]);
                    count = count + 1;
                }
                i = i + 1;
            }

            sort(interX, interX + count);

            int k = 0;
            while (k < count) {
                setcolor(YELLOW);
                line(interX[k], scan, interX[k + 1], scan);
                k = k + 2;
            }

            scan = scan + 1;
        }
    }
};

int main() {
    ScanFill obj;
    obj.readVertices();

    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    obj.fillPolygon();

    getch();
    closegraph();
    return 0;
}
