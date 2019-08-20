#include<bits/stdc++.h>

using namespace std;

#define vp vector< pair<int, int> >

bool isAccessible(vector< vector<int> > board, int i, int j, int n) {
    return (i >= 0 && i < n && j >= 0 && j < n && board[i][j] == -1);
}

int getNoOfAccessPos(vector <vector<int> > board, int x, int y, int n) {
    
    int xMoves[8] =  {2, 1, -1, -2, -2, -1, 1, 2};
    int yMoves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isAccessible(board, x + xMoves[i], y + yMoves[i], n))
            count++;
    }

    return count;
}

pair<int, int> getNextMove(vector <vector<int> > board, int x, int y, int n) {
    
    int xMoves[8] =  {2, 1, -1, -2, -2, -1, 1, 2};
    int yMoves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int minInd = -1;
    int minVal = 10;
    for (int i = 0; i < 8; i++) {
        if (isAccessible(board, x + xMoves[i], y + yMoves[i], n)) {
            int count = getNoOfAccessPos(board, x + xMoves[i], y + yMoves[i], n);
            if (count < minVal) {
                minInd = i;
                minVal = count;
            }
        }
    }

    return make_pair(x + xMoves[minInd], y + yMoves[minInd]);
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

    int x = 0, y = 0;
    board[x][y] = 1;

    for (int i = 2; i <= n*n; i++) {
        
        pair<int, int> next = getNextMove(board, x, y, n);
        x = next.first;
        y = next.second;

        board[x][y] = i;
    }

    printBoard(board, n);
}