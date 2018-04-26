
/*
 * Verica si hay espacio en las listas para guardar la informacion de los threads
 * pSite -> 1: lado derecho
 * 			0: lado izquierdo
 */
int verifyForSpace(int pSite, int pBridge){
		if (pSite == SITE_RIGHT){
			if (pBridge==0){
				//printf("B1 SITE_RIGHT verifyForSpace \n");
				if (rightArray[MAX_THREADS-1]->state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==1){
				//printf("B2 SITE_RIGHT verifyForSpace \n");
				if (rightArrayB2[MAX_THREADS-1]->state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==2){
				//printf("B3 SITE_RIGHT verifyForSpace \n");
				if (rightArrayB3[MAX_THREADS-1]->state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			return MYTHREAD_NOT_ENOUGH_MEMORY;
		}
		else if (pSite == SITE_LEFT){
			if (pBridge==0){
				//printf("B1 SITE_LEFT verifyForSpace \n");
				if (leftArray[MAX_THREADS-1]->state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==1){
				//printf("B2 SITE_LEFT verifyForSpace \n");
				if (leftArrayB2[MAX_THREADS-1]->state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==2){
				//printf("B3 SITE_LEFT verifyForSpace \n");
				if (leftArrayB3[MAX_THREADS-1]->state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			return MYTHREAD_NOT_ENOUGH_MEMORY;
		}
		else{
			return MYTHREAD_INVALID_SITE;
		}

}


void insertNewThread (struct carVille* newCar,int pIndex){
	int b_ID=newCar->bridgeID;
	int site = newCar->direction;
	if (site == SITE_RIGHT){
		bridges[b_ID].rightArray[pIndex]= newCar;
	}
	if (site == SITE_LEFT){
		bridges[b_ID].leftArray[pIndex]= newCar;
	}
	

	write_log("There is a new car");

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
