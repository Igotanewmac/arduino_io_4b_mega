
#include <Arduino.h>

#include <tanglib.h>





void tanglib_setup() {

    pinMode( TANGLIB_DATAIN_0 , OUTPUT );
    pinMode( TANGLIB_DATAIN_1 , OUTPUT );
    pinMode( TANGLIB_DATAIN_2 , OUTPUT );
    pinMode( TANGLIB_DATAIN_3 , OUTPUT );
    pinMode( TANGLIB_DATAIN_4 , OUTPUT );
    pinMode( TANGLIB_DATAIN_5 , OUTPUT );
    pinMode( TANGLIB_DATAIN_6 , OUTPUT );
    pinMode( TANGLIB_DATAIN_7 , OUTPUT );
    

    digitalWrite( TANGLIB_DATAIN_0 , LOW );
    digitalWrite( TANGLIB_DATAIN_1 , LOW );
    digitalWrite( TANGLIB_DATAIN_2 , LOW );
    digitalWrite( TANGLIB_DATAIN_3 , LOW );
    digitalWrite( TANGLIB_DATAIN_4 , LOW );
    digitalWrite( TANGLIB_DATAIN_5 , LOW );
    digitalWrite( TANGLIB_DATAIN_6 , LOW );
    digitalWrite( TANGLIB_DATAIN_7 , LOW );
    

    pinMode( TANGLIB_DATAOUT_0 , INPUT );
    pinMode( TANGLIB_DATAOUT_1 , INPUT );
    pinMode( TANGLIB_DATAOUT_2 , INPUT );
    pinMode( TANGLIB_DATAOUT_3 , INPUT );
    pinMode( TANGLIB_DATAOUT_4 , INPUT );
    pinMode( TANGLIB_DATAOUT_5 , INPUT );
    pinMode( TANGLIB_DATAOUT_6 , INPUT );
    pinMode( TANGLIB_DATAOUT_7 , INPUT );
    

    pinMode( TANGLIB_SHIFTIN , OUTPUT );
    pinMode( TANGLIB_READWRITE , OUTPUT );
    pinMode( TANGLIB_COMMIT , OUTPUT );
    pinMode( TANGLIB_RESET , OUTPUT );
    pinMode( TANGLIB_EXECUTE , OUTPUT );
    pinMode( TANGLIB_ISFINISHED , INPUT_PULLUP );
    pinMode( TANGLIB_ISERROR , INPUT_PULLUP );
    
    digitalWrite( TANGLIB_SHIFTIN , LOW );
    digitalWrite( TANGLIB_READWRITE , LOW );
    digitalWrite( TANGLIB_COMMIT , LOW );
    digitalWrite( TANGLIB_RESET , LOW );
    digitalWrite( TANGLIB_EXECUTE , LOW );
    
}





/// @brief pulse the reset line for 1ms
void tanglib_reset() {
    digitalWrite( TANGLIB_RESET , HIGH );
    delay(1);
    digitalWrite( TANGLIB_RESET , LOW );
}









void tanglib_write( uint16_t wideaddress , uint8_t databyte ) {

    // shift in high byte of address
    digitalWrite( TANGLIB_DATAIN_0 , (wideaddress >> 8) & 0b00000001 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_1 , (wideaddress >> 8) & 0b00000010 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_2 , (wideaddress >> 8) & 0b00000100 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_3 , (wideaddress >> 8) & 0b00001000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_4 , (wideaddress >> 8) & 0b00010000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_5 , (wideaddress >> 8) & 0b00100000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_6 , (wideaddress >> 8) & 0b01000000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_7 , (wideaddress >> 8) & 0b10000000 ? HIGH : LOW );
    
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_0 );
    digitalWrite( TANGLIB_SHIFTIN , HIGH );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_1 );
    digitalWrite( TANGLIB_SHIFTIN , LOW );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_2 );
    
    
    // shift in low byte of address
    digitalWrite( TANGLIB_DATAIN_0 , wideaddress & 0b00000001 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_1 , wideaddress & 0b00000010 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_2 , wideaddress & 0b00000100 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_3 , wideaddress & 0b00001000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_4 , wideaddress & 0b00010000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_5 , wideaddress & 0b00100000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_6 , wideaddress & 0b01000000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_7 , wideaddress & 0b10000000 ? HIGH : LOW );
    
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_0 );
    digitalWrite( TANGLIB_SHIFTIN , HIGH );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_1 );
    digitalWrite( TANGLIB_SHIFTIN , LOW );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_2 );
    

    // shift in data
    digitalWrite( TANGLIB_DATAIN_0 , databyte & 0b00000001 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_1 , databyte & 0b00000010 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_2 , databyte & 0b00000100 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_3 , databyte & 0b00001000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_4 , databyte & 0b00010000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_5 , databyte & 0b00100000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_6 , databyte & 0b01000000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_7 , databyte & 0b10000000 ? HIGH : LOW );
    
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_0 );
    digitalWrite( TANGLIB_SHIFTIN , HIGH );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_1 );
    digitalWrite( TANGLIB_SHIFTIN , LOW );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_2 );
    

    // set readwrite high
    digitalWrite( TANGLIB_READWRITE , HIGH );

    // pulse commit
    delayMicroseconds( TANGLIB_COMMIT_DELAY_0 );
    digitalWrite( TANGLIB_COMMIT , HIGH );
    delayMicroseconds( TANGLIB_COMMIT_DELAY_1 );
    digitalWrite( TANGLIB_COMMIT , LOW );
    delayMicroseconds( TANGLIB_COMMIT_DELAY_2 );

    

    // set readwrite line low
    digitalWrite( TANGLIB_READWRITE , LOW );


}



