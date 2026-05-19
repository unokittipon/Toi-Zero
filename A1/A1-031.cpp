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
    if(a.size() == 4)cout << a[0] << ',' << a.substr(1,3);
    if(a.size() == 5)cout << a.substr(0,2) << ',' << a.substr(2,3);
    if(a.size() == 6)cout << a.substr(0,3) << ',' << a.substr(3,3);
}