#include <iostream>
#include <queue>
#include <string>
#include <utility>
using namespace std;

struct State {
  pair<int, int> red;
  pair<int, int> blue;
};

int n, m;
char board[10][10];
string visited[10][10][10][10];

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

bool IsHole(pair<int, int> pos) {
  if (board[pos.first][pos.second] == 'O')
    return true;
  return false;
}

bool IsWall(pair<int, int> pos) {
  if (board[pos.first][pos.second] == '#')
    return true;
  return false;
}

pair<int, int> NextStep(pair<int, int> pos, int direction) {
  int move_rows[4] = {0, 0, -1, 1};
  int move_cols[4] = {-1, 1, 0, 0};

  pos.first += move_rows[direction];
  pos.second += move_cols[direction];

  return pos;
}

pair<int, int> Move(pair<int, int> pos, int direction) {
  while (!(IsHole(pos) || IsWall(NextStep(pos, direction)))) {
    pos = NextStep(pos, direction);
  }

  return pos;
}

int GetMovingDistance(pair<int, int> current, pair<int, int> next) {
  return abs(current.first - next.first) + abs(current.second - next.second);
}

int GetOppositeDirection(int direction) {
  if (direction == 0)
    return 1;
  else if (direction == 1)
    return 0;
  else if (direction == 2)
    return 3;
  else
    return 2;
}

string BreadthFirstSearch(const pair<int, int>& red, const pair<int, int>& blue,
                          const pair<int, int>& hole) {
  queue<State> q;
  q.push({red, blue});
  visited[red.first][red.second][blue.first][blue.second].push_back('0');

  while (!q.empty()) {
    State current_state = q.front();
    pair<int, int> current_red = current_state.red;
    pair<int, int> current_blue = current_state.blue;
    q.pop();

    const string& current_visit =
        visited[current_red.first][current_red.second][current_blue.first]
               [current_blue.second];

    if (current_red == hole && current_blue != hole)
      return current_visit.substr(1);
    else if (current_blue == hole)
      continue;
    else if (current_visit.length() >= 12)
      break;

    for (int direction = 0; direction < 4; ++direction) {
      pair<int, int> next_red = Move(current_red, direction);
      pair<int, int> next_blue = Move(current_blue, direction);

      if (next_red == next_blue && next_red != hole) {
        int red_distance = GetMovingDistance(current_red, next_red);
        int blue_distance = GetMovingDistance(current_blue, next_blue);

        if (red_distance > blue_distance)
          next_red = NextStep(next_red, GetOppositeDirection(direction));
        else
          next_blue = NextStep(next_blue, GetOppositeDirection(direction));
      }

      string& next_visit = visited[next_red.first][next_red.second]
                                  [next_blue.first][next_blue.second];

      if (next_visit.length() > 0)
        continue;

      q.push({next_red, next_blue});
      next_visit = current_visit;
      next_visit.push_back('0' + direction);
    }
  }

  return "-1";
}

void Solve() {
  pair<int, int> red = Find('R');
  pair<int, int> blue = Find('B');
  pair<int, int> hole = Find('O');

  string answer = BreadthFirstSearch(red, blue, hole);

  if (answer == "-1") {
    cout << answer << '\n';
    return;
  }

  cout << answer.length() << '\n';

  for (char ch : answer)
    if (ch == '0')
      cout << 'L';
    else if (ch == '1')
      cout << 'R';
    else if (ch == '2')
      cout << 'U';
    else
      cout << 'D';
  cout << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
