int calcProb(int pExp, float pMedian){
	float exp = pMedian*pExp*(-1);
	float e = 2.718282f;
	float result = (1 - powf(e, exp))*100;
	int r = (int)result;
	return r;
}


int typeofcar(int pCar, int pAmb, int pRad, int pProb){
	if (pProb >= 0 && pProb <= pCar){
		return 0;//NORMAL_CAR
	}
	if (pProb > pCar && pProb <= (pCar+pAmb)){
		return 1; //RADIOACTIVE_CAR
	}
	if (pProb > (pCar+pAmb) && pProb <= (pCar+pAmb+pRad)){
		return 2;//AMBULANCE
	}
	return 3;
}
int exp_dist(int x){
	return	700000*exp(-(x/200000))+100000;
}

void generateCar(int car) {

	int bridge_id=rand()%3; //generate a random number between 0 and 3
	int site=rand()%2;
	struct dataID carID = {bridge_id,site};
	int vel =  (rand() % BRIDGE_CARSPEEDPROM)+1;
	mythread_create_car((void*)MoveTail, (void*)&carID, car, site, bridge_id, vel);
}

void* generateCars(){

	int uno = 1;
	int counter=1000;
	int p_carB = 100 - BRIDGE_AMBULANCEPORC - BRIDGE_RADIACTIVEPORC; //car probabilities to determinate if gets an ambulance or a radioactive
	if (p_carB < 0 ){
		printf("Error en definir probabilidades");
		return NULL;
	}
	float lB = (float)uno / (float)BRIDGE_DISTRIBUTION;
	int prob, car,time_generate_cars;
	int prob_calc;

	while(1){
		time_generate_cars=exp_dist(counter); //time increase with a exponential distribution
		counter++;
		usleep(time_generate_cars);
		prob_calc = calcProb(DIST, lB);
		prob = rand() % 100;

		if (prob < prob_calc){
			car = typeofcar(p_carB, BRIDGE_AMBULANCEPORC, BRIDGE_RADIACTIVEPORC, prob);
			int bridge_id=rand()%3; //generate a random number between 0 and 3
			int site=rand()%2;
			struct dataID carID = {bridge_id,site};
			int vel =  (rand() % BRIDGE_CARSPEEDPROM)+1;
			mythread_create_car((void*)MoveTail, (void*)&carID, car, site, bridge_id, vel);
		}


	}
	return NULL;
}
