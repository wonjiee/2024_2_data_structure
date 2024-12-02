#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

const int WALL = 0;
const int PATH = 1;
const int VISITED = 2;
const int BACKTRACKED = 3;

struct Position {
    int x,y;
    Position() {}
    Position(int x, int y):x(x),y(y){}
};

int offset[8][2] = {{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}};
int N;

bool movable(Position pos, int dir,int n, vector<vector<int>>&maze) {
    int x = pos.x + offset[dir][0];
    int y = pos.y + offset[dir][1];
    return x >= 0 && x < n && y >= 0 && y < n && maze[x][y] == PATH;
}

Position move_to(Position pos, int dir) {
    return Position(pos.x + offset[dir][0], pos.y + offset[dir][1]);
}

int find_component(int x, int y,vector<vector<int>>&maze,stack<Position>&s){
    Position cur(x, y);
    int result = 1;
    while (true) {
        maze[cur.x][cur.y] = VISITED;
        bool forwarded = false;
        for (int dir = 0; dir < 8; dir++) {
            if (movable(cur, dir,N,maze)) {
                s.push(cur);
                cur = move_to(cur, dir);
                forwarded = true;
                result++;
                break;
            }
        }
        if (!forwarded) {
            maze[cur.x][cur.y] = BACKTRACKED;
            if (s.empty()) {
                break;
            }
            cur = s.top(), s.pop();
        }
    }
    return result;
}

int main() {
    ifstream infile ("input.txt");
    int T;
    infile>>T;
    for(int i=0;i<T;i++) {
        infile >> N;
        vector<vector<int>>maze(N,vector<int>(N,0));
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++) {
                int tmp;
                infile>>tmp;
                maze[j][k]=tmp;
            }

        stack<Position> s;
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                if(maze[j][k]==PATH) {
                    cout << find_component(j,k,maze,s) << " ";
                }
        cout<<endl;

    }
    return 0;

}