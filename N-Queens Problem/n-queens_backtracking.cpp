#include <bits/stdc++.h>

using namespace std;

const int n = 8;
int pos = 0;
bitset<n+1> rows;
bitset<2*n> dd; //downward diagonal
bitset<2*n> ud; //upward diagonal
vector<int> ans(n+1);//index => column_index & value => row_index

//return row's queen position
int find_position(int index_column, int index_row_start){
    int index_row = index_row_start;
    for(; index_row <= n; index_row++){
        int index_ud = index_row+index_column-1;
        int index_dd = n-index_column+index_row;
        if(rows[index_row] || ud[index_ud] || dd[index_dd]) continue;
        rows.set(index_row);
        ud.set(index_ud);
        dd.set(index_dd);
        ans[index_column] = index_row;
        break;
    }
    if(index_row==n+1) return -1;
    return index_row;
}

void reset(int index_column, int index_row){
    rows.reset(index_row);
    ud.reset(index_row+index_column-1);
    dd.reset(n-index_column+index_row);
}

void solve(int index_column, int index_row_start){

    if(index_column == n+1 || index_column == -1) return;

    int index_row = find_position(index_column, index_row_start);
    
    if(index_row == -1 && index_column == 0) return;

    if(index_row == -1){
        int last_index_column = index_column - 1;
        int last_index_row = ans[last_index_column];
        reset(last_index_column, last_index_row);
        solve(last_index_column, last_index_row + 1);//backtracking
    }else{
        solve(index_column+1, 1);
    }
}


int main(){

    solve(1,1);

    for(int i = 1; i <= n; i++){
        cout << i << " " << ans[i] << endl;
    }

    return 0;
}