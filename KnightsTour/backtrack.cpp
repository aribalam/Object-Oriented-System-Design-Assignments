#include<bits/stdc++.h>

using namespace std;

#define vp vector< pair<int, int> >


bool addPointIfDefined(vp &points, int i, int j, int n) {
    if (i >= 0 && i < n && j >= 0 && j < n)
        points.push_back(make_pair(i, j));   
}

vp getNextMoves(int i, int j, int n) {
    vp v;

    addPointIfDefined(v, i+2, j+1, n);
    addPointIfDefined(v, i+1, j+2, n);
    addPointIfDefined(v, i-1, j+2, n);
    addPointIfDefined(v, i-2, j+1, n);
    addPointIfDefined(v, i-2, j-1, n);
    addPointIfDefined(v, i-1, j-2, n);
    addPointIfDefined(v, i+1, j-2, n);
    addPointIfDefined(v, i+2, j-1, n);

    return v;
}

bool solve(vector< vector<int> > &board, int x, int y, int n, int knightPlaced) {

    if (board[x][y] != -1)
        return false;

    board[x][y] = ++knightPlaced;
    
    if (knightPlaced == n * n)
        return true;

    vp moves = getNextMoves(x, y, n);
    for (int i = 0; i < moves.size(); i++) {
        if (solve(board, moves[i].first, moves[i].second, n, knightPlaced))
            return true;
    }

    board[x][y] = -1;
    return false;
}

void printBoard(vector< vector<int> > &board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    
    int n;
    cin >> n;

    vector< vector<int> > board(n, vector<int>(n, -1));

    if (solve(board, 0, 0, n, 0))
        printBoard(board, n);
    else
        cout << "No Solution" << endl;
}