#define PROC 10
#define QUANTUM 30

/* Lottery scheduler to handle with process traffic
 * in some bridge in Threadville
 */
void lottery_scheduler( ) {
  char process[PROC] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
  int arrival[PROC];
  memset(arrival, '\0', (PROC * sizeof(int)));
  int insert = 0, p = 0, q = 0, max_tick = 0;
  int ticket[PROC][PROC] ;
  char temp[PROC];

  int _time = arrival[0];
  int priority[PROC] = { 10, 2, 2, 4, 8, 4, 2, 2, 4, 8 }; /* prioridades!! */
  int lottery[PROC];
  memset(lottery, '\0', (PROC * sizeof(int)));

  for (unsigned int i = 0; i < PROC; i++) {
      printf("\tprocess: %c", process[i]);
      printf("\tarrival: %d", arrival[i]);
      printf("\tpriority: %d", priority[i]);
      printf("\n");
  }

  printf("quantum: %d\n", QUANTUM);
  printf("\ttime");
  printf("\tpriority");
  printf("\tprocess");
  printf("\tLottery");
  printf("\tticket");

  printf("---------------------------------------------------------");
  while ((priority[0] + priority[1] + priority[2] + priority[3] +
          priority[4] + priority[5] + priority[6] + priority[7] +
          priority[8] + priority[9]) > 0) {


    printf("---------------------------------------------------------\n");
    p = 0;
    for (unsigned int i = 0; i < PROC; i++) {
        if ((priority[i] > 0)) {
            lottery[i] = priority[i] / 2;
            if ((lottery[i] == 0) && (priority[i] > 0))
                lottery[i] = 1;
            for (unsigned int z = 0; z < lottery[i]; z++) {
                ticket[i][z] = p++;
                max_tick = p;
            }
            temp[i] = process[i];


            printf("\t" );
            printf("\t%d", priority[i]);
            printf("\t%d", temp[i]);
            printf("\t%d", lottery[i]);
            for (unsigned int z = 0; z < lottery[i]; z++)
                printf("\t::%d::", ticket[i][z]);
            printf("\n");
        } else if ((priority[i] > 0) && (_time < arrival[i])) {
            temp[i] = process[p];
            lottery[i] = priority[i] / 2;
            if ((lottery[i] == 0) && (priority[i] > 0))
                lottery[i] = 1;
            for (unsigned int z = 0; z < lottery[i]; z++){
                ticket[i][z] = p++;
                max_tick=p;
            }

            if (priority[i] > 0) {
                _time += QUANTUM;
            } else {
                _time += (priority[i] + QUANTUM);
            }

            printf("\t%d", _time);
            printf("\t%d", priority[p]);
            printf("\t%d", temp[i]);
            printf("\t%d", lottery[i]);
            for (unsigned int z = 0; z < lottery[i]; z++)
                printf("\t::%d::", ticket[i][z]);
            printf("\n");

        }
    }

    int winner = random_num(max_tick);
    for(unsigned int i = 0; i < PROC; i++ ) {
        for(unsigned int z = 0; z < lottery[i]; z++ ) {
            if(ticket[i][z] == winner)
                 q = i;
        }
    }
    printf("---------------------------------------------------------");
    printf("\nwinner: <<%d>>", winner);

    if ((priority[q] > 0))  {
      temp[q] = process[q];
      priority[q] -= QUANTUM;
    }


    if (priority[q] > 0) {
        _time += QUANTUM;
    } else {
        _time += (priority[q] + QUANTUM);
    }

    if (priority[q] < 0) {
        priority[q] = 0;
    }

    printf("\t%d", _time);
    printf("\t%d", priority[q]);
    printf("\t%d", temp[q]);
    printf("\n");

  }

}
