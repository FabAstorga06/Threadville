int bridgeEmpty(int bridgeID){


	for(int i=0; i<(bridges[bridgeID].bridge_size); i++){

		mymutex_lock(&lock);
		if(bridges[bridgeID].bridge[i]->state!=THREAD_AVAILABLE){
			return 0;
		}
		mymutex_unlock(&lock);
	}
	return 1;
}


int verifyDirection(int direction, int bridgeID){


	for(int i=0; i<(bridges[bridgeID].bridge_size); i++){

		mymutex_lock(&lock);
		if(bridges[bridgeID].bridge[i]->state!=THREAD_AVAILABLE){
			if (direction != bridges[bridgeID].bridge[i]->direction){
				return 0;
			}
		}
		mymutex_unlock(&lock);
	}
	return 1;
}

void MoveLeft(struct carVille* car){//validar si el de la entrada esta ocupado

	int p = car->bridgeID;
	bridges[p]._countL++;
	bridges[p].busy = BUSY;
	int i = bridges[p].bridge_size -1;//99;
	struct carVille* tmpcar;
	//tmpcar->state = THREAD_AVAILABLE;
	while(1){

		mymutex_lock(&lock);
		if(bridges[p].bridge[i]->state){
			car->state=0; //No disponible
			bridges[p].bridge[i] = car;

			break;
		}
		mymutex_unlock(&lock);
	}
	usleep(USMOVES*car->speed);//*car.speed);
	while(i>=0){
		mymutex_lock(&lock);
		if(i == 0){
			bridges[p].bridge[0]->state = THREAD_AVAILABLE;
			i--;
			continue;
		}

		if(bridges[p].bridge[i-1]->state){
			tmpcar = bridges[p].bridge[i-1];
			bridges[p].bridge[i-1] = bridges[p].bridge[i];
			bridges[p].bridge[i] = tmpcar;
			if (i==(bridges[p].bridge_size-1) && DISPATCHER == (int)ROUND_ROBIN){
				bridges[p].busy = NOTBUSY;
			}
			i--;
		}
		mymutex_unlock(&lock);
		usleep(USMOVES*car->speed);
	}
	if (bridgeEmpty(p)){
		bridges[p].busy = EMPTY;
		usleep(USMOVES/4);
		bridges[p].busy = NOTBUSY;
	}
	if (DISPATCHER != (int)ROUND_ROBIN){
		bridges[p].busy = NOTBUSY;
	}

}


void MoveRight(struct carVille *car){

	int p = car->bridgeID;
	bridges[p]._countR++;
	bridges[p].busy = BUSY;
	struct carVille *tmpcar;

	int i=0;
	while(1){
		mymutex_lock(&lock);
		if(bridges[p].bridge[i]->state){
			car->state=0;
			bridges[p].bridge[i] = car;
			break;
		}
		mymutex_unlock(&lock);
	}
	bridges[p].cont = 1;
	usleep(USMOVES*car->speed);//*car.speed);

	while(i<(bridges[p].bridge_size-1)){

		mymutex_lock(&lock);
		if(bridges[p].bridge[i+1]->state){
			tmpcar = bridges[p].bridge[i+1];
			bridges[p].bridge[i+1] = bridges[p].bridge[i];
			bridges[p].bridge[i] = tmpcar;
			if (i==1 && DISPATCHER == (int)ROUND_ROBIN){
				bridges[p].busy = NOTBUSY;
			}
			i++;
		}

		mymutex_unlock(&lock);
		usleep(USMOVES*car->speed);//*car.speed);
	}
	mymutex_lock(&lock);
	bridges[p].bridge[i]->state = THREAD_AVAILABLE;
	mymutex_unlock(&lock);
	if (bridgeEmpty(p)){
		bridges[p].busy = EMPTY;
		usleep(USMOVES/4);
		bridges[p].busy = NOTBUSY;
	}
	if (DISPATCHER != (int)ROUND_ROBIN){
		bridges[p].busy = NOTBUSY;
	}


}

