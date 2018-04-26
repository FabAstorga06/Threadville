#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

/******************************/
// Identifiers for physical matrix
#define BRIDGE0  0 
#define BRIDGE1  1
#define BRIDGE_AMT 2
#define MTX1_ADDR 0x71 
#define MTX2_ADDR 0x72
#define PORT 9600
#define ASCII 48

/******************************/
const uint8_t left_green0   = 2;
const uint8_t right_red0    = 3;
const uint8_t left_red0     = 4;
const uint8_t right_green0  = 5; 
/******************************/
const uint8_t left_green1   = 8;
const uint8_t right_red1    = 9;
const uint8_t left_red1     = 10;
const uint8_t right_green1  = 11;


//Instances and directions of matrixes adafruit library
static const uint8_t PROGMEM mtx_addr[] = { MTX1_ADDR, MTX2_ADDR };

Adafruit_8x8matrix matrix[BRIDGE_AMT] =  { Adafruit_8x8matrix(),
                                           Adafruit_8x8matrix() };


const byte caract_amt = 18;            // char serial message length                 
boolean    isNew = false;          // Flag for new incoming char array               
char       data_rcv[caract_amt];  // an array to store the received data            
char       end_marker = '\n';         // Allows to know when stop receive data.      


/*********** SETUP *******************/
void setup() {  
  Serial.begin(PORT); // Inicialization of serial port with 9600 baundrate
  
  matrix[BRIDGE0].begin( MTX1_ADDR ); 
  matrix[BRIDGE0].setRotation(2);
  matrix[BRIDGE1].begin( MTX2_ADDR ); 
  matrix[BRIDGE1].setRotation(2);  

  /* Active pin leds bridge 0  */
  pinMode(left_green0, OUTPUT); 
  pinMode(right_red0, OUTPUT);
  pinMode(left_red0, OUTPUT);
  pinMode(right_green0, OUTPUT);
  
  /* Active pin leds bridge 1 */  
  pinMode(left_green1, OUTPUT);
  pinMode(right_red1, OUTPUT);  
  pinMode(left_red1, OUTPUT);
  pinMode(right_green1, OUTPUT);
  
  clean_mtxs();                   
  draw_bridges();
  write_matrix();
}

/*********** LOOP *******************/
void loop() {     
 
     read_serial();
     data_parser();
}

/************************* EXTRA FUNCTIONS **********************************/


// This function erase all the values in ON state of matrix
void clean_mtxs() {
    matrix[BRIDGE0].clear();
    matrix[BRIDGE1].clear();
}

// This function display all the values in ON state of matrix
void write_matrix() {
    matrix[BRIDGE0].writeDisplay();
    matrix[BRIDGE1].writeDisplay();
}

// This function display bridges for test matrix
void draw_bridges( ) {
    draw_bridge(4, BRIDGE0);
    draw_bridge(3, BRIDGE1);
}

// this function displays a bridge in one matrix according to width
void draw_bridge(int length_, int id_mtx){
  switch (length_) {
    case 1:
      matrix[id_mtx].drawLine(0,0, 7,0, LED_ON);
      matrix[id_mtx].drawLine(2,4, 2,7, LED_ON); 
      matrix[id_mtx].drawLine(5,6, 5,7, LED_ON); 
      matrix[id_mtx].drawLine(2,5, 5,5, LED_ON); 
      
      break;
    case 2:
      matrix[id_mtx].drawLine(0,0, 7,0, LED_ON); 
      matrix[id_mtx].drawLine(2,4, 2,7, LED_ON);
      matrix[id_mtx].drawLine(3,4, 3,7, LED_ON); 
      break;
    case 3: 
      matrix[id_mtx].drawLine(0,0, 7,0, LED_ON); 
      matrix[id_mtx].drawLine(2,4, 4,4, LED_ON);
      matrix[id_mtx].drawLine(2,5, 2,7, LED_ON); 
      matrix[id_mtx].drawLine(4,5, 4,7, LED_ON);
      break;   
    case 4:
      matrix[id_mtx].drawLine(0,0, 1,0, LED_ON); 
      matrix[id_mtx].drawLine(6,0, 7,0, LED_ON); 
      matrix[id_mtx].drawLine(2,0, 5,0, LED_ON); 
      matrix[id_mtx].drawLine(2,4, 5,4, LED_ON);
      matrix[id_mtx].drawLine(2,5, 2,7, LED_ON); 
      matrix[id_mtx].drawLine(5,5, 5,7, LED_ON);
      break; 
    default: 
      break;
  }
}

