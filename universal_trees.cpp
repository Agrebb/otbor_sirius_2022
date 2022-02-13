#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
using namespace std;

bool are_equal(string & a, string & b, int depth){
    int n = (1<<(depth+1)) - 1;
    vector <vector <int>> dp(n, vector <int> (n));
    for (int d = depth; d >= 0; d--){
        for (int v1 = (1<<d)-1; v1 < (1<<(d+1))-1; v1++){
            for (int v2 = (1<<d)-1; v2 < (1<<(d+1))-1; v2++) {
                dp[v1][v2] = (a[v1] == b[v2]);
                if (d < depth) {
                    dp[v1][v2] &= (dp[2*v1+1][2*v2+1] && dp[2*v1+2][2*v2+2]) ||
                            (dp[2*v1+1][2*v2+2] && dp[2*v1+2][2*v2+1]);
                }
            }
        }
    }
    return dp[0][0];
}

bool is_included(string & a, string & b, int depth_a, int depth_b){
    int na = (1<<(depth_a+1)) - 1, nb = (1<<(depth_b+1)) - 1;
    vector <vector <int>> dp(na, vector <int> (nb));
    for (int v = nb - 1; v >= 0; v--){
        for (int u = na - 1; u >= 0; u--){
            if (2*v+1 >= nb){
                dp[u][v] = (2*u+1 >= na) && (b[v] == a[u]);
            }
            else{
                int lower = dp[u][2*v+1] || dp[u][2*v+2], current = 0;
                if (b[v] == a[u]){
                    if (2*u+1 >= na) current = 1;
                    else{
                        current = (dp[2*u+1][2*v+1] && dp[2*u+2][2*v+2]) ||
                                (dp[2*u+1][2*v+2] && dp[2*u+2][2*v+1]);
                    }
                }
                dp[u][v] = lower || current;
            }
            // cout << u << " " << v << " " << dp[u][v] << endl;
        }
    }
    return dp[0][0];
}

vector <char> L{'A', 'O'};

string get_tree_by_types(vector <int> & types, int n){
    string tree(2*n-1, 'A');
    tree[0] = L[types[0]];
    for (int i = 1; i < n; i++){
        tree[2*i-1] = L[types[i] >= 1];
        tree[2*i] = L[types[i] >= 2];
    }
    return tree;
}

vector <string> generate_all(int depth){
    int n = (1<<depth);
    vector <string> result;
    vector <int> types(n, 0);
    while (1){
        result.push_back(get_tree_by_types(types, n));

        bool finish = true;
        for (int i = 0; i < n; i++){
            int maxtype = 2 - (i == 0);
            if (types[i] < maxtype){
                types[i]++;
                finish = false;
                break;
            }
            else types[i] = 0;
        }
        if (finish) break;
    }
    return result;
}

string generate_tree(int depth){
    int n = (1<<depth);
    vector <int> types(n, 0);
    types[0] = (rand() % 2);
    for (int i = 1; i < n; i++){
        types[i] = (rand() % 3);
    }
    return get_tree_by_types(types, n);
}

int main(){
    auto depth2 = generate_all(2);

    int num_tries = 1000000;
    while (num_tries--) {
        string t = generate_tree(4);
        bool ok = true;
        for (string s : depth2) {
            if (!is_included(s, t, 2, 4)) {
                ok = false;
                break;
            }
        }
        if (ok){
            cout << t << "\n";
            return 0;
        }
    }

    return 0;
}


