#include <Arduino.h>




// include the library code:
#include <LiquidCrystal.h>

// dfrobot sheild pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);



// define the button pin
#define BUTTONPIN A0



#include <tanglib.h>









// make a little timer
unsigned long stopwatchstartval = 0;
unsigned long stopwatchstopval = 0;

void stopwatch_start() {
  stopwatchstartval = millis();
}

void stopwatch_stop() {
  stopwatchstopval = millis();
}


unsigned long stopwatch_duration() {
  return (stopwatchstopval - stopwatchstartval);
}







// put function declarations here:

uint16_t counter = 0;


int8_t menucurrentchoice = 0;

uint8_t menumaxchoices = 6;

String menutext[6] = { "Reset Chip" ,
                       "test 01" ,
                       "test 02" ,
                       "test 03" ,
                       "test 04" ,
                       "test 05"
                       };


void menucommand_00();

void menucommand_01();

void menucommand_02();

void menucommand_03();

void menucommand_04();

void menucommand_05();





void domenuaction() {

  lcd.setCursor( 0 , 1 );
  lcd.print( "Executing" );
  delay( 750 );

  switch (menucurrentchoice)
  {
  case 0:
    menucommand_00();
    break;
  
  case 1:
    menucommand_01();
    break;

  case 2:
    menucommand_02();
    break;
  
  case 3:
    menucommand_03();
    break;
  
  case 4:
    menucommand_04();
    break;
  case 5:
    menucommand_05();
    break;
  
  default:
    break;
  }

  return;

}




void displaymenu() {

  lcd.clear();
  lcd.setCursor( 0 , 0 );

  lcd.print( menutext[ menucurrentchoice ] );

}




// button scores
// none   1023
// right  0
// up     131
// down   308
// left   481
// select 720



void checkbutton() {

  int buttonraw = analogRead( BUTTONPIN );

  if ( buttonraw > 1000 ) { /* no button is pressed */ return; }
  if ( buttonraw < 100 ) { /* right button is pressed */ }
  if ( ( buttonraw > 100 ) && ( buttonraw < 200 ) ) { /* up button is pressed */ menucurrentchoice++; }
  if ( ( buttonraw > 250 ) && ( buttonraw < 350 ) ) { /* down button is pressed */ menucurrentchoice--; }
  if ( ( buttonraw > 450 ) && ( buttonraw < 500 ) ) { /* left button is pressed */ }
  if ( ( buttonraw > 700 ) && ( buttonraw < 750 ) ) { /* select button is pressed */ domenuaction(); }
  


  if ( menucurrentchoice == menumaxchoices ) { menucurrentchoice = ( menumaxchoices - 1 ); }
  if ( menucurrentchoice < 0 ) { menucurrentchoice = 0; }

  displaymenu();

}







// put your setup code here, to run once:
void setup() {
  Serial.begin(9600);
  Serial.println("Starting Up!");
  
  lcd.begin( 16 , 2 );
  lcd.display();
  lcd.print("Hello World!");

  pinMode(10 , OUTPUT);
  digitalWrite(10,HIGH);

  // set the buttonpin to input
  pinMode( BUTTONPIN , INPUT );


  tanglib_setup();



  randomSeed(analogRead(A2));
  // show the menu screen
  displaymenu();


  

}





void loop() {
  // put your main code here, to run repeatedly:

    checkbutton();

  //lcd.clear();
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print( analogRead( BUTTONPIN ) );

  delay( 750 );


}





// put function definitions here:




// reset the chip
void menucommand_00() {
  lcd.clear();
  lcd.print("Go!");

  tanglib_reset();

  delay(1000);
  
}











void showbyte() {
  lcd.clear();

  lcd.print( tanglib_read( 0x0000 ) , HEX );
  
  lcd.print(":");

  lcd.print( tanglib_read( 0xC000 ) , HEX );
  
}



void bankfill( uint8_t banksel , uint8_t databyte ) {

  // set bank select register
  tanglib_write( 0x0000 , 0x10 );
  tanglib_write( 0x0001 , banksel );
  
  // bankfill A with immedeate
  tanglib_write( 0x0002 , 0x14 );
  tanglib_write( 0x0003 , databyte );

  // end
  //tanglib_write( 0x0004 , 0x01 );

  tanglib_execute();

  delay(1);
  tanglib_reset();

}




void bankclear() {
  bankfill(0x00,0x00);
  bankfill(0x40,0x00);
  bankfill(0x80,0x00);
  bankfill(0xC0,0x00);
}












void test01() {


  lcd.clear();
  lcd.print("Read/write test.");


  tanglib_reset();


  tanglib_write( 0x0000 , 0xDE );
  tanglib_write( 0x0001 , 0xAD );
  tanglib_write( 0x0002 , 0xBE );
  tanglib_write( 0x0003 , 0xEF );
  tanglib_write( 0x0004 , 0xDE );
  tanglib_write( 0x0005 , 0xAD );
  tanglib_write( 0x0006 , 0xBE );
  tanglib_write( 0x0007 , 0xEF );


  lcd.setCursor(0,1);

  lcd.print( tanglib_read( 0x0000 ) , HEX );
  lcd.print( tanglib_read( 0x0001 ) , HEX );
  lcd.print( tanglib_read( 0x0002 ) , HEX );
  lcd.print( tanglib_read( 0x0003 ) , HEX );
  lcd.print( tanglib_read( 0x0004 ) , HEX );
  lcd.print( tanglib_read( 0x0005 ) , HEX );
  lcd.print( tanglib_read( 0x0006 ) , HEX );
  lcd.print( tanglib_read( 0x0007 ) , HEX );




    


}










