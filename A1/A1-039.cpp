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
    cin >> a;
    ll b = 1;
    for(int i = 1;i <= a;i++){
        b *= i;
    }
    cout << b;
}