/*Purpose : This programme is written to read the Photoresistor value using the JeeNode board
   Programmer : Ram Singh
   Date : 21 Sept 2018
   Ver : 00

   Input : Nil.
   Output : The mesured value be send over serial port using (9600 bps)
   
   Description : The programme is written to read the ristance value of photoresistor which is varying depinding
   on the light inteisity. The measured value will have impact of noise and will lead to randome variotion in
   the value. This random variation is used as source of randomness.

   Referecne :   https://startingelectronics.org/tutorials/arduino/modules/photo-resistor/
                 
******************************************************************************/
// Defining the costants
#define SERIAL 9600
#define SIZE 200 // Size of array

// Defining the variables
/*************************/
uint16_t counter;
int16_t RES[SIZE];

int sensorPin = A4;   // select the analog input pin for the photoresistor

// Setup function for JeeNode
/*****************************/
void setup() {
  Serial.begin(SERIAL);
  counter=0;
}
// Function to blinking the LED
/*******************************/
void blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,LOW);
  delay(DELAY_MS);
  digitalWrite(PIN,HIGH);
}

void loop() {

  for(uint16_t i=0; i< SIZE; i++){
    RES[i] = analogRead(sensorPin);
    delay(200);
  }
  

  for(uint16_t i = 0; i < SIZE; i++){
    Serial.println(RES[i]);
    //Serial.print(",");
     blink(9,10);
    
  }
  
}
