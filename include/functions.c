
/*
 * Verica si hay espacio en las listas para guardar la informacion de los threads
 */
int verifyForSpace(int node){
	if(GRAPH[node].occupied[4]==0){
		return 1;
	}
	else{
		return 0;
	}
}


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
