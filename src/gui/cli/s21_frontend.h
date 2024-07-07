
/// @mainpage
/// @file s21_frontend.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-07-07
///
/// @copyright Copyright (c) 2024

#ifndef S21_GUI_H
#define S21_GUI_H

#include <ncurses.h>
#include <time.h>

#include "../../header.h"

/// Размер основоного окна по оси У
#define MAIN_WIN_Y H_SIZE + 5

/// Размер основоного окна по оси Х
#define MAIN_WIN_X W_SIZE * 3 + 4

/// Размер игрового поля по оси У
#define FIELD_WIN_Y H_SIZE + 2

/// Размер игрового поля по оси Х
#define FIELD_WIN_X W_SIZE * 2 + 2

/// Положения игрового поля относительно основного окна по У
#define POS_FIELD_Y 2

/// Положения игрового поля относительно основного окна по Х
#define POS_FIELD_X 1

///  Размер поля след фигуры по оси У
#define NEXT_WIN_Y NEXT_SIZE

///  Размер поля след фигуры по оси Х
#define NEXT_WIN_X (NEXT_SIZE) * 2 + 1

/// Положения поля след фигуры относительно основного окна по У
#define POS_NEXT_Y 2

/// Положения поля след фигуры относительно основного окна по Х
#define POS_NEXT_X W_SIZE * 2 + 3

/// Значок левой половинки квадратика фигуры
#define SIGN_LEFT ACS_CKBOARD

/// Значок правой половинки квадратика фигуры
#define SIGN_RIGHT ACS_CKBOARD

/// @brief Структура для создания полей отрисовк с координатами левого верхнего
/// угла и длиной и шириной экрана
/// @param sx Отступ по оси х
/// @param sy Отступ по оси у
/// @param x Ширина по оси х
/// @param y Высота по оси у
typedef struct {
  int sx;
  int sy;
  int x;
  int y;
} win_t;

///@brief Функция инициализирующая Ncurses и рисующая рамки полей
void s21_init_frontend();

/// @brief Функция по отрисоки игрового состояния
/// @param state Структура игрового состояния
/// @param game_state Переменная отвечающая за то идет игра или нет
void s21_print_game(GameInfo_t state, int game_state);

/// @brief Функция по отрисовке счета и наибольшего счета
/// @param state Структура игрового состояния
void s21_print_score(GameInfo_t state);

/// @brief Функция по отрисовке уровня, скорости и паузы
/// @param state Структура игрового состояния
void s21_print_game_stat(GameInfo_t state);

/// @brief Функция заполняющее поле нулями
/// @param win Структура поля
void s21_free_field(win_t win);

/// @brief Функция по заполнения поля состоянием
/// @param field Двумерный массив, который необходимо отрисовать
/// @param win Структура поля
void s21_fill_field(int **field, win_t win);

/// @brief Функция по отрисовке прямоугольника поля
/// @param top_y Координата верха по у
/// @param bottom_y Координата низа по У
/// @param left_x Координата левого края по Х
/// @param right_x Координата правого края по Х
void s21_print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

/// @brief Функция по получению ввода игрока
/// @return Возвращает действие, которое совершил игрок
int s21_get_key();

#endif