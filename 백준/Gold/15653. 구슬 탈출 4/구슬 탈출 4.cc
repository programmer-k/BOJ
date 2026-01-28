#include <cstring>
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

struct State {
  pair<int, int> red;
  pair<int, int> blue;
};

int n, m;
char board[10][10];
int visited[10][10][10][10];
int next_row[4] = {0, 1, 0, -1};
int next_col[4] = {1, 0, -1, 0};

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m;

  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> board[i][j];
}

pair<int, int> Find(char ch) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      if (board[i][j] == ch)
        return {i, j};
  return {-1, -1};
}

bool CanMove(const pair<int, int>& p, int i) {
  if (board[p.first + next_row[i]][p.second + next_col[i]] == '#' ||
      board[p.first][p.second] == 'O')
    return false;
  return true;
}

int CalculateAbsoluteDiff(const pair<int, int>& p1, const pair<int, int>& p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

State CalculateNextState(const State& state, int direction) {
  pair<int, int> next_red = state.red;
  pair<int, int> next_blue = state.blue;

  while (CanMove(next_red, direction)) {
    next_red.first += next_row[direction];
    next_red.second += next_col[direction];
  }

  while (CanMove(next_blue, direction)) {
    next_blue.first += next_row[direction];
    next_blue.second += next_col[direction];
  }

  if (next_red == next_blue && board[next_red.first][next_red.second] != 'O') {
    int red_move = CalculateAbsoluteDiff(next_red, state.red);
    int blue_move = CalculateAbsoluteDiff(next_blue, state.blue);

    if (red_move > blue_move) {
      next_red.first -= next_row[direction];
      next_red.second -= next_col[direction];
    } else {
      next_blue.first -= next_row[direction];
      next_blue.second -= next_col[direction];
    }
  }

  return {next_red, next_blue};
}

bool IsSuccessful(const State& state) {
  if (board[state.red.first][state.red.second] == 'O' &&
      board[state.blue.first][state.blue.second] != 'O')
    return true;
  return false;
}

bool IsFail(const State& state) {
  if (board[state.blue.first][state.blue.second] == 'O')
    return true;
  return false;
}

int BreadthFirstSearch(pair<int, int> start_red, pair<int, int> start_blue,
                       pair<int, int> hole) {
  queue<State> q;
  memset(visited, -1, sizeof(visited));
  q.push({start_red, start_blue});
  visited[start_red.first][start_red.second][start_blue.first]
         [start_blue.second] = 0;

  while (!q.empty()) {
    State state = q.front();
    q.pop();

    if (IsSuccessful(state))
      return visited[state.red.first][state.red.second][state.blue.first]
                    [state.blue.second];
    else if (IsFail(state))
      continue;

    for (int direction = 0; direction < 4; ++direction) {
      State next_state = CalculateNextState(state, direction);

      int& visit = visited[next_state.red.first][next_state.red.second]
                          [next_state.blue.first][next_state.blue.second];
      if (visit != -1)
        continue;

      q.push(next_state);
      visit = visited[state.red.first][state.red.second][state.blue.first]
                     [state.blue.second] +
              1;
    }
  }

  return -1;
}

void Solve() {
  pair<int, int> red = Find('R');
  pair<int, int> blue = Find('B');
  pair<int, int> hole = Find('O');

  cout << BreadthFirstSearch(red, blue, hole) << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
