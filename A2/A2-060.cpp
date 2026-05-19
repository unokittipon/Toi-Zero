#include <iostream>
#include <vector>

using namespace std;

struct Bullet {
    int x, y, d;
};

int main() {
    int N;
    cin >> N;
    
    vector<Bullet> bullets(N);
    for (int i = 0; i < N; ++i) {
        cin >> bullets[i].x >> bullets[i].y >> bullets[i].d;
    }

    for (int tx = 1; tx < 1000; ++tx) {
        for (int ty = 1; ty < 1000; ++ty) {
            bool is_match = true;
            
            for (int i = 0; i < N; ++i) {
                long long dx = tx - bullets[i].x;
                long long dy = ty - bullets[i].y;
                long long dist_sq = dx * dx + dy * dy;
                
                if (dist_sq != (long long)bullets[i].d * bullets[i].d) {
                    is_match = false;
                    break;
                }
            }
            
            if (is_match) {
                cout << tx << " " << ty << endl;
                return 0;
            }
        }
    }

    return 0;
}