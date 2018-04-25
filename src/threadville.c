/* Program dependences */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "map_utils.c"
#include "data_utils.c"
#include "log_utils.c"
#include "schedulers.c"

/*****************************************************************************/

int main(int argc, char* argv[] ) {

  srand(time(NULL));
  log_file = fopen(LOG, "w");
  memset(mtx, '\0', (ROWS_MAP*COLS_MAP * sizeof(unsigned int)));

  Carville* r;
  r = malloc(sizeof(struct vehicle));
  r->_color = 3;
  printf("Color: %d\n", r->_color);

  /* Change map */
  /*  while (1) {
    write_map();
    for (int i = 0; i < ROWS_MAP; i++) {
      for (int j = 0; j < COLS_MAP; j++){
          mtx[i][j] = mtx[i][j] + 1;
      }
    }
    sleep(5);
  }*/

  /* Write messages in log file */
  write_log("hola 1");
  write_log("hola 2");
  write_log("hola 3");

  /* SCHEDULERS */

  lottery_scheduler();

  /* Get key events */
//  verify_key_events();

  fclose(log_file);
  return 0;
}
