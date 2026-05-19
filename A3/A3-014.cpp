#include <bits/stdc++.h>
using namespace std;

int n;
int mn[100005];
int ans = 0;
int m = 0;
int l = 0;
int a;

int main(){
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> a;
        if(a > 18){
            m++;
        }else{
            l++;
        }
    }
    if(m == 0 && l == 0){
        ans = 0;
    }else if(m == 1 && l == 0){
        ans = 1;
    }else if(m == 0 && l == 1){
        ans = 1;
    }else if(m == 1 && l == 1){
        ans = 2;
    }else if(m == 1 && l == 2){
        ans = 3;
    }else if(m == 2 && l == 2){
        ans = 4;
    }else if(m == l){
        ans = m*2;
    }else if(m < l){
        ans = m+l;
    }else if(m > l){
        ans = (m*2-1);
    }
    cout << ans;
    
}