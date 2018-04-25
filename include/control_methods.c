int waitingAux(int BridgeID, char side){//MAX_THREADS
	int resp = 1;
	int i = 0;
	for(i = 0; i < (MAX_THREADS/4);i++){
		if(side == 'D'){
			if(bridges[BridgeID].rightArray[0].state != THREAD_AVAILABLE){
				return 0;
			}
		}else{
			if(bridges[BridgeID].leftArray[0].state != THREAD_AVAILABLE){
				return 0;
			}
		}
	}
	return resp;
}
void changetheWay(int pBid){
	int b1 = 0;
	int b2 = 0;
	if (bridges[pBid].busy == EMPTY){
		usleep(1000);
		b1 = waitingAux(pBid, 'D');
		b2 = waitingAux(pBid, 'I');

		if (!b2 && b1){ // 1  -  0
			mymutex_lock(&lock);
			bridges[pBid].cont = 0;
			bridges[pBid].oficial = 0;
			mymutex_unlock(&lock);
		}
		else if (!b1 && b2){ // 0  -  1
			mymutex_lock(&lock);
			bridges[pBid].cont = 1;
			bridges[pBid].oficial = 1;
			mymutex_unlock(&lock);
		}
		else if (!b2 && !b1){
			mymutex_lock(&lock);
			bridges[pBid].cont = 3;
			bridges[pBid].oficial = 3;
			mymutex_unlock(&lock);
		}
	}
}

void *Semaphore(void* BridgeID){

	int i = *((int*) BridgeID);

	int b;
	int sleep = 0;
	int timesleep = 10000;
	if(i == 0){b = TIME_1*1000000;}
	else if(i == 1){b = TIME_2*1000000;}
	else if(i == 2){b = TIME_3*1000000;}
	else if(i == 3){b = TIME_4*1000000;}

	while(1){
		mymutex_lock(&lock);
		bridges[i].semaforo = (bridges[i].semaforo)?0:1;
		mymutex_unlock(&lock);
		sleep = 0;
		while(1){
			if (DISPATCHER == (int)REAL_TIME){ //si es planificador de tiempo real
				if(bridges[i].semaforo == 0){ //si el semaforo esta en cero//rojo
					if (bridges[i].rightArray[0].type == AMBULANCE){ // si el primer carro es una ambulancia
						bridges[i]._countR=0;										//Contador derecho =0
						bridges[i]._countL=0;										//contador izquierdo =0
						break;
					}
				}
				else{
					if (bridges[i].leftArray[0].type == AMBULANCE){
						bridges[i]._countL=0;
						bridges[i]._countR=0;
						break;
					}
				}
			}
			if (sleep < b){
				usleep(timesleep);
				sleep+=timesleep;
			}
			else{
				break;
			}
		}
	}
}

void *Transit_officer(void* BridgeID){

	int i = *((int*) BridgeID);
	bridges[i].oficial = 0;
	while(1){
		if (bridges[i]._countL==bridges[i].k_cars){
			mymutex_lock(&lock);
			bridges[i]._countR = 0;
			bridges[i]._countL = 0;
			bridges[i].oficial = 1;
			mymutex_unlock(&lock);
		}
		else if (bridges[i]._countR==bridges[i].k_cars){
			mymutex_lock(&lock);
			bridges[i]._countR = 0;
			bridges[i]._countL = 0;
			bridges[i].oficial = 0;
			mymutex_unlock(&lock);
		}
		if (DISPATCHER == (int)REAL_TIME){
			if (bridges[i].busy == EMPTY){
				if(bridges[i].oficial == 0){
					if (bridges[i].rightArray[0].type == AMBULANCE){
						bridges[i].oficial = 1;
						bridges[i]._countR=0;
						bridges[i]._countL=0;
					}
				}
				else{
					if (bridges[i].leftArray[0].type == AMBULANCE){
						bridges[i].oficial = 0;
						bridges[i]._countL=0;
						bridges[i]._countR=0;
					}
				}
			}
		}
	}
}


void *Jungle_Law(void* BridgeID){

	int i = *((int*) BridgeID);
	bridges[i].cont = 3;//0->L 1->R

	while(1){
		if (DISPATCHER == (int)REAL_TIME){
			if (bridges[i].busy == EMPTY){

				if (bridges[i].rightArray[0].type == AMBULANCE){
					bridges[i].cont = 1;
					continue;
				}
				if (bridges[i].leftArray[0].type == AMBULANCE){
					bridges[i].cont = 0;
					continue;
				}

				if (bridges[i].rightArray[0].type == RADIOACTIVE_CAR &&
						(bridges[i].leftArray[0].state == THREAD_AVAILABLE
								|| bridges[i].leftArray[0].type == NORMAL_CAR)){
					bridges[i].cont = 1;
					continue;
				}
				if (bridges[i].leftArray[0].type == RADIOACTIVE_CAR &&
						(bridges[i].rightArray[0].state == THREAD_AVAILABLE
								|| bridges[i].rightArray[0].type == NORMAL_CAR)){
					bridges[i].cont = 0;
					continue;
				}

			}
		}
		changetheWay(i);
	}
}
