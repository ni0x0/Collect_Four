#include "game_info.h"
#include <stdbool.h>
#include <conio.h> 
#include <limits.h>
#include <string.h>

#define MAX_DEPTH 4        // Максимальная глубина обхода   
#define WIN_SCORE 1000     // Оценочные очки при выйгрыше
#define LOSS_SCORE -1000   //                    пройгрыше
#define DRAW_SCORE 0       //                    ничьей


bool check_full_field(int8_t* indexes, uint8_t field_width);                     // Проверка на полностью заполненное поле
struct COMBINATION_INFO check_the_win(uint8_t player,                            // Проверка на выйгрыш 
    uint8_t field[DEPTH][MAX_FIELD_WIDTH], uint8_t field_width);                   

int minimax(struct GAME_DATA* game_data, int depth, int is_maximizing_player);   // Рекурсивный проход по комбинациям
int8_t get_computer_move(struct GAME_DATA* game_data);                           // Получение хода "Компьютера"