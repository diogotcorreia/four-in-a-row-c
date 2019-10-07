// C-based Tic-Tac-Toe game by Diogo Correia and João Joaquim

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Define constants
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define PLAYER1 'A'
#define PLAYER2 'B'
#define AIR '.'
#define BOARD_COLUMNS 7
#define BOARD_ROWS 6

// Function declaration
void clear_screen();
void rules_instructions();
void start_board();
void print_board();
void start_game();
void execute_play();
char verify_winner();
char getMatrixAt();
bool is_tie();
void game_end(char winner);

// Board array and starting function
// The first dimension holds columns from left to right
// The second dimension holds rows from bottom to top
// For example, matrix[4][0] means fifth column, bottom row.
char matrix[BOARD_COLUMNS][BOARD_ROWS];

// This boolean defines which player is playing.
// False means Player 1 (X)
// True means Player 2 (O)
bool turn = false;

// The winner of the game.
char winner = AIR;

// The main function. This is what handles the game start.
int main()
{
  clear_screen();
  rules_instructions();
  start_board();
  start_game();
  return 0;
}

// Prints the instructions to the console.
void rules_instructions()
{
  printf("\n Welcome to this C-based 4-in-a-row game by Diogo Correia and João Joaquim!\n");
  printf("\n In order to win the game, you must have four of your characters aligned, either vertically, horizontally or diagonally.\n");
  printf("\n Player 1 plays with '%c' and Player 2 with '%c'.\n", PLAYER1, PLAYER2);
  printf("\n To start playing, choose the number correspondent to the column you wish to occupy, and press ENTER.\n");
  printf("\n Press CTRL + C at any time to exit.\n");
  printf("\n Good luck! \n\n\n");
}

// Initializes an empty board.
void start_board()
{
  int i, j;
  for (i = 0; i < BOARD_COLUMNS; i++)
    for (j = 0; j < BOARD_ROWS; j++)
      matrix[i][j] = AIR;
}

// Prints the current board to the console.
void print_board()
{
  int k, l, m;
  for (k = BOARD_ROWS - 1; k >= 0; k--)
  {
    for (l = 0; l < BOARD_COLUMNS; l++)
    {
      switch (matrix[l][k])
      {
      case PLAYER1:
        printf(" " ANSI_COLOR_RED "%c" ANSI_COLOR_RESET " ", matrix[l][k]);
        break;
      case PLAYER2:
        printf(" " ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET " ", matrix[l][k]);
        break;
      default:
        printf(" " ANSI_COLOR_YELLOW "%c" ANSI_COLOR_RESET " ", matrix[l][k]);
      }
    }
    printf("\n");
  }
  for (m = 0; m < BOARD_COLUMNS; m++)
    printf("---");
  printf("\n");
  for (m = 0; m < BOARD_COLUMNS; m++)
    printf(" %d ", m + 1);
  printf("\n\n");
}

// Cleans the screen.
void clear_screen()
{
  system("@cls||clear");
}

// Handles the game logic.
void start_game()
{
  char winner = AIR;
  // Keep the game running while no one wins and there is no tie.
  do
  {
    print_board();
    execute_play();
    clear_screen();
    winner = verify_winner();
  } while (winner == AIR && !is_tie());
  print_board();
  game_end(winner);
}

// Executes a round on the game.
void execute_play()
{
  int column;
  printf("\nPlayer %d (%c) turn: ", turn ? 2 : 1, turn ? PLAYER2 : PLAYER1);
  scanf("%d", &column);
  if (column > BOARD_COLUMNS)
  {
    printf("\nInvalid play! There is no such column!\n");
    execute_play();
    return;
  }
  int i;
  for (i = 0; i < BOARD_ROWS; i++)
  {
    if (matrix[column - 1][i] != AIR)
      continue;
    matrix[column - 1][i] = turn ? PLAYER2 : PLAYER1;
    turn = !turn;
    return;
  }
  printf("\nInvalid play! That column is already full!\n");
  execute_play();
}

// Checks if there is a winner. Does not check ties.
char verify_winner()
{
  // TODO
  int i, j, accumolated;
  for (i = 0; i < BOARD_COLUMNS; i++)
    // Same here
    for (j = 0; j < BOARD_ROWS; j++)
    {
      if (matrix[i][j] == AIR)
        continue;
      // Check vertically only upwards
      if (matrix[i][j] == matrix[i][j + 1] && matrix[i][j] == matrix[i][j + 2] && matrix[i][j] == matrix[i][j + 3])
        return matrix[i][j];
      // Check horizontally only to the right
      if (matrix[i][j] == matrix[i + 1][j] && matrix[i][j] == matrix[i + 2][j] && matrix[i][j] == matrix[i + 3][j])
        return matrix[i][j];
      // Check diagonally to the right
      if (matrix[i][j] == matrix[i + 1][j + 1] && matrix[i][j] == matrix[i + 2][j + 2] && matrix[i][j] == matrix[i + 3][j + 3])
        return matrix[i][j];
      // Check diagonally to the left
      if (matrix[i][j] == matrix[i - 1][j + 1] && matrix[i][j] == matrix[i - 2][j + 2] && matrix[i][j] == matrix[i - 3][j + 3])
        return matrix[i][j];
    }

  return AIR;
}

// Checks if there is a tie.
bool is_tie()
{
  int p, q;
  for (p = 0; p < BOARD_COLUMNS; p++)
    for (q = 0; q < BOARD_ROWS; q++)
      if (matrix[p][q] == AIR)
        return false;
  return true;
}

// Ends the game.
void game_end(char winner)
{
  switch (winner)
  {
  case PLAYER1:
    printf("\nPlayer 1 won!\n");
    break;
  case PLAYER2:
    printf("\nPlayer 2 won!\n");
    break;
  default:
    printf("\nIt's a tie!\n");
  }
  printf("Press ENTER to exit.\n");
  // This waits for an ENTER press;
  char ch;
  scanf("%c", &ch);
  scanf("%c", &ch);
}
