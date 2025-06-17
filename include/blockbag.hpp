#include "block.hpp"
#include <random>
#include <vector>

using namespace std;

class BlockBag {
private:
  static const int NUM_BLOCKS = 7;
  vector<int> queue;

  // random number generation
  random_device dev;
  mt19937 rng;

  void reset_bag();
public:
  BlockBag();
  //~BlockBag();

  Block get_next_block();
};
