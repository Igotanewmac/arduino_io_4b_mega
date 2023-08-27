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

  // lcd backlight on weird pin
  pinMode(10 , OUTPUT);
  digitalWrite(10,HIGH);

  // set the buttonpin to input
  pinMode( BUTTONPIN , INPUT );


  // set up the tang pins
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

  delay(10);
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
  lcd.print("Test 03");

  // send a halt to the tang

  // clear out the command stream
  tanglib_commandstream_reset( 0x00 );

  
  // clear out all memory banks too
  bankclear();
  
  // reset the chip, just in case
  tanglib_reset();

  // add the halt to the command stream
  //command_0x01_halt();

  //tanglib_commandstream_send();


  // execute it!
  tanglib_execute_and_wait();

  // if this works, pass the test!
  lcd.setCursor(0,1);
  lcd.print("Pass!");



}




// test 4 loop counting

void test04() {

  lcd.clear();
  lcd.print("Test 04");

  // send a halt to the tang

  // clear out the command stream
  tanglib_commandstream_reset( 0x00 );

  // reset the chip, just in case
  tanglib_reset();

  // clear out all memory banks too
  bankclear();
  


  // set the loopmin to usr_data_0
  command_0x24_load_value_to_register( TANG_RSEL_DATA_0 , 0x01 );
  // set the loopmax to usr_data_1
  command_0x24_load_value_to_register( TANG_RSEL_DATA_1 , 0x05 );
  // clear usr_data_2
  command_0x24_load_value_to_register( TANG_RSEL_DATA_2 , 0x00 );

  
  // loopstart:
  uint16_t loopstartaddress = tanglib_commandstream_getindex();

  // increment usr_data_2
  command_0x30_inc( TANG_RSEL_DATA_2 );
  // increment usr_data_0
  command_0x30_inc( TANG_RSEL_DATA_0 );

  // usr_data_0 xor usr_data_1 into usr_data_3
  command_0x48_xor( TANG_RSEL_DATA_0 , TANG_RSEL_DATA_1 , TANG_RSEL_DATA_3 );
  
  // jmpnz usr_data_3 to loopstart
  command_0x50_jmpnz_immed( TANG_RSEL_DATA_3 , loopstartaddress );


  // set usr_wideptr_0 to dst 0x0000
  command_0x24_load_value_to_register( TANG_RSEL_WIDEPTR_0 , (uint8_t)( ( ( TANG_DST_START | 0x0000 ) >> 8 ) & 0xFF ) );
  command_0x24_load_value_to_register( TANG_RSEL_WIDEPTR_LOW_0 , (uint8_t)( ( TANG_DST_START | 0x0000 ) & 0xFF ) );
  
  // set bank select to A usr_data_2 , B usr_wideptr_0
  command_0x20_load_to_register_select( TANG_RSEL_DATA_3 , TANG_RSEL_WIDEPTR_0 );

  // copy register A to memory pointed to by B
  command_0x23_write_rselA_to_rselB();

  // halt
  command_0x01_halt();



  // full send!
  tanglib_commandstream_send();

  // execute it!
  tanglib_execute_and_wait();

  // if this works, pass the test!
  lcd.setCursor(0,1);
  lcd.print("Pass! ");

  lcd.print( tanglib_read( TANG_DST_START | 0x0000 ) , HEX );

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
  test03();
  while(1);
}

void menucommand_04() {
  test04();
  while(1);
}

void menucommand_05() {
  while(1);
}



























