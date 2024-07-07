/// @mainpage header.h
/// @file header.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-07-07
///
/// @copyright Copyright (c) 2024

#ifndef S21_MAIN_H
#define S21_MAIN_H

/// @brief Перечисление, содержащие в себе все возможные действия, которые может
/// совершить игрок
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/// @brief Структура игрового состояния
/// @param field Двумерный массив поля
/// @param next Двумерный массив след фигуры
/// @param score Счет игры
/// @param high_score Максимальный рекорд
/// @param level Нынешний уровень
/// @param speed Ныняшняя скорость
/// @param pause Пауза игры
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

/// @brief Структура с переменными конечного автомата
/// @param game_state Эта переменная отвечат за то, должен ли выполнятся игровой
/// цикл
/// @param play Эта переменная говорит о завершении программы
typedef struct {
  int game_state;
  int play;
} game_t;

/// @brief Проверка ввода с клавиатуры и применение необходимой функции к игре
/// @param action Действие, которое совершил игрок
void userInput(int action);

/// @brief Получаем состояние игры в данный момент, необходимо для отрисовки
/// @return На выходе получаем копию игрового состояния, куда записано положение
/// фигуры игрока на поле
GameInfo_t updateCurrentState();

#include "./brick_game/tetris/s21_backend.h"
#include "./gui/cli/s21_frontend.h"

#endif