void test02() {

  lcd.clear();
  lcd.print("Test 02");


  for ( uint32_t i = 0 ; i < 65535 ; i++ ) {
    tanglib_write( i , (uint8_t)(i&0xFF) );
  }


  lcd.setCursor(0,1);
  lcd.print("Checking");


  for ( uint32_t i = 0 ; i < 65535 ; i++ ) {
    if ( tanglib_read( i ) != (uint8_t)(i&0xFF) ) {
      lcd.clear();
      lcd.print("Fail!");
      lcd.setCursor(0,1);
      lcd.print(i , HEX );
      lcd.print(":");
      lcd.print((uint8_t)(i&0xFF));
      lcd.print(":");
      lcd.print( tanglib_read( i ) );
      while(1);
    }
  }

  lcd.clear();
  lcd.print("Pass!");

}










void test03() {

  lcd.clear();
  lcd.print("Execution Test!");

  tanglib_reset();

  tanglib_write( 0b1000000000000000 , 0x00 );
  tanglib_write( TANG_CMD_END , 0x01 );

  tanglib_execute_and_wait();

  lcd.setCursor(0,1);
  lcd.print("pass!");







}




void test04() {

  lcd.clear();
  lcd.print("Register Test");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();

  tanglib_write( address++ , 0x10 );
  tanglib_write( address++ , TANG_BANKA_KEY );
  tanglib_write( address++ , 0x11 );
  tanglib_write( address++ , 0x01 );
  
  tanglib_execute_and_wait();

  lcd.setCursor(0,1);


  lcd.print( tanglib_read( TANG_SRC_START ) , HEX );



}







void test05() {

  lcd.clear();
  lcd.print("Bankfill Test");
  lcd.setCursor(0,1);

  tanglib_reset();



  uint16_t address = TANG_CMD_START;
  uint8_t testbyte = 0xAA;

  // load bank register
  tanglib_write( address++ , 0x10 );
  tanglib_write( address++ , TANG_BANKA_SRC );
  
  // fill bank A with immedeate
  tanglib_write( address++ , 0x14 );
  tanglib_write( address++ , testbyte );
  
  // halt
  tanglib_write( address++ , 0x01 );
  
  tanglib_execute_and_wait();


  // now check bank was written
  for ( uint32_t i = TANG_SRC_START ; i <= TANG_SRC_END ; i++ ) {

      if ( tanglib_read( i ) != testbyte ) {
        lcd.clear();
        lcd.print("Fail! src");
        lcd.setCursor(0,1);
        lcd.print(i,HEX);
        lcd.print(":");
        lcd.print( tanglib_read( i ) );
        while (1);
      }

  }


  lcd.print("S:OK");





  address = TANG_CMD_START;
  testbyte = 0x55;

  // load bank register
  tanglib_write( address++ , 0x10 );
  tanglib_write( address++ , TANG_BANKA_KEY );
  
  // fill bank A with immedeate
  tanglib_write( address++ , 0x14 );
  tanglib_write( address++ , testbyte );
  
  // halt
  tanglib_write( address++ , 0x01 );
  
  tanglib_execute_and_wait();


  // now check bank was written
  for ( uint32_t i = TANG_KEY_START ; i <= TANG_KEY_END ; i++ ) {

      if ( tanglib_read( i ) != testbyte ) {
        lcd.clear();
        lcd.print("Fail! key");
        lcd.setCursor(0,1);
        lcd.print(i,HEX);
        lcd.print(":");
        lcd.print( tanglib_read( i ) );
        while (1);
      }

  }


  lcd.print("K:OK");




  address = TANG_CMD_START;
  testbyte = 0x01;

  // load bank register
  tanglib_write( address++ , 0x10 );
  tanglib_write( address++ , TANG_BANKA_CMD );
  
  // fill bank A with immedeate
  tanglib_write( address++ , 0x14 );
  tanglib_write( address++ , testbyte );
  
  // halt
  tanglib_write( address++ , 0x01 );
  
  tanglib_execute_and_wait();


  // now check bank was written
  for ( uint32_t i = TANG_CMD_START ; i <= TANG_CMD_END ; i++ ) {

      if ( tanglib_read( i ) != testbyte ) {
        lcd.clear();
        lcd.print("Fail! cmd");
        lcd.setCursor(0,1);
        lcd.print(i,HEX);
        lcd.print(":");
        lcd.print( tanglib_read( i ) );
        while (1);
      }

  }


  lcd.print("C:OK");




  address = TANG_CMD_START;
  testbyte = 0xAA;

  // load bank register
  tanglib_write( address++ , 0x10 );
  tanglib_write( address++ , TANG_BANKA_DST );
  
  // fill bank A with immedeate
  tanglib_write( address++ , 0x14 );
  tanglib_write( address++ , testbyte );
  
  // halt
  tanglib_write( address++ , 0x01 );
  
  tanglib_execute_and_wait();


  // now check bank was written
  for ( uint32_t i = TANG_DST_START ; i <= TANG_DST_END ; i++ ) {

      if ( tanglib_read( i ) != testbyte ) {
        lcd.clear();
        lcd.print("Fail! dst");
        lcd.setCursor(0,1);
        lcd.print(i,HEX);
        lcd.print(":");
        lcd.print( tanglib_read( i ) , HEX);
        while (1);
      }

  }


  lcd.print("D:OK");




}








// test06 register select register test

void test06() {

  lcd.clear();
  lcd.print("Register Select");
  lcd.setCursor(0,1);

  uint16_t address = TANG_CMD_START;

  tanglib_reset();

  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x81 );
  tanglib_write( address++ , 0x21 );
  tanglib_write( address++ , 0x01 );
  
  tanglib_execute_and_wait();

  lcd.setCursor(0,1);
  lcd.print( tanglib_read( 0x0000 ) , BIN );
  lcd.setCursor(8,1);
  lcd.print( tanglib_read( 0x0001 ) , BIN );

}








