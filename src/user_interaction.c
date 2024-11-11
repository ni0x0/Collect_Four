#include "user_interactions.h"

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