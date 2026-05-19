#include <iostream>

using namespace std;

int main() {
    int A, B, d, r;
    if (!(cin >> A >> B >> d >> r)) return 0;

    int count = 0;
    for (int x = A; x <= B; ++x) {
        if (x % d == r) {
            count++;
        }
    }

    cout << count << endl;

    return 0;
}