// test07 register read-write test

// program

// load 0xAA into usr_data_0
// 0x24 load immedeate into register
// 0x00 usr_data_0 mask
// 0xAA The value to load

// load 0x0000 into usr_wideptr_0
// 0x24 load immedeate into register
// 0x80 usr_wideptr_0 high byte mask
// 0x00 the value to load
// 0x24 load immedeate into register
// 0x40 usr_wideptr_0 low byte mask
// 0x00 the value to load

// load A->B into register select
// 0x20 load immedeate into register select register
// 0x00 usr_data_0 mask
// 0x80 usr_wideptr_0 mask

// copy register byte A to wideptr B
// 0x23 write register byte A to wideptr B

// halt
// 0x01 Halt and signal finished.



void test07() {

  lcd.clear();
  lcd.print("Register Test");


  uint16_t address = TANG_CMD_START;

  uint8_t testbyte = 0xDE;

  tanglib_reset();

  // program

  // load 0xAA into usr_data_0
  // 0x24 load immedeate into register
  tanglib_write( address++ , 0x24 );
  // 0x00 usr_data_0 mask
  tanglib_write( address++ , 0x00 );
  // 0xAA The value to load
  tanglib_write( address++ , testbyte );
  
  // load 0x0000 into usr_wideptr_0
  // 0x24 load immedeate into register
  tanglib_write( address++ , 0x24 );
  // 0x80 usr_wideptr_0 high byte mask
  tanglib_write( address++ , 0x80 );
  // 0x00 the value to load
  tanglib_write( address++ , 0x00 );
  // 0x24 load immedeate into register
  tanglib_write( address++ , 0x24 );
  // 0x40 usr_wideptr_0 low byte mask
  tanglib_write( address++ , 0x40 );
  // 0x00 the value to load
  tanglib_write( address++ , 0x00 );
  
  // load A->B into register select
  // 0x20 load immedeate into register select register
  tanglib_write( address++ , 0x20 );
  // 0x00 usr_data_0 mask
  tanglib_write( address++ , 0x00 );
  // 0x80 usr_wideptr_0 mask
  tanglib_write( address++ , 0x80 );
  
  // copy register byte A to wideptr B
  // 0x23 write register byte A to the location pointed to by wideptr B
  tanglib_write( address++ , 0x23 );
  
  // halt
  // 0x01 Halt and signal finished.
  tanglib_write( address++ , 0x01 );
  

  tanglib_execute_and_wait();


  lcd.setCursor(0,1);
  lcd.print( tanglib_read( 0x0000 ) , HEX );


}








// test08 big test of all registers

// program

// load immedeate into each byte of register

// copy them all to memory

// read them all out

// check them.


void test08() {

  lcd.clear();
  lcd.print("register bigtest");



uint16_t address = TANG_CMD_START;

  
  address = TANG_CMD_START;
  tanglib_reset();
  
  // load 16 bytes of data register
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x03 );
  tanglib_write( address++ , 0x03 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x04 );
  tanglib_write( address++ , 0x04 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x05 );
  tanglib_write( address++ , 0x05 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x06 );
  tanglib_write( address++ , 0x06 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x07 );
  tanglib_write( address++ , 0x07 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x08 );
  tanglib_write( address++ , 0x08 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x09 );
  tanglib_write( address++ , 0x09 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0A );
  tanglib_write( address++ , 0x0A );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0B );
  tanglib_write( address++ , 0x0B );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0C );
  tanglib_write( address++ , 0x0C );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0D );
  tanglib_write( address++ , 0x0D );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0E );
  tanglib_write( address++ , 0x0E );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0F );
  tanglib_write( address++ , 0x0F );
  
  
  
  // set output widptr high
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x80 );
  tanglib_write( address++ , 0x00 );
  
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x00 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x01 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x02 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x03 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x03 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x04 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x04 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x05 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x05 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x06 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x06 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x07 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x07 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x08 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x08 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x09 );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x09 );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x0A );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x0A );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x0B );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x0B );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x0C );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x0C );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x0D );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x0D );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x0E );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x0E );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  // set output wideptr low
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x0F );
  // set register select register
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x0F );
  tanglib_write( address++ , 0x00 );
  // do copy
  tanglib_write( address++ , 0x23 );
  
  
  
  tanglib_write( address++ , 0x01 );
  
  
  tanglib_execute_and_wait();


  lcd.setCursor(0,1);
  lcd.print( tanglib_read( 0x0000 ) , HEX );
  lcd.print( tanglib_read( 0x0001 ) , HEX );
  lcd.print( tanglib_read( 0x0002 ) , HEX );
  lcd.print( tanglib_read( 0x0003 ) , HEX );
  lcd.print( tanglib_read( 0x0004 ) , HEX );
  lcd.print( tanglib_read( 0x0005 ) , HEX );
  lcd.print( tanglib_read( 0x0006 ) , HEX );
  lcd.print( tanglib_read( 0x0007 ) , HEX );
  lcd.print( tanglib_read( 0x0008 ) , HEX );
  lcd.print( tanglib_read( 0x0009 ) , HEX );
  lcd.print( tanglib_read( 0x000A ) , HEX );
  lcd.print( tanglib_read( 0x000B ) , HEX );
  lcd.print( tanglib_read( 0x000C ) , HEX );
  lcd.print( tanglib_read( 0x000D ) , HEX );
  lcd.print( tanglib_read( 0x000E ) , HEX );
  lcd.print( tanglib_read( 0x000F ) , HEX );
  







  // lcd.setCursor(0,1);
  // lcd.print("Pass all!");



}







