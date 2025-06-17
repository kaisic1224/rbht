#include "board.hpp"

class Game {
private:
  int score = 0;
  int lines_cleared = 0;
  Board player1;
  Board player2;

  // manage networking here

public:
  Game();
};
