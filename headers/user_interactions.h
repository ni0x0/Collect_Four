#include "outp_functions.h"
#include "logic.h"

uint8_t choose_game_mode();                       // Выбор режима: 1 или 2 игрока
uint8_t get_field_width();                        // Задание пользователем желаемой ширины поля
void game_process(struct GAME_DATA * game_data);  // Игровой процесс заполнения поля фишками