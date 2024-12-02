#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

const int MAX_SIZE = 100;
const int PATH =0;
int n;
int maze[MAX_SIZE][MAX_SIZE];

int offset[4][2] = { {-1, 0},
                     {0, 1},
                     {1, 0},
                     {0, -1} };

void read_maze(){
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cin>>maze[i][j];
    }
}

bool movable(pair<int,int> cur,int dir){
    int x =cur.first + offset[dir][0];
    int y = cur.second + offset[dir][1];
    return x>=0 && x<n && y>=0 && y<n && maze[x][y]==PATH;
}

pair<int,int> move_to(pair<int,int> pos, int dir){
    return make_pair(pos.first + offset[dir][0], pos.second + offset[dir][1]);
}

int count_routes(pair<int, int> cur) {
    if (cur.first == n - 1 && cur.second == n - 1) {
        return 1;
    }

    int count = 0;
    maze[cur.first][cur.second] = 1;
    for (int dir = 0; dir < 4; dir++) {
        if (movable(cur, dir)) {
            pair<int, int> next = move_to(cur, dir);
            count += count_routes(next);
        }
    }
    maze[cur.first][cur.second] = PATH;
    return count;
}

int main() {
    read_maze();
    cout<<count_routes({0,0});
    return 0;
}

