/// @mainpage
/// @file s21_backend.h
/// @author machelch
/// @brief
/// @version 1.0
/// @date 2024-07-07
///
/// @copyright Copyright (c) 2024

#ifndef S21_TETRIS_H
#define S21_TETRIS_H

/// Ширина игрового поля
#define W_SIZE 10

/// Высота игрового поля
#define H_SIZE 20

/// Размер массива с Фигурами
#define NEXT_SIZE 5

/// Количество фигур
#define BRICK_COUNT 7

/// Название игры
#define GAME_NAME "Tetris"

/// Путь до файла с рекордами
#define SCORE_FILE "score.txt"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../header.h"

/// @brief Структура игрового кирпичика (тетриса)
/// @param brick Ссылка на двумерный массив с фигурой
/// @param pos_x Положение тетриса по оси х
/// @param pos_y Положение тетриса по оси у
typedef struct {
  int **brick;
  int pos_x;
  int pos_y;
} curr_brick_t;

/// @brief Функция инициализации игрового состояния
void s21_init_state();

/// @brief Функция получения игрового состояния
/// @return Указатель на нынешнее игровое состояние
GameInfo_t *s21_get_state();

/// @brief Функция превращения двумерного массива в массив указателей
/// @param buff Исходный массив размером row * col
/// @param matr Массив указателей row, куда будут записаны указатели на строки
/// @param row Количество строк
/// @param col Количество столбцов
void transform(int *buff, int **matr, int row, int col);

/// @brief Основная игровая функция, которая изменяет структуру игрового
/// состояния
/// @param key Действие, полученное от игрока
/// @return Возвращает значение конечного автомата, продолжаем ли мы игру или
/// нет
int s21_game_state(int key);

/// @brief Функция копирования фигуры, копирует из массива только не нулевые
/// значения
/// @param orig Куда должен быть записан массив
/// @param next Откуда должен быть получен массив
/// @param x Положение массива next относительно массива orig по х
/// @param y Положение массива next относительно массива orig по у
void s21_copy_figure(int **orig, int **next, int x, int y);

/// @brief Функция по проверки, была ли нажата клавиша паузы
/// @param key Действие игрока
void s21_check_pause(int key);

/// @brief Функция по заполнению матрицы нулями
/// @param matrix Указатель на матрицу
/// @param row Кол-во строк
/// @param column Кол-во столбцов
void s21_fill_zero(int **matrix, int row, int column);

/// @brief Функция по записи в массив с фигурой новой фигуры
/// @param brick Указатель на матрицу
void s21_init_shape(int **brick);

/// @brief Функция получение состояния фигуры в данный момент
/// @return Возвращает указатель на структуру фигуры
curr_brick_t *s21_get_brick();

/// @brief Функция инициализации фигуры
void s21_init_brick();

/// @brief Функция инициализации следующей фигуры
void s21_init_next();

/// @brief Функция выполняющая вращение фигуры
void s21_action();

/// @brief Функция выполняющая перемещение в указанном направлении
/// @param dir Направление перемещения
void s21_move(int dir);

/// @brief Копирует матрицу полностью
/// @param dir Куда копировать матрицу
/// @param source Откуда копировать матрицу
/// @param row Кол-во строк
/// @param col Кол-во столбцов
void s21_copy_matrix(int **dir, int **source, int row, int col);

/// @brief Функция проверки где у фигуры находится левый или правый край в
/// массиве
/// @param wall Переменная отвечающая за поиск соответствующего края
/// @return Координата по х относительно массива фигуры, где находится
/// соотвествтвующий край
int s21_check_brick_pos(int wall);

/// @brief Функция перемещения фигуры вниз, и проверки пересечения с дном или
/// полем
/// @return Возвращает 1 в случае успешного перемещения 0 в случае пересечения
int s21_step_down();

/// @brief Функция проверки пересечения с полем или дном
/// @param brick Указатель на массив с фигурой
/// @param pos_x Положение фигуры по х
/// @param pos_y Положения фигуры по у
/// @return 0 - если нет пересечения 1 если есть пересечение
int s21_check_colission(int **brick, int pos_x, int pos_y);

/// @brief Функция по проверки пересечения с полем
/// @param pos_x Позиция клетки поля относительно массива фигуры по х
/// @param pos_y Позиция клетки поля относительно массива фигуры по у
/// @param cel Значение в указанной точке поля
/// @param brick Указатель на массив с фигурой
/// @return Возвращает 0 - если нет пересечения, 1 - если есть пересечение
int s21_check_colission_with_field(int pos_x, int pos_y, int cel, int **brick);

/// @brief Прикрепление старой фигуры к полю и спавн новой с проверкой на
/// возможность спавна
/// @return Возвращает 1 - если спавн удачный, 0 - если неудачный
int s21_attach_and_spawn_next();

/// @brief Записывает high_score в файл с рекордами
void s21_record_score();

/// @brief Перезапускает состояния фигур и поля к изначальному
void s21_restart_states();

/// @brief Проверка заполненности строк и увеличивает рекорд
void s21_check_lines();

/// @brief Удаляет указанную строку и смещает поле вниз
/// @param row Строка, которую нужно удалить
void s21_move_field_down(int row);

/// @brief Получает состояние конечного автомата
/// @return Указатель на состояние
game_t *s21_get_game();

/// @brief Проверка нужен ли lvlup
void s21_check_level();

/// @brief Копирует игрока игрока на игровое поле
/// @param field Указатель на матрицу, куда нужно скопировать
void s21_copy_player(int **field);

#endif