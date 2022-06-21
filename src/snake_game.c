#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

uint8_t end_of_game = 0;
uint8_t first_turn = 1;
uint8_t score = 0;
// x_current and y_current indicate the current position of the head
uint8_t x_current = 1;
uint8_t y_current = 1;
int board_height;
int board_width;
uint8_t x_food;
uint8_t y_food;


void input_board_dimension(void) {
// allows the user to choose board dimensions
    printf("Input width of the board: ");
    scanf("%d", &board_width);
    printf("Input height of the board: ");
    scanf("%d", &board_height);
}

void initial_food(void) {
// x_food and y_food indicate the current position of the food item
    x_food = (rand() % (board_height - 1)) + 1;
    y_food = (rand() % (board_width - 1)) + 1;
}


void setup_borders(void) {
// "clear" clears the screen
    system("clear");
    // scoreboard
    printf("#######  Score: %d  #######\n\n", score);

    for (uint8_t i = 0; i < board_height; ++i) {
        for (uint8_t j = 0; j < board_width; ++j) {
            if (i == 0 || j == 0 || i == board_width - 1 || j == board_height - 1) {
                printf("=");
            }
            else {
                if (i == x_food && j == y_food) {
                printf("*");
                }
                else if (i == x_current && j == y_current) {
                printf(">");
                }
                else {
                printf(" ");
                }
            }
        }
        printf("\n");
    }
}


void player_move(void) {
    // sleeps for 50000 microseconds or 0.05 seconds, sleep() rounds down to 0
    usleep(50000);
    char move = getchar();
    switch (move) {
        case 'a': y_current--; break;
        case 's': x_current++; break;
        case 'd': y_current++; break;
        case 'w': x_current--; break;
        // pressing any other key ends game
        default: end_of_game = 1;
    }

    // if snake goes out of borders
    if (x_current < 0 || x_current > board_height \
    || y_current < 0 || y_current > board_width) {
        end_of_game = 1;
    }

    if (x_current == x_food && y_current == y_food) {
    // new food item generated
        x_food = (rand() % (board_height - 1)) + 1;
        y_food = (rand() % (board_width - 1)) + 1;
        score++;
    }

}


int main(void) {
    input_board_dimension();
    initial_food();
    
    while (!end_of_game) {
        setup_borders();
        player_move();
    }

    printf("Game over!\n");
    return 0;
}