// test09  test inc and dec

// program
// load immedeate into usr_data_0
// increment
// increment
// increment
// load immedeate value into wideptr
// load immedeate value into register select
// perform copy to memory
// halt


void test09() {


  lcd.clear();
  lcd.print("Test 09");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();
  
  // program
  // load immedeate into usr_data_0
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x05 );
  // increment
  tanglib_write( address++ , 0x34 );
  tanglib_write( address++ , 0x00 );
  // increment
  tanglib_write( address++ , 0x34 );
  tanglib_write( address++ , 0x00 );
  // increment
  tanglib_write( address++ , 0x34 );
  tanglib_write( address++ , 0x00 );
  // load immedeate value into wideptr
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x80 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x00 );
  
  // load immedeate value into register select
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x80 );
  
  // perform copy to memory
  tanglib_write( address++ , 0x23 );
  
  // halt
  tanglib_write( address++ , 0x01 );

  tanglib_execute_and_wait();
  

  lcd.setCursor(0,1);
  lcd.print( tanglib_read( 0x0000 ) , HEX );




}








// test A jmp test

// program

// load immedeate into usr_data_0
// jmp XXXX
// increment usr_data_0
// set bank register immedeate
// set usr_wideptr_0 immedeate
// copy A to B
// finish


void test0A() {

  lcd.clear();
  lcd.print("Test 0A");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();
  
  

  // load immedeate into usr_data_0
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x05 );
  // jmp XXXX
  tanglib_write( address++ , 0x50 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x0C );
  // increment usr_data_0
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x00 );
  // increment usr_data_0
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x00 );
  // increment usr_data_0
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x00 );
  // set register select immedeate
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x80 );
  // set usr_wideptr_0 immedeate
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x80 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x00 );
  // copy A to B
  tanglib_write( address++ , 0x23 );
  // finish
  tanglib_write( address++ , 0x01 );
  

  tanglib_execute_and_wait();
  

  lcd.setCursor(0,1);
  lcd.print( tanglib_read( 0x0000 ) , HEX );



}
















// test 0B jmpz test

// program
// load register select register
// load wideptr
// load value into usr_data_0
// decrement usr_data_0
// jmp if usr_data_0 equals zero
// copy from A to B
// finish

void test0B() {

  lcd.clear();
  lcd.print("Test 0B");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();
  
  

  
  // program
  // load register select register
  tanglib_write( address++ , 0x20 );//00
  tanglib_write( address++ , 0x01 );//01
  tanglib_write( address++ , 0x80 );//02
  // load wideptr
  tanglib_write( address++ , 0x24 );//03
  tanglib_write( address++ , 0x80 );//04
  tanglib_write( address++ , 0x00 );//05
  tanglib_write( address++ , 0x24 );//06
  tanglib_write( address++ , 0x40 );//07
  tanglib_write( address++ , 0x00 );//08
  // load value into usr_data_0
  tanglib_write( address++ , 0x24 );//09
  tanglib_write( address++ , 0x00 );//0A
  tanglib_write( address++ , 0xDE );//0B
  // load value into usr_data_1
  tanglib_write( address++ , 0x24 );//0C
  tanglib_write( address++ , 0x01 );//0D
  tanglib_write( address++ , 0x00 );//0E
  // decrement usr_data_0
  tanglib_write( address++ , 0x34 );//0F
  tanglib_write( address++ , 0x00 );//10
  // increment usr_data_1
  tanglib_write( address++ , 0x30 );//11
  tanglib_write( address++ , 0x01 );//12
  // jmp if usr_data_0 equals zero
  tanglib_write( address++ , 0x54 );//13
  tanglib_write( address++ , 0x00 );//14
  tanglib_write( address++ , 0x00 );//15
  tanglib_write( address++ , 0x1A );//16
  // jmp unconditionally
  tanglib_write( address++ , 0x50 );//17
  tanglib_write( address++ , 0x00 );//18
  tanglib_write( address++ , 0x0F );//19
  // copy from A to B
  tanglib_write( address++ , 0x23 );//1A
  // finish
  tanglib_write( address++ , 0x01 );//1B
  
  
  
  
  
  
  
  

  tanglib_execute_and_wait();
  

  lcd.setCursor(0,1);
  lcd.print( tanglib_read( 0x0000 ) , HEX );



}








// add two numbers together with two counters and an accumulator


// program
// 
// set operand A into usr_data_0
// set operand B into usr_data_1
// 
// copy usr_data_0 to cpu_data_0
// copy usr_data_1 to cpu_data_1
// clear usr_data_2 to zero
// 
// loop1 first operand
// decrement cpu_data_0
// increment usr_data_2
// jmpnz cpu_data_0 loop1
// 
// loop2 second operand
// decrement cpu_data_1
// increment usr_data_2
// jmpnz cpu_data_1 loop2
// 
// set register select to usr_data_2 > wideptr0
// 
// copy register A to register B
// 
// finish

