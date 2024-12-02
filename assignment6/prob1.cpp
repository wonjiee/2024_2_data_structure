#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 100;
const int PATH =0;
int n;
int end_year;
int ground[MAX_SIZE][MAX_SIZE];

int offset[4][2] = { {-1, 0},
                     {0, 1},
                     {1, 0},
                     {0, -1} };

void read_ground(){
    ifstream infile("input1.txt");
    infile>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            infile>>ground[i][j];
    }
    infile>>end_year;
    infile.close();
}

bool movable(pair<int,int> cur,int dir){
    int x =cur.first + offset[dir][0];
    int y = cur.second + offset[dir][1];
    return x>=0 && x<n && y>=0 && y<n && ground[x][y]==PATH;
}

pair<int,int> move_to(pair<int,int> pos, int dir){
    return make_pair(pos.first + offset[dir][0], pos.second + offset[dir][1]);
}

void print_maze() {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++)
            cout << ground[i][j] << " ";
        cout << endl;
    }
}

int main(){
    read_ground();
    queue<pair<int,int>>que;
    int x,y;
    cin>>x>>y;
    pair<int,int> cur(x,y);
    ground[cur.first][cur.second]=-1;
    que.push(cur);
    int max_gress=1;
    while(!que.empty()){
        cur=que.front();
        que.pop();
        for(int dir=0;dir<4;dir++){
            if(movable(cur,dir)) {
                pair<int, int> p = move_to(cur, dir);
                if(ground[cur.first][cur.second]==-1-end_year)
                    break;
                ground[p.first][p.second] = ground[cur.first][cur.second] - 1;
                que.push(p);
                max_gress++;
            }
        }
    }
    //print_maze();
    cout<<max_gress;
    return 0;
}