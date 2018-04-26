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
