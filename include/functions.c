/*
 * Verifica por espacio en cualquiier posicion
 * */
int verifyForSpaceAux(int pSite, int pBridge){
	if (pSite == SITE_RIGHT){
		for (int var = 0; var < MAX_THREADS; ++var) {
			if (pBridge==1){
				if (rightArray[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
			if (pBridge==2){
				if (rightArrayB2[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
			if (pBridge==3){
				if (rightArrayB3[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
			if (pBridge==4){
				if (rightArrayB4[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
		}
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	else if (pSite == SITE_LEFT){
		for (int var = 0; var < MAX_THREADS; ++var) {
			if (pBridge==1){
				if (leftArray[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
			if (pBridge==2){
				if (leftArrayB2[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
			if (pBridge==3){
				if (leftArrayB3[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
			if (pBridge==4){
				if (leftArrayB4[var].state==THREAD_AVAILABLE){
					return var;
				}
			}
		}
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	else{
		return MYTHREAD_INVALID_SITE;
	}
}

/*
 * Verica si hay espacio en las listas para guardar la informacion de los threads
 * pSite -> 1: lado derecho
 * 			0: lado izquierdo
 */
int verifyForSpace(int pSite, int pFlag, int pBridge){
	if (pFlag){
		if (pSite == SITE_RIGHT){
			if (pBridge==1){
				//printf("B1 SITE_RIGHT verifyForSpace \n");
				if (rightArray[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==2){
				//printf("B2 SITE_RIGHT verifyForSpace \n");
				if (rightArrayB2[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==3){
				//printf("B3 SITE_RIGHT verifyForSpace \n");
				if (rightArrayB3[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==4){
				//printf("B4 SITE_RIGHT verifyForSpace \n");
				if (rightArrayB4[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}

			return MYTHREAD_NOT_ENOUGH_MEMORY;
		}
		else if (pSite == SITE_LEFT){
			if (pBridge==1){
				//printf("B1 SITE_LEFT verifyForSpace \n");
				if (leftArray[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==2){
				//printf("B2 SITE_LEFT verifyForSpace \n");
				if (leftArrayB2[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==3){
				//printf("B3 SITE_LEFT verifyForSpace \n");
				if (leftArrayB3[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			if (pBridge==4){
				//printf("B4 SITE_LEFT verifyForSpace \n");
				if (leftArrayB4[MAX_THREADS-1].state==THREAD_AVAILABLE){
					return MAX_THREADS-1;
				}
			}
			return MYTHREAD_NOT_ENOUGH_MEMORY;
		}
		else{
			return MYTHREAD_INVALID_SITE;
		}
	}
	else{
		return verifyForSpaceAux(pSite, pBridge);
	}
}



/*
 * Inserta un nuevo thread en la pocision indicada
 * por pIndex y en el arregle determido por pSite
 *
 */
void insertNewThread(pthread_t pId, void* (*pFuction) (void*), int pSite, int pPriority, int pType, int pIndex, int pBridge, int pSpeed){
	if (pBridge == 1){
		if (pSite == SITE_RIGHT){
			//printf("B1 SITE_RIGHT insertNewThread \n");
			rightArray[pIndex].state		= MYTHREAD_CREATED_STATED;
			rightArray[pIndex].fuction 		= pFuction;
			rightArray[pIndex].id 			= pId;
			rightArray[pIndex].priority 	= pPriority;
			rightArray[pIndex].type 		= pType;
			rightArray[pIndex].direction    ='D';//Agregue a patir de aqui inclusive
			rightArray[pIndex].bridgeID     = 0;//OJO temporal
			rightArray[pIndex].position     = MAX_THREADS-1;
			rightArray[pIndex].speed        = pSpeed;////aun no se usa
			//int 		speed;
		}
		if (pSite == SITE_LEFT){
			//printf("B1 SITE_LEFT insertNewThread \n");
			leftArray[pIndex].state			= MYTHREAD_CREATED_STATED;
			leftArray[pIndex].fuction 		= pFuction;
			leftArray[pIndex].id 			= pId;
			leftArray[pIndex].priority 		= pPriority;
			leftArray[pIndex].type 			= pType;
			leftArray[pIndex].direction     ='I';//cambiar despues
			leftArray[pIndex].bridgeID      = 0;
			leftArray[pIndex].position      = MAX_THREADS-1;
			leftArray[pIndex].speed         = pSpeed;////aun no se usa
		}
	}
	if (pBridge == 2){
		if (pSite == SITE_RIGHT){
			//printf("B2 SITE_RIGHT insertNewThread \n");
			rightArrayB2[pIndex].state		= MYTHREAD_CREATED_STATED;
			rightArrayB2[pIndex].fuction 		= pFuction;
			rightArrayB2[pIndex].id 			= pId;
			rightArrayB2[pIndex].priority 	= pPriority;
			rightArrayB2[pIndex].type 		= pType;
			rightArrayB2[pIndex].direction    ='D';//Agregue a patir de aqui inclusive
			rightArrayB2[pIndex].bridgeID     = 1;//OJO temporal
			rightArrayB2[pIndex].position     = MAX_THREADS-1;
			rightArrayB2[pIndex].speed        = pSpeed;////aun no se usa
		}

		if (pSite == SITE_LEFT){
			//printf("B2 SITE_LEFT insertNewThread \n");
			leftArrayB2[pIndex].state			= MYTHREAD_CREATED_STATED;
			leftArrayB2[pIndex].fuction 		= pFuction;
			leftArrayB2[pIndex].id 			= pId;
			leftArrayB2[pIndex].priority 		= pPriority;
			leftArrayB2[pIndex].type 			= pType;
			leftArrayB2[pIndex].direction     ='I';//cambiar despues
			leftArrayB2[pIndex].bridgeID      = 1;
			leftArrayB2[pIndex].position      = MAX_THREADS-1;
			leftArrayB2[pIndex].speed         = pSpeed;////aun no se usa
		}
	}
	if (pBridge == 3){
		if (pSite == SITE_RIGHT){
			//printf("B3 SITE_RIGHT insertNewThread \n");
			rightArrayB3[pIndex].state		= MYTHREAD_CREATED_STATED;
			rightArrayB3[pIndex].fuction 		= pFuction;
			rightArrayB3[pIndex].id 			= pId;
			rightArrayB3[pIndex].priority 	= pPriority;
			rightArrayB3[pIndex].type 		= pType;
			rightArrayB3[pIndex].direction    ='D';//Agregue a patir de aqui inclusive
			rightArrayB3[pIndex].bridgeID     = 2;//OJO temporal
			rightArrayB3[pIndex].position     = MAX_THREADS-1;
			rightArrayB3[pIndex].speed        = pSpeed;////aun no se usa
		}
		if (pSite == SITE_LEFT){
			//printf("B3 SITE_LEFT insertNewThread \n");
			leftArrayB3[pIndex].state			= MYTHREAD_CREATED_STATED;
			leftArrayB3[pIndex].fuction 		= pFuction;
			leftArrayB3[pIndex].id 			= pId;
			leftArrayB3[pIndex].priority 		= pPriority;
			leftArrayB3[pIndex].type 			= pType;
			leftArrayB3[pIndex].direction     ='I';//cambiar despues
			leftArrayB3[pIndex].bridgeID      = 2;
			leftArrayB3[pIndex].position      = MAX_THREADS-1;
			leftArrayB3[pIndex].speed         = pSpeed;////aun no se usa
		}
	}
	if (pBridge == 4){
		if (pSite == SITE_RIGHT){
			//printf("B4 SITE_RIGHT insertNewThread \n");
			rightArrayB4[pIndex].state		= MYTHREAD_CREATED_STATED;
			rightArrayB4[pIndex].fuction 		= pFuction;
			rightArrayB4[pIndex].id 			= pId;
			rightArrayB4[pIndex].priority 	= pPriority;
			rightArrayB4[pIndex].type 		= pType;
			rightArrayB4[pIndex].direction    ='D';//Agregue a patir de aqui inclusive
			rightArrayB4[pIndex].bridgeID     = 3;//OJO temporal
			rightArrayB4[pIndex].position     = MAX_THREADS-1;
			rightArrayB4[pIndex].speed        = pSpeed;////aun no se usa
		}
		if (pSite == SITE_LEFT){
			//printf("B4 SITE_LEFT insertNewThread \n");
			leftArrayB4[pIndex].state			= MYTHREAD_CREATED_STATED;
			leftArrayB4[pIndex].fuction 		= pFuction;
			leftArrayB4[pIndex].id 			= pId;
			leftArrayB4[pIndex].priority 		= pPriority;
			leftArrayB4[pIndex].type 			= pType;
			leftArrayB4[pIndex].direction     ='I';//cambiar despues
			leftArrayB4[pIndex].bridgeID      = 3;
			leftArrayB4[pIndex].position      = MAX_THREADS-1;
			leftArrayB4[pIndex].speed         = pSpeed;////aun no se usa
		}
	}
}

void datachspace(pthread_t pIdThread){
	for (int i=0;i<MAX_THREADS;i++){
		if (pIdThread == leftArray[i].id){
			leftArray[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArray[i].id){
			rightArray[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == leftArrayB2[i].id){
			leftArrayB2[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArrayB2[i].id){
			rightArrayB2[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == leftArrayB3[i].id){
			leftArrayB3[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArrayB3[i].id){
			rightArrayB3[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == leftArrayB4[i].id){
			leftArrayB4[i].state = THREAD_AVAILABLE;
			break;
		}
		if (pIdThread == rightArrayB4[i].id){
			rightArrayB4[i].state = THREAD_AVAILABLE;
			break;
		}
	}
}
