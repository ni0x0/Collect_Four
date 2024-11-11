#include "game_funs.h"

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

uint8_t choose_game_mode() {
    uint8_t curr_game_mode = ONE_PLAYER;
    uint8_t user_ch = 0;

    system("cls");
    printf("__COLLECT 4 GAME :)__\n\nChoose game mode: \n");
    printf("Use arrows(up/down)\n\"Enter\" - confirm the game mode\n\"Esc\" - close the game\n\n");

    while (1) {
        set_cursor(0, 7);
        print_choose_gm_menu(curr_game_mode);

        user_ch = _getch();

        if (user_ch == 224) {                           // Клавиша стрелки
            user_ch = _getch();                         // Доп. символ
            if (user_ch == 80) {                        // Стрелка вниз
                if (curr_game_mode == ONE_PLAYER) {
                    curr_game_mode = TWO_PLAYERS;
                }
            }
            else if (user_ch == 72) {                 // Стрелка вверх
                if (curr_game_mode == TWO_PLAYERS) {
                    curr_game_mode = ONE_PLAYER;
                }
            }
        }
        else if (user_ch == 13) {                     // Enter
            // printf("\nYour choice%d\n", curr_game_mode);
            break;
        }
        else if (user_ch == 27) {                     // Escape
            printf("\nExit\n");
            return 0;
        }
    }
    return curr_game_mode;
}

