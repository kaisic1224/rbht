#include <vector>

struct Cell {
  char colour;
  int x, y;
};

class Block {
private:
  int x, y;
  int width, height; // forms a bounding box
  std::vector<Cell> cells;

public:
  const int ROTATE_DIRS[2] = {0, 1};   // C, CC
  const int SHIFT_DIRS[3] = {0, 1, 2}; // LEFT, RIGHT, DOWN
  const int WALL_KICK[8][5][2] = {};

  bool rotate(int dir);
  bool shift(int dir);
  void display();

  Block(char colour);
  // virtual ~Block() = 0;
};
