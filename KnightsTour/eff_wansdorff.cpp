#include<bits/stdc++.h>

using namespace std;

#define vp vector< pair<int, int> >

int xMoves[8] =  {2, 1, -1, -2, -2, -1, 1, 2};
int yMoves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

vector< vector<int> > moveOrders;
vp switches;

bool isAccessible(vector< vector<int> > board, int i, int j, int n) {
    return (i >= 0 && i < n && j >= 0 && j < n && board[i][j] == -1);
}

int getNoOfAccessPos(vector <vector<int> > board, int x, int y, int n) {

    int count = 0;
    for (int i = 0; i < 8; i++) {
        if (isAccessible(board, x + xMoves[i], y + yMoves[i], n))
            count++;
    }

    return count;
}

void addOrder(vector< vector<int> > &orders, vp switches, int arr[8], int x, int y) {
    vector<int> v(8);
    for (int i = 0; i < 8; i++) {
        v.push_back(arr[i]);
    }

    orders.push_back(v);
    switches.push_back(make_pair(x, y));
}

void generateOrders(int m) {

    int order[8] = {3, 4, 2, 6, 1, 5, 7, 8};
    addOrder(moveOrders, switches, order, 0, 0);

    if(m % 8 == 0) {
        
        int order[8] = {8,7,6,4,2,1,3,5};
        addOrder(moveOrders, switches, order, m-1, m-2);

        int order[8] = {5,1,8,6,7,3,4,2};
        addOrder(moveOrders, switches, order, 2, 2);

        int order[8] = {8,7,6,4,2,1,3,5};
        addOrder(moveOrders, switches, order, m-1, m-2);

        int order[8] = {5,1,3,4,2,6,7,8};
        addOrder(moveOrders, switches, order, m-8, 1);

        int order[8] = {2,1,4,3,5,6,7,8};
        addOrder(moveOrders, switches, order, 7, m-3);

    }
    else if (m % 8 == 1) {

        int order[8] = {8,7,6,4,2,1,3,5};
        addOrder(moveOrders, switches, order, m-1, m-2);

        int order[8] = {5,1,3,2,4,6,7,8};
        addOrder(moveOrders, switches, order, 2, 2);

        int order[8] = {3,2,4,8,1,7,6,5};
        addOrder(moveOrders, switches, order, m-6, (m+2)/9);

    }

    else if (m % 8 == 2) {

        int order[8] = {8,7,6,4,2,1,3,5};
        addOrder(moveOrders, switches, order, 6, 1);

        int order[8] = {5,4,1,3,2,6,7,8};
        addOrder(moveOrders, switches, order, 3, 1);

        int order[8] = {5,2,4,3,1,6,7,8};
        addOrder(moveOrders, switches, order, m-15, 4);

        int order[8] = {8,5,6,4,7,1,2,3};
        addOrder(moveOrders, switches, order, 10, m-2);

        int order[8] = {1,5,7,4,6,8,2,3};
        addOrder(moveOrders, switches, order, 5, (m-6)/2);
    }

    else if(m % 8 == 3) {

        int order[8] = {4,2,6,8,1,3,5,7};
        addOrder(moveOrders, switches, order, m-1, m-2);

        int order[8] = {8,6,5,1,2,3,4,7};
        addOrder(moveOrders, switches, order, m-6, m);

        int order[8] = {5,1,8,6,7,3,4,2};
        addOrder(moveOrders, switches, order, 2, 5);

        int order[8] = {6,1,8,2,5,4,3,7};
        addOrder(moveOrders, switches, order, m-10, 3);

        int order[8] = {7,1,6,4,2,5,3,8};
        addOrder(moveOrders, switches, order, (m+1)/2, m-2);

    }

    else if(m % 8 == 4) {

        int order[8] = {8,7,6,4,2,1,3,5};
        addOrder(moveOrders, switches, order, m-1, m-2);

        int order[8] = {5,1,8,6,7,3,4,2};
        addOrder(moveOrders, switches, order, 2, 2);

        int order[8] = {5,1,3,4,2,6,7,8};
        addOrder(moveOrders, switches, order, m-8, 1);

        int order[8] = {8,6,7,5,3,4,2,1};
        addOrder(moveOrders, switches, order, 10, m-5);

        int order[8] = {7,8,5,6,3,4,2,1};
        addOrder(moveOrders, switches, order, 13, (m+2)/2);

    }

    else if(m%8 == 5)
    {

    if(m%16 == 5) {
    }
    else {
    }

}

else if(m%8 == 6)
{

if(i == 6 && j == 1)
    order = {8,7,6,4,2,1,3,5};
else if(i == 3 && j == 1)
    order = {5,4,1,3,2,6,7,8};
else if(i == m-10 && j == 1)
    order = {5,2,4,3,1,6,7,8};
else if(i == 10 && j == m-2)
    order = {8,5,6,4,7,1,2,3};
else if(i == 3 && j == (m+8)/2)
    order = {1,2,4,5,3,6,7,8};
}

else if(m%8 == 7)
{

if(i==m-1 && j == m-2)
    order = {4,2,6,8,1,3,5,7};
else if(i == m-6 && j == m)
    order = {8,6,5,1,2,3,4,7};
else if(i == 2 && j == 5)
    order = {5,1,8,6,7,3,4,2};
else if(i == m-6 && j == 3)
    order = {6,1,8,2,5,4,3,7};
else if(i == (m+1)/2 && j == m-2)
    order = {6,1,3,5,7,2,8,4};
}
}

pair<int, int> getNextMove(vector <vector<int> > board, int x, int y, int n) {

    int minInd = -1;
    int minVal = n+1;
    for (int i = 0; i < 8; i++) {
        if (isAccessible(board, x + xMoves[i], y + yMoves[i], n)) {
            int count = getNoOfAccessPos(board, x + xMoves[i], y + yMoves[i], n);
            if (count < minVal) {
                minInd = i;
                minVal = count;
            }
            else if (count == minVal) {

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