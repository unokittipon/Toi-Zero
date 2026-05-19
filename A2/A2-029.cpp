#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    for(int i = 0;i<n;i++){
        if(i > 0) cout << "0 ";
        if(i > 1){
            if(i < n-1){
                for(int j = 1; j < i; j++){
                    cout << "1 ";
                    }
            }else{
                for(int j = 1; j < i; j++){
                cout << "0 ";
                }
            }
            
        }
        cout << "0\n";
    }
}