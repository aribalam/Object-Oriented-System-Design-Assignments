#include<bits/stdc++.h>

using namespace std;

typedef struct point {
    int x, y;
} point;

point p0;

double distSq(point a, point b) {
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}

int crossProduct(point a, point b, point c) {
    int val = (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
    if (val == 0)
        return 0;
    return val > 0 ? 1 : -1;
}

bool comparePolarAngle(point p, point q) {
    int val = crossProduct(p, p0, q);
    if (val == 0)
        return distSq(p, p0) > distSq(q, p0)? true : false;
    return val < 0? true : false;
}

int main() {

    int n;
    cin >> n;

    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    int min = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[min].y)
            min = i;
        else if (points[i].y == points[min].y && points[i].x < points[min].x)
            min = i;
    }

    swap(points[0], points[min]);

    p0 = points[0];
    sort(points.begin()+1, points.end(), comparePolarAngle);
    
    stack<point> st;

    st.push(p0);
    st.push(points[1]);
    st.push(points[2]);
    for (int i = 3; i < n; i++) {
        point mid = st.top();
        st.pop();
        while (crossProduct(st.top(), mid, points[i]) <= 0) {
            mid = st.top();
            st.pop();
        }
        st.push(mid);
        st.push(points[i]);
    }

    while (!st.empty()) {
        point p = st.top();
        cout << "(" << p.x << ", " << p.y << ")";
        st.pop();
    }

}