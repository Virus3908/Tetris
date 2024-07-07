#include "s21_backend.h"

int s21_game_state(int key) {
  game_t *game = s21_get_game();
  static int cur_step = 0;
  s21_init_next();
  s21_init_brick();
  s21_init_state();
  GameInfo_t *state = s21_get_state();
  if (!state->pause) {
    userInput(key);
    s21_check_pause(key);
    cur_step++;
    if (cur_step > state->speed) {
      cur_step = 0;
      if (!s21_step_down()) game->game_state = s21_attach_and_spawn_next();
    }
    s21_check_lines();
  } else {
    s21_check_pause(key);
  }
  s21_check_level();
  if (!game->game_state) {
    s21_record_score();
    s21_restart_states();
  }
  return game->game_state;
}

// void print_field(int **field) {
//   for (int i = 0; i < H_SIZE; i++) {
//     mvprintw(i, 99, "%d", i);
//     for (int j = 0; j < W_SIZE; j++) {
//       mvprintw(i, j + 100, "%d", field[i][j]);
//     }
//   }
// }

void s21_copy_player(int **field) {
  GameInfo_t *state = s21_get_state();
  curr_brick_t *brick = s21_get_brick();
  s21_copy_matrix(field, state->field, H_SIZE, W_SIZE);
  s21_copy_figure(field, brick->brick, brick->pos_x, brick->pos_y);
}

GameInfo_t *s21_get_state() {
  static GameInfo_t state = {NULL, NULL, 0, 0, 0, 0, 0};
  return &state;
}
curr_brick_t *s21_get_brick() {
  static curr_brick_t brick = {NULL, 0, 0};
  return &brick;
}
curr_brick_t *s21_get_next() {
  static curr_brick_t next = {NULL, 0, 0};
  return &next;
}

game_t *s21_get_game() {
  static game_t game = {0, 1};
  return &game;
}

void s21_init_brick() {
  curr_brick_t *brick = s21_get_brick();
  if (!brick->brick) {
    static int buf_brick[NEXT_SIZE * NEXT_SIZE] = {0};
    static int *ptr_brick[NEXT_SIZE];
    transform(buf_brick, ptr_brick, NEXT_SIZE, NEXT_SIZE);
    brick->brick = ptr_brick;
    s21_init_shape(brick->brick);
    brick->pos_x = 3;
    brick->pos_y = -1;
  }
}

void s21_init_next() {
  curr_brick_t *brick = s21_get_next();
  if (!brick->brick) {
    static int buf_brick[NEXT_SIZE * NEXT_SIZE] = {0};
    static int *ptr_brick[NEXT_SIZE];
    transform(buf_brick, ptr_brick, NEXT_SIZE, NEXT_SIZE);
    brick->brick = ptr_brick;
    s21_init_shape(brick->brick);
    brick->pos_x = 3;
    brick->pos_y = -1;
  }
}

void s21_init_state() {
  GameInfo_t *state = s21_get_state();
  if (!state->field) {
    static int buf_field[W_SIZE * H_SIZE] = {0};
    static int *ptr_buf_field[H_SIZE];
    transform(buf_field, ptr_buf_field, H_SIZE, W_SIZE);
    state->field = ptr_buf_field;

    curr_brick_t *next = s21_get_next();
    state->next = next->brick;

    state->score = 0;
    state->high_score = 0;
    FILE *file;
    if ((file = fopen(SCORE_FILE, "r"))) {
      fscanf(file, "%d", &state->high_score);
      fclose(file);
    }
    state->speed = 1000;
    state->pause = 0;
  }
}

void transform(int *buff, int **matr, int row, int col) {
  for (int i = 0; i < row; i++) {
    matr[i] = buff + i * col;
  }
}

void s21_check_pause(int key) {
  GameInfo_t *state = s21_get_state();
  switch (key) {
    case Pause:
      state->pause = !state->pause;
      break;
  }
}

void s21_copy_figure(int **orig, int **next, int x, int y) {
  for (int i = 0; i < NEXT_SIZE; i++) {
    for (int j = 0; j < NEXT_SIZE; j++) {
      if (i + y >= 0 && j + x >= 0 && next[i][j])
        orig[i + y][j + x] = next[i][j];
    }
  }
}

