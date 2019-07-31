/*
    K-D Tree implementation for two dimensional space
    Operation performed: 
        Querying points inside the rectangle
 */

#include<bits/stdc++.h>

using namespace std;

#define vp vector<pair<int, int>>

// counter to compute number of comparisons and assignments made during construction of k-d Tree
int crtree = 0;

// counter to compute number of comparisons and assignments made during querying of points inside a rectangle
int qpoint = 0;

class node {
    
    public:
    pair<int, int> p;
    node* left;
    node* right;

};

// Function to create a node and initialize its variables
node* createNode(pair<int, int> p) {
    
    node* newNode = new node();
    newNode->p = p;
    newNode->left = NULL;
    newNode->right = NULL;

    // assignments operation above
    crtree++;

    return newNode;
}

// Function to insert a new point to a k-d Tree (k = 2)
node* insert(node* x, pair<int, int> p, int depth) {
    if (x == NULL)
        return createNode(p);

    // no duplicate points allowed
    if (x->p.first == p.first && x->p.second == p.second)
        return x;
    
    if (depth % 2 == 0) {

        // the node point partitions the space by a vertical line
        // compare by x-coordinate
        
        if (p.first > x->p.first)
            x->right = insert(x->right, p, depth + 1);
        else
            x->left = insert(x->left, p, depth + 1);

    }
    else {

        // the node point partitions the space by a horizontal line
        // compare by y-coordinate

        if (p.second > x->p.second)
            x->right = insert(x->right, p, depth + 1);
        else
            x->left = insert(x->left, p, depth + 1);
    
    }

    // Exactly two comparisons takes place above
    crtree += 2;

    return x;

}

// Function to print the points of the k-d Tree
void inorder(node* x) {
    if (x == NULL)
        return;

    inorder(x->left);
    cout << x->p.first << ", " << x->p.second << endl;
    inorder(x->right);
}

// Checks if the point is inside the query rectangle
bool isInside(pair<int, int> p, pair<int, int> p1, pair<int, int> p2) {
    
    // ine comparison takes place below
    qpoint++;
    
    if ((p.first >= p1.first && p.first <= p2.first) && (p.second >= p2.second && p.second <= p1.second))
        return true;
    return false;
}

// Gets all the points of the k-d Tree which are inside the query rectangle
void getPoints(node* x, int depth, vp &points, pair<int, int> p1, pair<int, int> p2) {

    if (x == NULL)
        return;

    if (depth % 2 == 0) {

        // the node point partitions the space by a vertical line
        // compare by x-coordinate

        // move into its left node if the rectangle lies to the left of the partition
        if (p1.first <= x->p.first) {
            getPoints(x->left, depth + 1, points, p1, p2);
        }

        // add point to the vector if its inside the rectangle
        if (isInside(x->p, p1, p2)) {
            points.push_back(x->p);
        }

        // move into its right node if the rectangle lies to the right of the partition
        if (p2.first > x->p.first) {
            getPoints(x->right, depth + 1, points, p1, p2); 
        }

        // Exactly three comparisons takes place above
        qpoint += 3;
        
    }
    else {

        // the node point partitions the space by a horizontal line
        // compare by y-coordinate

        // move into its left node if the rectangle lies below the partition
        if (p2.second <= x->p.second) {
            getPoints(x->left, depth + 1, points, p1, p2);
        }

        // add point to the vector if its inside the rectangle
        if (isInside(x->p, p1, p2)) {
            points.push_back(x->p);
        }

        // move into its right node if the rectangle lies above the partition
        if (p1.second > x->p.second) {
            getPoints(x->right, depth + 1, points, p1, p2); 
        }

        // Exactly three comparisons takes place above
        qpoint += 3;
        
    }

}

int main() {

    cout << "Do you want to write the input file yourself?" << endl;
    cout << "1 --> yes" << endl;
    cout << "0 --> no" << endl;

    int choice;
    cin >> choice;

    ofstream outfile;
    outfile.open("input.txt");


    cout << "Enter no. of points: " << endl;
    int n;
    if (choice)
        cin >> n;
    else
        n = rand() % 51 + 50;

    vp points(n);

    pair<int, int> p;
    for (int i = 0; i < n; i++) {
        
        if (choice)
            cin >> p.first >> p.second;
        else {
            p.first = rand() % 101;
            p.second = rand() % 101;
        }

        points[i] = p;
        outfile << p.first << ", " << p.second << endl;
    }

    outfile.close();


    node* root = NULL;

    for (int i = 0; i < n; i++) {
        root = insert(root, points[i], 0);    
    }

    cout << "k-d Tree created" << endl;
    cout << "Operations performed: " << crtree << endl;

    pair<int, int> p1, p2;
    cout << "Enter top-left point of the query rectangle" << endl;
    cin >> p1.first >> p1.second;
    cout << "Enter bottom-right point of the query rectangle" << endl;
    cin >> p2.first >> p2.second;

    vp result;
    getPoints(root, 0, result, p1, p2);

    cout << "Points queried" << endl;
    cout << "Operations performed: " << qpoint << endl;
    
    outfile.open("output.txt");
    
    outfile << p1.first << ", " << p1.second << endl;
    outfile << p2.first << ", " << p2.second << endl;
    outfile << endl;

    for (int i = 0; i < result.size(); i++)
        outfile << result[i].first << ", " << result[i].second << endl;
    
    outfile.close();

}

