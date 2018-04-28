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

int getRandomNode(){
	int node= rand()%SIZE_GRAPH; //amount of nodes
	int flag=0;
	for(int i=0; i<AMOUNT_ENTRANCE_NODES;i++){
		if(node==entrance_nodes[i]){
			flag=1;
		}
	}
	for(int i=0; i<AMOUNT_USELEES_NODES;i++){
		if(node==useless_[i] || flag==1){
			return getRandomNode();
		}
	}
	return node;
}




struct carVille* setCar(int car){
	int priority,a_node,f_node, speed, n_steps,color;

	a_node=getRandomNode();
	f_node=getRandomNode();

	a_node=105;
	f_node=114;
	int* route= dijkstra(a_node,f_node,&n_steps);


	speed =  (rand() % BRIDGE_CARSPEEDPROM)+1;


	if(car == NORMAL_CAR){priority = NORMAL;color=CAR_COLOR;}
	if(car == RADIOACTIVE_CAR){priority = EXTREME;color=RAD_COLOR;}
	if(car == AMBULANCE){priority = HIGH;color=AMB_COLOR;}
	if(car == BUS){priority = NORMAL;color=1;}


	struct carVille* newCar=malloc(sizeof(struct carVille));
	newCar->priority=priority;
	newCar->type=car;
	newCar->state=MYTHREAD_CREATED_STATED;
	newCar->position=4;
	newCar->speed=speed;
	newCar->actual_node=a_node;
	newCar->final_node=f_node;
	newCar->color=color;
	newCar->n_steps=n_steps;
	newCar->route=route;
	newCar->trips=0;
	newCar->inBridge=0;
}


void generateCar(int car) {

	struct carVille* newCar = setCar(car);
	mythread_create_car((void*)runCar, (void*)newCar);
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
	int prob, time_generate_cars;
	int prob_calc;

	while(1){
		time_generate_cars=exp_dist(counter); //time increase with a exponential distribution
		counter++;
		usleep(time_generate_cars);
		prob_calc = calcProb(DIST, lB);
		prob = rand() % 100;

		if (prob < prob_calc){
			int car = typeofcar(p_carB, BRIDGE_AMBULANCEPORC, BRIDGE_RADIACTIVEPORC, prob);
			struct carVille* newCar = setCar(car);
			mythread_create_car((void*)runCar, (void*)newCar);
		}


	}
	return NULL;
}
