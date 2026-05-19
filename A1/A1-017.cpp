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
    int a1,a2,a3,b1,b2,b3;
    cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
    if(a1 < b1)cout << '1';
    else if(a1 > b1)cout << '2';
    else {
        if(a2 < b2)cout << '1';
        else if(a2 > b2)cout << '2';
        else {
            if(a3 < b3)cout << '1';
            else if(a3 > b3)cout << '2';
            else cout << '0';
        }
    }
}