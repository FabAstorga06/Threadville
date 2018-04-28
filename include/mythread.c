
int _scheduler = 1;

/**
 * Selecciona un algoritmo de calendarizacion
 * indicado en el argumento de la funcion
 * */
void mythread_setsched(int pAlgorithm){
	_scheduler = pAlgorithm;
}

int mymutex_lock(pthread_mutex_t* pLock){
	int iret = pthread_mutex_lock(pLock);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}

int mymutex_unlock(pthread_mutex_t* pLock){
	int iret = pthread_mutex_unlock(pLock);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}

/**
 * Configura el almacenamiento de los threads
 * Solicita el espacio para las colas de datos
 */
int mythread_init(){
	leftArray	= malloc(MAX_THREADS*sizeof(struct carVille*));
	rightArray	= malloc(MAX_THREADS*sizeof(struct carVille*));
	leftArrayB2	= malloc(MAX_THREADS*sizeof(struct carVille*));
	rightArrayB2= malloc(MAX_THREADS*sizeof(struct carVille*));
	leftArrayB3	= malloc(MAX_THREADS*sizeof(struct carVille*));
	rightArrayB3= malloc(MAX_THREADS*sizeof(struct carVille*));

	for(int i=0;i<MAX_THREADS;i++){
  struct carVille* car1=malloc(sizeof(struct carVille));
  struct carVille* car2=malloc(sizeof(struct carVille));
  struct carVille* car3=malloc(sizeof(struct carVille));
  struct carVille* car4=malloc(sizeof(struct carVille));
  struct carVille* car5=malloc(sizeof(struct carVille));
  struct carVille* car6=malloc(sizeof(struct carVille));

  leftArray[i]=car1;
  rightArray[i]=car2;
  leftArrayB2[i]=car3;
  rightArrayB2[i]=car4;
  leftArrayB3[i]=car5;
  rightArrayB3[i]=car6;

 }

	//llenar esas colas con algo

	if (leftArray==NULL) {
		printf("Error - mythread_init() not enough memory");
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	if (rightArray==NULL) {
		printf("Error - mythread_init() not enough memory");
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	if (leftArrayB2==NULL) {
		printf("Error - mythread_init() not enough memory");
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	if (rightArrayB2==NULL) {
		printf("Error - mythread_init() not enough memory");
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	if (leftArrayB3==NULL) {
		printf("Error - mythread_init() not enough memory");
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	if (rightArrayB3==NULL) {
		printf("Error - mythread_init() not enough memory");
		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
	//revisar aca por que las colas solo tienen punteros, no objetos creados
	for (int var = 0; var < MAX_THREADS; ++var) {
		leftArray[var]->state = THREAD_AVAILABLE;
		rightArray[var]->state = THREAD_AVAILABLE;
		leftArrayB2[var]->state = THREAD_AVAILABLE;
		rightArrayB2[var]->state = THREAD_AVAILABLE;
		leftArrayB3[var]->state = THREAD_AVAILABLE;
		rightArrayB3[var]->state = THREAD_AVAILABLE;

	}
	printf("mythread has been initialized \n");
	return MYTHREAD_SUCCESS;

}

/**
 * Crea un nuevo hilo
 * Lo almacena en la cola corresposdiente
 * pStartRoutine -> metodo que ejecutara el thread
 * pArgument -> argumento de la funcion (pStartRoutine)
 */
int mythread_create_car( void* (*pStartRoutine) (void*),void *pArgument){
	int index =verifyForSpace(((struct carVille*)pArgument)->actual_node);//Modificar

	if (index != MYTHREAD_NOT_ENOUGH_MEMORY && index != MYTHREAD_INVALID_SITE){
		pthread_t thread;
		int  iret = pthread_create( &thread, NULL, pStartRoutine, (void*)pArgument);
		//asignar thread a newCar->id;
		if(iret){
			 return MYTHREAD_ERROR;
		}
		else{
			return MYTHREAD_SUCCESS;
		}
	}
	else{

		return MYTHREAD_NOT_ENOUGH_MEMORY;
	}
}

int mythread_create(pthread_t* thread, void* (*pStartRoutine) (void*),  void *pArgument){
	int  iret = pthread_create( thread, NULL, pStartRoutine, pArgument);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}

/**
 * Establece la bandera para poder terminar el thread (mythread_end()) en 1;
 */
void mythread_setcancelstateEnable(){
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}

/**
 * Establece la bandera para poder terminar el thread (mythread_end()) en 0;
 */
void mythread_setcancelstateDisable(){
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
}



/*
 * Configura liberación de recursos cuando el
 * hilo indicado en el argumento termina,
 * sino ha terminado no libera los recursos
 * */
int mythread_detach(pthread_t pIdThread){
	int iret = pthread_detach(pIdThread);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}
/*
 * Termine el thread indicado en el argumento, ademas libera los recursos
 * retorna 1 en exito, codigo del error en caso de falla
 * */
int mythread_end (pthread_t pIdThread){
	int iret = pthread_cancel(pIdThread);
	if (iret == MYTHREAD_OK){
		datachspace(pIdThread);
		return mythread_detach(pIdThread);
	}
	else{
		return MYTHREAD_ERROR;
	}
}

/**
 * El hilo en ejecucion actual cede el procesador a otro hilo
 * */
void mythread_yield(){
	///pthread_yield(NULL);
}

/*
 * Suspende la ejecucion de los demas hilos para terminar
 * el indicado en el argumento pIdThread
 * */
int mythread_join(pthread_t pIdThread){
	int iret = pthread_join(pIdThread, NULL);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}



void mythread_exit(){
	pthread_exit(NULL);
}

int mymutex_init(pthread_mutex_t* pLock){
	int iret = pthread_mutex_init(pLock, NULL);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}

int mymutex_destroy(pthread_mutex_t* pLock){
	int iret = pthread_mutex_destroy(pLock);;
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}
}



int mymutex_trylock(pthread_mutex_t* pLock){
	int iret = pthread_mutex_trylock(pLock);
	if (iret == MYTHREAD_OK){
		return MYTHREAD_SUCCESS;
	}
	else{
		return MYTHREAD_ERROR;
	}


}

//void mythread_setsched(char* sheduler){
//	strcpy(type_dispatcher,sheduler);
//}