void s21_fill_zero(int **brick, int row, int column) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column; j++) {
      brick[i][j] = 0;
    }
  }
}

void s21_init_shape(int **brick) {
  int seed = rand() % BRICK_COUNT;
  seed = 3;
  s21_fill_zero(brick, NEXT_SIZE, NEXT_SIZE);
  switch (seed) {
    case 0:  // z
      brick[1][1] = seed + 1;
      brick[1][2] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 1:  // s
      brick[1][2] = seed + 1;
      brick[1][3] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][1] = seed + 1;
      break;
    case 2:  // o
      brick[1][1] = seed + 1;
      brick[1][2] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][1] = seed + 1;
      break;
    case 3:  // l
      brick[0][2] = seed + 1;
      brick[1][2] = seed + 1;
      brick[2][2] = seed + 1;
      brick[3][2] = seed + 1;
      break;
    case 4:  // T
      brick[1][2] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 5:  // L
      brick[1][3] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
    case 6:  // J
      brick[1][1] = seed + 1;
      brick[2][1] = seed + 1;
      brick[2][2] = seed + 1;
      brick[2][3] = seed + 1;
      break;
  }
}

void s21_move(int dir) {
  GameInfo_t *state = s21_get_state();
  curr_brick_t *brick = s21_get_brick();
  if (dir == Left) {
    brick->pos_x -= 1;
    int pos = s21_check_brick_pos(dir);
    if (brick->pos_x + pos < 0 ||
        s21_check_colission(brick->brick, brick->pos_x, brick->pos_y)) {
      brick->pos_x += 1;
    }
  } else if (dir == Right) {
    brick->pos_x += 1;
    int pos = s21_check_brick_pos(dir);
    if (brick->pos_x + pos >= W_SIZE ||
        s21_check_colission(brick->brick, brick->pos_x, brick->pos_y)) {
      brick->pos_x -= 1;
    }
  } else if (dir == Down) {
    state->speed = 0;
  } else {
    state->speed = 10 - state->level;
  }
}

int s21_check_brick_pos(int wall) {
  curr_brick_t *brick = s21_get_brick();
  int res = -1;
  int start;
  int step;
  if (wall == Left) {
    start = 0;
    step = 1;
  } else {
    start = 4;
    step = -1;
  }
  for (int j = start; res < 0 && j * step < NEXT_SIZE - start; j += step) {
    for (int i = 0; res < 0 && i < NEXT_SIZE; i++) {
      if (brick->brick[i][j]) res = j;
    }
  }
  return res;
}

void s21_action() {
  curr_brick_t *brick = s21_get_brick();
  int buf_brick[NEXT_SIZE * NEXT_SIZE] = {0};
  int *buff[NEXT_SIZE];
  transform(buf_brick, buff, NEXT_SIZE, NEXT_SIZE);
  s21_copy_matrix(buff, brick->brick, NEXT_SIZE, NEXT_SIZE);
  for (int i = 0; i < NEXT_SIZE; i++) {
    for (int j = i; j < NEXT_SIZE; j++) {
      int stash = buff[i][j];
      buff[i][j] = buff[j][i];
      buff[j][i] = stash;
    }
  }

  for (int i = 0; buff[2][2] != 3 && buff[2][2] != 4 && i < NEXT_SIZE; i++) {
    for (int j = 0; j < NEXT_SIZE / 2; j++) {
      int stash = buff[i][j];
      buff[i][j] = buff[i][NEXT_SIZE - 1 - j];
      buff[i][NEXT_SIZE - 1 - j] = stash;
    }
  }
  if (!s21_check_colission(buff, brick->pos_x, brick->pos_y)) {
    s21_fill_zero(brick->brick, NEXT_SIZE, NEXT_SIZE);
    s21_copy_figure(brick->brick, buff, 0, 0);
    int pos_left = s21_check_brick_pos(Left);
    int pos_right = s21_check_brick_pos(Right);
    while (brick->pos_x + pos_left < 0) {
      brick->pos_x += 1;
    }
    while (brick->pos_x + pos_right >= W_SIZE) {
      brick->pos_x -= 1;
    }
  }
}

