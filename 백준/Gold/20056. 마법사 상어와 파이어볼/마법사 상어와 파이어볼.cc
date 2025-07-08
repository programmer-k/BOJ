#include <iostream>
#include <vector>
using namespace std;

struct FireBall {
  int m;
  int s;
  int d;
};

int n, m, k;
vector<vector<vector<FireBall>>> map(50, vector<vector<FireBall>>(50));

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int r, c, m, s, d;
    cin >> r >> c >> m >> s >> d;
    map[r - 1][c - 1].push_back({ m, s, d });
  }
}

void MoveFireBalls() {
  vector<int> move_rows = { -1, -1, 0, 1, 1, 1, 0, -1 };
  vector<int> move_cols = { 0, 1, 1, 1, 0, -1, -1, -1 };
  vector<vector<vector<FireBall>>> new_map(n, vector<vector<FireBall>>(n));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (const FireBall& ball : map[i][j]) {
        int new_row = (i + move_rows[ball.d] * ball.s + n * 1000) % n;
        int new_col = (j + move_cols[ball.d] * ball.s + n * 1000) % n;
        new_map[new_row][new_col].push_back(ball);
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (ssize(new_map[i][j]) > 1) {
        int total_mass = 0;
        int total_speed = 0;
        bool all_odd = true;
        bool all_even = true;
        
        for (const FireBall& ball : new_map[i][j]) {
          total_mass += ball.m;
          total_speed += ball.s;

          if (ball.d % 2 == 0)
            all_odd = false;
          else
            all_even = false;
        }

        vector<int> new_directions;
        if (all_odd || all_even) {
          new_directions.push_back(0);
          new_directions.push_back(2);
          new_directions.push_back(4);
          new_directions.push_back(6);
        } else {
          new_directions.push_back(1);
          new_directions.push_back(3);
          new_directions.push_back(5);
          new_directions.push_back(7);
        }

        int size = ssize(new_map[i][j]);
        int new_mass = total_mass / 5;
        new_map[i][j].clear();

        if (new_mass > 0) {
          for (int k = 0; k < 4; ++k) {
            int new_speed = total_speed / size;
            new_map[i][j].push_back({ new_mass, new_speed, new_directions[k] });
          }
        }
      }
    }
  }

  map = new_map;
}

int GetTotalMassForAllFireBalls() {
  int total_mass = 0;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (const FireBall& ball : map[i][j]) {
        total_mass += ball.m;
      }
    }
  }
  return total_mass;
}

void Solve() {
  for (int i = 0; i < k; ++i)
    MoveFireBalls();

  cout << GetTotalMassForAllFireBalls() << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}