void test0C() {

  lcd.clear();
  lcd.print("Test 0C");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();
  
  





  // program
  // 
  // set operand A into usr_data_0
  tanglib_write( address++ , 0x24 );//00
  tanglib_write( address++ , 0x00 );//01
  tanglib_write( address++ , 0x05 );//02
  // set operand B into usr_data_1
  tanglib_write( address++ , 0x24 );//03
  tanglib_write( address++ , 0x01 );//04
  tanglib_write( address++ , 0x05 );//05

  // clear usr_data_2 to zero
  tanglib_write( address++ , 0x24 );//06
  tanglib_write( address++ , 0x02 );//07
  tanglib_write( address++ , 0x00 );//08
  
  
  
  // loop1: first operand
  
  // decrement usr_data_0
  tanglib_write( address++ , 0x34 );//09
  tanglib_write( address++ , 0x00 );//0A
  // increment usr_data_2
  tanglib_write( address++ , 0x30 );//0B
  tanglib_write( address++ , 0x02 );//0C
  
  // jmpz usr_data_0 loop2
  tanglib_write( address++ , 0x54 );//0D
  tanglib_write( address++ , 0x00 );//0E
  tanglib_write( address++ , 0x00 );//0F
  tanglib_write( address++ , 0x14 );//10
  
  
  // jmp loop1
  tanglib_write( address++ , 0x50 );//11
  tanglib_write( address++ , 0x00 );//12
  tanglib_write( address++ , 0x09 );//13
  
  
  
  // loop2 second operand
  
  // decrement usr_data_1
  tanglib_write( address++ , 0x34 );//14
  tanglib_write( address++ , 0x01 );//15
  // increment usr_data_2
  tanglib_write( address++ , 0x30 );//16
  tanglib_write( address++ , 0x02 );//17
  
  // jmpz usr_data_1 finalpart
  tanglib_write( address++ , 0x54 );//18
  tanglib_write( address++ , 0x01 );//19
  tanglib_write( address++ , 0x00 );//1A
  tanglib_write( address++ , 0x1F );//1B
  
  // jmp loop2
  tanglib_write( address++ , 0x50 );//1C
  tanglib_write( address++ , 0x00 );//1D
  tanglib_write( address++ , 0x14 );//1E
  
  
  
  // final part
  
  // set usr_wideptr_0 to dst 0xC000
  tanglib_write( address++ , 0x24 );//1F
  tanglib_write( address++ , 0x80 );//20
  tanglib_write( address++ , 0xC0 );//21
  tanglib_write( address++ , 0x24 );//22
  tanglib_write( address++ , 0x40 );//23
  tanglib_write( address++ , 0x00 );//24
  
  // set register select to usr_data_2 > usr_wideptr_0
  tanglib_write( address++ , 0x20 );//25
  tanglib_write( address++ , 0x02 );//26
  tanglib_write( address++ , 0x80 );//27
  
  // copy register A to register B
  tanglib_write( address++ , 0x23 );//28
  
  // finish
  tanglib_write( address++ , 0x01 );//29
  


  tanglib_execute_and_wait();
  

  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );


}















// test 0D jmp test.



