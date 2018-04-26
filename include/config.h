
#ifndef CONFIG_H_
#define CONFIG_H_

//General
char type_dispatcher[] ="FCFS";//Options: "FCFS", "RR", "Priority_Scheduler", "Shortest_Job_First", "Real_Time_Scheduler", ""

//Bridge number 1
static const char CONTROL_METHOD_BRIDGE_1[] = "semaphore";//Options: "transit_officer", "semaphore", "jungle_law".
//Bridge number 2
static const char CONTROL_METHOD_BRIDGE_2[] = "transit_officer";
//Bridge number 3
static const char CONTROL_METHOD_BRIDGE_3[] = "jungle_law";

enum CONFIGFILE
{

	DISPATCHER				= 1,// 1->FCFS, 2->SJF 3->Prioridad 4->RR 5-> Real time

	QUANTUM 				= 400000,

	/******    BRIDGES LENGTH DEFINITION  ******/
	/*
	 * Max bridge length = 4
	 * */
	BRIDGE1_SIZE         	= 5,
	BRIDGE2_SIZE         	= 5,
	BRIDGE3_SIZE         	= 5,

	/****** BRIDGES DISTRIBUTION DEFINITION ******/
	/*
	 * 0: 1/1+e^(x*y)
	 * 1: = 1 / y
	 * */
    BRIDGE_DISTRIBUTION   	= 10,


	/****** CAR SPEED DEFINITION ******/
	/*
	 *numbers  1-5, 5=max speed
	 */
    BRIDGE_CARSPEEDPROM   	= 5,


	/****** BRIDGES TRAFFICMETHOD DEFINITION ******/
	/*
	 * 0:Traffic Officer
	 * 1:Semaphore
	 * 2:Jungle Law
	 * */
    BRIDGE1_TRAFFICMETHOD  	= 0,
    BRIDGE2_TRAFFICMETHOD  	= 0,
    BRIDGE3_TRAFFICMETHOD  	= 0,

	/****** BRIDGES SEMAPHORES DEFINITION ******/
	/*
	 * NUMBER FROM 1-5, 5=MAX TIME
	 * */
	TIME_1  				= 6,
	TIME_2  				= 6,
	TIME_3  				= 6,

	/****** BRIDGES K AMOUNT CARS DEFINITION ******/
	/*
	 * number of cars  1-10, 10=MAX K
	 * */
	K_CARS1       			= 3,
	K_CARS2       			= 3,
	K_CARS3       			= 3,

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
