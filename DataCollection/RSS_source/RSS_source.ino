/****************************************************************************************
   Purpose : This programme is written to read the RSSI value on the JeeNode board
   Programmer : Ram Singh
   Date : 17 Sept 2018
   Ver : 00

   Input : There should be a JeeNode device configured as tranmsitter and powered on.
   Output : The received signal strenght will be send over serial port using (9600 bps)
   
   Description : The programme is written to extract the RSSI values from Radio chip RFM12B 
   RF Module on JeeNode v5 using modified library from Charles-Henri Hallard

   Library referecne :   https://github.com/hallard/RFM12B_arssi
                         http://hallard.me/rfm12b_arssi-library/
******************************************************************************/


// **********************************************************************************
// Driver definition for HopeRF RFM12B RF Module
// **********************************************************************************
// License is the same as original libraries
//
// For any explanation see RFM12 module 
// http://www.hoperf.com/rf/fsk_module/RFM12B.htm
//
// Code based on following datasheet
// http://www.hoperf.com/upload/rf/RFM12B.pdf
//
// Based on the RFM12 driver from jeelabs.com (2009-02-09 <jc@wippler.nl>)
// modified 2012-12-12 (C) felix@lowpowerlab.com from LowPowerLab.com
// 
// Modified by Charles-Henri Hallard (http://hallard.me)
//
// History : V1.00 2014-08-01 - First release
//                              Added dynamic Chip select Pin selection 
//                              Added dynamic IRQ pin selection 
//                              Added check that RFM12B module is present
//                              Added true ARSSI reading 
//                                    Need hardware hack depending on module type
//
// All text above must be included in any redistribution.
//
// **********************************************************************************

#include "RFM12B_arssi.h"

// Defining the costants
#define SERIAL 9600
#define FREQUENCY RF12_868MHZ
#define RFM_CS_PIN  10 // RFM12B Chip Select Pin
#define RFM_IRQ_PIN 2  // RFM12B IRQ Pin
#define BOARD_VOLTAGE 3300 // Operating voltage of JeeNode bord in mV
#define SIZE 200 // Size of array

// Defining the variables
/*************************/

RFM12B radio;
byte nodeID = 20; //nodeID for Transmitter : 10, nodeID for Receiver (Master) : 20
byte senderID = 10; //senderID :20 for Transmitter configuation and senderID : 10 for Receiver (Master) configuration
byte brdcastID = 0;
uint16_t counter;
int8_t    rxRSSI;
int8_t RXrssiValues[SIZE];
//int8_t TXrssiValues[MAX];

// Defining the structure
/**************************/
typedef struct {
  int          nodeId; // nodeId as a field of message
  uint16_t     seqNum;    // current sequence number
  int8_t       data;
  char* msg = "TEST MESSAGE";

} Payload;

Payload theData, rxData;


// Setup function for JeeNode
/*****************************/
void setup(){
  Serial.begin(9600);
  counter = 0;
  rxRSSI =-100;

  // Initialising and checking the radio for presence of hardware modification
  // for reading RSSI
  if (radio.isPresent( RFM_CS_PIN, RFM_IRQ_PIN) )
  {
    radio.SetRSSI( 0, 450);
    Serial.println(F("RFM12B Detected OK!"));
  }
  else
  {
    Serial.println(F("RFM12B Detection FAIL!"));
    }
  radio.Initialize(nodeID, FREQUENCY, 100);
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

//Function : receive()for reading the received signal RSSI at master nodeID : 20
/*******************************************************************************/
int receive(){
 
  if (radio.ReceiveComplete()){
    if (radio.CRCPass()){
     // int8_t rssi = radio.ReadARSSI(BOARD_VOLTAGE);
     rxRSSI = radio.ReadARSSI(BOARD_VOLTAGE);
     
      byte receivedNodeID = radio.GetSender();
      if(receivedNodeID != senderID){
        return 0;
      }
      if (*radio.DataLen != sizeof(Payload)){
        return 0;
      }
      
      theData = *(Payload*)radio.Data; //assume radio.DATA actually contains our struct and not something else
           
     // send same data back (Its own NodeID and same Counter) Suppressed for File Output, 
        
     RXrssiValues[theData.seqNum] = rxRSSI;
     //TXrssiValues[theData.seqNum] = theData.dataRSSI;
          
      theData.nodeId = nodeID;
      theData.data = 55;
      delay(10);
     // radio.Send(pairID, (const void*)(&theData), sizeof(theData), true); 
     radio.Send(brdcastID, (const void*)(&theData), sizeof(theData), true);  // convereted to Broadcast ID
      
      if(theData.seqNum >= SIZE -1){
        return -1;
      }
    }
          
  }
  return 0;
}


//Function for transmitter nodeID: 10
//send A packet and Immediately wait for receive, If not received till time-out resend with same counter
  // If received the response measure the RSSI, Process Next Packet(with its measured val), Wait for Random delay
  //Send the next packet with increased counter
int transmit(){
  if(counter == SIZE){
    return -1;
  }
  theData.nodeId = nodeID;
  theData.seqNum = counter;
  theData.data = rxRSSI;
  //radio.Send(pairID, (const void*)(&theData), sizeof(theData), true); 
  radio.Send(brdcastID, (const void*)(&theData), sizeof(theData), true);  // convereted to Broadcast  
  for(int i = 0; i < 100; i++){
    if (radio.ReceiveComplete()){
      if (radio.CRCPass()){

    //rxRSSI = radio.ReadARSSI(BOARD_VOLTAGE);
        byte receivedNodeID = radio.GetSender();
        if(receivedNodeID != senderID){
          continue;
        }
        if (*radio.DataLen != sizeof(Payload)){
          continue;
        }
        rxData = *(Payload*)radio.Data; //assume radio.DATA actually contains our struct and not something else
        
        RXrssiValues[theData.seqNum] = theData.data;
        //TXrssiValues[counter] = rxRSSI;
         
        if ((rxData.seqNum == counter)&&(rxData.data == 55)) 
          counter++;
        srand(counter*100);
        
        delay(100 + rand()% 200);
        return 0;
    }
  }
  delay(50);
}
  return 0;
}

/*Function : serialDumpRSSI()
//This function is written to dump the measured RSSI at serial port */

int serailDumpRSSI(){
    
  //if(nodeID < 15)
    //Serial.print(senderID);
 // else 
    //Serial.print(nodeID);
  
    //Serial.print(" : ");

  for(uint16_t i = 0; i < SIZE; i++){
    Serial.println(RXrssiValues[i]);
    //Serial.print(",");
  }
  //Serial.println("&&");
  
  Serial.flush(); 
  
   delay(1000);
    counter=0;
    return 0;
}


void loop(){
  byte result = 0;
  if(nodeID < 15){
    result = transmit();
  } else {
    result = receive();
  }
 /*   */
  blink(9,10);
  //Serial.println(result);
  if( result != 0){
     serailDumpRSSI();
  }
}

