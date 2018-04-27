
//Variable global




#define CAR_AMT 5
#define _INFINITY 999999;
#define ADJ_MAP "include/adjacency_list.csv"
struct Node* GRAPH ;

//The city is created by Blocks that contains GRAPH.
//The Node is the basic structure for the map.
typedef struct Node{
    int position;
    struct carVille** car_list; //Each node may hold up to five cars.
    int amount_of_carVilles;
    int occupied [5];
    char isEmpty;
    //Maximum 2 successors according to the city design.
    struct Node* successor_1;
    struct Node* successor_2;
} NODE;

//Adds the created node to the graph and stablish its connections
void add_node (NODE* node, int position){
    GRAPH [position] = *node;
}

//Allocates a node in memory and initialize its data
NODE* create_node (int _position){
    NODE* node = (NODE*) calloc (sizeof(NODE), sizeof(NODE));
    node->car_list = (struct carVille**) calloc (sizeof(struct carVille*) * 5, sizeof(struct carVille*));
    for(int i = 0; i < 5; i++){
        struct carVille* car = malloc(sizeof(struct carVille));
        node->car_list[i] = car;
    }
    node->position = _position;
    node->amount_of_carVilles = 0;
    node->isEmpty = 0;
    return node;
}

void set_successors (int position, int* edges){

    if(edges[0] != -1){
    GRAPH [position].successor_1 = &GRAPH [edges[0]];
    }
    else{
        GRAPH [position].successor_1 = NULL;
    }
    if(edges[1] != -1){
    GRAPH [position].successor_2 = &GRAPH [edges[1]];
    }
    else{
        GRAPH [position].successor_2 = NULL;
    }
}

//Take a line of the .csv file and parse it.
const char* getfield(char* line, int num){
    const char* tok;
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n")){
        if (!--num)
            return tok;
    }
    return NULL;
}

//Reads the adjacency_list file and convert its information to data we can use to create the node
void parse_adjacency_list(){
    FILE* stream = fopen(ADJ_MAP, "r");
    char line[1024];
    int pos_in_graph;   //j + i*COLS
    int edge [2];
    while (fgets(line, 1024, stream)){
        char* tmp = strdup(line);

        //Variables needed to initiale the node
        pos_in_graph = atoi(getfield(tmp,1));

        //Create the node
        add_node(create_node(pos_in_graph), pos_in_graph);
        free(tmp);
    }
    fclose (stream);
    FILE* stream2 = fopen("include/adjacency_list.csv", "r");
    while (fgets(line, 1024, stream2)){
        char* tmp = strdup(line);
        char* tmp3 = strdup(line);
        char* tmp4 = strdup(line);

        pos_in_graph = atoi(getfield(tmp,1));
        edge [0] = atoi(getfield(tmp3,4));
        edge [1] = atoi(getfield(tmp4,5));

        set_successors(pos_in_graph, edge);
        free(tmp3);
        free(tmp4);
    }
    fclose (stream2);
}

//Set the initial weights to the WEIGHTS matrix
void set_weights(){
    for (int i = 0; i < ROWS*COLS; i++){
        for (int j = 0; j < COLS*ROWS; j++){
            int k;
            WEIGHTS [i][j] = _INFINITY;
            if (GRAPH [i].successor_1 != NULL){
                 k = GRAPH [i].successor_1->position;
                 if (k == j){
                     WEIGHTS [i][k] = GRAPH [i].successor_1->amount_of_carVilles;
                 }
            }
            if (GRAPH [i].successor_2 != NULL){
                k = GRAPH [i].successor_2->position;
                if (k == j){
                    WEIGHTS [i][k] = GRAPH [i].successor_2->amount_of_carVilles;
                }
            }
        }
    }
}

//Return the useless nodes of the graph. This is, so cars don't spawn in these nodes
int* useless_nodes(){
    int* useless = (int*) malloc (46 * sizeof(int));
    int counter = 0;
    for (int i = 0; i < ROWS*COLS; i++){
        NODE* node = &GRAPH[i];
        if (node->successor_1 == NULL && node->successor_2 == NULL){
            useless [counter] = i;
            counter++;
        }
    }
    return useless;
}

/*
 *
 *
 * FUNCITON JUST FPR THE GRTAPHIAL INTERFACE
 * Determines the most important vehicle in each node to print it in the GUI.
 * Return the color of the vehicle so it get painted
 */

void most_important_vehicle() {
    int* color_list = (int *) malloc (ROWS*COLS * sizeof(int));
    for (int i = 0; i < ROWS*COLS; i++){
        int _priority = 0;
        int _color = 0;
        for(int j = 0; j < CAR_AMT; j++){
            if ((GRAPH[i].car_list[j]->priority) > _priority){
                _priority = GRAPH [i].car_list[j]->priority;
                _color = GRAPH [i].car_list[j]->color;
            }
        }
        color_list[i] = _color;
    }
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            gui_mtx [i][j] = color_list [j + i*COLS];
        }
    }
}



//Initializes the whole map. Allocates it in memory
void init_map (){ //Allocates the memory for the adjacency list of the graph
    GRAPH = malloc(ROWS * COLS * sizeof(struct Node));
}

/*
 *
 *  PATH FINDING FUNCTIONS WITH DIJKSTRA
 *
 */

int* dijkstra(int start_node, int end_node, int *size){
    int node_amt = ROWS * COLS;
    int MAX = COLS * ROWS; //204 Maximum account of nodes
    int distance [MAX];
    int pred [MAX];
    int visited [MAX]; //List with the already visited nodes
    int count;  //Nodes seen so far
    int mindistance;
    int nextnode = 1;

    //initialize pred[], distance[] and visited[]
    for(int i = 0; i < node_amt; i++){
        distance [i] = WEIGHTS[start_node][i];
        pred [i] = start_node;
        visited [i] = 0;
    }

    distance [start_node] = 0;
    visited [start_node] = 1;
    count = 1;

    //Arrays used to set the final path.
    int* path;
    int* reversed;

    while (count < node_amt - 1){
        mindistance = _INFINITY;

        //nextnode gives the node at minimum distance
        for (int i = 0; i < node_amt; i++){
            if (distance[i] < mindistance && !visited[i]){
                mindistance = distance[i];
                nextnode = i;
            }
        }
        //check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (int j = 0; j < node_amt; j++){
            if (!visited[j]){
                if (mindistance + WEIGHTS[nextnode][j] < distance[j]){
                    distance[j] = mindistance + WEIGHTS[nextnode][j];
                    pred[j] = nextnode;
                }
            }
        }
        count ++;
    }
    //The DIJKSTRA algorithm logic ends here

    //Print the path and distance of each node
    int contador = 1;

    if (end_node != start_node){
        printf("\nDistance of node%d=%d", end_node, distance[end_node]);
        printf("\nPath=%d", end_node);

        int j = end_node;
        do{
            contador++;
            j = pred[j];
        }while (j != start_node);

        //Generates the path array with the nodes to visit
        path = (int*) malloc (contador * sizeof(int));
        int* reversed = (int*) malloc (contador * sizeof(int));
        reversed [0] = end_node;
        j = end_node;
        int k = 1;
        do{
            j = pred[j];
            reversed [k] = j;
            printf("<-%d", reversed [k]);
            k++;
        }while (j != start_node);
        printf("\n");

        //Reverse the path array
        for (int i = 0, n = contador - 1; i < contador; i++, n--){
            path [i] = reversed [n];
        }

    }
    *(size) = contador;
    return path;

    //Return an array with the path from the initial node to the end node
}
