#include "../include/board.hpp"
#include <bitset>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <utility>

inline enum Block::RotateDirection reverse(Block::RotateDirection dir) {
  if (dir == Block::RotateDirection::C) {
    return Block::RotateDirection::CC;
  } else {
    return Block::RotateDirection::C;
  }
}

Board::Board() : cells{}, v_cells{}, block_bag{}, queue{}, hold{'O'}, current{'O'} {
  for (int i = 0; i < 6; i++) {
    Block next_b = block_bag.get_next_block();
    queue.emplace_back(next_b);
  }
  current = std::move(queue[0]);
  queue.pop_front();
}

bool Board::move_block(Block::ShiftDirection dir) {
  // prebound checks
  if ((current.x <= 0 && current.bumps[current.rotation_state][0] == 0 &&
       dir == Block::ShiftDirection::Left) ||
      (current.x == 0 && current.bumps[current.rotation_state][0] == 1 &&
       dir == Block::ShiftDirection::Left) ||
      ((current.x + current.width == 10) && (current.bumps[current.rotation_state][0] == 0) &&
       dir == Block::ShiftDirection::Right) ||
      (current.x + current.width == 10 && current.bumps[current.rotation_state][0] == 1 &&
       dir == Block::ShiftDirection::Right) ||
      (current.y + current.height - 1 == 19 && dir == Block::ShiftDirection::Down))
    return false;
  // rather than performing a shift, check_collision, then unshift if incorrect,
  // we can just immediately compare
  // Regarding bitmask heights: their bounding box intersects with
  std::array<uint16_t, 5> bitmask = current.bitmask_rotations[current.rotation_state];
  switch (dir) {
  case Block::ShiftDirection::Right: {
    // shift 1 extra to the right, then compare
    for (int i = 0; i < 5; i++) {
      if (current.y + i > 19)
        break;
      uint16_t translated = bitmask[i] >> (current.x + 1);
      if ((translated & cells[current.y + i]) != 0) {
        return false;
      }
    }
    break;
  }
  case Block::ShiftDirection::Left: {
    // shift to current.x left 1 position
    for (int i = 0; i < 5; i++) {
      if (current.y + i > 19)
        break;
      uint16_t translated = 0;
      if (current.x <= 0) {
        translated = bitmask[i] << (-1 * (current.x - 1));
      } else {
        translated = bitmask[i] >> (current.x - 1);
      }
      if ((translated & cells[current.y + i]) != 0) {
        return false;
      }
    }
    break;
  }
  case Block::ShiftDirection::Down: {
    // start from bottom row of height
    for (int i = 5 - 1; i >= 0; i--) {
      if (current.y + i + 1 > 19)
        continue;
      if (((bitmask[i] >> (current.x - current.bumps[current.rotation_state][0])) &
           cells[current.y + i + 1]) != 0) {
        return false;
      }
    }
    break;
  }
  }
  current.shift(dir);
  return true;
}

bool Board::rotate_block(Block::RotateDirection dir) {
  // perform true rotation
  current.rotate(dir);
  // go through wall kick data
  std::vector<std::array<int, 2>> prev_offset{};
  prev_offset.reserve(5);

  // do not update rotation_state if rotation fails
  size_t next_state = (current.rotation_state + static_cast<int>(dir)) % 4;
  // edge case until i find a way to handle more elegantly
  // if (current.colour == 'I' && next_state == 1) {
  //   current.height = 5;
  // } else if (current.colour == 'I' && next_state != 1) {
  //   current.height = 4;
  // }
  if (current.colour == 'O') {
    std::array<int, 2> state{
        Block::O_WALL_KICK[current.rotation_state][0][0] - Block::O_WALL_KICK[next_state][0][0],
        // we are storing inverted
        (Block::O_WALL_KICK[current.rotation_state][0][1] - Block::O_WALL_KICK[next_state][0][1]) *
            -1};
    prev_offset.emplace_back(state);
  } else if (current.colour == 'I') {
    for (int i = 0; i < 5; i++) {
      std::array<int, 2> state{Block::I_WALL_KICK[current.rotation_state][i][0] -
                                   Block::I_WALL_KICK[next_state][i][0],
                               // we are storing inverted
                               (Block::I_WALL_KICK[current.rotation_state][i][1] -
                                Block::I_WALL_KICK[next_state][i][1]) *
                                   -1};
      prev_offset.emplace_back(state);
    }
  } else {
    for (int i = 0; i < 5; i++) {
      std::array<int, 2> state{
          Block::WALL_KICK[current.rotation_state][i][0] - Block::WALL_KICK[next_state][i][0],
          // we are storing inverted
          (Block::WALL_KICK[current.rotation_state][i][1] - Block::WALL_KICK[next_state][i][1]) *
              -1};
      prev_offset.emplace_back(state);
    }
  }
  // check collision, and match first wall kick
  // first go through all cells and add new offset
  std::array<uint16_t, 5> bitmask = current.bitmask_rotations.at(next_state);
  // for each in prev_offset
  for (size_t i = 0; i < prev_offset.size(); i++) {
    // check bitwise masks
    // bound check first
    if (((current.y + prev_offset[i][1]) < 0) || current.y + prev_offset[i][1] >= 19)
      continue;

    // check each row in bitwise mask
    for (int j = 0; j < 5; j++) {
      uint16_t translated = bitmask[j] >> (current.x + prev_offset[i][0]);
      if ((translated & cells[current.y + prev_offset[i][1]]) != 0) {
        current.rotate(reverse(dir));
        return false;
      }
    }
    // first rotation offset works
    current.x += prev_offset[i][0];
    current.y += prev_offset[i][1];
    break;
  }

  current.rotation_state = next_state;
  return true;
}

