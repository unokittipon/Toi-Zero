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
    string a;
    cin >> a;
    int b = 0;
    for(auto x : a){
        if(x == 'a' || x == 'u' || x == 'o' || x == 'i' || x == 'e')b++;
    }
    cout << b;
}