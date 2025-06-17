#include "../include/block.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <utility>

Block::Block(char colour)
    : x{3}, y{0}, rotation_state{0}, bitmask_rotations{}, bumps{}, colour{colour} {
  Cell t1, t2, t3, t4;
  switch (colour) {
  case 'L': {
    this->width = 3;
    this->height = 2;
    this->origin[0] = this->origin[1] = 1;

    // construct L block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 2, 1};
    t4 = {colour, 2, 0};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    // compute all transformation bitmasks
    std::array<uint16_t, 5> L0 = {0b0010000000, 0b1110000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> L1 = {0b0100000000, 0b0100000000, 0b0110000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> L2 = {0b0000000000, 0b1110000000, 0b1000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> L3 = {0b1100000000, 0b0100000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    bitmask_rotations[0] = L0;
    bitmask_rotations[1] = L1;
    bitmask_rotations[2] = L2;
    bitmask_rotations[3] = L3;
    std::array<uint16_t, 2> b0 = {0, 0};
    std::array<uint16_t, 2> b1 = {1, 0};
    std::array<uint16_t, 2> b2 = {0, 1};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b0;
    break;
  }
  case 'J': {
    this->width = 3;
    this->height = 2;
    this->origin[0] = this->origin[1] = 1;

    // construct J block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 2, 1};
    t4 = {colour, 0, 0};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    // compute all transformation bitmasks
    std::array<uint16_t, 5> J0 = {0b1000000000, 0b1110000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> J1 = {0b0110000000, 0b0100000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> J2 = {0b0000000000, 0b1110000000, 0b0010000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> J3 = {0b0100000000, 0b0100000000, 0b1100000000, 0b0000000000,
                                  0b0000000000};
    bitmask_rotations[0] = J0;
    bitmask_rotations[1] = J1;
    bitmask_rotations[2] = J2;
    bitmask_rotations[3] = J3;
    std::array<uint16_t, 2> b0 = {0, 0};
    std::array<uint16_t, 2> b1 = {1, 0};
    std::array<uint16_t, 2> b2 = {0, 1};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b0;
    break;
  }
  case 'S': {
    this->width = 3;
    this->height = 2;
    this->origin[0] = this->origin[1] = 1;

    // construct S block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 1, 0};
    t4 = {colour, 2, 0};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    std::array<uint16_t, 5> S0 = {0b0110000000, 0b1100000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> S1 = {0b0100000000, 0b0110000000, 0b0010000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> S2 = {0b0000000000, 0b0110000000, 0b1100000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> S3 = {0b1000000000, 0b1100000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    bitmask_rotations[0] = S0;
    bitmask_rotations[1] = S1;
    bitmask_rotations[2] = S2;
    bitmask_rotations[3] = S3;
    std::array<uint16_t, 2> b0 = {0, 0};
    std::array<uint16_t, 2> b1 = {1, 0};
    std::array<uint16_t, 2> b2 = {0, 1};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b0;
    break;
  }
  case 'Z': {
    this->width = 3;
    this->height = 2;
    this->origin[0] = this->origin[1] = 1;

    // construct Z block
    t1 = {colour, 0, 0};
    t2 = {colour, 1, 0};
    t3 = {colour, 1, 1};
    t4 = {colour, 2, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    std::array<uint16_t, 5> Z0 = {0b1100000000, 0b0110000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> Z1 = {0b0010000000, 0b0110000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> Z2 = {0b0000000000, 0b1100000000, 0b0110000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> Z3 = {0b0100000000, 0b1100000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    bitmask_rotations[0] = Z0;
    bitmask_rotations[1] = Z1;
    bitmask_rotations[2] = Z2;
    bitmask_rotations[3] = Z3;
    std::array<uint16_t, 2> b0 = {0, 0};
    std::array<uint16_t, 2> b1 = {1, 0};
    std::array<uint16_t, 2> b2 = {0, 1};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b0;
    break;
  }
  case 'I': {
    this->x = 2; // special case, this starts I piece centered in board
    this->width = 4;
    this->height = 1;
    this->origin[0] = this->origin[1] = 2;

    // construct I block
    t1 = {colour, 1, 2};
    t2 = {colour, 2, 2};
    t3 = {colour, 3, 2};
    t4 = {colour, 4, 2};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    std::array<uint16_t, 5> I0 = {0b0000000000, 0b0000000000, 0b0111100000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> I1 = {0b0000000000, 0b0010000000, 0b0010000000, 0b0010000000,
                                  0b0010000000};
    std::array<uint16_t, 5> I2 = {0b0000000000, 0b0000000000, 0b1111000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> I3 = {0b0010000000, 0b0010000000, 0b0010000000, 0b0010000000,
                                  0b0000000000};
    bitmask_rotations[0] = I0;
    bitmask_rotations[1] = I1;
    bitmask_rotations[2] = I2;
    bitmask_rotations[3] = I3;

    std::array<uint16_t, 2> b0 = {1, 2};
    std::array<uint16_t, 2> b1 = {2, 1};
    std::array<uint16_t, 2> b2 = {0, 2};
    std::array<uint16_t, 2> b3 = {2, 0};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b3;
    break;
  }
  case 'O': {
    this->width = 2;
    this->height = 2;
    this->origin[0] = 2;
    this->origin[1] = 1;

    // construct O block
    t1 = {colour, 1, 0};
    t2 = {colour, 2, 0};
    t3 = {colour, 1, 1};
    t4 = {colour, 2, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    std::array<uint16_t, 5> O0 = {0b0110000000, 0b0110000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> O1 = {0b0000000000, 0b0110000000, 0b0110000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> O2 = {0b0000000000, 0b1100000000, 0b1100000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> O3 = {0b1100000000, 0b1100000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    bitmask_rotations[0] = O0;
    bitmask_rotations[1] = O1;
    bitmask_rotations[2] = O2;
    bitmask_rotations[3] = O3;

    std::array<uint16_t, 2> b0 = {1, 0};
    std::array<uint16_t, 2> b1 = {1, 1};
    std::array<uint16_t, 2> b2 = {0, 1};
    std::array<uint16_t, 2> b3 = {0, 0};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b3;
    break;
  }
  case 'T': {
    this->width = 3;
    this->height = 2;
    this->origin[0] = this->origin[1] = 1;

    // construct T block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 1, 0};
    t4 = {colour, 2, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});

    std::array<uint16_t, 5> T0 = {0b0100000000, 0b1110000000, 0b0000000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> T1 = {0b0100000000, 0b0110000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> T2 = {0b0000000000, 0b1110000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    std::array<uint16_t, 5> T3 = {0b0100000000, 0b1100000000, 0b0100000000, 0b0000000000,
                                  0b0000000000};
    bitmask_rotations[0] = T0;
    bitmask_rotations[1] = T1;
    bitmask_rotations[2] = T2;
    bitmask_rotations[3] = T3;
    std::array<uint16_t, 2> b0 = {0, 0};
    std::array<uint16_t, 2> b1 = {1, 0};
    std::array<uint16_t, 2> b2 = {0, 1};
    bumps[0] = b0;
    bumps[1] = b1;
    bumps[2] = b2;
    bumps[3] = b0;
    break;
  }
  }
}

Block::Block(const Block &b)
    : x{b.x}, y{b.y}, width{b.width}, height{b.height}, cells{b.cells},
      rotation_state{b.rotation_state}, colour{b.colour}, bitmask_rotations{b.bitmask_rotations},
      bumps{b.bumps} {
  origin[0] = b.origin[0];
  origin[1] = b.origin[1];
}

Block &Block::operator=(const Block &b) {
  Block new_block{b};
  swap(*this, new_block);

  return *this;
}

Block &Block::operator=(Block &&b) noexcept {
  swap(*this, b);
  return *this;
}

void swap(Block &a, Block &b) noexcept {
  std::swap(a.x, b.x);
  std::swap(a.y, b.y);
  std::swap(a.width, b.width);
  std::swap(a.height, b.height);
  std::swap(a.cells, b.cells);
  std::swap(a.rotation_state, b.rotation_state);
  std::swap(a.bitmask_rotations, b.bitmask_rotations);
  std::swap(a.bumps, b.bumps);
  std::swap(a.colour, b.colour);
  a.origin[0] = b.origin[0];
  a.origin[1] = b.origin[1];
}

void Block::rotate(Block::RotateDirection dir) {
  // int offsetX = origin[0];
  // int offsetY = origin[1];

  // not needed for now since we are using bitmasks
  // for (auto &cell : cells) {
  //   // get coordinates relative to their rotation origin, and perform rotation
  //   int newX = cell.x - offsetX;
  //   int newY = cell.y - offsetY;
  //   cell.x = newY;
  //   cell.y = newX;
  //   if (dir == Block::RotateDirection::C) {
  //     cell.x *= -1;
  //   } else if (dir == Block::RotateDirection::CC) {
  //     cell.y *= -1;
  //   }
  //   // convert back to Bottom-Right (BR) format
  //   cell.x += offsetX;
  //   cell.y += offsetY;
  // }
  // update width and height
  std::swap(width, height);
}

void Block::shift(Block::ShiftDirection dir) {
  switch (dir) {
  case Block::ShiftDirection::Left:
    this->x -= 1;
    break;
  case Block::ShiftDirection::Right:
    this->x += 1;
    break;
  case Block::ShiftDirection::Down:
    this->y += 1;
    break;
  }
}

// for text-game only
void Block::display() {
  for (int i = 0; i < this->height; i++) {
    for (int j = 0; j < this->width; j++) {
      bool printed = false;
      for (auto cell : cells) {
        if (cell.y == i && cell.x == j) {
          std::cout << cell.colour;
          printed = true;
        }
      }
      if (!printed)
        std::cout << " ";
    }
    std::cout << std::endl;
  }
}

std::ostream &operator<<(std::ostream &out, Cell &cell) {
  out << '[' << cell.x << ", " << cell.y << ']' << std::endl;
  return out;
}

std::ostream &operator<<(std::ostream &out, Block &b) {
  out << '[' << b.x << ", " << b.y << ']' << std::endl;

  return out;
}
