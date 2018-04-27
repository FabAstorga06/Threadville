void * runCar(struct carVille* car){
  int final_node,actual_node,next_node;
  int a,n,f;

  f=(car->n_steps-1);
  a=0;
  n=a+1;

  final_node= car->route[f];



  mymutex_lock(&lock);
  GRAPH[car->actual_node].car_list[0]=car;
  GRAPH[car->actual_node].occupied[0]=OCCUPIED; //occupy the space in the node equal to actual node
  mymutex_unlock(&lock);

  while(1){
    sleep(2*car->speed);

    mymutex_lock(&lock);
    car->actual_node= car->route[a];
    car->next_node= car->route[n];
    mymutex_unlock(&lock);

    if(final_node==car->actual_node){
      mymutex_lock(&lock);
      GRAPH[car->actual_node].occupied[0]=NOTOCCUPIED;
      mymutex_unlock(&lock);
      break;
      //create new trip
      //car->trip++;
    }
    if(car->inBridge==0){
      if(car->position==4){
          if(verifyForSpace(next_node)){
            /*if(verificar si el siguiente nodo es de un puente){
              //car->inBridge==1;
              //setear variables bridge_id, direction, position del carro para el puente que entra
              //en MoveLeft y MoveRight mover carro a siguiente nodo --> GRAPH[car->actual_node].occupied[0]=0;
                                                                 //  -->GRAPH[car->next_node].occupied[0]=1;
                                                                 //car->inBridge =0;
                                                                 //ver MOVETAIL para verificar cual espacio tiene que desocuparse
            }else{}*/

            mymutex_lock(&lock);
            GRAPH[car->actual_node].occupied[car->position]=NOTOCCUPIED;
            GRAPH[car->next_node].occupied[0]=OCCUPIED;
            GRAPH[car->next_node].car_list[0]=car;
            a=n; n++; car->position=0;
            mymutex_unlock(&lock);
        }
      }
      else{
        if(GRAPH[car->actual_node].occupied[car->position+1]==NOTOCCUPIED){
          mymutex_lock(&lock);
          GRAPH[car->actual_node].occupied[car->position]=NOTOCCUPIED;
          GRAPH[car->actual_node].occupied[car->position+1]=OCCUPIED;
          GRAPH[car->actual_node].car_list[car->position+1]=car;
          car->position++;
          mymutex_unlock(&lock);
        }
      }
    }
    else{

    }
  }

}
