#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int max = 0;
    int nmax = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if(a > max){
            nmax = 1;
            max = a;
        }else if(a == max) nmax++;

    }
    cout << max << '\n' << nmax;
}