//This function allows read from serial until end marker appears
void read_serial( )   {
     static byte indx = 0;
     char rd_c;
     while (Serial.available() > 0 && isNew == false ) {
         rd_c = Serial.read();        
         if (rd_c != end_marker) {
             data_rcv[indx] = rd_c;
             indx++;
             if (indx >= caract_amt) {
              indx = caract_amt-1;
             }
         }
         else {
             data_rcv[indx] = '\n'; // terminate the string
             indx = 0;
             isNew = true;
         }
     }
}

void update_semaphore(int mtx_id,int flag )  {
  if(flag )  {
    if(mtx_id == 0) {
      digitalWrite(left_green0,  HIGH);  
      digitalWrite(right_red0,   HIGH);
      digitalWrite(left_red0,    LOW);
      digitalWrite(right_green0, LOW);
    }
    else if(mtx_id == 1) {
      digitalWrite(left_green1,  HIGH); 
      digitalWrite(right_red1,   HIGH);
      digitalWrite(left_red1,    LOW);
      digitalWrite(right_green1, LOW);
    }
  }
  else {
    if(mtx_id == 0) {
      digitalWrite(left_green0,  LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(right_red0,   LOW);
      digitalWrite(left_red0,    HIGH);
      digitalWrite(right_green0, HIGH);
    }
    else if(mtx_id == 1) {
      digitalWrite(left_green1,  LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(right_red1,   LOW);
      digitalWrite(left_red1,    HIGH);
      digitalWrite(right_green1, HIGH);
    }
  }       
}

void update_officer(int mtx_id,int flag ) {

  if( flag ) {
    if(mtx_id == 0 ){
      digitalWrite(left_green0,  HIGH);   
      digitalWrite(right_red0,   LOW);
      digitalWrite(left_red0 ,   HIGH);
      digitalWrite(right_green0, LOW);
    }
    else if(mtx_id == 1 ){
      digitalWrite(left_green1,  HIGH);  
      digitalWrite(right_red1,   LOW);
      digitalWrite(left_red1 ,   HIGH);
      digitalWrite(right_green1, LOW);
    }
  }
  else {
    if( mtx_id == 0 ) {
      digitalWrite(left_green0,  LOW);  
      digitalWrite(right_red0,   HIGH);
      digitalWrite(left_red0 ,   LOW);
      digitalWrite(right_green0, HIGH);
    }
    else if( mtx_id == 1 ) {
      digitalWrite(left_green1,  LOW);   
      digitalWrite(right_red1,   HIGH);
      digitalWrite(left_red1 ,   LOW);
      digitalWrite(right_green1, HIGH);
    }    
    
  }

}

void trafficMethod(int mtx_id, int type, int indicator1, int indicator2) {
  switch( type )  {
    case 0:
      update_semaphore(mtx_id, indicator1);
      break;
    case 1: 
      update_officer(mtx_id, indicator2);
      break;
  } 
}
    
//// This function display the left queue,bridge or right queue in one matrix
void drawQueue(int mtx_id, int side, int car1, int car2, int car3, int car4){
  
  if( side==0 ) {                        // Draw left queue
    draw_car(mtx_id, car1, 1, 1);
    draw_car(mtx_id, car2, 0, 1);
    draw_car(mtx_id, car3, 0, 4);
    draw_car(mtx_id, car4, 1, 4); 
  }
  else if( side==1 ) {                   // Draw right queue
    draw_car(mtx_id, car1, 6, 1);
    draw_car(mtx_id, car2, 7, 1);
    draw_car(mtx_id, car3, 7, 4);
    draw_car(mtx_id, car4, 6, 4);     
  }
  else {                                 // Draw brigde
    draw_car(mtx_id, car1, 2, 1);
    draw_car(mtx_id, car2, 3, 1);
    draw_car(mtx_id, car3, 4, 1);
    draw_car(mtx_id, car4, 5, 1);  
  } 
  
} 

//This function display a car in x,y  according to type matrix in one 
void draw_car(int mtx_id, int type, int pos_x, int pos_y) { 
     switch ( type ) {
      case 0:
        matrix[mtx_id].drawPixel(pos_x, pos_y, LED_ON);
        break;
      case 1:
        matrix[mtx_id].drawLine(pos_x, pos_y, pos_x, pos_y+1, LED_ON);
        break;
      case 2:
        matrix[mtx_id].drawLine(pos_x, pos_y, pos_x, pos_y+2, LED_ON);
        break;
      default:
        matrix[mtx_id].drawLine(pos_x, pos_y, pos_x, pos_y+2, LED_OFF); 
        break; 
    } 
}


//This function allows to detect the leght of the bridge.
int sizeofbridge(char firstp, char secp, char thrdp, char frthp){
  if( (firstp=='#') && (secp=='#') && (thrdp=='#') && (frthp=='#') )  {  return 0; }
  else if ( (secp=='#') && (thrdp=='#') && (frthp=='#') )             {  return 1; }
  else if( (thrdp=='#') && (frthp=='#') )                             {  return 2; }
  else if( frthp=='#' )                                               {  return 3; }
  else                                                                {  return 4; }
}

//This function allows parse the  characters received array and display all matrix state.
void data_parser( ) {
 if (isNew ) {
   isNew = false;
   int size_bridge = sizeofbridge(data_rcv[8],data_rcv[9],data_rcv[10],data_rcv[11]);
   switch( data_rcv[0] )  {
     case '0': 
         matrix[BRIDGE0].clear();       // Clear the matrix                             
         draw_bridge(size_bridge,BRIDGE0);     // Draw bridge according to size
         trafficMethod(0,data_rcv[1]-ASCII, data_rcv[2]-ASCII, data_rcv[3]-ASCII); //turn off/on the leds depends of the traffic method
         drawQueue(0,0,data_rcv[7]-ASCII,data_rcv[6]-ASCII,data_rcv[5]-ASCII,data_rcv[4]-ASCII);      // draw left queue
         drawQueue(0,1,data_rcv[12]-ASCII,data_rcv[13]-ASCII,data_rcv[14]-ASCII,data_rcv[15]-ASCII);  // draw bridge 
         drawQueue(0,2,data_rcv[8]-ASCII,data_rcv[9]-ASCII,data_rcv[10]-ASCII,data_rcv[11]-ASCII);    //draw right queue
         matrix[BRIDGE0].writeDisplay();      // Display matrix with leds_on   
         break;
     case '1':         
         matrix[BRIDGE1].clear();
         draw_bridge(size_bridge,BRIDGE1);
         trafficMethod(1,data_rcv[1]-ASCII, data_rcv[2]-ASCII, data_rcv[3]-ASCII);
         drawQueue(1,0,data_rcv[7]-ASCII,data_rcv[6]-ASCII,data_rcv[5]-ASCII,data_rcv[4]-ASCII);
         drawQueue(1,1,data_rcv[12]-ASCII,data_rcv[13]-ASCII,data_rcv[14]-ASCII,data_rcv[15]-ASCII);
         drawQueue(1,2,data_rcv[8]-ASCII,data_rcv[9]-ASCII,data_rcv[10]-ASCII,data_rcv[11]-ASCII);
         matrix[BRIDGE1].writeDisplay();
         break;
     
     default:
         break;  
   } 
 }
}

