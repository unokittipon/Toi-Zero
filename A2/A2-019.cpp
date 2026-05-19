    #include <bits/stdc++.h>
    using namespace std;

    int main(){
        cin.tie(NULL)->sync_with_stdio(false);
        string a;
        char f[3] ={'B','U','U'};
        cin >> a;
        bool b = false;
        int ans = 0;
        int mx = 0;
        int p = 0;
        for (int i = 0; i < a.length(); i++){
            if((a[i] == 'B'|| a[i] == 'b')&& !b){
                b = true;
                p = i;
            }
            else if((a[i] == 'B'|| a[i] == 'b') && b){
                b = true;
                ans = 0;
                //p = i;
            }
            else if((a[i] == 'U'|| a[i] == 'u') && b){
                ans++;
                if(mx < ans) mx = ans;
            }

        }
        if(!b){
            for(int i = 0;i< a.length();i++){
                cout << f[(i)%3];
            }
        }else if(b && mx <= 1){
            for(int i = 0;i< a.length();i++){ 
                if(i <= p){
                    cout << a[i];
                }else{
                    cout << 'U';
                }
            }
        }else{
            cout << "Yes " << mx;
        }
    }