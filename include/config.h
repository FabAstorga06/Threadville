
#ifndef CONFIG_H_
#define CONFIG_H_

//General
char type_dispatcher[] ="FCFS";//Options: "FCFS", "RR", "Priority_Scheduler", "Shortest_Job_First", "Real_Time_Scheduler", ""

//Bridge number 1
static const char CONTROL_METHOD_BRIDGE_1[] = "transit_officer";//Options: "transit_officer", "semaphore", "jungle_law".
//Bridge number 2
static const char CONTROL_METHOD_BRIDGE_2[] = "semaphore";
//Bridge number 3
static const char CONTROL_METHOD_BRIDGE_3[] = "transit_officer";
//Bridge number 4
static const char CONTROL_METHOD_BRIDGE_4[] = "jungle_law";

enum CONFIGFILE
{

	DISPATCHER				= 1,// 1->FCFS, 2->SJF 3->Prioridad 4->RR 5-> Real time

	QUANTUM 				= 400000,

	/******    BRIDGES LENGTH DEFINITION  ******/
	/*
	 * Max bridge length = 4
	 * */
	BRIDGE1_SIZE         	= 4,
	BRIDGE2_SIZE         	= 4,
	BRIDGE3_SIZE         	= 4,
	BRIDGE4_SIZE         	= 4,

	/****** BRIDGES DISTRIBUTION DEFINITION ******/
	/*
	 * 0: 1/1+e^(x*y)
	 * 1: = 1 / y
	 * */
    BRIDGE1_DISTRIBUTION   	= 10,
    BRIDGE2_DISTRIBUTION   	= 10,
    BRIDGE3_DISTRIBUTION   	= 10,
    BRIDGE4_DISTRIBUTION   	= 10,


	/****** CAR SPEED DEFINITION ******/
	/*
	 *numbers  1-5, 5=max speed
	 */
    BRIDGE1_CARSPEEDPROM   	= 5,
    BRIDGE2_CARSPEEDPROM   	= 5,
    BRIDGE3_CARSPEEDPROM   	= 5,
    BRIDGE4_CARSPEEDPROM   	= 5,


	/****** BRIDGES TRAFFICMETHOD DEFINITION ******/
	/*
	 * 0:Traffic Officer
	 * 1:Semaphore
	 * 2:Jungle Law
	 * */
    BRIDGE1_TRAFFICMETHOD  	= 0,
    BRIDGE2_TRAFFICMETHOD  	= 0,
    BRIDGE3_TRAFFICMETHOD  	= 0,
    BRIDGE4_TRAFFICMETHOD  	= 0,

	/****** BRIDGES SEMAPHORES DEFINITION ******/
	/*
	 * NUMBER FROM 1-5, 5=MAX TIME
	 * */
	TIME_1  				= 6,
	TIME_2  				= 6,
	TIME_3  				= 6,
	TIME_4  				= 6,

	/****** BRIDGES K AMOUNT CARS DEFINITION ******/
	/*
	 * number of cars  1-10, 10=MAX K
	 * */
	K_CARS1       			= 3,
	K_CARS2       			= 3,
	K_CARS3       			= 3,
	K_CARS4			      	= 3,

	/****** BRIDGES AMBULANCE PERCENT DEFINITION ******/
	/*
	 *percent of ambulances  0-100,
	 * */
    BRIDGE1_AMBULANCEPORC  = 30,
    BRIDGE2_AMBULANCEPORC  = 30,
    BRIDGE3_AMBULANCEPORC  = 30,
    BRIDGE4_AMBULANCEPORC  = 30,

	/****** BRIDGES RADIACTIVES PERCENT DEFINITION ******/
	/*
	 *percent of radiactives  0-100,
	 * */
    BRIDGE1_RADIACTIVEPORC = 30,
    BRIDGE2_RADIACTIVEPORC = 30,
    BRIDGE3_RADIACTIVEPORC = 30,
    BRIDGE4_RADIACTIVEPORC = 30

};


#endif /* CONFIG_H_ */
