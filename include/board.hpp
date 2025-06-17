#include "blockbag.hpp"
#include <cstdint>
#include <deque>

using namespace std;

class Board {
private:
  // use for all layout purposes, store rows as bitwise
  uint16_t cells[20]{0b0000000000};
  // need to preserve colouring
  char v_cells[20][10]{};

  // block_bag, a hm of all the posisble remaining blocks
  // queue, a 5-block window of the board's next pieces
  // hold, a block the board will hold
  // current, the current block that can be rotated/shifted/held
  BlockBag block_bag;
  deque<Block> queue{};
  Block hold;

  // keep track of lines cleared/lines received
  int line_recv;
  int line_send;


  // uses current block and checks for collision
  bool check_collision();

public:
  Board();
  // ~Board();

  Block current;
  // player interaction commands
  // move, drop, rotate, hold
  bool move_block(Block::ShiftDirection dir);
  bool rotate_block(Block::RotateDirection dir);
  bool drop_block();
  bool hold_block();

  void display();
};
