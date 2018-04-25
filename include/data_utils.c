 #define F1 80
 #define F2 81
 #define F3 82
 #define F4 83

/* Generate random number */
unsigned int random_num(int a) {
  return (unsigned int)rand() /(unsigned int)(RAND_MAX/a);
}

/*****************************************************************************/
/* Data structure */

typedef struct vehicle
{
     unsigned int _speed;
     unsigned int _color;
     unsigned int _time;
     unsigned int _model;
     unsigned int _priority;
     int* _route;
} Carville;

/* ---------------------------------- */

/* HACER ALGORITMO DE DIJSKSTRA */


/*****************************************************************************/
/* Verify if F1,F2,F3,F4 key are pressed */
void verify_key_events() {

  char _key = getchar();
  switch (_key) {
    case F1: /* Create car with random values */
      printf("Pressed F1\n");
      break;
    case F2: /* Create car with specific user values  */
      printf("Pressed F2\n");
      break;
    case F3: /* Create an ambulance with random values */
      printf("Pressed F3\n");
      break;
    case F4: /* Create radioactive car with random values */
      printf("Pressed F4\n");
      break;
    default:
    //  printf("Otra tecla\n");
      break;
  }

}
