#include <bits/stdc++.h>
using namespace std;

int n;
int nm[1005];
int ans=0;
int a=0;

int main()
{
    cin >> n; 
    for (int i = 0; i < n; i++)
    {
        cin >> nm[i];
    }
    sort(nm, nm + n);
    for (int i = 0; i < n; i++)
    {
        ans += (a+nm[i])*2;
        a += nm[i];
    }
    cout << ans;
}