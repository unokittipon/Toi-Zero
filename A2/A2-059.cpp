#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

string getHashtagName(int id) {
    string names[] = {"", "TechTrends", "EcoLife", "FoodieHeaven", "FashionWeek", "HealthyLiving"};
    return names[id];
}

int main() {
    int n, d;
    cin >> n >> d;

    long long max_total = -1;
    string top_performer = "";

    for (int i = 0; i < n; ++i) {
        int id;
        cin >> id;
        
        long long total = 0;
        long long first_day = 0, last_day = 0;

        for (int j = 0; j < d; ++j) {
            long long u;
            cin >> u;
            if (j == 0) first_day = u;
            if (j == d - 1) last_day = u;
            total += u;
        }

        double avg = (double)total / d;

        string trend;
        if (last_day > first_day) trend = "GROWING";
        else if (last_day < first_day) trend = "DECLINING";
        else trend = "STABLE";

        cout << getHashtagName(id) << ": " << total << " total, " 
             << fixed << setprecision(2) << avg << " avg, " << trend << endl;

        if (total > max_total) {
            max_total = total;
            top_performer = getHashtagName(id);
        }
    }

    cout << "Top performer: " << top_performer << endl;

    return 0;
}