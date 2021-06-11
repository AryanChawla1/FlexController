/*
 * @Author: Aryan Chawla
 * @Name: FlexControllerReceive
 * 
 * @Function: Receive data in form of boolean from other HM-10 Sensor
 *            It also has the LCD for the game code
 * 
 */

// Receiving data in the form of a struct from transmitter
// Reads from the software UART and prints the received packet


// Library to make a Software UART
#include <SoftwareSerial.h>

//Library to work with the LCD
#include <LiquidCrystal.h>

#define RX 9
#define TX 8
#define BAUDRATE 9600

SoftwareSerial BTSerial(RX, TX); // (RX, TX)

// Struct to hold the data we want to receive
struct Packet {
  int flex;
} pkt; // Instantiate a Packet struct

//Pins for LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}
 
void loop() {
  // Receive data from the bluetooth
  bluetooth_receive();  

  // Necessary forced delay
  delay(1);
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
  // Check the software serial buffer for data to read
  if(BTSerial.available() >= sizeof(Packet)) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt,sizeof(Packet));
    
    // Print packet (debug)
    print_packet();
  }   
}

// Function to print packet data (debug)
void print_packet() {  
  lcd.setCursor(0,1);
  lcd.print(pkt.flex);
}
