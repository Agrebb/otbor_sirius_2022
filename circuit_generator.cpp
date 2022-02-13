#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
using namespace std;

void gen_thr2(int n){
    cout << n << " " << 3*n - 5 << " " << 1 << "\n";
    for (int i = 1; i <= n; i++) cout << i << " ";
    cout << "\n";
    cout << n+1 << " " << 1 << " " << 2 << " 0111\n";
    for (int i = 2; i < n - 1; i++){
        cout << n+i << " " << n+i-1 << " " << i + 1 << " 0111\n";
    }
    cout << 2*n - 1 << " " << 1 << " " << 2 << " 0001\n";
    for (int i = 2; i < n; i++){
        cout << 2*n + i - 2 << " " << n+i-1 << " " << i + 1 << " 0001\n";
    }
    cout << 3*n - 2 << " " << 2*n-1 << " " << 2*n << " 0111\n";
    for (int i = 2; i < n - 1; i++){
        cout << 3*n + i - 3 << " " << 2*n + i - 1 << " " << 3*n + i - 4 << " 0111\n";
    }
    cout << 4*n - 5 << "\n";
}

void gen_xor(int i1, int i2, int st){
    cout << st++ << " " << i1 << " " << i2 << " 0111\n";
    cout << st++ << " " << i1 << " " << i2 << " 1110\n";
    cout << st << " " << st-1 << " " << st-2 << " 0001\n";
}

void gen_xor4(){
    cout << "4 15 1\n";
    for (int i = 1; i <= 4; i++) cout << i << " ";
    cout << "\n";
    gen_xor(1, 2, 5);
    gen_xor(1, 2, 8);
    gen_xor(3, 4, 11);
    gen_xor(3, 4, 14);
    cout << 17 << " " << 7 << " " << 13 << " 0111\n";
    cout << 18 << " " << 10 << " " << 16 << " 1110\n";
    cout << 19 << " " << 17 << " " << 18 << " 0001\n";
    cout << 19 << "\n";
}

int main(){
    gen_xor4();
    return 0;
}