void s21_copy_matrix(int **dir, int **source, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      dir[i][j] = source[i][j];
    }
  }
}

int s21_step_down() {
  int res_move = 1;
  curr_brick_t *brick = s21_get_brick();
  brick->pos_y += 1;
  if (s21_check_colission(brick->brick, brick->pos_x, brick->pos_y)) {
    brick->pos_y -= 1;
    res_move = 0;
  }
  return res_move;
}

int s21_check_colission(int **brick, int pos_x, int pos_y) {
  int res = 0;
  GameInfo_t *state = s21_get_state();
  for (int i = 0; i < NEXT_SIZE && !res; i++) {
    for (int j = 0; j < NEXT_SIZE && !res; j++) {
      if (brick[i][j] && i + pos_y >= H_SIZE) {
        res = 1;
      }
    }
  }
  for (int i = 0; i < H_SIZE && !res; i++) {
    for (int j = 0; j < W_SIZE && !res; j++) {
      res = s21_check_colission_with_field(j - pos_x, i - pos_y,
                                           state->field[i][j], brick);
    }
  }
  return res;
}

int s21_check_colission_with_field(int pos_x, int pos_y, int cel, int **brick) {
  int res = 0;
  for (int i = 0; i < NEXT_SIZE && !res; i++) {
    for (int j = 0; j < NEXT_SIZE && !res; j++) {
      if (cel && brick[i][j] && pos_x == j && pos_y == i) {
        res = 1;
      }
    }
  }
  return res;
}

int s21_attach_and_spawn_next() {
  int game_state = 1;
  GameInfo_t *state = s21_get_state();
  curr_brick_t *brick = s21_get_brick();
  curr_brick_t *next = s21_get_next();
  s21_copy_figure(state->field, brick->brick, brick->pos_x, brick->pos_y);
  s21_copy_matrix(brick->brick, next->brick, NEXT_SIZE, NEXT_SIZE);
  s21_init_shape(next->brick);
  brick->pos_x = next->pos_x;
  brick->pos_y = next->pos_y;
  state->next = next->brick;
  game_state = !s21_check_colission(brick->brick, brick->pos_x, brick->pos_y);
  return game_state;
}

void s21_record_score() {
  GameInfo_t *state = s21_get_state();
  FILE *file;
  file = fopen(SCORE_FILE, "w+");
  fprintf(file, "%d", state->high_score);
  fclose(file);
}

void s21_restart_states() {
  GameInfo_t *state = s21_get_state();
  curr_brick_t *brick = s21_get_brick();
  curr_brick_t *next = s21_get_next();
  s21_fill_zero(state->field, H_SIZE, W_SIZE);
  s21_fill_zero(brick->brick, NEXT_SIZE, NEXT_SIZE);
  s21_fill_zero(next->brick, NEXT_SIZE, NEXT_SIZE);
  state->field = NULL;
  brick->brick = NULL;
  next->brick = NULL;
  s21_init_next();
  s21_init_brick();
  s21_init_state();
}

void s21_check_lines() {
  GameInfo_t *state = s21_get_state();
  int num_rows = 0;
  for (int i = 0; i < H_SIZE; i++) {
    int row_full = 1;
    for (int j = 0; row_full && j < W_SIZE; j++) {
      row_full = state->field[i][j];
    }
    if (row_full) {
      s21_move_field_down(i);
      num_rows++;
    }
  }
  while (num_rows) {
    num_rows--;
    state->score += pow(2, num_rows) * 100;
  }
  if (state->score > state->high_score) {
    state->high_score = state->score;
  }
}

void s21_move_field_down(int row) {
  GameInfo_t *state = s21_get_state();
  for (int i = 0; i < W_SIZE; i++) {
    for (int j = row; j >= 0; j--) {
      if (j == 0) {
        state->field[j][i] = 0;
      } else {
        state->field[j][i] = state->field[j - 1][i];
      }
    }
  }
}

void s21_check_level() {
  GameInfo_t *state = s21_get_state();
  state->level = state->score / 600;
  if (state->level > 10) {
    state->level = 10;
  }
}