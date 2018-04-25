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
}
