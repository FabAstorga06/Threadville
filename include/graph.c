
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
<<<<<<< HEAD
    NODE* node = malloc(sizeof(NODE));
    node->car_list = malloc (sizeof(struct carVille*) * 5);
    for(int i=0;i<5;i++){
      node->car_list[i]=garbageCar;
=======
    NODE* node = (NODE*) calloc (sizeof(NODE), sizeof(NODE));
    node->car_list = (struct carVille**) calloc (sizeof(struct carVille*) * 5, sizeof(struct carVille*));
    for(int i = 0; i < 5; i++){
        struct carVille* car = malloc(sizeof(struct carVille));
        node->car_list[i] = car;
>>>>>>> 18a14c2f25229c73c3e13b9d12604203905b06da
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
<<<<<<< HEAD

int edge[2];
for(int i=0;i<SIZE_GRAPH;i++){
    add_node(create_node(i), i);
}

  edge[0]=1; edge[1]=-1;set_successors(0,edge);
  edge[0]=2; edge[1]=-1;set_successors(1,edge);
  edge[0]=3; edge[1]=19;set_successors(2,edge);
  edge[0]=4; edge[1]=-1;set_successors(3,edge);
  edge[0]=5; edge[1]=-1;set_successors(4,edge);
  edge[0]=6; edge[1]=-1;set_successors(5,edge);
  edge[0]=7; edge[1]=23;set_successors(6,edge);
  edge[0]=8; edge[1]=24;set_successors(7,edge);
  edge[0]=9; edge[1]=-1;set_successors(8,edge);
  edge[0]=10; edge[1]=-1;set_successors(9,edge);
  edge[0]=11; edge[1]=6;set_successors(10,edge);
  edge[0]=12; edge[1]=-1;set_successors(11,edge);
  edge[0]=13; edge[1]=29;set_successors(12,edge);
  edge[0]=14; edge[1]=-1;set_successors(13,edge);
  edge[0]=15; edge[1]=-1;set_successors(14,edge);
  edge[0]=16; edge[1]=-1;set_successors(15,edge);
  edge[0]=33; edge[1]=-1;set_successors(16,edge);
  edge[0]=0; edge[1]=-1;set_successors(17,edge);
  edge[0]=-1; edge[1]=-1;set_successors(18,edge);
  edge[0]=36; edge[1]=-1;set_successors(19,edge);
  edge[0]=-1; edge[1]=-1;set_successors(20,edge);
  edge[0]=4; edge[1]=-1;set_successors(21,edge);
  edge[0]=-1; edge[1]=-1;set_successors(22,edge);
  edge[0]=40; edge[1]=-1;set_successors(23,edge);
  edge[0]=41; edge[1]=-1;set_successors(24,edge);
  edge[0]=-1; edge[1]=-1;set_successors(25,edge);
  edge[0]=9; edge[1]=-1;set_successors(26,edge);
  edge[0]=10; edge[1]=-1;set_successors(27,edge);
  edge[0]=-1; edge[1]=-1;set_successors(28,edge);
  edge[0]=46; edge[1]=-1;set_successors(29,edge);
  edge[0]=-1; edge[1]=-1;set_successors(30,edge);
  edge[0]=14; edge[1]=-1;set_successors(31,edge);
  edge[0]=-1; edge[1]=-1;set_successors(32,edge);
  edge[0]=50; edge[1]=-1;set_successors(33,edge);
  edge[0]=17; edge[1]=-1;set_successors(34,edge);
  edge[0]=34; edge[1]=-1;set_successors(35,edge);
  edge[0]=35; edge[1]=-1;set_successors(36,edge);
  edge[0]=36; edge[1]=-1;set_successors(37,edge);
  edge[0]=37; edge[1]=21;set_successors(38,edge);
  edge[0]=38; edge[1]=-1;set_successors(39,edge);
  edge[0]=74; edge[1]=-1;set_successors(40,edge);
  edge[0]=75; edge[1]=-1;set_successors(41,edge);
  edge[0]=-1; edge[1]=-1;set_successors(42,edge);
  edge[0]=26; edge[1]=-1;set_successors(43,edge);
  edge[0]=27; edge[1]=-1;set_successors(44,edge);
  edge[0]=39; edge[1]=-1;set_successors(45,edge);
  edge[0]=45; edge[1]=-1;set_successors(46,edge);
  edge[0]=46; edge[1]=-1;set_successors(47,edge);
  edge[0]=47; edge[1]=31;set_successors(48,edge);
  edge[0]=48; edge[1]=-1;set_successors(49,edge);
  edge[0]=49; edge[1]=67;set_successors(50,edge);
  edge[0]=34; edge[1]=52;set_successors(51,edge);
  edge[0]=53; edge[1]=-1;set_successors(52,edge);
  edge[0]=54; edge[1]=70;set_successors(53,edge);
  edge[0]=55; edge[1]=-1;set_successors(54,edge);
  edge[0]=56; edge[1]=-1;set_successors(55,edge);
  edge[0]=62; edge[1]=-1;set_successors(56,edge);
  edge[0]=-1; edge[1]=-1;set_successors(57,edge);
  edge[0]=-1; edge[1]=-1;set_successors(58,edge);
  edge[0]=-1; edge[1]=-1;set_successors(59,edge);
  edge[0]=-1; edge[1]=-1;set_successors(60,edge);
  edge[0]=-1; edge[1]=-1;set_successors(61,edge);
  edge[0]=63; edge[1]=-1;set_successors(62,edge);
  edge[0]=64; edge[1]=80;set_successors(63,edge);
  edge[0]=65; edge[1]=-1;set_successors(64,edge);
  edge[0]=66; edge[1]=-1;set_successors(65,edge);
  edge[0]=67; edge[1]=-1;set_successors(66,edge);
  edge[0]=84; edge[1]=-1;set_successors(67,edge);
  edge[0]=51; edge[1]=-1;set_successors(68,edge);
  edge[0]=-1; edge[1]=-1;set_successors(69,edge);
  edge[0]=87; edge[1]=-1;set_successors(70,edge);
  edge[0]=-1; edge[1]=-1;set_successors(71,edge);
  edge[0]=55; edge[1]=-1;set_successors(72,edge);
  edge[0]=-1; edge[1]=-1;set_successors(73,edge);
  edge[0]=91; edge[1]=-1;set_successors(74,edge);
  edge[0]=92; edge[1]=-1;set_successors(75,edge);
  edge[0]=-1; edge[1]=-1;set_successors(76,edge);
  edge[0]=43; edge[1]=-1;set_successors(77,edge);
  edge[0]=44; edge[1]=-1;set_successors(78,edge);
  edge[0]=-1; edge[1]=-1;set_successors(79,edge);
  edge[0]=97; edge[1]=-1;set_successors(80,edge);
  edge[0]=-1; edge[1]=-1;set_successors(81,edge);
  edge[0]=65; edge[1]=-1;set_successors(82,edge);
  edge[0]=-1; edge[1]=-1;set_successors(83,edge);
  edge[0]=101; edge[1]=-1;set_successors(84,edge);
  edge[0]=68; edge[1]=-1;set_successors(85,edge);
  edge[0]=85; edge[1]=-1;set_successors(86,edge);
  edge[0]=86; edge[1]=-1;set_successors(87,edge);
  edge[0]=87; edge[1]=-1;set_successors(88,edge);
  edge[0]=88; edge[1]=72;set_successors(89,edge);
  edge[0]=89; edge[1]=-1;set_successors(90,edge);
  edge[0]=125; edge[1]=-1;set_successors(91,edge);
  edge[0]=126; edge[1]=-1;set_successors(92,edge);
  edge[0]=-1; edge[1]=-1;set_successors(93,edge);
  edge[0]=77; edge[1]=-1;set_successors(94,edge);
  edge[0]=78; edge[1]=-1;set_successors(95,edge);
  edge[0]=90; edge[1]=-1;set_successors(96,edge);
  edge[0]=96; edge[1]=-1;set_successors(97,edge);
  edge[0]=97; edge[1]=-1;set_successors(98,edge);
  edge[0]=98; edge[1]=82;set_successors(99,edge);
  edge[0]=99; edge[1]=-1;set_successors(100,edge);
  edge[0]=100; edge[1]=118;set_successors(101,edge);
  edge[0]=85; edge[1]=103;set_successors(102,edge);
  edge[0]=104; edge[1]=-1;set_successors(103,edge);
  edge[0]=105; edge[1]=121;set_successors(104,edge);
  edge[0]=106; edge[1]=-1;set_successors(105,edge);
  edge[0]=107; edge[1]=-1;set_successors(106,edge);
  edge[0]=113; edge[1]=-1;set_successors(107,edge);
  edge[0]=-1; edge[1]=-1;set_successors(108,edge);
  edge[0]=-1; edge[1]=-1;set_successors(109,edge);
  edge[0]=-1; edge[1]=-1;set_successors(110,edge);
  edge[0]=-1; edge[1]=-1;set_successors(111,edge);
  edge[0]=-1; edge[1]=-1;set_successors(112,edge);
  edge[0]=114; edge[1]=-1;set_successors(113,edge);
  edge[0]=115; edge[1]=131;set_successors(114,edge);
  edge[0]=116; edge[1]=-1;set_successors(115,edge);
  edge[0]=117; edge[1]=-1;set_successors(116,edge);
  edge[0]=118; edge[1]=-1;set_successors(117,edge);
  edge[0]=135; edge[1]=-1;set_successors(118,edge);
  edge[0]=102; edge[1]=-1;set_successors(119,edge);
  edge[0]=-1; edge[1]=-1;set_successors(120,edge);
  edge[0]=138; edge[1]=-1;set_successors(121,edge);
  edge[0]=-1; edge[1]=-1;set_successors(122,edge);
  edge[0]=106; edge[1]=-1;set_successors(123,edge);
  edge[0]=-1; edge[1]=-1;set_successors(124,edge);
  edge[0]=142; edge[1]=-1;set_successors(125,edge);
  edge[0]=143; edge[1]=-1;set_successors(126,edge);
  edge[0]=-1; edge[1]=-1;set_successors(127,edge);
  edge[0]=94; edge[1]=-1;set_successors(128,edge);
  edge[0]=95; edge[1]=-1;set_successors(129,edge);
  edge[0]=-1; edge[1]=-1;set_successors(130,edge);
  edge[0]=148; edge[1]=-1;set_successors(131,edge);
  edge[0]=-1; edge[1]=-1;set_successors(132,edge);
  edge[0]=116; edge[1]=-1;set_successors(133,edge);
  edge[0]=-1; edge[1]=-1;set_successors(134,edge);
  edge[0]=152; edge[1]=-1;set_successors(135,edge);
  edge[0]=119; edge[1]=-1;set_successors(136,edge);
  edge[0]=136; edge[1]=-1;set_successors(137,edge);
  edge[0]=137; edge[1]=-1;set_successors(138,edge);
  edge[0]=138; edge[1]=-1;set_successors(139,edge);
  edge[0]=139; edge[1]=106;set_successors(140,edge);
  edge[0]=140; edge[1]=-1;set_successors(141,edge);
  edge[0]=176; edge[1]=-1;set_successors(142,edge);
  edge[0]=177; edge[1]=-1;set_successors(143,edge);
  edge[0]=-1; edge[1]=-1;set_successors(144,edge);
  edge[0]=128; edge[1]=-1;set_successors(145,edge);
  edge[0]=129; edge[1]=-1;set_successors(146,edge);
  edge[0]=141; edge[1]=-1;set_successors(147,edge);
  edge[0]=147; edge[1]=-1;set_successors(148,edge);
  edge[0]=148; edge[1]=-1;set_successors(149,edge);
  edge[0]=149; edge[1]=133;set_successors(150,edge);
  edge[0]=150; edge[1]=-1;set_successors(151,edge);
  edge[0]=151; edge[1]=169;set_successors(152,edge);
  edge[0]=136; edge[1]=-1;set_successors(153,edge);
  edge[0]=155; edge[1]=-1;set_successors(154,edge);
  edge[0]=156; edge[1]=172;set_successors(155,edge);
  edge[0]=157; edge[1]=-1;set_successors(156,edge);
  edge[0]=158; edge[1]=-1;set_successors(157,edge);
  edge[0]=164; edge[1]=-1;set_successors(158,edge);
  edge[0]=-1; edge[1]=-1;set_successors(159,edge);
  edge[0]=-1; edge[1]=-1;set_successors(160,edge);
  edge[0]=-1; edge[1]=-1;set_successors(161,edge);
  edge[0]=-1; edge[1]=-1;set_successors(162,edge);
  edge[0]=-1; edge[1]=-1;set_successors(163,edge);
  edge[0]=165; edge[1]=-1;set_successors(164,edge);
  edge[0]=166; edge[1]=182;set_successors(165,edge);
  edge[0]=167; edge[1]=-1;set_successors(166,edge);
  edge[0]=168; edge[1]=-1;set_successors(167,edge);
  edge[0]=169; edge[1]=-1;set_successors(168,edge);
  edge[0]=186; edge[1]=-1;set_successors(169,edge);
  edge[0]=153; edge[1]=-1;set_successors(170,edge);
  edge[0]=-1; edge[1]=-1;set_successors(171,edge);
  edge[0]=189; edge[1]=-1;set_successors(172,edge);
  edge[0]=-1; edge[1]=-1;set_successors(173,edge);
  edge[0]=157; edge[1]=-1;set_successors(174,edge);
  edge[0]=-1; edge[1]=-1;set_successors(175,edge);
  edge[0]=193; edge[1]=-1;set_successors(176,edge);
  edge[0]=194; edge[1]=-1;set_successors(177,edge);
  edge[0]=-1; edge[1]=-1;set_successors(178,edge);
  edge[0]=145; edge[1]=-1;set_successors(179,edge);
  edge[0]=146; edge[1]=-1;set_successors(180,edge);
  edge[0]=-1; edge[1]=-1;set_successors(181,edge);
  edge[0]=199; edge[1]=-1;set_successors(182,edge);
  edge[0]=-1; edge[1]=-1;set_successors(183,edge);
  edge[0]=167; edge[1]=-1;set_successors(184,edge);
  edge[0]=-1; edge[1]=-1;set_successors(185,edge);
  edge[0]=203; edge[1]=-1;set_successors(186,edge);
  edge[0]=170; edge[1]=-1;set_successors(187,edge);
  edge[0]=187; edge[1]=-1;set_successors(188,edge);
  edge[0]=188; edge[1]=-1;set_successors(189,edge);
  edge[0]=189; edge[1]=-1;set_successors(190,edge);
  edge[0]=190; edge[1]=174;set_successors(191,edge);
  edge[0]=191; edge[1]=-1;set_successors(192,edge);
  edge[0]=192; edge[1]=197;set_successors(193,edge);
  edge[0]=193; edge[1]=-1;set_successors(194,edge);
  edge[0]=194; edge[1]=-1;set_successors(195,edge);
  edge[0]=195; edge[1]=179;set_successors(196,edge);
  edge[0]=196; edge[1]=180;set_successors(197,edge);
  edge[0]=197; edge[1]=-1;set_successors(198,edge);
  edge[0]=198; edge[1]=182;set_successors(199,edge);
  edge[0]=199; edge[1]=-1;set_successors(200,edge);
  edge[0]=200; edge[1]=184;set_successors(201,edge);
  edge[0]=201; edge[1]=-1;set_successors(202,edge);
  edge[0]=202; edge[1]=-1;set_successors(203,edge);
=======
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
>>>>>>> 18a14c2f25229c73c3e13b9d12604203905b06da
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
