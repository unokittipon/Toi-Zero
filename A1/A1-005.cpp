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
    int a,b;
    cin >> a >> b;
    if(a >= 1 && a <= 3){
        if(a == 3 && b >= 21)cout << "spring";
        else cout << "winter";
    }else if(a >= 4 && a <= 6){
        if(a == 6 && b >= 21)cout << "summer";
        else cout << "spring";
    }else if(a >= 7 && a <= 9){
        if(a == 9 && b >= 21)cout << "fall";
        else cout << "summer";
    }else if(a >= 10 && a <= 12){
        if(a == 12 && b >= 21)cout << "winter";
        else cout << "fall";
    }
}