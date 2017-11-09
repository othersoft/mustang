#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  char  help;
  char  verbose;
  char  force;
  int   white;
  char  *storage;
  }
PARAM;

typedef struct{
  char  matrix[8][8];
  int   size;
  int   side;
  int   turn;
  }
BOARD;

void PrintMenu(void){

  fprintf(stderr, 
  "                                        \n"
  " Usage:                                 \n"  
  "   ./mustang <option> <storage>         \n"
  "                                        \n"
  " The <option>:                          \n"
  "   [0] - show this menu,                \n"
  "   [1] - choose board side,             \n"
  "   [2] - show board,                    \n"
  "   [3] - add my move,                   \n"
  "   [4] - add oponent move,              \n"
  "   [5] - remove my previous move,       \n"
  "   [6] - remove oponent previous move,  \n"
  "   [7] - credits.                       \n"
  "                                        \n"
  " The <storage>: game memory file.       \n"
  "                                        \n");
  
  return;
  }

void PrintVersion(void){

  fprintf(stderr, 
  "                                               \n"
  " Mustang: chess game for email correspondence. \n"
  " D. Pratas <pratas@ua.pt> GPL3, 2017-2018, V1. \n"
  "                                               \n");

  return;
  }

void InitBoard(BOARD *B){
  
  B->matrix[7][0] = 't'; B->matrix[7][1] = 'h'; B->matrix[7][2] = 'b'; B->matrix[7][3] = 'q';
  B->matrix[7][4] = 'k'; B->matrix[7][5] = 'b'; B->matrix[7][6] = 'h'; B->matrix[7][7] = 't';

  B->matrix[6][0] = 'p'; B->matrix[6][1] = 'p'; B->matrix[6][2] = 'p'; B->matrix[6][3] = 'p';
  B->matrix[6][4] = 'p'; B->matrix[6][5] = 'p'; B->matrix[6][6] = 'p'; B->matrix[6][7] = 'p';

  B->matrix[5][0] = ' '; B->matrix[5][1] = ' '; B->matrix[5][2] = ' '; B->matrix[5][3] = ' ';
  B->matrix[5][4] = ' '; B->matrix[5][5] = ' '; B->matrix[5][6] = ' '; B->matrix[5][7] = ' ';

  B->matrix[4][0] = ' '; B->matrix[4][1] = ' '; B->matrix[4][2] = ' '; B->matrix[4][3] = ' ';
  B->matrix[4][4] = ' '; B->matrix[4][5] = ' '; B->matrix[4][6] = ' '; B->matrix[4][7] = ' ';

  B->matrix[3][0] = ' '; B->matrix[3][1] = ' '; B->matrix[3][2] = ' '; B->matrix[3][3] = ' ';
  B->matrix[3][4] = ' '; B->matrix[3][5] = ' '; B->matrix[3][6] = ' '; B->matrix[3][7] = ' ';

  B->matrix[2][0] = ' '; B->matrix[2][1] = ' '; B->matrix[2][2] = ' '; B->matrix[2][3] = ' ';
  B->matrix[2][4] = ' '; B->matrix[2][5] = ' '; B->matrix[2][6] = ' '; B->matrix[2][7] = ' ';

  B->matrix[1][0] = 'P'; B->matrix[1][1] = 'P'; B->matrix[1][2] = 'P'; B->matrix[1][3] = 'P';
  B->matrix[1][4] = 'P'; B->matrix[1][5] = 'P'; B->matrix[1][6] = 'P'; B->matrix[1][7] = 'P';

  B->matrix[0][0] = 'T'; B->matrix[0][1] = 'H'; B->matrix[0][2] = 'B'; B->matrix[0][3] = 'Q';
  B->matrix[0][4] = 'K'; B->matrix[0][5] = 'B'; B->matrix[0][6] = 'H'; B->matrix[0][7] = 'T';

  return;
  }


void VisualizeInitBoard(void){

  fprintf(stderr, 
  "                                       \n"
  "               YOUR BOARD:             \n"
  "                                       \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 8  | t | h | b | q | k | b | h | t |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 7  | p | p | p | p | p | p | p | p |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 6  |   |   |   |   |   |   |   |   |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 5  |   |   |   |   |   |   |   |   |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 4  |   |   |   |   |   |   |   |   |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 3  |   |   |   |   |   |   |   |   |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 2  | P | P | P | P | P | P | P | P |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  " 1  | T | H | B | Q | K | B | H | T |  \n"
  "    +---+---+---+---+---+---+---+---+  \n"
  "                                       \n"
  "      A | B | C | D | E | F | G | H    \n"
  "                                       \n"
  "                                       \n"
  "                 Legend:               \n"
  "                                       \n"
  "               p,P - Pawn,             \n"
  "               h,H - Horse,            \n"
  "               b,B - Bishop,           \n"
  "               t,T - Tower,            \n"
  "               q,Q - Queen,            \n"
  "               k,K - King.             \n"
  "                                       \n");

  return;
  }

