/*
 * @Author: Aryan Chawla
 * @Name: FlexControllerTransmit
 * 
 * @Function: Transmit data in form of boolean from Analog Input EMG sensor to
 * the Receiver MicroController
 * 
 * @Note: Proper values for EMG needed
 */
 
// Transmitting data in form of boolean in the form of a struct to receiver
// Writes (hardcoded) data to the software UART and prints the transmitted packet


// Library to make a Software UART
#include <SoftwareSerial.h>

#define TX 2
#define RX 3
 
SoftwareSerial BTSerial(RX, TX);

#define BAUDRATE 9600

// Struct to hold the data we want to transmit
struct Packet {
  bool flex;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);  
}
 
void loop() {  
  // Receive data from EMG sensor
  emg_input();
  // Transmit data via bluetooth
  bluetooth_transmit();  

  // Necessary forced delay
  delay(1);
}

// Function responsible for transmitting data over bluetooth
void bluetooth_transmit() {
  // Update data to be transmitted
  
  // Write packet data to the bluetooth - and transmit
  BTSerial.write((byte *) & pkt,sizeof(Packet));

  // Print packet (debug)
  print_packet();
}

// Function to print packet data (debug)
void print_packet() {  
  Serial.print("TX: Result is: ");
  Serial.print(pkt.flex);
  Serial.print("\n");
}

// Function to receive the EMG values and compute whether muscle is flexed
void emg_input() {
  // read the input from the analog pin 0
  int sensorValue = analogRead(A0);

  if (sensorValue > 200) {
    pkt.flex = true;
  }
  else {
    pkt.flex = false;
  }
}