uint8_t tanglib_read( uint16_t wideaddress ) {


    // shift in high byte of address
    digitalWrite( TANGLIB_DATAIN_0 , (wideaddress >> 8) & 0b00000001 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_1 , (wideaddress >> 8) & 0b00000010 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_2 , (wideaddress >> 8) & 0b00000100 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_3 , (wideaddress >> 8) & 0b00001000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_4 , (wideaddress >> 8) & 0b00010000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_5 , (wideaddress >> 8) & 0b00100000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_6 , (wideaddress >> 8) & 0b01000000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_7 , (wideaddress >> 8) & 0b10000000 ? HIGH : LOW );
    
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_0 );
    digitalWrite( TANGLIB_SHIFTIN , HIGH );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_1 );
    digitalWrite( TANGLIB_SHIFTIN , LOW );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_2 );
    
    
    // shift in low byte of address
    digitalWrite( TANGLIB_DATAIN_0 , wideaddress & 0b00000001 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_1 , wideaddress & 0b00000010 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_2 , wideaddress & 0b00000100 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_3 , wideaddress & 0b00001000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_4 , wideaddress & 0b00010000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_5 , wideaddress & 0b00100000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_6 , wideaddress & 0b01000000 ? HIGH : LOW );
    digitalWrite( TANGLIB_DATAIN_7 , wideaddress & 0b10000000 ? HIGH : LOW );
    
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_0 );
    digitalWrite( TANGLIB_SHIFTIN , HIGH );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_1 );
    digitalWrite( TANGLIB_SHIFTIN , LOW );
    delayMicroseconds( TANGLIB_SHIFTIN_DELAY_2 );
    
    // set readwrite line low
    digitalWrite( TANGLIB_READWRITE , LOW );

    // pulse commit
    delayMicroseconds( TANGLIB_COMMIT_DELAY_0 );
    digitalWrite( TANGLIB_COMMIT , HIGH );
    delayMicroseconds( TANGLIB_COMMIT_DELAY_1 );
    digitalWrite( TANGLIB_COMMIT , LOW );
    delayMicroseconds( TANGLIB_COMMIT_DELAY_2 );


    // read data
    uint8_t returnval = 0;
    returnval |= digitalRead( TANGLIB_DATAOUT_0 );
    returnval |= digitalRead( TANGLIB_DATAOUT_1 ) << 1;
    returnval |= digitalRead( TANGLIB_DATAOUT_2 ) << 2;
    returnval |= digitalRead( TANGLIB_DATAOUT_3 ) << 3;
    returnval |= digitalRead( TANGLIB_DATAOUT_4 ) << 4;
    returnval |= digitalRead( TANGLIB_DATAOUT_5 ) << 5;
    returnval |= digitalRead( TANGLIB_DATAOUT_6 ) << 6;
    returnval |= digitalRead( TANGLIB_DATAOUT_7 ) << 7;
    

    return returnval;
}







void tanglib_execute_and_wait() {

    digitalWrite( TANGLIB_EXECUTE , HIGH );

    while ( !digitalRead( TANGLIB_ISFINISHED ) ){delay(1);};

    digitalWrite( TANGLIB_EXECUTE , LOW );


}




void tanglib_execute_and_wait() {

    digitalWrite( TANGLIB_EXECUTE , HIGH );

    digitalWrite( TANGLIB_EXECUTE , LOW );

}


























