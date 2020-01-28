#include <iostream>
#define SIZE 8
using namespace std;

int TC;
int road[SIZE][SIZE];
bool visit[SIZE][SIZE];
int length;
int N, K;
pair<int, int> top[5]; //봉우리 위치 x,y
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
void go(int x, int y, int len, bool ok);

int main() {


	cin >> TC;
	for (int tc = 1; tc <= TC; tc++) {		
		int Max_high = 0; //봉우리 최대 높이
		int Max_cnt = 0;  //최대 봉우리 수
		cin >> N >> K;
		
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cin >> road[i][j];// 봉우리 높이 입력
				visit[i][j] = false;
				if (Max_high <= road[i][j]) Max_high = road[i][j];
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (Max_high == road[i][j]) {
					top[Max_cnt++] = make_pair(i, j);					
				}
			}
		}
		length = 0; //길이 초기화
		for (int i = 0; i < Max_cnt; i++) {
			go(top[i].first, top[i].second, 1, true);
		}
		cout << "#" << tc << " " << length << '\n';
	}




	return 0;
}
void go(int x, int y, int len, bool ok) {

	if (len > length)length = len;
	visit[x][y] = true;
	
	for (int k = 0; k < 4; k++) {
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx < 0 || ny < 0 || nx >= N || ny >= N)continue;
		if (visit[nx][ny])continue;
		if (road[nx][ny] < road[x][y]) {
			go(nx, ny, len + 1, ok);
		}
		else if (road[nx][ny] - K < road[x][y] && ok)		{			
					
			for (int dip = 1; dip <= K; dip++) {
				if (road[nx][ny] - dip >= road[x][y])continue;
				if (road[nx][ny] - dip < road[x][y]) {
					road[nx][ny] -= dip;
					go(nx, ny, len + 1, false);
					road[nx][ny] += dip;
				}
			}
			
		}
	}
	visit[x][y] = false;

}