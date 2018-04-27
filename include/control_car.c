void * runCar(struct carVille* car){
  int final_node,actual_node,next_node;
  int a,n,f;

  f=(car->n_steps-1);
  a=0;
  n=a+1;

  final_node= car->route[f];



  mymutex_lock(&lock);
  GRAPH[actual_node].occupied[0]=1; //occupy the space in the node equal to actual node
  mymutex_unlock(&lock);

  while(1){
    //USLEEP de la velocidad del carro

    mymutex_lock(&lock);
    car->actual_node= car->route[a];
    car->next_node= car->route[n];
    mymutex_unlock(&lock);

    if(final_node==car->actual_node){
      mymutex_lock(&lock);
      GRAPH[car->actual_node].occupied[0]=0;
      mymutex_unlock(&lock);
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
            GRAPH[car->actual_node].occupied[car->position]=0;
            GRAPH[car->next_node].occupied[0]=1;
            GRAPH[car->next_node].car_list[0]=car;
            a=n; n++; car->position=0;
            mymutex_unlock(&lock);
        }
      }
      else{
        if(GRAPH[car->actual_node].occupied[car->position+1]==0){
          mymutex_lock(&lock);
          GRAPH[car->actual_node].occupied[car->position]=0;
          GRAPH[car->actual_node].occupied[car->position+1]=1;
          car->position++;
          mymutex_unlock(&lock);
        }
      }
    }
    else{

    }
  }

}
