#include <cstdint>
#include <iostream>
#include <vector>
#include <array>

struct Cell {
  char colour;
  int x, y;
};

class Block {
private:
  int x, y; // 0-indexed start/end pos
  unsigned int width, height; // forms a bounding box, counts positive space below and to the right
  unsigned int origin[2];     // perform rotations later
  std::vector<Cell> cells;
  short int rotation_state;
  std::array<std::array<uint16_t, 5>, 4> bitmask_rotations;
  std::array<std::array<uint16_t, 2>, 4> bumps;

public:

  char colour;
  enum class State { Spawn = 0, Right = 1, Reverse = 2, Left = 3 };
  enum class ShiftDirection { Left = 0, Right = 1, Down = 2 };
  enum class RotateDirection { C = 1, CC = -1 };

  // wall kick table defined for SZ,JL,T
  static constexpr int WALL_KICK[4][5][2] = {
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
      {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
      {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}};
  static constexpr int I_WALL_KICK[4][5][2] = {
      {{0, 0}, {-1, 0}, {2, 0}, {-1, 0}, {2, 0}},
      {{-1, 0}, {0, 0}, {0, 0}, {0, 1}, {0, -2}},
      {{-1, 1}, {1, 1}, {-2, 1}, {1, 0}, {-2, 0}},
      {{0, 1}, {0, 1}, {0, 1}, {0, -1}, {0, 2}}};
  static constexpr int O_WALL_KICK[4][1][2] = {
      {{0,0}},
      {{0, -1}},
      {{-1, -1}},
      {{-1, 0}}
  };

  // "true" rotation
  void rotate(const RotateDirection dir);
  void shift(const ShiftDirection dir);
  void display();

  Block(char colour);
  Block(const Block &b);
  Block &operator=(const Block &b);
  Block &operator=(Block &&b) noexcept;
  friend void swap(Block &a, Block &b) noexcept;
  friend class Board;
  friend std::ostream &operator<<(std::ostream &out, Block& b);
  // virtual ~Block() = 0;
};

std::ostream &operator<<(std::ostream &out, Cell &cell);
