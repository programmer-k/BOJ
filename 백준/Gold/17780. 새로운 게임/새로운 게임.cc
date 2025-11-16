#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

enum Color { kWhite, kRed, kBlue };

enum Direction { kNone, kRight, kLeft, kUp, kDown };

struct PieceInfo {
  int row;
  int col;
  int direction;
};

int n, k;
vector<vector<int>> board(14, vector<int>(14, kBlue));
vector<PieceInfo> pieces;
vector<vector<vector<int>>> map(14, vector<vector<int>>(14));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      cin >> board[i][j];

  pieces.resize(k + 1);
  for (int i = 1; i <= k; ++i)
    cin >> pieces[i].row >> pieces[i].col >> pieces[i].direction;
}

void InitMap() {
  for (int i = 1; i <= k; ++i) {
    int row = pieces[i].row;
    int col = pieces[i].col;
    map[row][col].push_back(i);
  }
}

bool IsGameOver() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      if (ssize(map[i][j]) >= 4)
        return true;
  return false;
}

int GetOppositeDirection(int direction) {
  if (direction == kRight)
    return kLeft;
  else if (direction == kLeft)
    return kRight;
  else if (direction == kUp)
    return kDown;
  else
    return kUp;
}

void MovePiece(int piece_id) {
  int row = pieces[piece_id].row;
  int col = pieces[piece_id].col;

  // Do not move the piece if it is not located at the bottom.
  if (map[row][col].front() != piece_id)
    return;

  vector<int> move_rows = {0, 0, 0, -1, 1};
  vector<int> move_cols = {0, 1, -1, 0, 0};
  int direction = pieces[piece_id].direction;

  int next_row = row + move_rows[direction];
  int next_col = col + move_cols[direction];
  int next_board = board[next_row][next_col];

  if (next_board == kWhite) {
    map[next_row][next_col].insert(map[next_row][next_col].end(),
                                   map[row][col].begin(), map[row][col].end());

    for (int id : map[row][col]) {
      pieces[id].row = next_row;
      pieces[id].col = next_col;
    }
    map[row][col].clear();
  } else if (next_board == kRed) {
    reverse(map[row][col].begin(), map[row][col].end());
    map[next_row][next_col].insert(map[next_row][next_col].end(),
                                   map[row][col].begin(), map[row][col].end());

    for (int id : map[row][col]) {
      pieces[id].row = next_row;
      pieces[id].col = next_col;
    }
    map[row][col].clear();
  } else {
    direction = GetOppositeDirection(direction);
    pieces[piece_id].direction = direction;

    next_row = row + move_rows[direction];
    next_col = col + move_cols[direction];
    next_board = board[next_row][next_col];

    if (next_board != kBlue)
      MovePiece(piece_id);
  }
}

void Solve() {
  int turn = 1;
  bool isGameOver = false;

  InitMap();
  while (turn <= 1000) {
    for (int i = 1; i <= k; ++i)
      MovePiece(i);

    if (IsGameOver()) {
      isGameOver = true;
      break;
    }

    ++turn;
  }

  if (isGameOver)
    cout << turn << '\n';
  else
    cout << "-1\n";
}

int main() {
  GetInput();
  Solve();
  return 0;
}
