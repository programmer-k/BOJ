#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

struct Data {
  int row;
  int col;
  int state;
};

int w, h;
char room[20][20];
int visited[20][20][1'024];

bool GetInput() {
  cin >> w >> h;

  if (w == 0 && h == 0)
    return false;

  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      cin >> room[i][j];

  return true;
}

pair<int, int> Find(char ch) {
  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (room[i][j] == ch)
        return {i, j};

  return {-1, -1};
}

vector<pair<int, int>> FindDirtyPlaces() {
  vector<pair<int, int>> dirty_places;

  for (int i = 0; i < h; ++i)
    for (int j = 0; j < w; ++j)
      if (room[i][j] == '*')
        dirty_places.push_back({i, j});

  return dirty_places;
}

int BreathFirstSearch(pair<int, int> start,
                      const vector<pair<int, int>>& dirty_places) {
  queue<Data> q;
  memset(visited, -1, sizeof(visited));
  q.push({start.first, start.second, 0});
  visited[start.first][start.second][0] = 0;

  while (!q.empty()) {
    Data data = q.front();
    int row = data.row;
    int col = data.col;
    int state = data.state;
    q.pop();

    if (state >= (1 << ssize(dirty_places)) - 1)
      return visited[row][col][state];

    int move_rows[4] = {1, 0, -1, 0};
    int move_cols[4] = {0, 1, 0, -1};
    for (int i = 0; i < 4; ++i) {
      int next_row = row + move_rows[i];
      int next_col = col + move_cols[i];

      if (next_row < 0 || next_col < 0 || next_row >= h || next_col >= w)
        continue;

      char next_val = room[next_row][next_col];
      if (next_val == 'x')
        continue;

      int next_state = state;
      if (next_val == '*') {
        int index = lower_bound(dirty_places.begin(), dirty_places.end(),
                                make_pair(next_row, next_col)) -
                    dirty_places.begin();
        next_state |= 1 << index;
      }

      if (visited[next_row][next_col][next_state] != -1)
        continue;

      q.push({next_row, next_col, next_state});
      visited[next_row][next_col][next_state] = visited[row][col][state] + 1;
    }
  }

  return -1;
}

void Solve() {
  pair<int, int> start = Find('o');
  vector<pair<int, int>> dirty_places = FindDirtyPlaces();
  cout << BreathFirstSearch(start, dirty_places) << '\n';
}

int main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  while (GetInput())
    Solve();

  return 0;
}
