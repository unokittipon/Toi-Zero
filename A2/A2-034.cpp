#include <bits/stdc++.h>
#define ll long long
#define sp << ' ' <<
#define nl << '\n' 
#define cnl cout << '\n'
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;

bool s[50000];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int a;
    cin >> a;
    s[0] = 1;
    s[1] = 1;
    for(int i = 2;i <= a;i++){
        if(!s[i]){
            for(int j = i + i;j <= a;j += i)s[j] = 1;
        }
    }
    if(s[a])cout << "No";
    else{
        cout << "Yes\n";
        for(int i = 2;i <= a;i++){
            if(!s[i])cout << i << ' ';
        }
    }
}