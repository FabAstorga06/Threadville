
#ifndef DATA_H_
#define DATA_H_

#include <pthread.h>

/*
 *state : 1 -> disponible, otro valor usado.
 *
 */
struct carVille
{
		void* (*fuction) (void*); //
		pthread_t 	id; //
        int 		priority; //
        int 		type; // tipo de carro
        int 		state; //
        char		direction;
        int			bridgeID;
        int			position;
        int 		speed;
};

struct carVille *leftArray;
struct carVille *rightArray;
struct carVille *leftArrayB2;
struct carVille *rightArrayB2;
struct carVille *leftArrayB3;
struct carVille *rightArrayB3;
struct carVille *leftArrayB4;
struct carVille *rightArrayB4;


struct puente{
	int bridge_size;
	int semaforo;
	int oficial;
	int cont;
	int _countR;
	int _countL;
	int k_cars;
	char* control_method;
	struct carVille *bridge;
	struct carVille *leftArray;
	struct carVille *rightArray;
	int busy;
	int bridge_id;
};


struct puente puente1;
struct puente puente2;
struct puente puente3;
struct puente puente4;

struct dataID{
	int BridgeID;
	char side;
};

struct puente bridges[4];

pthread_mutex_t lock;

char* update1;
char* update2;
char* update3;
char* update4;

#endif /* DATA_H_ */
