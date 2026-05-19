#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    char a,b,c;
    cin >> a >> b >> c;
    int ans = 0;
    if(a == 'S'){
        if(b == 'R'){
            ans = 60;
        }else{
            ans = 80;
        }
    }else if(a == 'M'){
        if(b == 'R'){
            ans = 80;
        }else{
            ans = 100;
        }
    }else{
        if(b == 'R'){
            ans = 100;
        }else{
            ans = 120;
        }
    }
    if(c == 'N'){
        cout << ans;
    }else if(c == 'P'){
        int i;
        cin >> i;
        ans += 15*i;
        cout << ans;
    }else {
        int i;
        cin >> i;
        ans += 10*i;
        cout << ans;
    }
}