void test0D() {


  
  lcd.clear();
  lcd.print("Test 0D");

  //uint16_t address = TANG_CMD_START;

  tanglib_reset();
  

  // bank fill with halts
  for ( uint16_t i = TANG_CMD_START ; i <= TANG_CMD_END ; i++ ) {
    tanglib_write( i , 0x00 );
  }

  lcd.setCursor( 0 , 1 );
  lcd.print("Checking");


  // test of jmpi

  // 0x8000 0x24 set
  tanglib_write( 0x8000 , 0x24 );
  // 0x8001 0x00 usr_data_0
  tanglib_write( 0x8001 , 0x00 );
  // 0x8002 0x00 0
  tanglib_write( 0x8002 , 0x00 );

  // 0x8003 0x50 jmp
  tanglib_write( 0x8003 , 0x50 );
  // 0x8004 0x02 immed
  tanglib_write( 0x8004 , 0x02 );
  // 0x8005 0x80 addrh
  tanglib_write( 0x8005 , 0x80 );
  // 0x8006 0x10 addrl
  tanglib_write( 0x8006 , 0x10 );

  // 0x8007 0x24 set
  tanglib_write( 0x8007 , 0x24 );
  // 0x8008 0x00 usr_data_0
  tanglib_write( 0x8008 , 0x00 );
  // 0x8009 0x01 1
  tanglib_write( 0x8009 , 0x01 );


  tanglib_write( 0x800A , 0x01 );
  







  // test of jmpp

  // 0x8010 0x24 set
  tanglib_write( 0x8010 , 0x24 );
  // 0x8011 0x20 usr_addr_0
  tanglib_write( 0x8011 , 0x20 );
  // 0x8012 0x80 addrh
  tanglib_write( 0x8012 , 0x80 );
  // 0x8013 0x24 set
  tanglib_write( 0x8013 , 0x24 );
  // 0x8014 0x10 usr_addr_0
  tanglib_write( 0x8014 , 0x10 );
  // 0x8015 0x20 addrl
  tanglib_write( 0x8015 , 0x20 );

  // 0x8016 0x50 jmp
  tanglib_write( 0x8016 , 0x50 );
  // 0x8017 0x03 ptr
  tanglib_write( 0x8017 , 0x03 );
  // 0x8018 0x20 rsel usr_address_0
  tanglib_write( 0x8018 , 0x20 );

  // 0x8019 0x24 set
  tanglib_write( 0x8019 , 0x24 );
  // 0x801A 0x00 usr_data_0
  tanglib_write( 0x801A , 0x00 );
  // 0x801B 0x02 2
  tanglib_write( 0x801B , 0x02 );










  // test of jmpzi

  // 0x8020 0x24 set
  tanglib_write( 0x8020 , 0x24 );
  // 0x8021 0x01 usr_data_1
  tanglib_write( 0x8021 , 0x01 );
  // 0x8022 0x00 0
  tanglib_write( 0x8022 , 0x00 );

  // 0x8023 0x50 jmp
  tanglib_write( 0x8023 , 0x50 );
  // 0x8024 0x08 zero, immed
  tanglib_write( 0x8024 , 0x08 );
  // 0x8025 0x01 rsel
  tanglib_write( 0x8025 , 0x01 );
  // 0x8026 0x80 addrh
  tanglib_write( 0x8026 , 0x80 );
  // 0x8027 0x30 addrl
  tanglib_write( 0x8027 , 0x30 );

  // 0x8028 0x24 set
  tanglib_write( 0x8028 , 0x24 );
  // 0x8029 0x00 usr_data_0
  tanglib_write( 0x8029 , 0x00 );
  // 0x802A 0x03 3
  tanglib_write( 0x802A , 0x03 );










  // test of jmpzp

  // 0x8030 0x24 set
  tanglib_write( 0x8030 , 0x24 );
  // 0x8031 0x01 usr_data_1
  tanglib_write( 0x8031 , 0x01 );
  // 0x8032 0x00 0
  tanglib_write( 0x8032 , 0x00 );

  // 0x8033 0x24 set
  tanglib_write( 0x8033 , 0x24 );
  // 0x8034 0x21 usr_address_1
  tanglib_write( 0x8034 , 0x21 );
  // 0x8035 0x80 addrh
  tanglib_write( 0x8035 , 0x80 );
  // 0x8036 0x24 set
  tanglib_write( 0x8036 , 0x24 );
  // 0x8037 0x11 usr_address_1
  tanglib_write( 0x8037 , 0x11 );
  // 0x8038 0x40 addrl
  tanglib_write( 0x8038 , 0x40 );

  // 0x8039 0x50 jmp
  tanglib_write( 0x8039 , 0x50 );
  // 0x803A 0x0C zero, pointer
  tanglib_write( 0x803A , 0x0C );
  // 0x803B 0x01 rsel usr_data_1
  tanglib_write( 0x803B , 0x01 );
  // 0x803C 0x21 rsel usr_address_1
  tanglib_write( 0x803C , 0x21 );

  // 0x803D 0x24 set
  tanglib_write( 0x803D , 0x24 );
  // 0x803E 0x00 usr_data_0
  tanglib_write( 0x803E , 0x00 );
  // 0x803F 0x04 4
  tanglib_write( 0x803F , 0x04 );









  // test of jmpnzi

  // 0x8040 0x24 set
  tanglib_write( 0x8040 , 0x24 );
  // 0x8041 0x01 usr_data_1
  tanglib_write( 0x8041 , 0x01 );
  // 0x8042 0x01 1
  tanglib_write( 0x8042 , 0x01 );

  // 0x8043 0x50 jmp
  tanglib_write( 0x8043 , 0x50 );
  // 0x8044 0x20 not zero, immed
  tanglib_write( 0x8044 , 0x20 );
  // 0x8045 0x01 rsel
  tanglib_write( 0x8045 , 0x01 );
  // 0x8046 0x80 addrh
  tanglib_write( 0x8046 , 0x80 );
  // 0x8047 0x50 addrl
  tanglib_write( 0x8047 , 0x50 );

  // 0x8048 0x24 set
  tanglib_write( 0x8048 , 0x24 );
  // 0x8049 0x00 usr_data_0
  tanglib_write( 0x8049 , 0x00 );
  // 0x804A 0x05 5
  tanglib_write( 0x804A , 0x05 );









  // test of jmpnzp

  // 0x8050 0x24 set
  tanglib_write( 0x8050 , 0x24 );
  // 0x8051 0x01 usr_data_1
  tanglib_write( 0x8051 , 0x01 );
  // 0x8052 0x01 1
  tanglib_write( 0x8052 , 0x1 );

  // 0x8053 0x24 set
  tanglib_write( 0x8053 , 0x24 );
  // 0x8054 0x21 usr_address_1
  tanglib_write( 0x8054 , 0x21 );
  // 0x8055 0x80 addrh
  tanglib_write( 0x8055 , 0x80 );
  // 0x8056 0x24 set
  tanglib_write( 0x8056 , 0x24 );
  // 0x8057 0x11 usr_address_1
  tanglib_write( 0x8057 , 0x11 );
  // 0x8058 0x60 addrl
  tanglib_write( 0x8058 , 0x60 );

  // 0x8059 0x50 jmp
  tanglib_write( 0x8059 , 0x50 );
  // 0x805A 0x30 not zero, pointer
  tanglib_write( 0x805A , 0x30 );
  // 0x805B 0x01 rsel usr_data_1
  tanglib_write( 0x805B , 0x01 );
  // 0x805C 0x21 rsel usr_address_1
  tanglib_write( 0x805C , 0x21 );

  // 0x805D 0x24 set
  tanglib_write( 0x805D , 0x24 );
  // 0x805E 0x00 usr_data_0
  tanglib_write( 0x805E , 0x00 );
  // 0x805F 0x06 6
  tanglib_write( 0x805F , 0x06 );








  // 0x8060 0x24 set
  tanglib_write( 0x8060 , 0x24 );
  // 0x8061 0x80 usr_wideptr_0
  tanglib_write( 0x8061 , 0x80 );
  // 0x8062 0x addrh
  tanglib_write( 0x8062 , 0xC0 );
  // 0x8063 0x24 set
  tanglib_write( 0x8063 , 0x24 );
  // 0x8064 0x40 usr_wideptr_0
  tanglib_write( 0x8064 , 0x40 );
  // 0x8065 0x adrl
  tanglib_write( 0X8065 , 0x00 );

  // 0x8066 0x20 set register select register
  tanglib_write( 0x8066 , 0x20 );
  // 0x8067 0x00 usr_data_0
  tanglib_write( 0x8067 , 0x00 );
  // 0x8068 0x80 usr_wideptr_0
  tanglib_write( 0x8068 , 0x80 );

  // 0x8069 0x23 copy data from A to B
  tanglib_write( 0x8069 , 0x23 );

  // 0x806A 0x01 finish
  tanglib_write( 0x806A , 0x01 );



  // stop at end
  tanglib_write( TANG_CMD_END , 0x01 );



  tanglib_execute_and_wait();
  
  lcd.clear();
  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );


}




