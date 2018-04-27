#define MAX_LENGTH 1024

int verifyNextNode(int node){
  for (int i=0;i<AMOUNT_ENTRANCE_NODES;i++){
    if(node==entrance_nodes[i]){
      return 1;
    }
    else{
      return 0;
    }
  }
}

void setBridgeVariables(struct carVille* car){
  car->position=4;
  car->state=MYTHREAD_CREATED_STATED;
  car->inBridge==1;
  switch (car->next_node) {
    case NLB1:{
          car->bridgeID=1;
          car->direction=LEFT;
          break;
    }
    case NRB1:{
          car->bridgeID=1;
          car->direction=RIGHT;
          break;
    }
    case NLB2:{
          car->bridgeID=2;
          car->direction=LEFT;
          break;
    }
    case NRB2:{
          car->bridgeID=2;
          car->direction=RIGHT;
          break;
    }
    case NLB3:{
          car->bridgeID=3;
          car->direction=LEFT;
          break;
    }
    case NRB3:{
          car->bridgeID=3;
          car->direction=RIGHT;
          break;
    }
    default:
      break;
  }

}

void * runCar(struct carVille* car){
  int a,n;
  a=0;
  n=a+1;  

  mymutex_lock(&lock);
  GRAPH[car->actual_node].occupied[4]=OCCUPIED; //occupy the space in the node equal to actual node
  GRAPH[car->actual_node].car_list[4]=car;
  mymutex_unlock(&lock);

  while(1) {
    usleep(USMOVES*car->speed);
    mymutex_lock(&lock);
    car->actual_node= car->route[a];
    car->next_node= car->route[n];



    if(car->final_node==car->actual_node||car->n_steps==2){
      mymutex_lock(&lock);
      GRAPH[car->actual_node].occupied[4]=NOTOCCUPIED;
      mymutex_unlock(&lock);
      break;
      //create new trip
      //car->trip++;
    }
    if(car->inBridge==0){
      if(car->position==0){
          if(verifyForSpace(car->next_node)){
            if(verifyNextNode(car->next_node)){
              setBridgeVariables(car);
              mymutex_lock(&lock);
              GRAPH[car->actual_node].occupied[car->position]=NOTOCCUPIED;
              GRAPH[car->next_node].occupied[4]=OCCUPIED;
              GRAPH[car->next_node].car_list[4]=car;
              a=n; n++;
              mymutex_unlock(&lock);
              pthread_t thread;
              mythread_create(&thread,(void*)MoveTail,car);

              //se puede hacer un thread con MOVETAIL;

              //setear variables bridge_id, direction, position del carro para el puente que entra position=4;
              //en MoveLeft y MoveRight mover carro a siguiente nodo --> GRAPH[car->actual_node].occupied[4]=NOTOCCUPIED;
                                                                 //  -->GRAPH[car->next_node].occupied[4]=OCCUPIED;
                                                                 //car->inBridge =0;
                                                                 //ver MOVETAIL para verificar cual espacio tiene que desocuparse
                                                                 //a=n; n++;
            }
            else{
              mymutex_lock(&lock);
              GRAPH[car->actual_node].occupied[car->position]=NOTOCCUPIED;
              GRAPH[car->next_node].occupied[4]=OCCUPIED;
              GRAPH[car->next_node].car_list[4]=car;
              a=n; n++; car->position=4;
              mymutex_unlock(&lock);
          }


        }
      }
      else{
        if(GRAPH[car->actual_node].occupied[car->position-1]==NOTOCCUPIED){
          mymutex_lock(&lock);
          GRAPH[car->actual_node].occupied[car->position]=NOTOCCUPIED;
          GRAPH[car->actual_node].occupied[car->position-1]=OCCUPIED;
          GRAPH[car->actual_node].car_list[car->position-1]=car;
          car->position--;
          mymutex_unlock(&lock);
        }
      }
    }
    else{

    }
    /* Write message in log file */
  /*  mymutex_lock(&lock);
    char message[MAX_LENGTH];
    snprintf(message, sizeof message, "Car in node: %d is in position: %d",
             car->actual_node, car->position ); 
    write_log(message);
    mymutex_unlock(&lock);*/
  }

}
