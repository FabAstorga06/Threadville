
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

  car->state=MYTHREAD_CREATED_STATED;
  car->inBridge=1;
  switch (car->next_node) {
    case NLB1:{
          car->bridgeID=0;
          car->direction=LEFT;
          break;
    }
    case NRB1:{
          car->bridgeID=0;
          car->direction=RIGHT;
          break;
    }
    case NLB2:{
          car->bridgeID=1;
          car->direction=LEFT;
          break;
    }
    case NRB2:{
          car->bridgeID=1;
          car->direction=RIGHT;
          break;
    }
    case NLB3:{
          car->bridgeID=2;
          car->direction=LEFT;
          break;
    }
    case NRB3:{
          car->bridgeID=2;
          car->direction=RIGHT;
          break;
    }
    default:
      break;
  }

}

void* runCar(struct carVille* car){
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
    mymutex_unlock(&lock);

    /* Write message in log file */
  /*  char message[1024];
     snprintf(message, sizeof message, "Car in node: %d is in position: %d",
             car->actual_node, car->position );
    msg_log_file(message);   */



    if(car->final_node==car->actual_node||car->n_steps==2){
      mymutex_lock(&lock);
      GRAPH[car->actual_node].occupied[4]=NOTOCCUPIED;
      mymutex_unlock(&lock);
      break;
      //create new trip
      //car->trip++;
    }
    else if(car->inBridge==0){
      if(car->position==0){
          if(verifyForSpace(car->next_node)){
            if(verifyNextNode(car->next_node)){
              setBridgeVariables(car);
              GRAPH[car->actual_node].occupied[car->position]=NOTOCCUPIED;
              GRAPH[car->next_node].occupied[4]=OCCUPIED;

              if (car->direction == SITE_RIGHT){
              bridges[car->bridgeID].rightArray[4]= car;
             }
             if (car->direction == SITE_LEFT){
              bridges[car->bridgeID].leftArray[4]= car;
             }
              //GRAPH[car->next_node].car_list[4]=car;
              a=n; n++,car->position=4;
              MoveTail(car);

              //se puede hacer un thread con MOVETAIL;

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

  }

}
