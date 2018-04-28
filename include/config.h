
#ifndef CONFIG_H_
#define CONFIG_H_


//Bridge number 1
static const char CONTROL_METHOD_BRIDGE_1[] = "transit_officer";//Options: "transit_officer", "semaphore", "jungle_law".
//Bridge number 2
static const char CONTROL_METHOD_BRIDGE_2[] = "semaphore";
//Bridge number 3
static const char CONTROL_METHOD_BRIDGE_3[] = "jungle_law";

enum CONFIGFILE
{

	DISPATCHER				= 1,// 1->RR, 2->LOTTERY 3-> Real time

	QUANTUM 				= 400000,

	/****** BRIDGES DISTRIBUTION DEFINITION ******/
	/*
	 * 0: 1/1+e^(x*y)
	 * */
    BRIDGE_DISTRIBUTION   	= 10,


	/****** CAR SPEED DEFINITION ******/
	/*
	 *numbers  1-5, 5=max speed
	 */
    BRIDGE_CARSPEEDPROM   	= 5,



	/****** BRIDGES SEMAPHORES DEFINITION ******/
	/*
	 * NUMBER FROM 1-5, 5=MAX TIME
	 * */
	TIME  				= 6,

	/****** BRIDGES K AMOUNT CARS DEFINITION ******/
	/*
	 * number of cars  1-10, 10=MAX K
	 * */
	K_CARS       			= 3,

	/****** BRIDGES AMBULANCE PERCENT DEFINITION ******/
	/*
	 *percent of ambulances  0-100,
	 * */
    BRIDGE_AMBULANCEPORC  = 30,

	/****** BRIDGES RADIACTIVES PERCENT DEFINITION ******/
	/*
	 *percent of radiactives  0-100,
	 * */
    BRIDGE_RADIACTIVEPORC = 30,

};


#endif /* CONFIG_H_ */
