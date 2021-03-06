/* Map constants */

#define MAP "ui/threadville_map.txt"
#define ROWS_MAP 12
#define COLS_MAP 17

FILE* tv_map;

/*****************************************************************************/
/* Write data to file */
void write_data(unsigned int pix) {

  if (tv_map == NULL ) {
      printf("Error opening file...\n");
      exit(1);
  }
  fprintf(tv_map, "%d#", pix);
}

/* Write the threadville map to file */
void write_map() {

  tv_map = fopen(MAP, "w");

  for (int i = 0; i < ROWS_MAP; i++) {
    for (int j = 0; j < COLS_MAP; j++) {
        write_data(gui_mtx[i][j]);
    }
  }
  fclose(tv_map);
}

void* update_map () {
    while (1) {
        most_important_vehicle();
        write_map();
        sleep(1);
    }
}
