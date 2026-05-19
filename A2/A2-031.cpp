#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    char a[10][100];
    cin >> n;
    for(int i = 0;i < n;i++){
        cin >> a[1][i];
    }
    for(int i = 0;i < n;i++){
        cin >> a[2][i];
    }
    int m;
    cin >> m;
    for(int i = 0;i < m;i++){
        int aa,bb;
        char cc;
        cin >> aa >> bb >> cc;
        a[aa][bb] = cc;
    }
    int no = n;
    for(int i = 0;i < n;i++){
        if(a[1][i] == 'A' && a[2][i] == 'T'){
            no--;
        }
        else if(a[1][i] == 'T' && a[2][i] == 'A'){
            no--;
        }
        else if(a[1][i] == 'C' && a[2][i] == 'G'){
            no--;
        }
        else if(a[1][i] == 'G' && a[2][i] == 'C'){
            no--;
        }
    }
    for(int i = 0;i < n;i++){
        cout << a[1][i] << ' ';
    }
    cout << '\n';
    for(int i = 0;i < n;i++){
        cout << a[2][i] << ' ';
    }
    cout << '\n' << no;


}



