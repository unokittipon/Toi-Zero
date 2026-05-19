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
    char a;
    int b;
    cin >> a >> b;
    if(a == 'H' && b == 4567){
        cout << "safe unlocked";
    }else{
        if(a != 'H' && b != 4567){
            cout << "safe locked";
        }else if(a != 'H' && b == 4567){
            cout << "safe locked - change char";
        }else{
            cout << "safe locked - change digit";
        }
    }
}