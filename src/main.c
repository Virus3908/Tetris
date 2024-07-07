#include "header.h"

int main() {
  s21_init_frontend();
  game_t *game = s21_get_game();
  GameInfo_t state;
  int key = 0;
  while (game->play) {
    key = s21_get_key();
    userInput(key);
    while (game->game_state) {
      key = s21_get_key();
      game->game_state = s21_game_state(key);
      state = updateCurrentState();
      s21_print_game(state, game->game_state);
    }
    s21_print_game(state, game->game_state);
  }
  endwin();
  return 0;
}