// 0x48 c = A xor B


void test0E() {

  lcd.clear();
  lcd.print("Test 0E");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();
  
  





  // program
  // 
  // load AA into usr_data_0
  // load AA into usr_data_1
  // xor A B C
  // load wideptr
  // copy C to wideptr
  // halt

  
  // program
  // 
  // load A into usr_data_0
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0xAA );
  // load B into usr_data_1
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x00 );
  // xor A B C
  tanglib_write( address++ , 0x48 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x02 );
  // load wideptr
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x80 );
  tanglib_write( address++ , 0xC0 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x00 );
  // set register select
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x80 );
  // copy C to wideptr
  tanglib_write( address++ , 0x23 );
  // halt
  tanglib_write( address++ , 0x01 );
  

  tanglib_execute_and_wait();
  

  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );




}




// loop using xor comparison


void test0F() {

  lcd.clear();
  lcd.print("Test 0F");

  uint16_t address = TANG_CMD_START;

  tanglib_reset();
  
  


  // load everything!

  // set usr_data_0 to mincounter
  // set usr_data_1 to maxcounter
  // loopstart:
  // increment usr_data_0
  // increment usr_data_3
  // usr_data_2 = usr_data_0 xor usr_data_1
  // jmpnz usr_data_2 loopstart
  // copy data out
  // halt


  // program
  // 
  
  
  // set usr_data_0 to mincounter
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x05 );
  // set usr_data_1 to maxcounter
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x09 );
  // loopstart:
  // increment usr_data_0
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x00 );
  // increment usr_data_3
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x03 );

  // usr_data_2 = usr_data_0 xor usr_data_1
  tanglib_write( address++ , 0x48 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x02 );

  // jmpnz usr_data_2 immed to loopstart
  tanglib_write( address++ , 0x50 );
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x06 );
  
  // copy data out
  // load wideptr
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x80 );
  tanglib_write( address++ , 0xC0 );
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x40 );
  tanglib_write( address++ , 0x00 );
  // set register select
  tanglib_write( address++ , 0x20 );
  tanglib_write( address++ , 0x03 );
  tanglib_write( address++ , 0x80 );
  // copy usr_data_3 to wideptr
  tanglib_write( address++ , 0x23 );
  
  
  // halt
  tanglib_write( address++ , 0x01 );
  

  tanglib_execute_and_wait();
  

  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );




}






void test10() {

  lcd.clear();
  lcd.print("Test 0F");


  tanglib_reset();
  

    // bank fill with halts
  for ( uint16_t i = TANG_CMD_START ; i <= TANG_CMD_END ; i++ ) {
    tanglib_write( i , 0x00 );
  }

  lcd.setCursor( 0 , 1 );
  lcd.print("Checking");




  uint16_t address = TANG_CMD_END;

  tanglib_write( address , 0x01 );

  
  


  // load everything!

  // set usr_data_0 to mincounter
  // set usr_data_1 to maxcounter
  // loopstart:
  // increment usr_data_0
  // increment usr_data_3
  // usr_data_2 = usr_data_0 xor usr_data_1
  // jmpnz usr_data_2 loopstart
  // copy data out
  // halt


  // program
  // 
  
  
  stopwatch_start();
  tanglib_execute_and_wait();
  stopwatch_stop();

  
  lcd.clear();
  lcd.print(stopwatch_duration());
  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );
  




}









// jump test

void test11() {

  lcd.clear();
  lcd.print("Test 11");


  tanglib_reset();
  
  lcd.setCursor(0,1);
  lcd.print("Bankfill");

  bankclear();

  lcd.setCursor( 0 , 1 );
  lcd.print("                ");
  lcd.print("Checking");




  uint16_t address = TANG_CMD_START;


  // set register to check usr_data_0

  // set address register to target

  // jump

  // set register test fail result

  // stop





  tanglib_write( address , 0x00 );

  
  stopwatch_start();
  //tanglib_execute_and_wait();
  stopwatch_stop();

  
  lcd.clear();
  lcd.print(stopwatch_duration());
  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );
  




}









// jmp rel fwd


