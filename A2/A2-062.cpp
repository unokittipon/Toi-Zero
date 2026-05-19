#include <bits/stdc++.h>
#define ll long long
#define sp << ' ' <<
#define nl << '\n' 
#define cnl cout << '\n'
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;

int b[5];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    string a;
    getline(cin,a);
    for(auto x : a){
        if(x == 'a' || x == 'A')b[0]++;
        else if(x == 'e' || x == 'E')b[1]++;
        else if(x == 'i' || x == 'I')b[2]++;
        else if(x == 'o' || x == 'O')b[3]++;
        else if(x == 'u' || x == 'U')b[4]++;
    }
    for(int i = 0;i < 5;i++){
        if(b[i]){
            if(i == 0)cout << "a: " << b[0] nl;
            if(i == 1)cout << "e: " << b[1] nl;
            if(i == 2)cout << "i: " << b[2] nl;
            if(i == 3)cout << "o: " << b[3] nl;
            if(i == 4)cout << "u: " << b[4] nl;
        }
    }
}