uint8_t get_field_width() {
    uint8_t num;
    char c;

    while (1) {
        system("cls");
        printf("__COLLECT 4 GAME :)__\n\n");

        printf("\"Enter\" - confirm the field width\n\"0\" - return to game mode choosing\n\n");
        printf("Choose field width(from 4 to %d) : ", MAX_FIELD_WIDTH);

        if (scanf_s("%hhu", &num) == 1) {
            c = getchar();
            if (c == '\n') {
                if (num == 0)
                    return 0;
                else
                    if (num >= 4 && num <= MAX_FIELD_WIDTH)
                        break;
                    else {
                        printf("Wrong number. Try again... (press any key)");
                        c = _getch();
                        continue;
                    }

            }
        }

        while ((c = getchar()) != '\n' && c != EOF);

        printf("Wrong input. Try again... (press any key)");
        c = _getch();
    }
    // printf("Num:%d:", num);
    // c = _getch();
    return num;
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

bool check_full_field(int8_t* indexes, uint8_t field_width) {
    for (int8_t i = 0; i < field_width; i++) {
        if (indexes[i] != -1) {
            return false;
        }
    }
    return true;
}

struct COMBINATION_INFO check_the_win(uint8_t player, uint8_t field[DEPTH][MAX_FIELD_WIDTH], uint8_t field_width) {
    struct COMBINATION_INFO win_pos;
    win_pos.player = player;
    bool four_in_row = true;
    
    // vertically
    win_pos.dir = VERTICAL;
    win_pos.y = 0;
    for (int8_t j = 0; j < field_width; j++) {
        win_pos.x = j;
        four_in_row = true;
        for (int8_t i = 0; i < DEPTH; i++) {
            if (field[i][j] != player) {
                four_in_row = false;
                break;
            }
        }
        if (four_in_row == true)
            return win_pos;
    }

    // horisontally
    win_pos.dir = HORISONTAL;
    for (int8_t i = 0; i < DEPTH; i++) {
        win_pos.y = i;

        for (int8_t j = 0; j <= field_width - 4; j++) {
            win_pos.x = j;
            four_in_row = true;

            for (int8_t k = 0; k < 4; k++) {
                if (field[i][j + k] != player) {
                    four_in_row = false;
                    break;
                }
            }
            if (four_in_row == true)
                return win_pos;
        }
    }

    // diag down
    win_pos.dir = DIAG_DOWN;
    win_pos.y = 0;
    for (int8_t j = 0; j <= field_width - 4; j++) {
        win_pos.x = j;
        four_in_row = true;

        for (int8_t k = 0; k < DEPTH; k++) {
            if (field[k][j + k] != player) {
                four_in_row = false;
                break;
            }
        }
        if (four_in_row == true)
            return win_pos;
    }

    // diag up
    win_pos.dir = DIAG_UP;
    win_pos.y = 0;
    for (int8_t j = 0; j <= field_width - 4; j++) {
        win_pos.x = j;
        four_in_row = true;

        for (int8_t k = 0; k < DEPTH; k++) {
            if (field[DEPTH - k - 1][j + k] != player) {
                four_in_row = false;
                break;
            }
        }
        if (four_in_row == true)
            return win_pos;
    }

    win_pos.dir = NONE;
    return win_pos;
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

int minimax(struct GAME_DATA* game_data, int depth, int is_maximizing_player) {
    // is_maximizing_player: 0 - игрок, 1 - компьютер

    int score = 0;
    if (check_the_win(1, game_data->game_field, game_data->user_field_width).dir != NONE)
        score = PLAYER;
    else if (check_the_win(2, game_data->game_field, game_data->user_field_width).dir != NONE)
        score = COMPUTER;

    if (score == COMPUTER) return WIN_SCORE - depth;  // Победа компьютера
    if (score == PLAYER) return LOSS_SCORE + depth;   // Победа игрока
    if (depth >= MAX_DEPTH) return DRAW_SCORE;        // Предел глубины

    if (is_maximizing_player) { // Ход компьютера
        int best_score = INT_MIN;
        for (int col = 0; col < game_data->user_field_width; col++) {
            if (game_data->free_indexes[col] != -1) {
                struct GAME_DATA temp_game_data;
                memcpy(&temp_game_data, game_data, sizeof(struct GAME_DATA));

                temp_game_data.game_field[temp_game_data.free_indexes[col]--][col] = COMPUTER;

                int current_score = minimax(&temp_game_data, depth + 1, 0);
                best_score = (current_score > best_score) ? current_score : best_score;
            }
        }
        return best_score;
    }
    else {                      // Ход игрока
        int best_score = INT_MAX;
        for (int col = 0; col < game_data->user_field_width; col++) {
            if (game_data->free_indexes[col] != -1) {
                struct GAME_DATA temp_game_data;
                memcpy(&temp_game_data, game_data, sizeof(struct GAME_DATA));

                temp_game_data.game_field[temp_game_data.free_indexes[col]--][col] = PLAYER;

                int current_score = minimax(&temp_game_data, depth + 1, 1);
                best_score = (current_score < best_score) ? current_score : best_score;
            }
        }
        return best_score;
    }
}

int8_t get_computer_move(struct GAME_DATA* game_data) {
    int best_score = INT_MIN;
    int8_t best_move = 0;

    for (int8_t col = 0; col < game_data->user_field_width; col++) {
        if (game_data->free_indexes[col] != -1) {
            struct GAME_DATA temp_game_data;
            memcpy(&temp_game_data, game_data, sizeof(struct GAME_DATA));

            temp_game_data.game_field[temp_game_data.free_indexes[col]--][col] = COMPUTER;

            int move_score = minimax(&temp_game_data, 1, 0);
            if (move_score > best_score) {
                best_score = move_score;
                best_move = col;
            }
        }
    }

    return best_move;
}


void game_process(struct GAME_DATA * game_data) {
    system("cls");
    printf("__COLLECT 4 GAME :)__\n\n");
    printf("Use arrows(left/right)\n\"Enter\" - confirm the column\n\"Esc\" - return to first menu\n\n\n");

    print_field(game_data->user_field_width);
   
    uint8_t user_ch, curr_col = 0, curr_player = 1;
    print_chip_up_pos(curr_player, curr_col, game_data->user_field_width);

    while (1) {
        
        print_chip_up_pos(curr_player, curr_col, game_data->user_field_width);

        if (game_data->game_mode == ONE_PLAYER && curr_player == COMPUTER) {
            curr_col = get_computer_move(game_data);
            user_ch = 13;
        }
        else user_ch = _getch();


        if (user_ch == 224) {                           // Клавиша стрелки
            user_ch = _getch();                         // Доп. символ
            if (user_ch == 77) {                        // Стрелка вправо
                if (curr_col < game_data->user_field_width - 1) {
                    curr_col++;
                }
            }
            else if (user_ch == 75) {                   // Стрелка влево
                if (curr_col > 0) {
                    curr_col--;
                }
            }
        }
        else if (user_ch == 13) {                       // Enter
            if (game_data->free_indexes[curr_col] == -1)
                continue;

            print_chip_field_pos(curr_player, game_data->free_indexes[curr_col], curr_col);
            game_data->game_field[game_data->free_indexes[curr_col]][curr_col] = curr_player;

            game_data->free_indexes[curr_col]--;

            struct COMBINATION_INFO win_comb = check_the_win(curr_player, game_data->game_field, game_data->user_field_width);
            if (win_comb.dir != NONE) {
                win_comb.game_mode = game_data->game_mode;
                highlight_win_comb(win_comb);

                set_cursor(0, 6);
                printf("%*c", 2*(game_data->user_field_width) + 1, ' ');
                set_cursor(0, DEPTH + 9);
                if (curr_player == 1)
                    printf("GOOD GAME :) PLAYER 1 WON THE GAME!! ");
                else if (game_data->game_mode == ONE_PLAYER)
                    printf("SO SAD :( YOU LOST TO A SILLY ALGORITHM. ");
                else 
                    printf("GOOD GAME :) PLAYER 2 WON THE GAME!! ");
                printf("press any key to continue...");
                _getch();
                break;
            }

            if (check_full_field(&(game_data->free_indexes[0]), game_data->user_field_width) == true) {
                set_cursor(0, 6);
                printf("%*c", 2 * (game_data->user_field_width) + 1, ' ');
                set_cursor(0, DEPTH + 9);
                printf("GOOD GAME :) IT'S A DRAW!! press any key to continue...");
                _getch();
                break;
            }

            curr_col = 0;
            if (curr_player == 1)
                curr_player = 2;
            else  curr_player = 1;
        }
        else if (user_ch == 27) {                     // Escape
            printf("\nExit\n");
            break;
        }
    }
}





