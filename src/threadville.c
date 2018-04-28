#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include "config.h"
#include "constants.h"
#include "data.h"
#include "graph.c"
#include "map_utils.c"
#include "log_utils.c"
#include "schedulers.c"
#include "functions.c"
#include "mythread.c"
#include "control_methods.c"
#include "update_simulations.c"
#include "movement_bridges.c"
#include "control_car.c"
#include "generate_car.c"
#include "data_utils.c"


#define NUM_THREADS 7 /* Amount threads */
#define MSG_SIZE 17

//char type_dispatcher[] ="Priority_Scheduler";//"FCFS";//
void create_bridge( struct puente *bridge, int b_size, struct carVille** l_array,
	 				struct carVille **r_array, int k_cars, const char* ctrl_method, int b_id){
	bridge->bridge_size = b_size;

	bridge->bridge =  malloc(bridge->bridge_size*sizeof(struct carVille*));
	for(int i=0; i<bridge->bridge_size;i++){
		struct carVille* space_bridge = malloc(sizeof(struct carVille));
		bridge->bridge[i] = space_bridge;
	}

	for(int i=0; i<bridge->bridge_size; i++){
		bridge->bridge[i]->state = THREAD_AVAILABLE; // THREAD_AVAILABLE -> on file CONSTANTS_H_
	}
	bridge->semaforo = 0;
	bridge->oficial = 0;
	bridge->cont = 0;
	bridge->_countL = 0;
	bridge->_countR = 0;
	bridge->k_cars = k_cars; //number of cars in the bridge

	bridge->control_method = (char*) malloc(25 * sizeof(char) );
    strcpy(bridge->control_method, ctrl_method);
	bridge->leftArray = l_array; //pointer of struct carVille
	bridge->rightArray = r_array; //pointer of struct carVille

	bridge->busy = NOTBUSY;
	bridge->bridge_id = b_id;
}

void TestScheduler(struct puente *bridge, pthread_t* ptr_list_thread, void* (*pStartRoutine) (void*), char* cmp_method ){
  if(!strcmp(bridge->control_method,cmp_method)) {
    int success;
    int* arg= &bridge->bridge_id;
    success = mythread_create(ptr_list_thread, pStartRoutine, arg);
    if (success != MYTHREAD_SUCCESS){ //MYTHREAD_SUCCESS from file constants
      printf("ERROR; return code from mythread_create() is %d\n", success);
      exit(-1);
    }
  }
}

void 	setNodesListToBridges(){
		GRAPH[NLB1].car_list=leftArray;
		GRAPH[NRB1].car_list=rightArray;
		GRAPH[NLB2].car_list=leftArrayB2;
		GRAPH[NRB2].car_list=rightArrayB2;
		GRAPH[NLB3].car_list=leftArrayB3;
		GRAPH[NRB3].car_list=rightArrayB3;
}

int main(){

	msg_log_file("--------------------THREADVILLE ACTIVITY-----------------------");
	srand(time(NULL));
	/* INITIALIZE GRAPH */
	garbageCar=malloc(sizeof(struct carVille));
	garbageCar->priority=4;
	init_map ();

	parse_adjacency_list();
	set_weights(); //Fill the WEIGHTS matrix

	//sleep(2);

	/************************************************************************************/
	pthread_t threads[NUM_THREADS];
	mythread_init();
	if (mymutex_init(&lock) != MYTHREAD_SUCCESS){
		printf("\n mymutex init failed\n");
		exit(-1);
	}
	update1 = (char*)malloc(MSG_SIZE * sizeof(char));
	update2 = (char*)malloc(MSG_SIZE * sizeof(char));
	update3 = (char*)malloc(MSG_SIZE * sizeof(char));

	setNodesListToBridges();
	create_bridge (&bridge1,BRIDGE1_SIZE,leftArray, rightArray, K_CARS1, CONTROL_METHOD_BRIDGE_1, 0); //CONTROL_METHOD_BRIDGE_X from config file
	create_bridge (&bridge2,BRIDGE2_SIZE,leftArrayB2, rightArrayB2, K_CARS2, CONTROL_METHOD_BRIDGE_2, 1);
	create_bridge (&bridge3,BRIDGE3_SIZE,leftArrayB3, rightArrayB3, K_CARS3, CONTROL_METHOD_BRIDGE_3, 2);

	//-----------BRIDGES INICIALIZATION---------
	bridges[0] = bridge1;
	bridges[1] = bridge2;
	bridges[2] = bridge3;

	/* Write messages in log file */
    char message1[100];
	char message2[100];
	char message3[100];
    snprintf(message1, sizeof message1, "Threadville message: The bridge %d is been controlled by %s",
						 bridge1.bridge_id, CONTROL_METHOD_BRIDGE_1);
    msg_log_file(message1);

	snprintf(message2, sizeof message2, "Threadville message: The bridge %d is been controlled by %s",
	 					 bridge2.bridge_id, CONTROL_METHOD_BRIDGE_2);
    msg_log_file(message2);

	snprintf(message3, sizeof message3, "Threadville message: The bridge %d is been controlled by %s",
						 bridge3.bridge_id, CONTROL_METHOD_BRIDGE_3);
    msg_log_file(message3);


	//-----------SEMAFORE------------------
	TestScheduler(&bridges[0], &threads[3], Semaphore,"semaphore");
	TestScheduler(&bridges[1], &threads[4], Semaphore,"semaphore");
	TestScheduler(&bridges[2], &threads[5], Semaphore,"semaphore");

	//-----------TRANSIT OFFICER------------
	TestScheduler(&bridges[0], &threads[3], Transit_officer,"transit_officer");
	TestScheduler(&bridges[1], &threads[4], Transit_officer,"transit_officer");
	TestScheduler(&bridges[2], &threads[5], Transit_officer,"transit_officer");

		//-----------JUNGLE LAW-----------------
	TestScheduler(&bridges[0], &threads[3], Jungle_Law,"jungle_law");
	TestScheduler(&bridges[1], &threads[4], Jungle_Law,"jungle_law");
	TestScheduler(&bridges[2], &threads[5], Jungle_Law,"jungle_law");

	generateCar(RADIOACTIVE_CAR);
	sleep(10);
	/************************************************************************/
	int  rg, rf, rk, rgui;

	//-----------KEYBOARD THREADS-----------
	rk = mythread_create(&threads[0], verify_key_events, NULL);
	if (rk != MYTHREAD_SUCCESS ) {
		printf("ERROR; return code from mythread_create() rk is %d\n", rk);
		exit(-1);
	}

  //-----------UPDATE ARDUINO-------------
    rf = mythread_create(&threads[1], UpdateArduino, NULL);
	if (rf != MYTHREAD_SUCCESS ) {
		printf("ERROR; return code from mythread_create() rf is %d\n", rf);
		exit(-1);
	}

	//-----------GENERATE CARS-------------
	/*rg = mythread_create(&threads[2], generateCars, NULL);
	if (rg != MYTHREAD_SUCCESS ) {
		printf("ERROR; return code from mythread_create() rg is %d\n", rg);
		exit(-1);
	}*/

	//generateCar(RADIOACTIVE_CAR);;

	//-----------MAP UPDATE-----------------
	/*rgui = mythread_create(&threads[6], update_map, NULL);
	if (rgui != MYTHREAD_SUCCESS ) {
		printf("ERROR; return code from mythread_create() rgui is %d\n", rgui);
		exit(-1);
	}*/

	mymutex_destroy(&lock);
	mythread_exit();
}
