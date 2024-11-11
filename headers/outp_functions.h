#include"game_info.h"
#include <windows.h>

void set_cursor(uint8_t x, uint8_t y);                         // Установка курсора на координату (x,y)

void print_choose_gm_menu(uint8_t current_game_mode);          // Вывод меню выбора игрового режима

void print_field(uint8_t field_width);                                        // Вывод игрового поля
void print_chip_up_pos(uint8_t player, uint8_t column, uint8_t field_width);  // Вывод фишки в нужной позиции над полем
void print_chip_field_pos(uint8_t player, uint8_t row, uint8_t column);       // Вывод фишки в нужной позиции в поле

void highlight_win_comb(struct COMBINATION_INFO win_comb);     // Выделение "победной" комбинации     