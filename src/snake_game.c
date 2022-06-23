#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>


unsigned int game_mode;
unsigned int lost_game = 0;
unsigned int end_of_game = 0;
unsigned int first_turn = 1;
unsigned int score = 0;
// x_current and y_current indicate the current position of the head
unsigned int x_current = 1;
unsigned int y_current = 1;
unsigned int board_height;
unsigned int board_width;
unsigned int x_food;
unsigned int y_food;


void input_boardsize_and_mode(void) {
// allows the user to choose board dimensions
    printf("Input width of the board: ");
    scanf("%d", &board_width);
    printf("Input height of the board: ");
    scanf("%d", &board_height);
    printf("Enter 1 for high score mode or 2 for fastest to ten mode: ");
    scanf("%i", &game_mode);
}

void initial_food(void) {
// x_food and y_food indicate the current position of the food item
  label1:
    x_food = (rand() % (board_height - 2)) + 1;
    y_food = (rand() % (board_width - 2)) + 1;
    if (x_food == 1 && y_food == 1) {
      goto label1;
    }
}


void setup_borders(void) {
// "clear" clears the screen
    system("clear");
    printf("#######  Score: %d  #######\n\n", score);

    for (uint8_t i = 0; i < board_height; ++i) {
        for (uint8_t j = 0; j < board_width; ++j) {
            if (i == 0 || j == 0 || i == board_width - 1 || j == board_height - 1) {
                printf("#");
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
    printf("Use w,a,s,d to move or press q to quit.\n");
}


void player_move(void) {

    static struct termios old_val, new_val;
    tcgetattr(STDIN_FILENO, &old_val);
    new_val = old_val;
    new_val.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_val);
    char move = getchar();
    switch (move) {
        case 'a': y_current--; break;
        case 's': x_current++; break;
        case 'd': y_current++; break;
        case 'w': x_current--; break;
        case 'q': end_of_game = 1; break;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_val);

    // if snake goes out of borders
    if (x_current <= 0 || x_current >= board_height - 1
    || y_current <= 0 || y_current >= board_width - 1) {
       lost_game = 1;
       end_of_game = 1;
    }

    if (x_current == x_food && y_current == y_food) {
    // new food item generated
      label2:
        x_food = (rand() % (board_height - 2)) + 1;
        y_food = (rand() % (board_width - 2)) + 1;
        if (x_food == x_current && y_food == y_current) {
          goto label2;
        }
        score++;
    }

}


int main(void) {
    input_boardsize_and_mode();
    initial_food();
    clock_t t;
    int f;
    t = clock();
    
    if (game_mode == 1) {
      goto label3;
    }
    

    while(!end_of_game && score < 10) {
      setup_borders();
        player_move();
        t = clock() - t;
    }
    goto label4;
    
  label3:
    while (!end_of_game) {
        setup_borders();
        player_move();
        t = clock() - t;
    }

  label4:
    if (lost_game) {
      printf("\nGame over. You crashed into a wall.");
    }

    printf("\nThanks for playing. You scored %i point(s) in %.1lf seconds.\n\n", score, ((double) t/1000));
    return 0;
}
