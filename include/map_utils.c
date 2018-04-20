/* Map constants */

#define MAP "ui/threadville_map.txt"
#define ROWS_MAP 3
#define COLS_MAP 3

FILE* tv_map;
unsigned int mtx[3][3] = {  {1, 2, 3},
                            {4, 5, 6},
                            {9, 8, 7}  };

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
