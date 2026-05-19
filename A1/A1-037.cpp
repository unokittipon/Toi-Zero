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
    int n;
    cin >> n;
    
    int val[]    = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string sym[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    
    string ans = "";
    for (int i = 0; i < 13; i++) {
        while (n >= val[i]) {
            ans += sym[i];
            n -= val[i];
        }
    }
    
    cout << ans;
}