void VisualizeBoard(BOARD *B){

  fprintf(stderr,
  "                                                                             \n"
  "               YOUR BOARD:                           OPONENT BOARD:          \n"
  "                                                                             \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 8  | %c | %c | %c | %c | %c | %c | %c | %c |      |   |   |   |   |   |   |   |   |\n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 7  | %c | %c | %c | %c | %c | %c | %c | %c |                                      \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 6  | %c | %c | %c | %c | %c | %c | %c | %c |                                \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 5  | %c | %c | %c | %c | %c | %c | %c | %c |                                \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 4  | %c | %c | %c | %c | %c | %c | %c | %c |                                \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 3  | %c | %c | %c | %c | %c | %c | %c | %c |                                \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 2  | %c | %c | %c | %c | %c | %c | %c | %c |                                \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  " 1  | %c | %c | %c | %c | %c | %c | %c | %c |                                \n"
  "    +---+---+---+---+---+---+---+---+      +---+---+---+---+---+---+---+---+ \n"
  "                                                                             \n"
  "      A | B | C | D | E | F | G | H          A | B | C | D | E | F | G | H   \n"
  "                                       \n"
  "                                       \n"
  "                 Legend:               \n"
  "                                       \n"
  "               p,P - Pawn,             \n"
  "               h,H - Horse,            \n"
  "               b,B - Bishop,           \n"
  "               t,T - Tower,            \n"
  "               q,Q - Queen,            \n"
  "               k,K - King.             \n"
  "                                       \n",
  B->matrix[7][0], B->matrix[7][1], B->matrix[7][2], B->matrix[7][3],
  B->matrix[7][4], B->matrix[7][5], B->matrix[7][6], B->matrix[7][7],

  B->matrix[6][0], B->matrix[6][1], B->matrix[6][2], B->matrix[6][3],
  B->matrix[6][4], B->matrix[6][5], B->matrix[6][6], B->matrix[6][7],

  B->matrix[5][0], B->matrix[5][1], B->matrix[5][2], B->matrix[5][3],
  B->matrix[5][4], B->matrix[5][5], B->matrix[5][6], B->matrix[5][7],

  B->matrix[4][0], B->matrix[4][1], B->matrix[4][2], B->matrix[4][3],
  B->matrix[4][4], B->matrix[4][5], B->matrix[4][6], B->matrix[4][7],

  B->matrix[3][0], B->matrix[3][1], B->matrix[3][2], B->matrix[3][3],
  B->matrix[3][4], B->matrix[3][5], B->matrix[3][6], B->matrix[3][7],

  B->matrix[2][0], B->matrix[2][1], B->matrix[2][2], B->matrix[2][3],
  B->matrix[2][4], B->matrix[2][5], B->matrix[2][6], B->matrix[2][7],

  B->matrix[1][0], B->matrix[1][1], B->matrix[1][2], B->matrix[1][3],
  B->matrix[1][4], B->matrix[1][5], B->matrix[1][6], B->matrix[1][7],

  B->matrix[0][0], B->matrix[0][1], B->matrix[0][2], B->matrix[0][3],
  B->matrix[0][4], B->matrix[0][5], B->matrix[0][6], B->matrix[0][7]);

  return;
  }

//////////////////////////////////////////////////////////////////////////////
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - M A I N - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argc, char *argv[]){
  int   n, try;
  char  **p = *&argv;
  BOARD *B  = (BOARD *) malloc(1 * sizeof(BOARD));
  PARAM *P  = (PARAM *) malloc(1 * sizeof(PARAM));

  if(argc != 3){ 
    PrintMenu();
    return EXIT_SUCCESS;
    }

  int option = atoi(argv[argc-2]);
  P->storage = argv[argc-1];

  InitBoard(B);

  switch(option){
    case 0: 
    PrintMenu();
    break;

    case 1:
    try = 0;
    while(1){
      fprintf(stderr, 
      "                          \n"
      " Choose board side:       \n"
      "   [1] - white,           \n"
      "   [2] - Black.           \n"
      " Choice: ");
      scanf("%d", &P->white);
      fprintf(stderr, "\n");
      if(P->white == 1 || P->white == 2)
        break;
      if(try > 1)
        fprintf(stderr, "Are you stupid or what?!\n\n");
      fprintf(stderr, "Error: unknown board side! Choose 1 or 2.\n");

      if(try > 6)
        return EXIT_SUCCESS;
      ++try;
      } 

    break;

    case 2:
    //VisualizeInitBoard();
    VisualizeBoard(B);
    break;

    case 3:
    break;
  
    case 4:
    break;

    case 5:
    break;

    case 6:
    break;

    case 7:
    PrintVersion();
    break;

    default:
    fprintf(stderr, 
    "                                                \n"
    " Error: Unknown argument! Use [0,7] interval!   \n"
    "                                                \n");
    }

  return EXIT_SUCCESS;
  }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
