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
    string a,b,c;
    cin >> a >> b >> c;
    if(a.size() > 5 && b.size() > 5)cout << a[0] << a[1] << b[b.size()-1] << c[c.size()-1];
    else cout << a[0] << c << b[b.size()-1];
}