#include <stdio.h>

char grid[1025][1025];
int visited[1025][1025];

int main() {
    int N, M;
    while (scanf("%d %d", &N, &M) == 2) {

        for (int i = 0; i < N; i++)
            scanf("%s", grid[i]);

        
        static int qx[1024*1024];
        static int qy[1024*1024];

        int cliques = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                visited[i][j] = 0;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {

              
                if (grid[i][j] == '.' && !visited[i][j]) {
                    cliques++;

                    // BFS
                    int f = 0, b = 0;
                    qx[b] = i;
                    qy[b] = j;
                    visited[i][j] = 1;
                    b++;

                    while (f < b) {
                        int x = qx[f], y = qy[f];
                        f++;

                        // 4 directions
                        int dx[4] = {1, -1, 0, 0};
                        int dy[4] = {0, 0, 1, -1};

                        for (int k = 0; k < 4; k++) {
                            int nx = x + dx[k];
                            int ny = y + dy[k];

                            if (nx >= 0 && nx < N && ny >= 0 && ny < M) {
                                if (!visited[nx][ny] && grid[nx][ny] == '.') {
                                    visited[nx][ny] = 1;
                                    qx[b] = nx;
                                    qy[b] = ny;
                                    b++;
                                }
                            }
                        }
                    }
                }
            }
        }

        printf("%d\n", cliques);
    }
    return 0;
}
