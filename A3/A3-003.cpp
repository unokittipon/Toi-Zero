#include <bits/stdc++.h>
#define ll long long
#define sp << ' ' <<
#define nl << '\n' 
#define cnl cout << '\n'
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;
int e1[305],e2[305],n;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i = 1;i <= n;i++){
        cin >> e1[i];
    }
    for(int i = 1;i <= n;i++){
        cin >> e2[i];
    }
    int s1 = 1;
    int s2 = 1;
    int count = 0;
    for(int i = 1;i <= n;i++){
        if(s1 == s2 && e1[i] == e2[i])count++;
        else if(s2 > s1 && s2 < e1[i] && (e2[i] > e1[i] || e2[i] < s1))count++;
        s1 = e1[i];
        s2 = e2[i];
    }
    cout << count;
}