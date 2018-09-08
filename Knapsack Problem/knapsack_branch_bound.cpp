#include <bits/stdc++.h>

using namespace std;

#define cn(x) cout << #x << " = " << x << endl;

vector<int> values;
vector<int> weights;
vector<int> order;
vector<double> portions;
vector<int> best_solution;
vector<int> current_solution;
vector<bool> used;
int current_value = 0;
int best_value = INT_MIN;
int n = 0;

//estimation of the current solution considering the current value of the knapsack + the best items
//in terms of value/weight outside the knapsack using linear relaxation
double estimate(int current_value, int capacity, int start){
    // cout << "-------------- estimate --------------------------" << endl;
    // cout << current_value << " " << capacity << " " << start << endl;
    int room = capacity;
    double estimation = current_value;//value of the items already in the knapsack
    int n = order.size();
    for(int i = 1; i <= n; i++){
        int index = order[i];
        if(index < start || current_solution[index]) continue;
        int weight = weights[index];
        int value  = values[index];
        portions[index] = 1;
        if(weight <= room){
            estimation += value;
            room -= weight;
        }else{
            portions[index] = room/(double)weight;
            double amount = value*portions[index];
            estimation += amount;
            break;
        }
    }
    // cout << "-------------- END estimate --------------------------" << endl;
    return estimation;//(int)ans;
}


void print_current_solution(vector<int> & vs){
    for(int i = 1; i <= n; i++){
        cout << vs[i] << " ";
    }
    cout << endl;
}

void print_used(){
    for(int i = 1; i < used.size(); ++i) cout << used[i] << " ";
    cout << endl;
}

void knapsack(int current_value, int remaining_capacity, double estimation, int index, vector<int> & current_solution){
    // cout << current_value << " " << remaining_capacity << " " << estimation << " " << index << " # "; 
    // print_current_solution(current_solution);
    if(estimation <= best_value) return;//bound


    if(index == n+1){
        if(current_value > best_value){
            best_value = current_value;
            // cn(remaining_capacity)
            // cn(current_value)
            // cout << "[ " << remaining_capacity << " | " << current_value << " ] => ";
            for(int i = 1; i <= n; i++){
                best_solution[i] = current_solution[i];
                // cout << best_solution[i] << " ";
            }
            // cout << endl;
        }
        return;
    }

    if(weights[index] <= remaining_capacity){
        // cn(values[index])
        // cn(weights[index])
        double new_estimation = estimate(current_value+values[index], remaining_capacity-weights[index], index+1);
        current_solution[index] = 1;
        knapsack(current_value+values[index], remaining_capacity-weights[index], new_estimation, index+1, current_solution);
        //si portions[indx] == 1 no hay que calcular la nueva estimation, ya que el item ya es parte de ella
    }
    if(current_solution[index]){
        current_solution[index] = 0;
    }
    double new_estimation = estimate(current_value, remaining_capacity, index+1);
    // cn(new_estimation)
    knapsack(current_value, remaining_capacity, new_estimation, index+1, current_solution);
}


void solve_branch_bound(string filename){
    ifstream fin(filename);
    // int n;
    int capacity;
    fin >> n >> capacity;
    
    values.resize(n+1);
    weights.resize(n+1);
    order.resize(n+1);
    best_solution.resize(n+1);
    current_solution.resize(n+1);
    portions.resize(n+1);
    used.resize(n+1);
    
    pair<double, int> ps[n+1];// < value/peso , original position >
    for(int i = 1; i <= n; i++){
        fin >> values[i];
        fin >> weights[i];
        ps[i].first = values[i]/(double)weights[i];
        ps[i].second = i;
    }
    sort(ps+1, ps+n+1);
    for(int i = n, j = 1; j <= n; j++, i--){
        order[j] = ps[i].second; 
    }

    double estimation = estimate(0, capacity, 0);

    knapsack(0, capacity, estimation, 1, current_solution);
    
    cout << best_value << " " << 0 << endl;
    for(int i = 1; i <= n; i++) cout << best_solution[i] << " ";
    cout << endl;
    cout.flush();
}


int main(int argc, char** argv){
    if(argc < 2) return 0;
    string filename = argv[1];
    solve_branch_bound(filename);
    
    return 0;
}