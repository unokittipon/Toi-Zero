// No Point
#include <bits/stdc++.h>
#define ll long long
#define nl <<'\n'
#define cnl cout << '\n';
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int a;
    cin >> a;
    int ten = 0,five = 0,two = 0,one = 0;
    ten = a/10;
    a = a - ten*10;
    five = a/5;
    a = a - five*5;
    two = a/2;
    a = a - two*2;
    one = a;
    cout << "10 = " << ten << '\n';
    cout << "5 = " << five << '\n';
    cout << "2 = " << two << '\n';
    cout << "1 = " << one << '\n';
}