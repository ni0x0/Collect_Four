#ifndef GAME_INFO_H  // Проверяем, был ли уже определён макрос
#define GAME_INFO_H

#include <stdio.h>
#include <stdint.h>

#define DEPTH 4                // "Глубина" поля
#define MAX_FIELD_WIDTH 24     // Максимальная ширина поля

enum Game_Mode {               // Режим игры   
	ONE_PLAYER = 1,
	TWO_PLAYERS = 2
};

enum PLAYER_TYPE {             // Тип игрока
    PLAYER = 1,
    COMPUTER = 2
};

enum Direction {               // Направление (для комбинации)
    NONE,
    VERTICAL,
    HORISONTAL,
    DIAG_DOWN,
    DIAG_UP
};

struct COMBINATION_INFO {      // Структура с информацией об комбинации фишек
    uint8_t x;                 // x и y - координаты первой фишки
    uint8_t y;
    uint8_t dir;               // (1 из enum Direction)

    uint8_t player;
    uint8_t game_mode;
};

struct GAME_DATA {                                 // Информация об игре в целом
    uint8_t game_field [DEPTH][MAX_FIELD_WIDTH];   // "Игровое поле" 
    int8_t free_indexes[MAX_FIELD_WIDTH];          // Доступные позиции в столбцах 

    uint8_t game_mode;                             // Игровой режим (1 или 2 игрока)
    uint8_t user_field_width;                      // Ширина поля, заданная пользователем
};

#endif