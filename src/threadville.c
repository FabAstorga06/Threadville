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

/*****************************************************************************/

int main(int argc, char* argv[] ) {

  log_file = fopen(LOG, "w");

  Busville* r;
  r = malloc(sizeof(struct bus));
  r->_color = GREEN;
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
  write_log("Message 1");
  write_log("Message 2");
  write_log("Message 3");

  fclose(log_file);
  return 0;
}
