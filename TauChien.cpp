#include<bits/stdc++.h>
using namespace std;

int M, N, K;

string allDirs = "WESN";
vector<vector<vector<int>>> dp;

vector<string> sea_map;

string directions;
void input(){
    cin >> M >> N >> K;
    for(int i = 0; i < M; i++){
        string s;
        cin >> s;
        sea_map.push_back(s);
    }
    
    for(int i = 0; i < M; i++){
        vector<vector<int>> vt(N, vector<int>(K+1, -1));
        dp.push_back(vt);
    }
    string s;
    cin >> s;
    directions = " " + s;
}

bool isSafe(int i, int j){
    return 0 <= i && i < M && 0 <= j && j < N;
}

vector<int> mapping_reverse_move(char dir){
    switch(dir){
        case 'N':
            return vector<int>{1, 0};
        case 'S':
            return vector<int>{-1, 0};
        case 'W':
            return vector<int>{0, 1};
        case 'E':
            return vector<int>{0, -1};
        default:
            return vector<int>{0, 0};
    }
}

bool posDir(char c1, char c2){
    return (c1 == 'W' && c2 == 'E') || (c1 == 'N' && c2 == 'S') || (c1 == 'E' && c2 == 'W') || (c1 == 'S' && c2 == 'N');
}

int solve(int i, int j, int k){
    if(!isSafe(i, j)) return 0;

    if(dp[i][j][k] != -1) return dp[i][j][k];

    if(k == 0) dp[i][j][k] = sea_map[i][j] != '#' ? 1 : 0; //xuat phat tai o i,j
    else{
        if(sea_map[i][j] == '#'){
            dp[i][j][k] = 0;
        }else{
            dp[i][j][k] = 0;
            if(directions[k] == '?'){
                for(char dir: allDirs){
                    vector<int> ans = mapping_reverse_move(dir);
                    int move_x = ans[0];
                    int move_y = ans[1];
                    if(solve(i + move_x, j + move_y, k-1)){
                        dp[i][j][k] =  1;
                        break;
                    }
                }
            }else{
                vector<int> ans = mapping_reverse_move(directions[k]);
                int move_x = ans[0];
                int move_y = ans[1];
                dp[i][j][k] = solve(i + move_x, j + move_y, k-1);
            }
        }
    }
    return dp[i][j][k];

    
    
}

int main(){
    freopen("data.txt", "r", stdin);
    freopen("data_out.txt", "w", stdout);

    input();
    int res = 0;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if(sea_map[i][j] != '#'){
                if(solve(i, j, K)){
                    // cout << i << " " << j << endl;
                    res++;
                };
            }
        }
    }
    cout << res << endl;
}