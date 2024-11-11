#include "outp_functions.h"

void set_cursor(uint8_t x, uint8_t y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_choose_gm_menu(uint8_t current_game_mode) {

    if (current_game_mode == ONE_PLAYER) {
        printf("-> 1 player \n");
        printf("   2 players \n");
    }
    else {
        printf("   1 player \n");
        printf("-> 2 players \n");
    }
}

void print_field(uint8_t field_width) {

    for (uint8_t i = 0; i < DEPTH + 1; i++) {
        for (uint8_t j = 0; j < 2 * field_width + 1; j++) {
            if (j % 2 == 0)
                printf("|");
            else
                if (i == DEPTH)
                    printf("=");
                else
                    printf(" ");
        }
        printf("\n");
    }
}

void print_chip_up_pos(uint8_t player, uint8_t column, uint8_t field_width) {
    set_cursor(0, 6);
    uint8_t i = 2 * column + 2;
    uint8_t j = 2 * field_width - i;

    printf("%*c%*c\n", i, (player == 1) ? 'O' : 'X', j, ' ');
}

void print_chip_field_pos(uint8_t player, uint8_t row, uint8_t column) {

    set_cursor(2 * column + 1, row + 7);
    printf("%c", (player == 1) ? 'O' : 'X');

}

void highlight_win_comb(struct COMBINATION_INFO win_comb) {
    char elem[] = "\033[??m!\033[0m";
    
    if (win_comb.player == 1) {
        elem[2] = '9';
        elem[3] = '2';
        elem[5] = 'O';
    }
    else {
        elem[2] = '3';
        elem[5] = 'X';
        if (win_comb.game_mode == TWO_PLAYERS)
            elem[3] = '6';
        else 
            elem[3] = '1';
    }

    int i = 0, j = 0;
    for (int k = 0; k < 4; k++) {
        switch (win_comb.dir)
        {
        case VERTICAL:
            i = win_comb.y + 7 + k;
            j = 2 * win_comb.x + 1;
            break;
        case HORISONTAL:
            i = win_comb.y + 7;
            j = 2 * (win_comb.x + k) + 1;
            break;
        case DIAG_DOWN:
            i = win_comb.y + 7 + k;
            j = 2 * (win_comb.x + k) + 1;
            break;
        case DIAG_UP:
            i = win_comb.y + 7 + (DEPTH - 1 - k);
            j = 2 * (win_comb.x + k) + 1;
            break;
        default:
            break;
        }
        set_cursor(j, i);
        printf("%s", elem);
    }
}
