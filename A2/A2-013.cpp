#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    char a;
    int b,c;
    int ans;
    cin >> a >> b;
    if(a == 'H'){
        ans = 5*b;
    }else if(a == 'O'){
        ans = 3*b;
    }else{
        ans = 2*b;
    }
    cin >> a >> b >> c;
    if(a == 'R'){
        if(b == 1){
            ans += 12 * c;
        }else if(b == 2){
            ans += 18 * c;
        }else{
            ans += 25 * c;
        }
    }else if(a == 'T'){
        if(b == 1){
            ans += 15 * c;
        }else if(b == 2){
            ans += 20 * c;
        }else{
            ans += 30 * c;
        }
    }else{
        if(b == 1){
            ans += 10 * c;
        }else if(b == 2){
            ans += 15 * c;
        }else{
            ans += 20 * c;
        }
    }
    cout << ans;
}