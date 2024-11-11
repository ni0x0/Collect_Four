#include "user_interactions.h"

int main() {   
    struct GAME_DATA game_data;
	
	while (1) {
        memset(&game_data, 0, sizeof(struct GAME_DATA));
        memset(&(game_data.free_indexes), DEPTH - 1, sizeof(game_data.free_indexes));

        game_data.game_mode = choose_game_mode();
        if (game_data.game_mode == 0)
            break;
        
        game_data.user_field_width = get_field_width();
        if (game_data.user_field_width == 0)
            continue;

        game_process(&game_data);
	}

	return 0;
}