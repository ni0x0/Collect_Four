#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <conio.h> 
#include <windows.h>
#include <limits.h>

#define DEPTH 4
#define MAX_FIELD_WIDTH 24

#define MAX_DEPTH 4  
#define WIN_SCORE 1000
#define LOSS_SCORE -1000
#define DRAW_SCORE 0

enum Game_Mode {
	ONE_PLAYER = 1,
	TWO_PLAYERS = 2
};

enum PLAYER_TYPE {
    PLAYER = 1,
    COMPUTER = 2
};

enum Direction {
    NONE,
    VERTICAL,
    HORISONTAL,
    DIAG_DOWN,
    DIAG_UP
};

struct GAME_DATA {
    uint8_t game_field [DEPTH][MAX_FIELD_WIDTH];    
    int8_t free_indexes[MAX_FIELD_WIDTH];

    uint8_t game_mode;
    uint8_t user_field_width;
};

struct COMBINATION_INFO {
    uint8_t x;
    uint8_t y;
    uint8_t dir;

    uint8_t player;
    uint8_t game_mode;
};

void set_cursor(uint8_t x, uint8_t y);

void print_choose_gm_menu(uint8_t current_game_mode);
uint8_t choose_game_mode();

uint8_t get_field_width();

void print_field(uint8_t field_width);
void print_chip_up_pos(uint8_t player, uint8_t column, uint8_t field_width);
void print_chip_field_pos(uint8_t player, uint8_t row, uint8_t column);

bool check_full_field(int8_t* indexes, uint8_t field_width);
struct COMBINATION_INFO check_the_win(uint8_t player, uint8_t field[DEPTH][MAX_FIELD_WIDTH], uint8_t field_width);
void highlight_win_comb(struct COMBINATION_INFO win_comb);

int minimax(struct GAME_DATA* game_data, int depth, int is_maximizing_player);
int8_t get_computer_move(struct GAME_DATA* game_data);

void game_process(struct GAME_DATA * game_data);
