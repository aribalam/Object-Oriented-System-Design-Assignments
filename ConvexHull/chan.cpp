#include<bits/stdc++.h>
#include<fstream>

using namespace std;

typedef struct point {
    int x, y;
} point;

point p0;

// Finds the distance square between two points
double distSq(point a, point b) {
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}


// Cross Product between qp and qr
int crossProduct(point p, point q, point r) {
    int val = (p.x - q.x)*(r.y - q.y) - (p.y - q.y)*(r.x - q.x);
    if (val == 0)
        return 0;
    return val > 0? 1: -1;
}

// Comparison function wrt polar angle
bool comparePolarAngle(point p, point q) {
    int val = crossProduct(p, p0, q);
    if (val == 0)
        return distSq(p, p0) > distSq(q, p0)? true : false;
    return val < 0? true : false;
}

// Compare polar angle with given pivot
bool hashigherpolarAngle(point p, point q, point pivot) {
    int val = crossProduct(p, pivot, q);
    if (val == 0)
        return distSq(p, pivot) > distSq(q, pivot)? true : false;
    return val < 0? true : false;
}

point leftTangent(vector<point> points, point p) {

    int lo = 0, hi = points.size()-1;
    
    int first_after = crossProduct(p, points[1], points[0]);
    int first_before = crossProduct(p, points[points.size()-1], points[0]);

    if (first_after < 0 && first_before < 0)
        return points[0];

    while (lo <= hi) {

        int lo_before;
        if (lo == 0)
            lo_before = crossProduct(p, points[points.size()-1], points[lo]);
        else
            lo_before = crossProduct(p, points[lo-1], points[lo]);

        int lo_after = crossProduct(p, points[(lo+1) % points.size()], points[lo]);

        if (lo_after == 0 && lo_before == 0)
            return points[points.size()-1];
        if (!lo_after > 0 && !lo_before > 0)
            return points[lo];
        
        int mid = (lo + hi) / 2;

        int mid_before = crossProduct(p, points[mid-1], points[mid]);
        int mid_after = crossProduct(p, points[(mid+1) % points.size()], points[mid]);

        int lo_mid = crossProduct(p, points[lo], points[mid]);

        if (mid_after > 0) {
            
            if (lo_after <= 0)
                lo = mid + 1;
            else {

                if (lo_mid > 0)
                    hi = mid - 1;
                else
                    lo = mid + 1;
            }
        
        }
        else if (mid_before > 0) {

            if (lo_after <= 0) {

                if (lo_mid >= 0)
                    lo = mid + 1;
                else
                    hi = mid - 1;

            }
            else
                hi = mid - 1;

        }
        else if (mid_after == 0 && mid_before == 0)
            return points[(mid-1) % points.size()];
        else
            return points[mid];
    }

    return points[lo];
}

// Graham Scan Algorithm to compute convex hull from a set of points
vector<point> grahamScan(vector<point> &points) {
    
    int min = 0;
    for (int i = 1; i < points.size(); i++) {
        if (points[i].y < points[min].y)
            min = i;
        else if (points[i].y == points[min].y && points[i].x < points[min].x)
            min = i;
    }

    swap(points[0], points[min]);

    p0 = points[0];
    sort(points.begin()+1, points.end(), comparePolarAngle);

    if (points.size() < 3)
        return points;

    stack<point> st;

    st.push(p0);
    st.push(points[1]);
    st.push(points[2]);

    for (int i = 3; i < points.size(); i++) {
        point mid = st.top();
        st.pop();
        
        while (crossProduct(st.top(), mid, points[i]) <= 0) {
            int cross = crossProduct(st.top(), mid, points[i]);
            mid = st.top();
            st.pop(); 
        }
        st.push(mid);
        st.push(points[i]);
    }

    vector<point> vec;
    while (!st.empty()) {
        vec.push_back(st.top());
        st.pop();
    }

    return vec;
}

stack<point> chan(vector<point> a, int n) {

    for (int t = 0; t < a.size(); t++) {
        
        for (int m = 2; m < pow(2, pow(2, t)); m++) {
            
            int partitions = ceil(((double)n) / m);

            vector<point> P[partitions];
            int offset = 0;
            for (int i = 0; i < partitions; i++) {
                P[i].assign(a.begin() + offset, a.begin() + min(offset + m, n));
                offset += m;
            }

            point minPoint = a[0];
            for (int i = 0; i < n; i++) {
                if (a[i].y < minPoint.y)
                    minPoint = a[i];
                else if (a[i].x < minPoint.x)
                    minPoint = a[i];
            }

            vector<point> hulls[partitions];
            // run graham scan in each of the partitions
            for (int i = 0; i < partitions; i++) {
                hulls[i] = grahamScan(P[i]);
            }

            stack<point> st;

            point p = minPoint;

            for (int i = 0; i < m; i++) {

                st.push(p);

                point leftMostPoint = leftTangent(hulls[0], p);

                for (int j = 1; j < partitions; j++) {
                    point q = leftTangent(hulls[j], p);
                    if (hashigherpolarAngle(q, leftMostPoint, p))
                        leftMostPoint = q;
                }

                p = leftMostPoint;

                if (p.x == minPoint.x && p.y == minPoint.y)
                    return st;
            }          
        }
    }
}

int main() {

    ifstream infile;
    infile.open("input.txt");

    vector<point> a;
    int x, y;
    while (infile >> x >> y) {
        point p;
        p.x = x;
        p.y = y;
        a.push_back(p);
    }
    infile.close();

    int n = a.size();
    // int m = 5;
    // int partitions = ceil(((double)n) / m);

    // cout << n << endl;
    // cout << m << endl;

    // point minPoint = a[0];
    // for (int i = 0; i < n; i++) {
    //     if (a[i].y < minPoint.y)
    //         minPoint = a[i];
    //     else if (a[i].x < minPoint.x)
    //         minPoint = a[i];
    // }

    // // partitioning the points into n/m parts
    // vector<point> P[partitions];
    // int offset = 0;
    // for (int i = 0; i < partitions; i++) {
    //     P[i].assign(a.begin() + offset, a.begin() + min(offset + m, n));
    //     offset += m;
    // }

    // vector<point> hulls[partitions];
    // // run graham scan in each of the partitions
    // for (int i = 0; i < partitions; i++) {
    //     hulls[i] = grahamScan(P[i]);
    // }

    // cout << "hulls computed" << endl;

    // stack<point> st;

    // point p = minPoint;

    // }
    // do {

    //     st.push(p);

    //     point leftMostPoint = leftTangent(hulls[0], p);

    //     for (int j = 1; j < partitions; j++) {
    //         point q = leftTangent(hulls[j], p);
    //         if (hashigherpolarAngle(q, leftMostPoint, p))
    //             leftMostPoint = q;
    //     }

    //     p = leftMostPoint;
    // }
    // while (p.x != minPoint.x || p.y != minPoint.y);

    ofstream outfile;
    outfile.open("output.txt");

    stack<point> st = chan(a, n);

    while (!st.empty()) {
        point pt = st.top();
        outfile << "(" << pt.x << ", " << pt.y << ")" << endl;
        st.pop();
    }
    outfile.close();

}