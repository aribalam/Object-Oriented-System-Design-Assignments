#include<bits/stdc++.h>

using namespace std;

typedef struct point {
    int x, y;
} point;

int crossProduct(vector<point> &points, int a, int b, int c) {
    int val = (points[a].x - points[b].x) * (points[c].y - points[b].y) - (points[a].y - points[b].y) * (points[c].x - points[b].x);
    if (val == 0)
        return 0;
    return val > 0 ? 1 : -1;
}

int main() {

    int n;
    cin >> n;

    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    int p = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[p].x)
            p = i;
    }

    int start = p;
    
    stack<point> st;

    int q;
    do {
        st.push(points[p]);

        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (crossProduct(points, p, i, q) > 0)
                q = i;
        }

        p = q;
    }
    while (p != start);

    cout << "The convex hull points are : " << endl;
    while (!st.empty()) {
        point pt = st.top();
        cout << "(" << pt.x << ", " << pt.y << ")" << endl;
        st.pop();
    } 
}