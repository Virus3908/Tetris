#include "header.h"

GameInfo_t updateCurrentState() {
  GameInfo_t *state = s21_get_state();
  GameInfo_t buff = {NULL, NULL, 0, 0, 0, 0, 0};
  buff.next = state->next;
  buff.level = state->level;
  buff.speed = state->speed;
  buff.pause = state->pause;
  buff.high_score = state->high_score;
  buff.score = state->score;
  static int field[W_SIZE * H_SIZE] = {0};
  static int *ptr_field[H_SIZE];
  transform(field, ptr_field, H_SIZE, W_SIZE);
  buff.field = ptr_field;
  s21_copy_player(buff.field);
  //   print_field(buff.field);
  return buff;
}

void userInput(int action) {
  game_t *game = s21_get_game();
  if (game->game_state) {
    switch (action) {
      case Left:
        s21_move(Left);
        break;
      case Right:
        s21_move(Right);
        break;
      case Action:
        s21_action();
        break;
      case Down:
        s21_move(Down);
        break;
      case Terminate:
        game->play = 0;
        game->game_state = 0;
        break;
      default:
        s21_move(action);
        break;
    }
  } else {
    switch (action) {
      case Terminate:
        game->play = 0;
        game->game_state = 0;
        break;
      case Start:
        game->game_state = 1;
        break;
    }
  }
}