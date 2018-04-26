
#ifndef DATA_H_
#define DATA_H_

#include <pthread.h>

#define PATH "adjacency_list.csv"
#define NODE_AMT 46
int* useless_;
/*
 *state : 1 -> disponible, otro valor usado.
 *
 */
struct carVille
{
        int 		priority; //
        pthread_t 	id; //
        int 		type; // type of car 0=NORMAL_CAR; 1= RADIOACTIVE_CAR; 2=AMBULANCE; 3=NOTCAR; 4=BUS
        int 		state; //
        int		  direction; //0 =LEFT 1=RIGHT
        int			bridgeID;
        int			position;
        int 		speed;
        int     actual_node;
        int     final_node;
        int*    route;
				//nodo actual
				//ruta
				//final ruta
				//color *
};

struct carVille**leftArray;
struct carVille**rightArray;
struct carVille**leftArrayB2;
struct carVille**rightArrayB2;
struct carVille**leftArrayB3;
struct carVille**rightArrayB3;


struct puente{
	int bridge_size; //size of the bridge, it must be equal to MAX_THREADS in CONSTANTS_H_ file to get coherence
	int semaforo; //to manage the control method semaphore, 0=LEFT ; 1=RIGHT
	int oficial;
	int cont;
	int _countR; //Number of cars in the rightArray
	int _countL; //Number of cars in the leftArray
	int k_cars; //variable to count the pass of the cars in transit_officer method control
	char* control_method; //type of method control
	struct carVille **bridge; //list of cars in the bridge
	struct carVille **leftArray; //list of cars in the left queue
	struct carVille **rightArray; //list of cars in the right queue
	int busy; //state of the bridge 0= NOTBUSY, 1=BUSY, 2=EMPTY
	int bridge_id; //number of the bridge
};


struct puente puente1;
struct puente puente2;
struct puente puente3;

struct dataID{
	int BridgeID;
	int side;
};

struct puente bridges[3];

pthread_mutex_t lock;

char* update1;
char* update2;
char* update3;

#endif /* DATA_H_ */
