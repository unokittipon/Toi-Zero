#include <bits/stdc++.h>
using namespace std;

int n,s,ss;
//int mnl[305][5];
int mnh[305];
bool aa = false;
bool bb = false;

int main(){
    cin >> n >> s;
    ss = s;
    for(int i = 0; i < n;i++){
        cin >> mnh[i];
    }
    for(int i = 0; i < n;i++){
        int a,b;
        aa = false;
        bb = false;
        
        if(mnh[i] % 3  == 0){
            a = mnh[i]/3;
            b = 10 * a;
            s -= b;
            aa = true;
        }
        if(mnh[i] % 4 == 0){
            a = mnh[i]/4;
            b = 10 * a;
            ss -= b;
            bb = true;
        }
        if(!aa){
            s -= b;
        }
        if(!bb){
            ss -= b;
        }

    }
    cout << s << ' ' << ss;
}