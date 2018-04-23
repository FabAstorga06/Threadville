/* Map constants */

#define MAP "ui/threadville_map.txt"
#define ROWS_MAP 15
#define COLS_MAP 11

FILE* tv_map;
unsigned int mtx[15][11] = {  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  };

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
    for (int j = 0; j < COLS_MAP; j++){
        write_data(mtx[i][j]);
    }
  }
  fclose(tv_map);
}
