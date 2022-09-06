#include "../2020.hpp"
using namespace std;

#define PI 3.14159265358

class Ship {
 public:
  Ship() : _x{0}, _y{0}, _direction{0} {}
  ~Ship() {}

  size_t navigate(vector<string> &input) {
    for (int i = 0; i < input.size(); i++) {
      executeCommand(input[i]);
    }
    return countDistance();
  }

  void executeCommand(std::string &input) {
    smatch match;
    regex_match(input, match, regex(R"((N|S|E|W|L|R|F)([0-9]+))"));
    string cmd = match[1].str();
    int value = stoi(match[2].str());
    if (cmd == "N") {
      move(0, value);
    } else if (cmd == "S") {
      move(0, -value);
    } else if (cmd == "E") {
      move(value, 0);
    } else if (cmd == "W") {
      move(-value, 0);
    } else if (cmd == "F") {
      moveForward(value);
    } else if (cmd == "L") {
      changeDirection(value);
    } else if (cmd == "R") {
      changeDirection(-value);
    }
  }
  size_t countDistance(void) { return abs(_x) + abs(_y); }

 protected:
  int _x;
  int _y;
  double _direction;

  virtual void move(int x, int y) {
    _x += x;
    _y += y;
  }
  virtual void moveForward(size_t len) {
    move(len * round(cos(_direction)), len * round(sin(_direction)));
  }
  virtual void changeDirection(int angle) { _direction += PI * angle / 180; }
};

class WShip : public Ship {
 public:
  WShip() : _wx{10}, _wy{1} {}
  ~WShip() {}

 private:
  int _wx;
  int _wy;

  void move(int x, int y) override {
    _wx += x;
    _wy += y;
  }
  void moveForward(size_t len) override {
    _x += len * _wx;
    _y += len * _wy;
  }
  void changeDirection(int angle) override {
    float rad = PI * angle / 180;
    int new_wx = _wx * round(cos(rad)) - _wy * round(sin(rad));
    int new_wy = _wy * round(cos(rad)) + _wx * round(sin(rad));
    _wx = new_wx;
    _wy = new_wy;
    //     _direction = atan2(_wy, _wx);
    // size_t len = sqrt (_wy*_wy + _wx * _wx);
    // _direction += PI * angle / 180;
    // _wy = round(len*sin(_direction));
    // _wx = round(len*cos(_direction));
  }
};

const std::string y2020::solve_12a(const std::vector<std::string> &input) {
  Ship ship = Ship();
  return to_string(ship.navigate(const_cast<std::vector<std::string>&>(input)));
}

const std::string y2020::solve_12b(const std::vector<std::string> &input) {
  WShip ship = WShip();
  return to_string(ship.navigate(const_cast<std::vector<std::string>&>(input)));
}