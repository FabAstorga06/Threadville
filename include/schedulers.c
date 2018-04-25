<<<<<<< HEAD
int sjfSCH(int idB, char side){
	struct carVille tmp;
	if (side=='I'){
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].leftArray[j].state==THREAD_AVAILABLE){
					if (bridges[idB].leftArray[j+1].state!=THREAD_AVAILABLE){
						tmp = bridges[idB].leftArray[j];
						bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
						bridges[idB].leftArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].leftArray[j+1].state!=THREAD_AVAILABLE){
						if (bridges[idB].leftArray[j].speed<bridges[idB].leftArray[j+1].speed){
							tmp = bridges[idB].leftArray[j];
							bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
							bridges[idB].leftArray[j+1] = tmp;
						}
					}
				}
			}
		}
		if (bridges[idB].leftArray[0].state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
	else{
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].rightArray[j].state==THREAD_AVAILABLE){
					if (bridges[idB].rightArray[j+1].state!=THREAD_AVAILABLE){
						tmp = bridges[idB].rightArray[j];
						bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
						bridges[idB].rightArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].rightArray[j+1].state!=THREAD_AVAILABLE){
						if (bridges[idB].rightArray[j].speed<bridges[idB].rightArray[j+1].speed){
							tmp = bridges[idB].rightArray[j];
							bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
							bridges[idB].rightArray[j+1] = tmp;
						}

					}
				}
			}
		}
		if (bridges[idB].rightArray[0].state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
}


int prioryteSCH(int idB, char side){
	struct carVille tmp;
	if (side=='I'){
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].leftArray[j].state==THREAD_AVAILABLE){
					if (bridges[idB].leftArray[j+1].state!=THREAD_AVAILABLE){
						tmp = bridges[idB].leftArray[j];
						bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
						bridges[idB].leftArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].leftArray[j+1].state!=THREAD_AVAILABLE){
						if (bridges[idB].leftArray[j].type<bridges[idB].leftArray[j+1].type){
							tmp = bridges[idB].leftArray[j];
							bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
							bridges[idB].leftArray[j+1] = tmp;
						}
					}
				}
			}
		}
		if (bridges[idB].leftArray[0].state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
	else{
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].rightArray[j].state==THREAD_AVAILABLE){
					if (bridges[idB].rightArray[j+1].state!=THREAD_AVAILABLE){
						tmp = bridges[idB].rightArray[j];
						bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
						bridges[idB].rightArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].rightArray[j+1].state!=THREAD_AVAILABLE){
						if (bridges[idB].rightArray[j].type<bridges[idB].rightArray[j+1].type){
							tmp = bridges[idB].rightArray[j];
							bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
							bridges[idB].rightArray[j+1] = tmp;
						}

					}
				}
			}
		}
		if (bridges[idB].rightArray[0].state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
}


int fcfsSCH(int p, int i, char d){

	struct carVille tmpcar;
	if(i>0){
		if(d=='I' && bridges[p].leftArray[i-1].state){//Because THREAD_AVAILABLE =1
			tmpcar = bridges[p].leftArray[i-1];
			bridges[p].leftArray[i-1] = bridges[p].leftArray[i];
			bridges[p].leftArray[i] = tmpcar;
			bridges[p].leftArray[i-1].position = i-1;
			bridges[p].leftArray[i].position = i;
			i--;
		}
		if(d=='D' && bridges[p].rightArray[i-1].state){//Because THREAD_AVAILABLE =1
			tmpcar = bridges[p].rightArray[i-1];
			bridges[p].rightArray[i-1] = bridges[p].rightArray[i];
			bridges[p].rightArray[i] = tmpcar;
			bridges[p].rightArray[i-1].position = i-1;
			bridges[p].rightArray[i].position = i;
			i--;
		}
	}
	return i;
}


int DispatcherCars(int idB, int pos, char side){
	int i;
	if (DISPATCHER == (int)FIFO || DISPATCHER == (int)ROUND_ROBIN){//FCFS
		i = fcfsSCH(idB,  pos, side);
	}
	else if (DISPATCHER == (int)SJF){
		i = sjfSCH(idB, side);
	}
	else if (DISPATCHER == (int)HPF || DISPATCHER == (int)REAL_TIME){
		i = prioryteSCH(idB, side);
	}
	return i;
=======
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

>>>>>>> 83500b02e40ef5e2446c42770461739dc431ea4a
}
