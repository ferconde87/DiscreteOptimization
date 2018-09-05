#include <bits/stdc++.h>

using namespace std;

#define cn(x) cout << #x << " = " << x << endl;

vector<int> values;
vector<int> weights;
vector<int> order;
vector<int> best_solution;
vector<int> current_solution;
int current_value = 0;
int best_value = INT_MIN;
vector<bool> used;//used for estimate
int n = 0;


// int estimate(int capacity, int start){
//     int room = capacity;
//     double estimation = 0;
//     for(int i = start; i <= n; i++){
//         int index = order[i];
//         int weight = weights[index];
//         int value  = vs[index];
//         if(weight <= room){
//             estimation += value;
//             room -= weight;
//         }else{
//             double portion = room/(double)weight;
//             double amount = value*portion;
//             estimation += amount;
//             break;
//         }
//     }
//     return estimation;//(int)ans;
// }

//estimation of the current solution considering the current value of the knapsack + the best items
//in terms of value/weight outside the knapsack using linear relaxation
double estimate(int current_value, int capacity, int start){
    int room = capacity;
    double estimation = current_value;//value of the items already in the knapsack
    int n = order.size();
    for(int i = start; i <= n; i++){
        int index = order[i];
        int weight = weights[index];
        int value  = values[index];
        if(weight <= room){
            estimation += value;
            room -= weight;
        }else{
            double portion = room/(double)weight;
            double amount = value*portion;
            estimation += amount;
            break;
        }
    }
    return estimation;//(int)ans;
}

// vector<int> result;
// void knapsack(int value, int room, int estimation, int index){
//     // cout << value << "\t" << room << "\t" << estimation << endl;
//     if(index == vs.size()) return;
//     int v = vs[index];
//     int w = weights[index];
//     if(w <= room){
//         ans[index] = 1;
//         if(value+v > best){
//             best = value+v;
//             for(int i = 1; i <= n; i++) result[i] = ans[i];
//         } 
//         knapsack(value+v, room-w, estimation, index+1);
//     }
//     estimation = estimate(room, index+1);//considering only the elements from index+1 to n and 'room' capacity 
//     if(estimation+value < best){
//         // cout << value << "\t" << room << "\t" << estimation << endl;
//         return;
//     } 
        
//     ans[index] = 0;
//     knapsack(value, room, estimation+value, index+1);
     
// }

void knapsack(int current_value, int remaining_capacity, double estimation, int index, vector<int> & current_solution){
    
    if(estimation <= best_value) return;//bound


    if(index == n+1){
        if(current_value > best_value){
            best_value = current_value;
            // cout << remaining_capacity << endl;
            // cn(remaining_capacity)
            // cn(current_value)
            cout << current_value << " ";
            for(int i = 1; i <= n; i++){
                best_solution[i] = current_solution[i];
                // cout << best_solution[i] << " ";
            }
            cout << endl;
        }
        return;
    }

    if(weights[index] <= remaining_capacity){
        current_solution[index] = 1;
        double new_estimation = estimate(current_value+values[index], remaining_capacity-weights[index], index+1);
        knapsack(current_value+values[index], remaining_capacity-weights[index], new_estimation, index+1, current_solution);
    }
    if(current_solution[index]){
        current_solution[index] = 0;
        // current_value -= values[index];
    }
    knapsack(current_value, remaining_capacity, estimation, index+1, current_solution);
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