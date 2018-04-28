
#ifndef DATA_H_
#define DATA_H_

#include <pthread.h>

#define PATH "adjacency_list.csv"
#define NODE_AMT 46
#define ROWS 12
#define COLS 17

int useless_[AMOUNT_USELEES_NODES]={18,20,22,25,28,30,32,
									42,
									57,58,59,60,61,
									69,71,73,76,79,81,83,
									93,
									108,109,110,111,112,
									120,122,124,127,130,132,134,
									144,
									159,160,161,162,163,
									171,173,175,178,181,183,185};
int WEIGHTS [ROWS*COLS][ROWS*COLS]; // [ROWS*COLS] [ROWS*COLS]

unsigned int gui_mtx[ROWS][COLS];

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
        int		    direction; //0 =LEFT 1=RIGHT
        int			bridgeID;
        int			position;
        int 		speed;
        int         actual_node;
        int         next_node;
        int         final_node;
        int*        route;
        int         color;
        int         n_steps;
        int         trips;
        int         inBridge;
				//nodo actual
				//ruta
				//final ruta
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


struct puente bridge1;
struct puente bridge2;
struct puente bridge3;

struct carVille* garbageCar;

int bridge_nodes[AMOUNT_BRIDGES_NODES]={57, 58, 59, 60, 61, 108, 109, 110, 111,112, 159, 160, 161, 162, 163};

int entrance_nodes[AMOUNT_ENTRANCE_NODES]={NLB1,NRB1,NLB2,NRB2,NLB3,NRB3};
struct puente bridges[3];

pthread_mutex_t lock;

char* update1;
char* update2;
char* update3;

int routeBusOrange[STEPSBUSORANGE]={6,33,40,74,91,125,142,176,193,197,180,146,124,95,76,44,27,10};
int routeBusRed[STEPSBUSRED]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,31,50,67,84,101,118,135,152,169,186,203,
										202,201,200,199,198,197,196,195,194,193,192,191,190,187,170,163,156,119,102,85,68,51,34,17};
int routeBusYellow[STEPSBUSYELLOW]={104,105,106,107,113,114,115,116,99,82,65,48,47,46,45,39,38,37,36,53,70,87};
int routeBusGreen[STEPSBUSGREEN]={101,118,135,152,151,150,149,148,147,141,140,139,138,137,136,119,102,85,68,51,
																	52,53,54,55,56,62,63,64,65,66,67,84};
int routeBusBlue[STEPSBUSBLUE]={97,96,90,89,88,87,104,126,138,155,156,157,158,164,165,166,167,150,133,116,99,98};
//Red bus: A1, B2, C2, roundabout, Y, roundabout, D2, E2, F2, L2, R2, X2, X3, W3, V3, roundabout, Z, roundabout, U3, T3, S3, M3, G3, A3, A1
//Green bus: L4, R4, R3, Q3, P3, O3, N3, M3, G3, G2, H2, I2, J2, K2, L2, L4.
//Blue bus: J4, I3, H3, N3, T2, U2, V2, W2, R1, K4, J4.
//Yellow bus: N1, O1, P2, Q2, L3, E4, D4, C3, B3, H3, N1.
//Orange bus: Y, Z

#endif /* DATA_H_ */
