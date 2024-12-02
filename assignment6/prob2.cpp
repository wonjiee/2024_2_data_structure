#include <iostream>
#include <fstream>

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
    ifstream infile("input2.txt");
    infile>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            infile>>maze[i][j];
    }
    infile.close();
}

bool movable(pair<int,int> cur,int dir){
    int x =cur.first + offset[dir][0];
    int y = cur.second + offset[dir][1];
    return x>=0 && x<n && y>=0 && y<n && maze[x][y]==PATH;
}

pair<int,int> move_to(pair<int,int> pos, int dir){
    return make_pair(pos.first + offset[dir][0], pos.second + offset[dir][1]);
}

void print_maze() {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }
}

int main(){
    read_maze();
    queue<pair<int,int>>que;
    pair<int,int>cur(0,0);
    maze[cur.first][cur.second]=-1;
    que.push(cur);

    while(!que.empty()){
        cur=que.front();
        pair<int,int>tmp =cur;
        que.pop();
        int count = maze[cur.first][cur.second];
        for(int dir=0;dir<4;dir++) {
            cur=tmp;
            while (movable(cur, dir)) {
                pair<int, int> p = move_to(cur, dir);
                if (maze[p.first][p.second] == 0) {
                    maze[p.first][p.second] = count - 1;
                } else {
                    if (maze[p.first][p.second] < count - 1)
                        maze[p.first][p.second] = count - 1;
                }
                que.push(p);
                cur = p;
            }
        }
    }
    print_maze();
    if(maze[n-1][n-1]==0)
        cout << "No path exists." << endl;
    else
        cout<<-(maze[n-1][n-1]+2)<<endl;
    return 0;
}