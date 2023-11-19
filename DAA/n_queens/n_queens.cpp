#include<bits/stdc++.h>
using namespace std;

bool isSafe(int row, int col, vector<string>&board, int n){
    int temprow = row;
    int tempcol = col;

    // horizontal direction
    while(col>=0){
        if(board[row][col] == 'Q') return false;
        col--;
    }

    row = temprow;
    col = tempcol;
    // upper diagonal direction 
    while(row>=0 && col>=0){
        if(board[row][col] == 'Q') return false;
        row--; col--;
    }

    row = temprow;
    col = tempcol;
    // lower diagnoal direction
    while(row<n && col>=0){
        if(board[row][col] == 'Q') return false;
        row++; col--;
    }

    return true;
}

void printBoard(vector<string>&board){

    for(auto it: board){
        for(auto ele: it){
            cout<<ele<<" ";
        }
        cout<<endl;
    }
}

void solve(int col, vector<vector<string>>& ans, vector<string>&board, int n){
    
    if(col == n){
        ans.push_back(board);
        return;
    }

    for(int row = 0; row<n; row++){
        if(isSafe(row, col, board, n)){
            cout<<"Trying to place queen on board["<<row<<"]"<<"["<<col<<"]"<<endl;
            board[row][col] = 'Q';
            printBoard(board);
            solve(col+1, ans, board, n);
            board[row][col] = '.';
        }
        else{
            cout<<endl;
            cout<<"Not able to place queen on board["<<row<<"]"<<"["<<col+1<<"]"<<endl;
            printBoard(board);
        }
    }
}

vector<vector<string>> solveNQueens(int n){
    vector<vector<string>> ans;
    vector<string>board(n);
    string s(n, '.');

    for(int i = 0; i<n; i++){
        board[i] = s;
    }
    solve(0, ans, board, n);

    return ans;
}

int main()
{
    int n;
    cout<<"Enter number of queens: "<<endl;
    cin>>n;

    vector<vector<string>> ans = solveNQueens(n);

    for(auto it: ans){
        for(auto ele: it){
            cout<<ele<<endl;
        }
        cout<<endl;
    }
    return 0;
}