void test12() {

  lcd.clear();
  lcd.print("Test 12");


  tanglib_reset();
  
  lcd.setCursor(0,1);
  lcd.print("Bankfill");

  bankclear();

  lcd.setCursor( 0 , 1 );
  lcd.print("                ");
  lcd.print("Checking");




  uint16_t address = TANG_CMD_START;

  
                        // 0x52 jmp rel fwd
                        // jmp flags
                        // 0b00000010 = jmp immed
                        // 0b00000011 = jmp rsel
                        // 0b00001000 = jmpz immed
                        // 0b00001100 = jmpz rsel
                        // 0b00100000 = jmpnz immed
                        // 0b00110000 = jmpnz rsel
                        // 0b10000000 = 
                        // 0b11000000 = 


  // jmp immed

  // jmprelfwd
  tanglib_write( address++ , 0x52 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x04 );
  
  // set register usr_data_F to FF
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0F );
  tanglib_write( address++ , 0xFF );

  
  // jmprelrsel
  // set register to jump rel value
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x04 );
  
  // jmprelfwd
  tanglib_write( address++ , 0x52 );
  tanglib_write( address++ , 0x03 );
  tanglib_write( address++ , 0x00 );
  
  // set register usr_data_F to FF
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x0F );
  tanglib_write( address++ , 0xFE );

  

  
  


  // copy data out
  // load wideptr
  tanglib_write( 0x8FF5 , 0x24 );
  tanglib_write( 0x8FF6 , 0x80 );
  tanglib_write( 0x8FF7 , 0xC0 );
  tanglib_write( 0x8FF8 , 0x24 );
  tanglib_write( 0x8FF9 , 0x40 );
  tanglib_write( 0x8FFA , 0x00 );
  // set register select
  tanglib_write( 0x8FFB , 0x20 );
  tanglib_write( 0x8FFC , 0x03 );
  tanglib_write( 0x8FFD , 0x80 );
  // copy usr_data_F to wideptr
  tanglib_write( 0x8FFE , 0x23 );
  // halt
  tanglib_write( 0x8FFF , 0x01 );









  stopwatch_start();
  tanglib_execute_and_wait();
  stopwatch_stop();

  
  lcd.clear();
  lcd.print(stopwatch_duration());
  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );
  




}










// loop test

// set mincounter to 5
// set maxcounter to 10
// incr mincounter
// incr target
// jmpnzrelbwd
// 

void test13() {

  lcd.clear();
  lcd.print("Test 13");


  tanglib_reset();
  
  lcd.setCursor(0,1);
  lcd.print("Bankfill");

  bankclear();

  lcd.setCursor( 0 , 1 );
  lcd.print("                ");
  lcd.print("Checking");

  uint16_t address = TANG_CMD_START;

  
                        // 0x52 jmp rel fwd
                        // jmp flags
                        // 0b00000010 = jmp immed
                        // 0b00000011 = jmp rsel
                        // 0b00001000 = jmpz immed
                        // 0b00001100 = jmpz rsel
                        // 0b00100000 = jmpnz immed
                        // 0b00110000 = jmpnz rsel
                        // 0b10000000 = 
                        // 0b11000000 = 



  // loop test

  // set mincounter to 5
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x05 );
  // set maxcounter to 10
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x0A );
  // incr mincounter
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x00 );
  // incr target
  tanglib_write( address++ , 0x30 );
  tanglib_write( address++ , 0x0F );
  // xor mincounter maxounter into check reg
  tanglib_write( address++ , 0x48 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x02 );
  // jmpnzrelbwd
  tanglib_write( address++ , 0x50 );
  tanglib_write( address++ , 0x02 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x00 );
  // 

  
  


  // copy data out
  // load wideptr
  tanglib_write( 0x8FF5 , 0x24 );
  tanglib_write( 0x8FF6 , 0x80 );
  tanglib_write( 0x8FF7 , 0xC0 );
  tanglib_write( 0x8FF8 , 0x24 );
  tanglib_write( 0x8FF9 , 0x40 );
  tanglib_write( 0x8FFA , 0x00 );
  // set register select
  tanglib_write( 0x8FFB , 0x20 );
  tanglib_write( 0x8FFC , 0x03 );
  tanglib_write( 0x8FFD , 0x80 );
  // copy usr_data_F to wideptr
  tanglib_write( 0x8FFE , 0x23 );
  // halt
  tanglib_write( 0x8FFF , 0x01 );









  stopwatch_start();
  tanglib_execute_and_wait();
  stopwatch_stop();

  
  lcd.clear();
  lcd.print(stopwatch_duration());
  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );
  




}




void test14() {
  
  lcd.clear();
  lcd.print("Test 14");


  tanglib_reset();
  
  lcd.setCursor(0,1);
  lcd.print("Bankfill");

  bankclear();

  lcd.setCursor( 0 , 1 );
  lcd.print("                ");
  lcd.print("Checking");

  uint16_t address = TANG_CMD_START;





  // tanglib_write( address++ , 0x00 );
  
  // set usr_data_0 to 5
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x05 );
  // set usr_data_b to 5
  tanglib_write( address++ , 0x24 );
  tanglib_write( address++ , 0x01 );
  tanglib_write( address++ , 0x03 );
  // C = A + B
  tanglib_write( address++ , 0x46 );
  tanglib_write( address++ , 0x00 );
  tanglib_write( address++ , 0x0F );
  //tanglib_write( address++ , 0x0F );
  
  // spin down to output
  


  // copy data out
  // load wideptr
  tanglib_write( 0x8FF5 , 0x24 );
  tanglib_write( 0x8FF6 , 0x80 );
  tanglib_write( 0x8FF7 , 0xC0 );
  tanglib_write( 0x8FF8 , 0x24 );
  tanglib_write( 0x8FF9 , 0x40 );
  tanglib_write( 0x8FFA , 0x00 );
  // set register select
  tanglib_write( 0x8FFB , 0x20 );
  tanglib_write( 0x8FFC , 0x0F );
  tanglib_write( 0x8FFD , 0x80 );
  // copy usr_data_F to wideptr
  tanglib_write( 0x8FFE , 0x23 );
  // halt
  tanglib_write( 0x8FFF , 0x01 );









  stopwatch_start();
  tanglib_execute_and_wait();
  stopwatch_stop();

  
  lcd.clear();
  lcd.print(stopwatch_duration());
  lcd.setCursor(0,1);
  // read dst 0
  lcd.print( tanglib_read( 0xC000 ) , HEX );
  

}










void menucommand_01() {
  test01();
  while(1);
}


void menucommand_02() {
  test02();
  while(1);
}


void menucommand_03() {
  while(1);
}

void menucommand_04() {
  while(1);
}

void menucommand_05() {
  while(1);
}



























