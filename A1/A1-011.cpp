#include <bits/stdc++.h>
#define ll long long
#define sp << ' ' <<
#define nl << '\n' 
#define cnl cout << '\n'
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;

string a;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    
    int n = s.size();
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && s[j] == s[i]) j++;
        cout << (j - i) << s[i];
        i = j;
    }
}