bool Board::drop_block() {
  // move down as far as possible
  while (move_block(Block::ShiftDirection::Down)) {
    display();
  }

  if (!check_collision())
    return false;

  // update Board
  // for (Cell c : current.cells) {
  //   v_cells[c.y + current.y][c.x + current.x] = 1;
  // }
  // update cells bitmask
  array<uint16_t, 5> bitmask = current.bitmask_rotations[current.rotation_state];
  for (int i = 0; i < 5; i++) {
    if (current.y + i > 19)
      continue;
    int row;
    if (current.x - current.bumps[current.rotation_state][0] < 0) {
      row = cells[current.y + i] |
            (bitmask[i] << -1 * (current.x - current.bumps[current.rotation_state][0]));
    } else {
      row = cells[current.y + i] |
            (bitmask[i] >>
             (current.x - current.bumps[current.rotation_state][0]));
    }
    // cells[current.y + i] = cells[current.y + i] |
    //                        (bitmask[i] >> (current.x - current.bumps[current.rotation_state][0]));
    cells[current.y + i] = row;
  }

  // checking full lines
  for (int read_row = 19; read_row > 0; --read_row) {
    if (!(cells[read_row] ^ 0b1111111111)) {
      int i = read_row;
      while (cells[i] != 0) {
        cells[i] = cells[i - 1];
        i--;
      }
    }
  }

  // add next block
  current = std::move(queue[0]);
  queue.pop_front();

  queue.emplace_back(block_bag.get_next_block());
  return true;
}

void Board::display() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 10; j++) {
      cout << " ";
    }
    cout << endl;
  }
  for (int i = 0; i < 20; i++) {
    cout << "|";
    if (current.y <= i && i <= current.y + current.height) {
      int row;
      if (current.x - current.bumps[current.rotation_state][0] < 0) {
        row = cells[i] | (current.bitmask_rotations[current.rotation_state][i - current.y]
                          << -1 * (current.x - current.bumps[current.rotation_state][0]));
      } else {
        row = cells[i] | (current.bitmask_rotations[current.rotation_state][i - current.y] >>
                          (current.x - current.bumps[current.rotation_state][0]));
      }
      cout << bitset<10>(row);
    } else {
      cout << bitset<10>(cells[i]);
    }
    cout << "|" << endl;
  }
  for (int i = 0; i < 12; i++)
    cout << "=";
  cout << endl;
}

bool Board::check_collision() {
  // assumes current is in a bounded position
  array<uint16_t, 5> bitmask = current.bitmask_rotations[current.rotation_state];
  for (int i = 0; i < 5; i++) {
    if (current.y + i > 19)
      continue;
    // compare each line of bitmask with row shifted right current.x times
    // and with row current.y + i
    uint16_t translated_row = bitmask[i] >> current.x;
    uint16_t compare_to = cells[current.y + i];

    // translated_row & compare_to == 0 - this and will only return 1 if 2
    // bits in the same position are both 1 - meaning there is a collision
    if ((translated_row & compare_to) != 0) {
      return false;
    }
  }
  return true;
}
