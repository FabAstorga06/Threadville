 #define F1 80
 #define F2 81
 #define F3 82
 #define F4 83

/*****************************************************************************/
/* Verify if F1,F2,F3,F4 key are pressed */
void* verify_key_events() {
  //system ("/bin/stty raw");
  char _key;
  while (1) {
    _key = getchar();
    switch (_key) {
      case F1: /* Create car with random values */
        generateCar(NORMAL_CAR);
        write_log("Pressed F1\n");
        //system ("/bin/stty cooked");
        break;
      case F2: /* Create car with specific user values  */
        generateCar(NORMAL_CAR);
        write_log("Pressed F2\n");
<<<<<<< HEAD
        system ("/bin/stty cooked");
=======
        //system ("/bin/stty cooked");
>>>>>>> 18a14c2f25229c73c3e13b9d12604203905b06da
        break;
      case F3: /* Create an ambulance with random values */
        generateCar(AMBULANCE);
        write_log("Pressed F3\n");
<<<<<<< HEAD
        system ("/bin/stty cooked");
=======
        //system ("/bin/stty cooked");
>>>>>>> 18a14c2f25229c73c3e13b9d12604203905b06da
        break;
      case F4: /* Create radioactive car with random values */
        generateCar(RADIOACTIVE_CAR);
        write_log("Pressed F4\n");
<<<<<<< HEAD
        system ("/bin/stty cooked");
=======
        //system ("/bin/stty cooked");
>>>>>>> 18a14c2f25229c73c3e13b9d12604203905b06da
        break;
      default:
        break;
    }

  }


}
