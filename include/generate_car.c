int calcProb(int pExp, float pMedian){
	float exp = pMedian*pExp*(-1);
	float e = 2.718282f;
	float result = (1 - powf(e, exp))*100;
	int r = (int)result;
	return r;
}


int typeofcar(int pCar, int pAmb, int pRad, int pProb){
	if (pProb >= 0 && pProb <= pCar){
		return 0;
	}
	if (pProb > pCar && pProb <= (pCar+pAmb)){
		return 1;
	}
	if (pProb > (pCar+pAmb) && pProb <= (pCar+pAmb+pRad)){
		return 2;
	}
	return 3;
}


void* generateCars() {

	int uno = 1;
	int p_carB1 = 100 - BRIDGE1_AMBULANCEPORC - BRIDGE1_RADIACTIVEPORC; //car probabilities for each bridge
	int p_carB2 = 100 - BRIDGE2_AMBULANCEPORC - BRIDGE2_RADIACTIVEPORC; //
	int p_carB3 = 100 - BRIDGE3_AMBULANCEPORC - BRIDGE3_RADIACTIVEPORC;
	int p_carB4 = 100 - BRIDGE4_AMBULANCEPORC - BRIDGE4_RADIACTIVEPORC;

	if (p_carB1 < 0 || p_carB2 < 0 || p_carB3 < 0 || p_carB4 < 0){
		printf("Error en definir probabilidades");
		return NULL;
	}

	float lB1 = (float)uno / (float)BRIDGE1_DISTRIBUTION;
	float lB2 = (float)uno / (float)BRIDGE2_DISTRIBUTION;
	float lB3 = (float)uno / (float)BRIDGE3_DISTRIBUTION;
	float lB4 = (float)uno / (float)BRIDGE4_DISTRIBUTION;

	int prob, site, car, vel;
	int s1 = 0;
	int s2 = 0;
	int s3 = 0;
	int s4 = 0;
	int prob_calc;
	int x = 20;
	int max_x=25;
	struct dataID carID1 = {0,'I'};
	struct dataID carID2 = {1,'I'};
	struct dataID carID3 = {2,'I'};
	struct dataID carID4 = {3,'I'};
	while(1){
		usleep(USCARS);
		prob_calc = calcProb(x, lB1);
		prob = rand() % 100;
		if (prob < prob_calc){
			vel =  (rand() % BRIDGE1_CARSPEEDPROM)+1;
			if (s1 == 0){s1=1;site  = 0;carID1.side='I';}//LEFT
			else{s1=0;site  = 1;carID1.side='D';}//RIGHT
			car = typeofcar(p_carB1, BRIDGE1_AMBULANCEPORC, BRIDGE1_RADIACTIVEPORC, prob);
			mythread_create_car((void*)MoveTail, (void*)&carID1, car, site, 1, 1, vel);
			//printf("car type B1: %d \n", car);
		}

		prob_calc = calcProb(x, lB2);
		prob = rand() % 100;
		if (prob < prob_calc){
			vel =  (rand() % BRIDGE2_CARSPEEDPROM)+1;
			if (s2 == 0){s2=1;site  = 0;carID2.side='I';}//LEFT
			else{s2=0;site  = 1;carID2.side='D';}//RIGHT
			car = typeofcar(p_carB2, BRIDGE2_AMBULANCEPORC, BRIDGE2_RADIACTIVEPORC, prob);
			mythread_create_car((void*)MoveTail, (void*)&carID2, car, site, 1, 2, vel);
			//printf("car type B2: %d \n", car);
		}

		prob_calc = calcProb(x, lB3);
		prob = rand() % 100;
		if (prob < prob_calc){
			vel = (rand() % BRIDGE3_CARSPEEDPROM)+1;
			if (s3 == 0){s3=1;site  = 0;carID3.side='I';}//LEFT
			else{s3=0;site  = 1;carID3.side='D';}//RIGHT
			car = typeofcar(p_carB3, BRIDGE3_AMBULANCEPORC, BRIDGE3_RADIACTIVEPORC, prob);
			mythread_create_car((void*)MoveTail, (void*)&carID3, car, site, 1, 3, vel);
			//printf("car type B3: %d \n", car);
		}

		prob_calc = calcProb(x, lB4);
		prob = rand() % 100;
		if (prob < prob_calc){
			vel =  1+(rand() % BRIDGE4_CARSPEEDPROM);
			if (s4 == 0){s4=1;site  = 0;carID4.side='I';}//LEFT
			else{s4=0;site  = 1;carID4.side='D';}//RIGHT
			car = typeofcar(p_carB4, BRIDGE4_AMBULANCEPORC, BRIDGE4_RADIACTIVEPORC, prob);
			mythread_create_car((void*)MoveTail, (void*)&carID4, car, site, 1, 4, vel);
			//printf("car type B4: %d \n", car);
		}
		//printf("\n");
		x++;
		if (x==max_x){
			x--;
		}

	}
	return NULL;
}
