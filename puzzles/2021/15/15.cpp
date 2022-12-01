// Puzzle is available at https://adventofcode.com/2021/day/15
// Keywords: shortest path
#include "../2021.hpp"
#include "../../../src/utils.hpp"
using namespace std;

struct Point {
  Point(): x{0}, y{0} {}
  Point(int x, int y) : x{x}, y{y} {}
  int x;
  int y;
  friend bool operator==(const Point &p1, const Point &p2) {
    return (p1.x == p2.x) && (p1.y == p2.y);
  }
};

static vector<vector<size_t>> generateFullMap(vector<vector<size_t>> &maze) {
  int xMax = maze[0].size();
  int yMax = maze.size();
  vector<vector<size_t>> newMap(5*yMax, vector<size_t> (5* xMax, 0));

  for (int i = 0; i < newMap.size(); i++) {
    for (int j = 0; j < newMap[0].size(); j++) {
      size_t val = maze[i%yMax][j%xMax] + i/yMax + j/xMax;
      if (val > 9) {
        val -= 9;
      } 
      newMap[i][j] = val;
    }
  }
  return newMap;
}


static Point getPointWithMinF(const vector<Point> &points, const vector<vector<size_t>> &f) {
  size_t fMin = f[points[0].x][points[0].y];
  size_t iMin = 0;
  for (int i = 1; i < points.size(); i++){
    size_t fCurrent = f[points[i].x][points[i].y];
    if (fCurrent < fMin) {
      fMin = fCurrent;
      iMin = i;
    }
  }
  return points[iMin];
}

static size_t Astar(vector<vector<size_t>> &maze, Point start, Point end){
  vector<Point> queue;
  vector<Point> passed;
  queue.push_back(start);  

  int xMax = maze[0].size();
  int yMax = maze.size();

  vector<vector<size_t>> g(yMax, vector<size_t> (xMax, 0));
  vector<vector<size_t>> f(yMax, vector<size_t> (xMax, 0));

  auto h = [xMax, yMax](int x, int y) {  
    // return (xMax - x - 1)+(yMax - y - 1);
    return 0;
  };
  
  auto getNeighbors = [xMax, yMax](int x, int y) {
    vector<Point> neighbors;
    if (0 < x) {
      neighbors.push_back(Point(x-1, y));
    }
    if (0 < y) {
      neighbors.push_back(Point(x, y-1));
    }
    if (x < xMax - 1) {
      neighbors.push_back(Point(x+1, y));
    }
    if (y < yMax - 1) {
      neighbors.push_back(Point(x, y+1));
    }
    return neighbors;
  };

  g[start.x][start.y] = 0;
  f[start.x][start.y] = g[start.x][start.y] + h(start.x, start.y);
  while (queue.size() != 0) {
    Point current = getPointWithMinF(queue, f);
    if (current == end) {
      break;
    }
    erase(queue, current);
    passed.push_back(current);
    for (auto &neighbor : getNeighbors(current.x, current.y)) {
      size_t score = g[current.x][current.y] + maze[neighbor.x][neighbor.y];
      if ((0 < g[neighbor.x][neighbor.y]) && (g[neighbor.x][neighbor.y]) <= score) {
        continue;
      } else {
        g[neighbor.x][neighbor.y] = score;
        f[neighbor.x][neighbor.y] = score + h(neighbor.x, neighbor.y);
        if (find(queue.begin(), queue.end(), neighbor) == queue.end()) {
          queue.push_back(neighbor);
        }
      }
    }
  }

  return f[end.x][end.y];
}

static vector<vector<size_t>> parseInput(const std::vector<std::string> &input) {
  vector<vector<size_t>> maze;
  for (int i = 0; i < input.size(); i++) {
    vector<size_t> tmp;
    for (int j = 0; j < input[0].size(); j++) {
      tmp.push_back(input[i][j] - '0');
    }
    maze.push_back(tmp);
  }
  return maze;
}

std::string y2021::solve_15a(const std::vector<std::string> &input) {
  auto maze = parseInput(input);
  return to_string(Astar(maze, Point(0, 0), Point(maze[0].size() - 1, maze.size() - 1)));
}

std::string y2021::solve_15b(const std::vector<std::string> &input) {
  auto maze = parseInput(input);
  auto newMap = generateFullMap(maze);
  return to_string(Astar(newMap, Point(0, 0), Point(newMap[0].size() - 1, newMap.size() - 1)));
}
