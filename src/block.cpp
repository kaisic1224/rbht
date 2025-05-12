#include "../include/block.hpp"
#include <iostream>

Block::Block(char colour) : x{0}, y{0} {
  Cell t1, t2, t3, t4;
  switch (colour) {
  case 'L':
    this->width = 3;
    this->height = 3;

    // construct L block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 2, 1};
    t4 = {colour, 2, 0};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  case 'J':
    this->width = 3;
    this->height = 3;

    // construct J block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 2, 1};
    t4 = {colour, 0, 0};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  case 'S':
    this->width = 3;
    this->height = 3;

    // construct S block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 1, 0};
    t4 = {colour, 2, 0};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  case 'Z':
    this->width = 3;
    this->height = 3;


    // construct Z block
    t1 = {colour, 0, 0};
    t2 = {colour, 1, 0};
    t3 = {colour, 1, 1};
    t4 = {colour, 2, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  case 'I':
    this->width = 4;
    this->height = 4;

    // construct I block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 2, 1};
    t4 = {colour, 3, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  case 'O':
    this->width = 4;
    this->height = 4;

    // construct O block
    t1 = {colour, 1, 0};
    t2 = {colour, 2, 0};
    t3 = {colour, 1, 1};
    t4 = {colour, 2, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  case 'T':
    this->width = 3;
    this->height = 3;

    // construct T block
    t1 = {colour, 0, 1};
    t2 = {colour, 1, 1};
    t3 = {colour, 1, 0};
    t4 = {colour, 2, 1};
    cells.insert(cells.end(), {t1, t2, t3, t4});
    break;
  }
}

bool Block::rotate(int dir) {}

bool Block::shift(int dir) {}


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
            if (!printed) std::cout << " ";
        }
        std::cout << std::endl;
    }
}
