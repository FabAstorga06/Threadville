#ifndef CONSTANTS_H_
#define CONSTANTS_H_



enum CONSTANTS
{
	//ThreadErros
	MYTHREAD_ERROR				= -1,
	MYTHREAD_NOT_ENOUGH_MEMORY 	= -2,
	MYTHREAD_INVALID_SITE	 	= -3,
	//Config
	MYTHREAD_OK					=  0,
	MYTHREAD_SUCCESS 			=  1,
	MAX_THREADS  				=  5, //max amount of cars y bridge arrays
	DEFAULT_PRIORITY			=  5,
	SITE_LEFT					=  0,
	SITE_RIGHT					=  1,
	
	//Thread states
	THREAD_AVAILABLE			=  1,
	MYTHREAD_CREATED_STATED		=  0,
	//Types of cars
	NORMAL_CAR					=  0,
	AMBULANCE			        =  1,
	RADIOACTIVE_CAR		     	=  2,
	NOTCAR                      =  3,
	BUS                         =  4,
	//Priority
	EXTREME                     =  1,
	HIGH                        =  2,
	NORMAL                      =  3,

	//SCHEDULERS
	FIFO        = 1,
	SJF         = 2,
	HPF         = 3,
    ROUND_ROBIN = 4,
	REAL_TIME   = 5,
	LOTTERY     = 6,

	//state of bridge
	NOTBUSY=0,
	BUSY=1,
	EMPTY=2,

	//directions
	LEFT=0,
	RIGHT=1,
	//distribution
	DIST= 20,
	//nodes
	SIZE_GRAPH=204,
	SIZE_CARLIST=5,
	//useless bridges nodes
	AMOUNT_BRIDGES_NODES=15,
	AMOUNT_USELEES_NODES=46,
	AMOUNT_ENTRANCE_NODES=6,
	//bridges_nodes
	NLB1=56, //node left bridge 1
	NRB1=45, //node right bridge 1
	NLB2=107,//node left bridge 2
	NRB2=96,//node right bridge 2
	NLB3=158,//node left bridge 3
	NRB3=147, //node right bridge 3


	//
	NOTOCCUPIED=0,
	OCCUPIED=1,
	//colors
	RED =1,
  GREEN =2,
	BLUE= 3,
  YELLOW =4,
  ORANGE =5,
	CAR_COLOR=6,
	AMB_COLOR=7,
	RAD_COLOR=8,

	USMOVES						= 45000,
	USUPDATEARD 				= 300000,
	//USCARS						= 2500000,
	USMOVETAIL					= 40000
};

#endif /* CONSTANTS_H_ */
