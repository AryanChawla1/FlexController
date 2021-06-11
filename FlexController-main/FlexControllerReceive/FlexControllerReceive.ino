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

//Custom Character that User Controls
byte character[8] = {
  0b01111,
  0b01000,
  0b01000,
  0b11111,
  0b11111,
  0b11111,
  0b01001
};

byte spike[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b01110,
  0b11111
};

int position_grid[2][16] = {
 { 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0 },
 { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 }
};

int character_position = 0;
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.clear();
  lcd.createChar(0, character);
  lcd.createChar(1, spike);

  create_game();
}
 
void loop() {
  // Receive data from the bluetooth
  bluetooth_receive();  

  // Necessary forced delay
  delay(1000);
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
  // Check the software serial buffer for data to read
  if(BTSerial.available() >= sizeof(Packet)) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt,sizeof(Packet));
    
   check_change();
  }   
}



void check_change() {
  if (pkt.flex == 1) {
    if (character_position == 0) {
      lcd.setCursor(0,0);
      lcd.print(" ");
      lcd.setCursor(0,1);
      lcd.write(byte(0));
      character_position = 1;
      position_grid[1][0] = 2;
      position_grid[0][0] = 0;
    }
    else {
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(0,0);
      lcd.write(byte(0));
      character_position = 0;
      position_grid[1][0] = 0;
      position_grid[0][0] = 2;
    }
  }

  move_spikes();
  create_game();
}

void create_game() {
  lcd.clear();
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 16; j++) {
      if (position_grid[i][j] == 2) {
        lcd.setCursor(j, i);
        lcd.write(byte(0));
      }
      else if (position_grid[i][j] == 1) {
        lcd.setCursor(j, i);
        lcd.write(byte(1));
      }
    }
  }
}

void move_spikes() {
  for (int i = 0; i < 2; i++) {
    for (int j = 2; j < 16; j++) {
      position_grid[i][j-1] = position_grid[i][j];
    }
  }

  if (position_grid[0][15] == 1 || position_grid[1][15] == 1) {
    position_grid[0][15] = 0;
    position_grid[1][15] = 0;
  }
  else {
    int spike_placer = random(0,2);

    if (spike_placer == 1) {
      position_grid[1][15] = 1;
      position_grid[0][15] = 0;
    }
    else {
      position_grid[1][15] = 0;
      position_grid[0][15] = 1;
    }
  }
}
