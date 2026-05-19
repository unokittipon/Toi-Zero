#include <bits/stdc++.h>
using namespace std;

int main() {
    int x;
    set<int> seen; 
    for (int i = 0; i < 10; i++) {
        cin >> x;
        if (seen.find(x) == seen.end()) {
            cout << x << " ";
            seen.insert(x);
        }
    }
    return 0;
}