void *MoveTail(struct dataID* precar){//(void *thread_data){//velocidad se puede incluir en struct
	struct carVille* car;
	int c = precar->side;
	if(c == RIGHT){// lado donde el carro se encuentra D-> Derecha I-> Izquierda
		car = bridges[precar->BridgeID].rightArray[MAX_THREADS-1]; // se obtiene el ultimo de la fila
	}else if(c == LEFT){
		car = bridges[precar->BridgeID].leftArray[MAX_THREADS-1];
	}else{
		return NULL;
	}

	int direction = car->direction; //direccion del carro
	int i = MAX_THREADS-1; // número de la ultima posicion de la lista de carros
	//car->position = MAX_THREADS-1;//¿¿¿¿????
	int n_puente = car->bridgeID; //id del puente al que pertenece


	while(1){
		mymutex_lock(&lock);
		i = DispatcherCars(n_puente, car->position, direction); //aplica calendarizacion
		mymutex_unlock(&lock);

		if(i == 0){
			mymutex_lock(&lock);
			if(!strcmp(bridges[n_puente].control_method,"semaphore")){
				mymutex_lock(&lock);

				if(car->direction ==LEFT && bridges[n_puente].semaforo == 0 &&  bridges[car->bridgeID].busy == NOTBUSY
						&& verifyDirection(LEFT, n_puente) ){
					car = bridges[n_puente].leftArray[0];
					bridges[n_puente].leftArray[0]->state = THREAD_AVAILABLE;
					DispatcherCars(n_puente, car->position, direction);
					MoveLeft(car);
					break;
				}
				else if(car->direction ==RIGHT && bridges[n_puente].semaforo == 1 && bridges[car->bridgeID].busy == NOTBUSY
						&& verifyDirection(RIGHT, n_puente)){//car.direction,
					car = bridges[n_puente].rightArray[0];
					bridges[n_puente].rightArray[0]->state = THREAD_AVAILABLE;
					DispatcherCars(n_puente, car->position, direction);
					MoveRight(car);
					break;
				}
			}

			else if(!strcmp(bridges[n_puente].control_method,"transit_officer")){
				int b = bridges[n_puente].oficial == 0 || bridges[n_puente].oficial == 3;
				int b2 = bridges[n_puente].oficial == 1 || bridges[n_puente].oficial == 3;
				if(car->direction ==LEFT && b && bridges[car->bridgeID].busy == NOTBUSY
						&& verifyDirection(LEFT, n_puente)){
					car = bridges[n_puente].leftArray[0];
					bridges[n_puente].leftArray[0]->state = THREAD_AVAILABLE;
					DispatcherCars(n_puente, car->position, direction);
					MoveLeft(car);
					break;
				}
				else if(car->direction ==RIGHT && b2 &&  bridges[car->bridgeID].busy == NOTBUSY
						&& verifyDirection(RIGHT, n_puente)){
					car = bridges[n_puente].rightArray[0];
					bridges[n_puente].rightArray[0]->state = THREAD_AVAILABLE;
					DispatcherCars(n_puente, car->position, direction);
					MoveRight(car);
					break;
				}
			}
			else if(!strcmp(bridges[n_puente].control_method,"jungle_law")){
				int b = bridges[n_puente].cont == 0 || bridges[n_puente].cont == 3;
				int b2 = bridges[n_puente].cont == 1 || bridges[n_puente].cont == 3;
				if(b && bridges[car->bridgeID].busy == NOTBUSY){
					car = bridges[n_puente].leftArray[0];
					bridges[n_puente].leftArray[0]->state = THREAD_AVAILABLE;
					DispatcherCars(n_puente, car->position, direction);
					MoveLeft(car);
					break;
				}

				else if(b2 &&  bridges[car->bridgeID].busy == NOTBUSY){
					car = bridges[n_puente].rightArray[0];
					bridges[n_puente].rightArray[0]->state = THREAD_AVAILABLE;
					DispatcherCars(n_puente, car->position, direction);
					MoveRight(car);
					break;
				}
			}
			mymutex_unlock(&lock);
		}
		car->position = i;

		usleep(USMOVETAIL);
	}
	return NULL;
}
