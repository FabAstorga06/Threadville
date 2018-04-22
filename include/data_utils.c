/* constants */
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define ORANGE 5

/* Generate random number */
unsigned int random_num(int a) {
  srand(time(NULL));
  return (unsigned int)rand() /(unsigned int)(RAND_MAX/a);
}

/*****************************************************************************/
/* Data structures */
typedef struct bus
{
     unsigned int _speed;
     char _route;
     unsigned int _color;
} Busville;

/* ---------------------------------- */
typedef struct car
{
     unsigned int _trips;
     unsigned int _speed;
     unsigned int _time;
     unsigned int _model;

} Carville;

/* ---------------------------------- */
typedef struct ambulance
{
     unsigned int _speed;

} Ambuville;

/* ---------------------------------- */
typedef struct radioactive
{
     unsigned int _color;
     unsigned int _speed;

} Radioville;

/* ---------------------------------- */

/* HACER ALGORITMO DE DIJSKSTRA */
