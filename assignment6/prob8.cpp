#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// 방향 벡터 (상, 하, 좌, 우)
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

// 순환(재귀) 함수
bool can_reach(vector<vector<int>> &board, int x, int y, int targetX, int targetY, int n) {
    // 목표 지점에 도달한 경우
    if (x == targetX && y == targetY)
        return true;

    // 방문 표시 (순환을 위한 임시 값)
    board[x][y] = -1;

    // 상, 하, 좌, 우 방향 탐색
    for (int dir = 0; dir < 4; dir++) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        // 말을 찾기 위해 경로 탐색
        while (nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] == 0) {
            nx += dx[dir];
            ny += dy[dir];
        }

        // 말을 하나 뛰어넘기
        if (nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] == 1) {
            // 말을 뛰어넘은 위치로 이동
            nx += dx[dir];
            ny += dy[dir];

            // 다음 위치가 유효하고 방문하지 않은 경우 재귀 호출
            if (nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] == 0) {
                if (can_reach(board, nx, ny, targetX, targetY, n))
                    return true;
            }
        }
    }

    // 되돌리기 (방문 표시 제거)
    board[x][y] = 0;
    return false;
}

int main() {
    int n;
    ifstream infile("input8.txt");
    infile>>n;
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            infile >> board[i][j];
        }
    }

    int startX, startY, endX, endY;
    infile >> startX >> startY >> endX >> endY;

    // 인덱스 조정 (1-based to 0-based)
    startX--; startY--; endX--; endY--;

    if (can_reach(board, startX, startY, endX, endY, n))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}
