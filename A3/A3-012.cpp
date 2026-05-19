#include <bits/stdc++.h>
using namespace std;

int n, s, ns = 0,nw;
int a[1005];
bool b[1005];
int main()
{
    cin >> n >> s;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }

    if (s)
    {
        nw = s;
        while (1)
        {
            if(!nw || b[nw]){
                break;
            }
            b[nw] = true;
            nw = a[nw];
            ns++;
            
        }
    }
    cout << ns;
}