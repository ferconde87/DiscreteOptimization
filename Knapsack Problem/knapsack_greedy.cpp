#include <bits/stdc++.h>

using namespace std;


void solve_greedy(string filename){
    ifstream fin(filename);
    int n, w; fin >> n >> w;
    int capacity = w;
    int vs[n+1];
    int ws[n+1];
    tuple<double, int, int> ps[n+1];
    int order[n+1];
    for(int i = 1; i <= n; i++){
        fin >> vs[i];
        fin >> ws[i];
        get<0>(ps[i]) = vs[i]/(double)ws[i];
        get<1>(ps[i]) = ws[i]; //get<0>(ps[i]) == get<0>(ps[j]) => el de peso menor va primero
        get<2>(ps[i]) = i;     //para la estimación, conviene elegir el de mayor peso primero***
    }
    sort(ps+1, ps+n+1);
    for(int i = n, j = 1; j <= n; j++, i--){
        order[j] = get<2>(ps[i]); //***es lo que se hace acá, al copiar los valores en orden inverso
    }
    int result[n+1]; for(int i = 1; i <= n; i++) result[i] = 0;
    int value = 0;  
    for(int i = 1; i <= n && w >= 0; i++){
        int index = order[i];
        if(ws[index] > w) continue;
        w-= ws[index];
        value += vs[index];
        result[index] = 1;
    }
    cout << value << " " << 0 << endl;
    for(int i = 1; i <= n; i++) cout << result[i] << " ";
    cout << endl;
    cout.flush();
}


int main(int argc, char** argv){
    if(argc < 2) return 0;
    string filename = argv[1];
    solve_greedy(filename);
    
    return 0;
}