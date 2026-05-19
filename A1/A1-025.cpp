#include <bits/stdc++.h>
#define ll long long
#define sp << ' ' <<
#define nl << '\n' 
#define cnl cout << '\n'
using namespace std;
const int nx = 1e5+5;
const int INF = 1e9+5;
const int MOD = 1e9+7;



int main(){
    cin.tie(0)->sync_with_stdio(0);
    string a;
    cin >> a;
    if(a[0] == 'A' || a[0] == 'a'){
        if(a[1] == 'D' || a[1] == 'd')cout << "ace of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "ace of hearts";
        else if(a[1] == 'S' || a[1] == 's')cout << "ace of spades";
        else cout << "ace of clubs";
    }else if(a[0] == 'J' || a[0] == 'j'){
        if(a[1] == 'D' || a[1] == 'd')cout << "jack of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "jack of hearts";
        else if(a[1] == 'S' || a[1] == 's')cout << "jack of spades";
        else cout << "jack of clubs";
    }else if(a[0] == 'Q' || a[0] == 'q'){
        if(a[1] == 'D' || a[1] == 'd')cout << "queen of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "queen of hearts";
        else if(a[1] == 'S' || a[1] == 's')cout << "queen of spades";
        else cout << "queen of clubs";
    }else if(a[0] == 'K' || a[0] == 'k'){
        if(a[1] == 'D' || a[1] == 'd')cout << "king of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "king of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "king of spades";
        else cout << "king of clubs";
    }else if(a.size() == 3){
        if(a[2] == 'D' || a[2] == 'd')cout << "10 of diamonds";
        else if(a[2] == 'H' || a[2] == 'h')cout << "10 of hearts";
        else if(a[2] == 'S' || a[2] == 's')cout << "10 of spades";
        else cout << "10 of clubs";
    }else if(a[0] == '1'){
        if(a[1] == 'D' || a[1] == 'd')cout << "1 of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "1 of hearts";
        else if(a[1] == 'S' || a[1] == 's')cout << "1 of spades";
        else cout << "1 of clubs";
    }else if(a[0] == '2'){
        if(a[1] == 'D' || a[1] == 'd')cout << "2 of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "2 of hearts";
        else if(a[1] == 'S' || a[1] == 's')cout << "2 of spades";
        else cout << "2 of clubs";
    }else if(a[0] == '3'){
        if(a[1] == 'D' || a[1] == 'd')cout << "3 of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "3 of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "3 of spades";
        else cout << "3 of clubs";
    }else if(a[0] == '4'){
        if(a[1] == 'D' || a[1] == 'd')cout << "4 of diamonds";
        else if(a[1] == 'H' || a[1] == 'h')cout << "4 of hearts";
        else if(a[1] == 'S' || a[1] == 's')cout << "4 of spades";
        else cout << "4 of clubs";
    }else if(a[0] == '5'){
        if(a[1] == 'D' || a[1] == 'd')cout << "5 of diamonds";
        else if(a[1] == 'H'|| a[1] == 'h')cout << "5 of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "5 of spades";
        else cout << "5 of clubs";
    }else if(a[0] == '6'){
        if(a[1] == 'D'|| a[1] == 'd')cout << "6 of diamonds";
        else if(a[1] == 'H'|| a[1] == 'h')cout << "6 of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "6 of spades";
        else cout << "6 of clubs";
    }else if(a[0] == '7'){
        if(a[1] == 'D'|| a[1] == 'd')cout << "7 of diamonds";
        else if(a[1] == 'H'|| a[1] == 'h')cout << "7 of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "7 of spades";
        else cout << "7 of clubs";
    }else if(a[0] == '8'){
        if(a[1] == 'D'|| a[1] == 'd')cout << "8 of diamonds";
        else if(a[1] == 'H'|| a[1] == 'h')cout << "8 of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "8 of spades";
        else cout << "8 of clubs";
    }else if(a[0] == '9'){
        if(a[1] == 'D'|| a[1] == 'd')cout << "9 of diamonds";
        else if(a[1] == 'H'|| a[1] == 'h')cout << "9 of hearts";
        else if(a[1] == 'S'|| a[1] == 's')cout << "9 of spades";
        else cout << "9 of clubs";
    }
}