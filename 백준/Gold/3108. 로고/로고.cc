#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct Rectangle {
  int x1;
  int y1;
  int x2;
  int y2;
};

struct Pos {
  int x;
  int y;
  int direction;
};

int n, answer;
vector<Rectangle> rectangles;
bool coordinates[1'001][1'001][4];
bool visited[1'001][1'001][4];

void GetInput() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

  cin >> n;

  rectangles.resize(n);
  for (int i = 0; i < n; ++i)
    cin >> rectangles[i].x1 >> rectangles[i].y1 >> rectangles[i].x2 >>
        rectangles[i].y2;
}

void Paint(const Rectangle& rectangle) {
  int min_x = min(rectangle.x1, rectangle.x2) + 500;
  int min_y = min(rectangle.y1, rectangle.y2) + 500;
  int max_x = max(rectangle.x1, rectangle.x2) + 500;
  int max_y = max(rectangle.y1, rectangle.y2) + 500;

  coordinates[min_x][min_y][RIGHT] = true;
  coordinates[min_x][max_y][RIGHT] = true;

  for (int x = min_x + 1; x < max_x; ++x) {
    coordinates[x][min_y][LEFT] = true;
    coordinates[x][min_y][RIGHT] = true;
    coordinates[x][max_y][LEFT] = true;
    coordinates[x][max_y][RIGHT] = true;
  }

  coordinates[max_x][min_y][LEFT] = true;
  coordinates[max_x][max_y][LEFT] = true;

  coordinates[min_x][min_y][UP] = true;
  coordinates[max_x][min_y][UP] = true;

  for (int y = min_y + 1; y < max_y; ++y) {
    coordinates[min_x][y][UP] = true;
    coordinates[min_x][y][DOWN] = true;
    coordinates[max_x][y][UP] = true;
    coordinates[max_x][y][DOWN] = true;
  }

  coordinates[min_x][max_y][DOWN] = true;
  coordinates[max_x][max_y][DOWN] = true;
}

Pos GetOpposite(Pos pos) {
  int next_x = pos.x;
  int next_y = pos.y;
  int direction;

  if (pos.direction == UP) {
    ++next_y;
    direction = DOWN;
  } else if (pos.direction == DOWN) {
    --next_y;
    direction = UP;
  } else if (pos.direction == LEFT) {
    --next_x;
    direction = RIGHT;
  } else {
    ++next_x;
    direction = LEFT;
  }

  return {next_x, next_y, direction};
}

void Push(queue<Pos>& q, int x, int y) {
  for (int i = 0; i < 4; ++i) {
    if (coordinates[x][y][i] && !visited[x][y][i]) {
      q.push({x, y, i});
      visited[x][y][i] = true;
      Pos pos = GetOpposite({x, y, i});
      visited[pos.x][pos.y][pos.direction] = true;
    }
  }
}

void BreadthFirstSearch(Pos start) {
  queue<Pos> q;
  q.push(start);
  visited[start.x][start.y][start.direction] = true;
  Pos opposite = GetOpposite(start);
  visited[opposite.x][opposite.y][opposite.direction] = true;

  while (!q.empty()) {
    Pos p = q.front();
    int x = p.x;
    int y = p.y;
    int direction = p.direction;
    q.pop();

    int next_x = x;
    int next_y = y;

    if (direction == UP)
      ++next_y;
    else if (direction == DOWN)
      --next_y;
    else if (direction == LEFT)
      --next_x;
    else
      ++next_x;

    Push(q, x, y);
    Push(q, next_x, next_y);
  }

  ++answer;
}

void Solve() {
  for (const Rectangle& rectangle : rectangles)
    Paint(rectangle);

  for (int i = 0; i <= 1'000; ++i)
    for (int j = 0; j <= 1'000; ++j)
      for (int k = 0; k < 4; ++k)
        if (coordinates[i][j][k] && !visited[i][j][k])
          BreadthFirstSearch({i, j, k});

  if (coordinates[500][500][0] || coordinates[500][500][1] ||
      coordinates[500][500][2] || coordinates[500][500][3])
    cout << answer - 1 << '\n';
  else
    cout << answer << '\n';
}

int main() {
  GetInput();
  Solve();
  return 0;
}
