#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


void terminal_format(char* update, int id){


	if (update[1]=='1'){//OFICIAL
		if (update[3]=='0'){
			printf("%s                 STOP", KRED);
			printf("%s                GO", KGRN);
		}
		else{
			printf("%s                 GO", KGRN);
			printf("%s                STOP", KRED);
		}
	}

	if (update[1]=='0'){//SEMAFORO
		if (update[2]=='0'){
			printf("%s                    RED", KRED);
			printf("%s                GREEN", KGRN);
		}
		else{
			printf("%s                    GREEN", KGRN);
			printf("%s                RED", KRED);
		}
	}

	if (update[1]=='2'){//SEMAFORO
		printf("%s                      JUNGLE RULES", KYEL);
	}


	if      (id==0){printf("%s", KBLU);}
	else if (id==1){printf("%s", KCYN);}
	else if (id==2){printf("%s", KMAG);}
	else		   {printf("%s", KWHT);}

	printf("\n    _________________                _________________\n                     |_______________|\n                                     ");

	for (int i=12; i<16; i++){
		if (update[i]=='0'){printf("CAR ");}
		else if (update[i]=='1'){printf("AMBUL ");}
		else if (update[i]=='2'){printf("RADIO ");}
		else {printf("    ");}
	}

	printf("\n                     ");

	for (int i=8; i<12; i++){
		if (update[i]=='0'){printf("CAR ");}
		else if (update[i]=='1'){printf("AMBUL ");}
		else if (update[i]=='2'){printf("RADIO ");}
		else {printf("    ");}
	}

	printf("\n   ");


	for (int i=4; i<8; i++){
		if (update[i]=='0'){printf(" CAR");}
		else if (update[i]=='1'){printf(" AMBUL");}
		else if (update[i]=='2'){printf(" RADIO");}
		else {printf("    ");}
	}

	printf("\n                     ________________\n    _________________|               |_________________\n\n\n");

}


char* updateAux(int bridgeID){
	char p = bridgeID + '0';
	char* update = (char*) malloc(17*sizeof(char));
	int i;
	for(i = 0 ;i < 17; i++){
		update[i]= '0';
	}
	update[0] = p;
	//pthread_mutex_lock(&lock);
	if(!strcmp(bridges[bridgeID].control_method,"semaphore")){
		update[1] = '0';
	}else if(!strcmp(bridges[bridgeID].control_method,"transit_officer")){
		update[1] = '1';
	}else if(!strcmp(bridges[bridgeID].control_method,"jungle_law")){
		update[1] = '2';
	}
	update[2] = bridges[bridgeID].semaforo + '0';
	update[3] = bridges[bridgeID].oficial + '0';
	update[7] = (!bridges[bridgeID].rightArray[0].state)?bridges[bridgeID].rightArray[0].type + '0':NOTCAR + '0';
	update[6] = (!bridges[bridgeID].rightArray[1].state)?bridges[bridgeID].rightArray[1].type + '0':NOTCAR + '0';
	update[5] = (!bridges[bridgeID].rightArray[2].state)?bridges[bridgeID].rightArray[2].type + '0':NOTCAR + '0';
	update[4] = (!bridges[bridgeID].rightArray[3].state)?bridges[bridgeID].rightArray[3].type + '0':NOTCAR + '0';
	update[8] = (!bridges[bridgeID].bridge[0].state)?bridges[bridgeID].bridge[0].type + '0':NOTCAR + '0';
	if(bridges[bridgeID].bridge_size>1){
		update[9] = (!bridges[bridgeID].bridge[1].state)?bridges[bridgeID].bridge[1].type + '0':NOTCAR + '0';
		if(bridges[bridgeID].bridge_size>2){
			update[10] = (!bridges[bridgeID].bridge[2].state)?bridges[bridgeID].bridge[2].type + '0':NOTCAR + '0';
			if(bridges[bridgeID].bridge_size>3){
				update[11] = (!bridges[bridgeID].bridge[3].state)?bridges[bridgeID].bridge[3].type + '0':NOTCAR + '0';
			}
			else{
				update[11] =  '#';
			}
		}
		else{
			update[10] =  '#';update[11] =  '#';
		}
	}
	else{
		update[9] =  '#';update[10] =  '#';update[11] =  '#';
	}
	update[12] = (!bridges[bridgeID].leftArray[0].state)?bridges[bridgeID].leftArray[0].type + '0':NOTCAR + '0';
	update[13] = (!bridges[bridgeID].leftArray[1].state)?bridges[bridgeID].leftArray[1].type + '0':NOTCAR + '0';
	update[14] = (!bridges[bridgeID].leftArray[2].state)?bridges[bridgeID].leftArray[2].type + '0':NOTCAR + '0';
	update[15] = (!bridges[bridgeID].leftArray[3].state)?bridges[bridgeID].leftArray[3].type + '0':NOTCAR + '0';
	//pthread_mutex_unlock(&lock);
	update[16] = '\n';
	return update;
}


void* UpdateArduino( )   {
	struct termios options;
	int fd;
	fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY );
	tcgetattr(fd, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(fd, TCSANOW, &options);
	if (fd == -1){
		perror("open_port: Unable to open /dev/ttyACM0 - ");
	}

	while(1){

		strcpy(update1, updateAux(0));
		strcpy(update2, updateAux(1));
		strcpy(update3, updateAux(2));
		strcpy(update4, updateAux(3));

		terminal_format(update1, 2);
		terminal_format(update2, 1);
		terminal_format(update3, 0);
		terminal_format(update4, 3);

		write(fd, update1, 17);
		write(fd, update2, 17);
	//	write(fd, update3, 17);

		usleep(USUPDATEARD);

	}
}
