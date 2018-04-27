/* log threadville activity */

#define LOG "log_file.txt"
FILE* log_file ;

/*****************************************************************************/

/* Write message to log file */
void write_log(char* msg ) {
  log_file = fopen(LOG, "a");
  if (log_file == NULL ) {
      printf("Error opening log file...\n");
      exit(1);
  }
  fprintf(log_file, "Threadville message: %s\n", msg);
  fclose(log_file);
}
