#include <bits/stdc++.h>
#define ll long long
#define sp << ' ' <<
#define nl << '\n' 
#define cnl cout << '\n'
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;



int main(){
    cin.tie(0)->sync_with_stdio(0);
    int a;
    char b;
    cin >> a >> b;
    if(b == 'c' || b == 'C'){
        if(a < 0)cout << "solid";
        else if(a <= 100)cout << "liquid";
        else cout << "gas";
    }else{
        if(a < 32)cout << "solid";
        else if(a <= 212)cout << "liquid";
        else cout << "gas";
    }
}