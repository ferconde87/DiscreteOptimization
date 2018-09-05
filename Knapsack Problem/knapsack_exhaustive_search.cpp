#include <bits/stdc++.h>

using namespace std;

vector<int> values;
vector<int> weights;
int best_value = INT_MIN;
vector<int> best_solution;
int n = 0;
int capacity = 0;

void knapsack(int current_value, int remaining_capacity, int index, vector<int> & current_solution){
    if(index == n+1){
        if(current_value > best_value){
            best_value = current_value;
            for(int i = 1; i <= n; i++){
                best_solution[i] = current_solution[i];
                cout << best_solution[i] << " ";
            }
            cout << endl;
        }
        return;
    }

    if(weights[index] <= remaining_capacity){
        current_solution[index] = 1;
        knapsack(current_value+values[index], remaining_capacity-weights[index], index+1, current_solution);
    }
    if(current_solution[index]){
        current_solution[index] = 0;
    }
    knapsack(current_value, remaining_capacity, index+1, current_solution);
}


void solve_recursive(string filename){
    ifstream fin(filename);
    fin >> n >> capacity;
    values.resize(n+1);
    weights.resize(n+1);
    best_solution.resize(n+1);
    vector<int> current_solution(n+1);

    for(int i = 1; i <= n; i++){
        fin >> values[i];
        fin >> weights[i];
    }
    
    knapsack(0, capacity, 1, current_solution);

    cout << best_value << " " << 0 << endl;
    for(int i = 1; i <= n; i++) cout << best_solution[i] << " ";
    cout << endl;
    cout.flush();
}


int main(int argc, char** argv){
    if(argc < 2) return 0;
    string filename = argv[1];
    
    solve_recursive(filename);

    return 0;
}