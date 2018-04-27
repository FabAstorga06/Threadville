
/*
 * Verica si hay espacio en las listas para guardar la informacion de los threads
 * pSite -> 1: lado derecho
 * 			0: lado izquierdo
 */
int verifyForSpace(int node){
	if(GRAPH[node].occupied[4]==0){
		return 1;
	}
	else{
		return 0;
	}
}


/*void insertNewThread (struct carVille* newCar){
	int b_ID=newCar->bridgeID;
	int site = newCar->direction;
	if (site == SITE_RIGHT){
		bridges[b_ID].rightArray[pIndex]= newCar;
	}
	if (site == SITE_LEFT){
		bridges[b_ID].leftArray[pIndex]= newCar;
	}


	write_log("There is a new car");

}*/

void datachspace(pthread_t pIdThread){
	for (int i=0;i<MAX_THREADS;i++){
		if (pIdThread == leftArray[i]->id){
			leftArray[i]->state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArray[i]->id){
			rightArray[i]->state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == leftArrayB2[i]->id){
			leftArrayB2[i]->state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArrayB2[i]->id){
			rightArrayB2[i]->state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == leftArrayB3[i]->id){
			leftArrayB3[i]->state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArrayB3[i]->id){
			rightArrayB3[i]->state = THREAD_AVAILABLE;
			break;
		}
	}
}
