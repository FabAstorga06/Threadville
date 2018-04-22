/* Program dependences */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "map_utils.c"
#include "data_utils.c"

/*****************************************************************************/

int main(int argc, char* argv[] ) {

  Busville r;
  printf("Color: %d\n", r._color);

  /* Change map */
  /*while (1) {
    write_map();
    for (int i = 0; i < ROWS_MAP; i++) {
      for (int j = 0; j < COLS_MAP; j++){
          mtx[i][j] = mtx[i][j] + 10;
      }
    }
    sleep(1);
  }*/

  return 0;
}
