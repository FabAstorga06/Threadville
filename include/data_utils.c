 #define F1 80
 #define F2 81
 #define F3 82
 #define F4 83

/*****************************************************************************/
/* Verify if F1,F2,F3,F4 key are pressed */
void* verify_key_events() {
  char _key;
  while (1) {
    _key = getchar();
    mymutex_lock(&lock);
    switch (_key) {
      case F1: /* Create car with random values */
        system ("/bin/stty raw");
        generateCar(NORMAL_CAR);
        msg_log_file("Threadville message: A car has been created pressing F1");
        system ("/bin/stty cooked");
        break;
      case F2: /* Create car with specific user values  */
        system ("/bin/stty raw");
        generateCar(NORMAL_CAR);
        msg_log_file("Threadville message: A car has been created pressing F2");
        system ("/bin/stty cooked");
        break;
      case F3: /* Create an ambulance with random values */
        system ("/bin/stty raw");
        generateCar(AMBULANCE);
        msg_log_file("Threadville message: An ambulance has been created pressing F3");
        system ("/bin/stty cooked");
        break;
      case F4: /* Create radioactive car with random values */
        system ("/bin/stty raw");
        generateCar(RADIOACTIVE_CAR);
        msg_log_file("Threadville message: A radioactive car has been created pressing F4");
        system ("/bin/stty cooked");
        break;
      default:
        break;
    }
    mymutex_unlock(&lock);
  }
}
