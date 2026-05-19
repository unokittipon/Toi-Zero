#include <bits/stdc++.h>
using namespace std;

int firdx[8] = {-1,-1,0,1,1,1,0,-1};
int firdy[8] = {0,1,1,1,0,-1,-1,-1};
int secdx[16] = {-2,-2,-2,-2,-2,-1,0,1,2,2,2,2,2,1,0,-1};
int secdy[16] = {-2,-1,0,1,2,2,2,2,2,1,0,-1,-2,-2,-2,-2};

int a,b,c,d;
int e,f,g;
int rabbit = 0;
int safe = 0;
int dan[100][100] = {0};

void mark(int f,int g){
    
    for(int i  = 0; i < 16;i++){
        int nx = f + secdx[i];
        int ny = g + secdy[i];
        if((nx >= 0 && ny >= 0 && nx < a && ny < b) && dan[nx][ny] == 0){
            dan[nx][ny] = 1; // why not use rabbit as a ref change dan to rabbit
            if(nx == c && ny == d && rabbit <= 20){
                rabbit = 20;
            }
        } 

    }
    for(int i  = 0; i < 8;i++){
        int nx = f + firdx[i];
        int ny = g + firdy[i];
        if((nx >= 0 && ny >= 0 && nx < a && ny < b) && (dan[nx][ny] == 0 || dan[nx][ny] == 1)){
            dan[nx][ny] = 2;
            if(nx == c && ny == d && rabbit <= 60){
                rabbit = 60;
            }
        }

    }

    int nx = f;
    int ny = g;
    if((nx >= 0 && ny >= 0 && nx < a && ny < b) && (dan[nx][ny] == 0 || dan[nx][ny] == 1 || dan[nx][ny] == 2)){
        dan[nx][ny] = 3;
        if(nx == c && ny == d && rabbit <= 100){
            rabbit = 100;
        }
    }

    
}
int main(){
    cin.tie(NULL)->sync_with_stdio(false);
    
    cin >> a >> b >> c >> d;
    cin >> e;
    
    for(int i = 0;i< e;i++){
        cin >> f >> g;
        mark(f,g);
    }
    for(int i = 0;i < a;i++){
        for(int j = 0;j < b;j++){
            if(dan[i][j] == 0){
                safe++;
            }
        }
    }
    cout << safe << '\n' << rabbit << '%';

    

}