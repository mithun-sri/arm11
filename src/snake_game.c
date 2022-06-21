#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

bool end_of_game = false;
int score = 0;
int x_current = 1;       // x_head and y_head indicate the current position of the head
int y_current = 1;
int board_height;
int board_width;
int x_food;
int y_food;


void input_board_dimension() {                           // allows the user to choose board dimensions
  scanf("Input width of the board: \n", &board_width);
  scanf("Input height of the board: \n", &board_height);
}

void initial_food() {
  x_food = (rand() % (board_width - 1)) + 1;     // x_food and y_food indicate the current position of the food item
  y_food = (rand() % (board_height - 1)) + 1;
}


void setup_borders() {
  system("cls");                     // cls clears the screen
  printf("#######  Score: %d  #######\n\n", score);    // scoreboard

  for (int i = 0; i < board_height; ++i) {
    for (int j = 0; j < board_width; ++j) {
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


void player_move()
{
  sleep(0.05);
  switch (getch()) {
    case 'a':
      y_current--;
      break;
    case 's':
      x_current++;
      break;
    case 'd':
      y_current++;
      break;
    case 'w':
      x_current--;
      break;
    default:
      end_of_game = true;
      break;
  }

  // if snake goes out of borders
  if (x_current < 0 || x_current > board_height || y_current < 0 || y_current > board_width) {
    end_of_game = true;
  }

  if (x_current == x_food && y_current == y_food) {
    x_food = (rand() % (board_width - 1)) + 1;
    y_food = (rand() % (board_height - 1)) + 1;           // new food item generated
    score ++;
  }

}


int main() {
  input_board_dimension();
  initial_food();

  while (!end_of_game) {
    setup_borders();
    player_move();
  }
  return 1;
}
