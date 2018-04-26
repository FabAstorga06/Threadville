#define PROC 10
#define QNTM 30

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

  printf("quantum: %d\n", QNTM);
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
                _time += QNTM;
            } else {
                _time += (priority[i] + QNTM);
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
      priority[q] -= QNTM;
    }


    if (priority[q] > 0) {
        _time += QNTM;
    } else {
        _time += (priority[q] + QNTM);
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


/**********************************************************************************************/

int sjfSCH(int idB, int side){
	struct carVille* tmp;
	if (side==LEFT){
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].leftArray[j]->state==THREAD_AVAILABLE){
					if (bridges[idB].leftArray[j+1]->state!=THREAD_AVAILABLE){
						tmp = bridges[idB].leftArray[j];
						bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
						bridges[idB].leftArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].leftArray[j+1]->state!=THREAD_AVAILABLE){
						if (bridges[idB].leftArray[j]->speed<bridges[idB].leftArray[j+1]->speed){
							tmp = bridges[idB].leftArray[j];
							bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
							bridges[idB].leftArray[j+1] = tmp;
						}
					}
				}
			}
		}
		if (bridges[idB].leftArray[0]->state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
	else{
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].rightArray[j]->state==THREAD_AVAILABLE){
					if (bridges[idB].rightArray[j+1]->state!=THREAD_AVAILABLE){
						tmp = bridges[idB].rightArray[j];
						bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
						bridges[idB].rightArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].rightArray[j+1]->state!=THREAD_AVAILABLE){
						if (bridges[idB].rightArray[j]->speed<bridges[idB].rightArray[j+1]->speed){
							tmp = bridges[idB].rightArray[j];
							bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
							bridges[idB].rightArray[j+1] = tmp;
						}

					}
				}
			}
		}
		if (bridges[idB].rightArray[0]->state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
}

/**********************************************************************************************/

int prioryteSCH(int idB, int side){
	struct carVille* tmp;
	if (side==LEFT){
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].leftArray[j]->state==THREAD_AVAILABLE){
					if (bridges[idB].leftArray[j+1]->state!=THREAD_AVAILABLE){
						tmp = bridges[idB].leftArray[j];
						bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
						bridges[idB].leftArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].leftArray[j+1]->state!=THREAD_AVAILABLE){
						if (bridges[idB].leftArray[j]->type<bridges[idB].leftArray[j+1]->type){
							tmp = bridges[idB].leftArray[j];
							bridges[idB].leftArray[j] = bridges[idB].leftArray[j+1];
							bridges[idB].leftArray[j+1] = tmp;
						}
					}
				}
			}
		}
		if (bridges[idB].leftArray[0]->state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
	else{
		for (int i=0; i<MAX_THREADS; i++){
			for (int j=0; j<MAX_THREADS-1; j++){
				if (bridges[idB].rightArray[j]->state==THREAD_AVAILABLE){
					if (bridges[idB].rightArray[j+1]->state!=THREAD_AVAILABLE){
						tmp = bridges[idB].rightArray[j];
						bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
						bridges[idB].rightArray[j+1] = tmp;
					}
				}
				else{
					if (bridges[idB].rightArray[j+1]->state!=THREAD_AVAILABLE){
						if (bridges[idB].rightArray[j]->type<bridges[idB].rightArray[j+1]->type){
							tmp = bridges[idB].rightArray[j];
							bridges[idB].rightArray[j] = bridges[idB].rightArray[j+1];
							bridges[idB].rightArray[j+1] = tmp;
						}

					}
				}
			}
		}
		if (bridges[idB].rightArray[0]->state != THREAD_AVAILABLE){
			return 0;
		}
		return 1;
	}
}

/**********************************************************************************************/

int fcfsSCH(int id_bridge, int pos, int side){

	struct carVille* tmpcar;
	if(pos>0){
		if(side==LEFT && bridges[id_bridge].leftArray[pos-1]->state){//Because THREAD_AVAILABLE =1
			tmpcar = bridges[id_bridge].leftArray[pos-1];
			bridges[id_bridge].leftArray[pos-1] = bridges[id_bridge].leftArray[pos];
			bridges[id_bridge].leftArray[pos] = tmpcar;
			bridges[id_bridge].leftArray[pos-1]->position = pos-1;
			bridges[id_bridge].leftArray[pos]->position = pos;
			pos--;
		}
		if(side==RIGHT && bridges[id_bridge].rightArray[pos-1]->state){//Because THREAD_AVAILABLE =1
			tmpcar = bridges[id_bridge].rightArray[pos-1];
			bridges[id_bridge].rightArray[pos-1] = bridges[id_bridge].rightArray[pos];
			bridges[id_bridge].rightArray[pos] = tmpcar;
			bridges[id_bridge].rightArray[pos-1]->position = pos-1;
			bridges[id_bridge].rightArray[pos]->position = pos;
			pos--;
		}
	}
	return pos;
}

/**********************************************************************************************/

int DispatcherCars(int idB, int pos, int side){
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
}
