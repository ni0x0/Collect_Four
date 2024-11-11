#include "logic.h"

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