#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Team {
    string name;
    int points;
};

bool compareTeams(const Team& a, const Team& b) {
    if (a.points != b.points) {
        return a.points > b.points; 
    }
    return a.name < b.name; 
}

int main() {
    vector<Team> teams = {{"CHE", 0}, {"LIV", 0}, {"MUN", 0}, {"NEW", 0}};
    vector<pair<int, int>> matches = {
        {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 3}
    };
    for (int i = 0; i < 6; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) {
            teams[matches[i].first].points += 3;
        } else if (a < b) {
            teams[matches[i].second].points += 3;
        } else {
            teams[matches[i].first].points += 1;
            teams[matches[i].second].points += 1;
        }
    }
    sort(teams.begin(), teams.end(), compareTeams);
    for (int i = 0; i < 4; ++i) {
        cout << i + 1 << ". " << teams[i].name << " " << teams[i].points << endl;
    }
}