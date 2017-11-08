#include <stdio.h>
#include <stdlib.h>

typedef struct{
  char    help;
  char    verbose;
  char    force;
  int     white;
  char    *storage;
  }
PARAM;

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

//////////////////////////////////////////////////////////////////////////////
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - M A I N - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int argc, char *argv[]){
  int   n;
  char  **p = *&argv;
  char  BOARD[8][8];
  PARAM *P = (PARAM *) malloc(1 * sizeof(PARAM));

  if(argc != 3){ 
    PrintMenu();
    return EXIT_SUCCESS;
    }

  int option = atoi(argv[argc-2]);
  P->storage = argv[argc-1];

  switch(option){
    case 0: 
    PrintMenu();
    break;

    case 1:
    fprintf(stderr, 
    "                          \n"
    " Choose board side:       \n"
    "   [1] - white,           \n"
    "   [2] - Black.           \n"
    " Choice: ");
    scanf("%d", &P->white);
    fprintf(stderr, "\n");

    
    break;

    case 2:
    VisualizeInitBoard();
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
