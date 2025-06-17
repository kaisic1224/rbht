#include "../include/blockbag.hpp"
#include <random>

BlockBag::BlockBag() : dev{random_device{}}, rng{dev()} {
  queue.reserve(BlockBag::NUM_BLOCKS);
  this->reset_bag();
}

void BlockBag::reset_bag() {
  // refill indexes
  for (int i = 0; i < BlockBag::NUM_BLOCKS; i++) {
    queue.emplace_back(i);
  }
}

Block BlockBag::get_next_block() {
  uniform_int_distribution<std::mt19937::result_type> dist(0, queue.size() - 1);
  int index = dist(rng);
  int block_id = queue[index];

  queue.erase(queue.begin() + index);

  if (queue.size() == 0)
    this->reset_bag();

  switch (block_id) {
  case 0:
    return Block('L');
  case 1:
    return Block('J');
  case 2:
    return Block('S');
  case 3:
    return Block('Z');
  case 4:
    return Block('T');
  case 5:
    return Block('I');
  default: // case 6:
    return Block('O');
  }
}
