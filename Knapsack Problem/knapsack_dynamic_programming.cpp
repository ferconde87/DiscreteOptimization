#include <bits/stdc++.h>

using namespace std;


void dp(int n, int w, int *vs, int *ws, vector<int> *a){

    for(int i = 1; i <= n; i++){
        for(int x = 0; x <= w; x++){
            if(x>=ws[i]) a[i][x] = max(a[i-1][x], a[i-1][x-ws[i]] + vs[i]);
            else a[i][x] = a[i-1][x];
        }
        for(int x = 0; x <= w; x++) a[0][x] = a[1][x];
    }

    cout << a[n][w] << " 1" << endl;
    
    int x = w;
    vector<bool> ans(n+1);
    for(int i = n; i > 0; i--){
        if(a[i][x]>a[i-1][x]){
            ans[i] = true;
            x-= ws[i];
        }
    }
    for(int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << endl;
    cout.flush();
}


int main(int argc, char** argv){
    if(argc < 2) return 0;
    string filename = argv[1];
    ifstream fin(filename);
    int w, n; fin >> n >> w;
    vector<int> a[n+1];
    for(int i = 0; i <= n; i++) a[i].resize(w+1);
    int vs[n+1];
    int ws[n+1];
    for(int x = 0; x <= w; x++) a[0][x] = 0;

    for(int i = 1; i <= n; i++){
        fin >> vs[i];
        fin >> ws[i];
    }
    
    dp(n,w,vs,ws,a);  
    
    return 0;
}