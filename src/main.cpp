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



void test01();
void test02();
void test03();
void test04();
void test05();
void test06();
void test07();
void test08();
void test09();
void test0A();
void test0B();
void test0C();
void test0D();
void test0E();
void test0F();
void test10();
void test11();
void test12();
void test13();
void test14();
void test15();
void test16();
void test17();
void test18();
void test19();
void test1A();
void test1B();
void test1C();
void test1D();
void test1E();
void test1F();







void menucommand_01() {
  test01();
  while(1);
}


void menucommand_02() {
  test02();
  while(1);
}


void menucommand_03() {
  test03();
  while(1);
}

void menucommand_04() {
  test04();
  while(1);
}

void menucommand_05() {
  test05();
  while(1);
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




































