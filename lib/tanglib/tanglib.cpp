
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




void tanglib_execute() {

    digitalWrite( TANGLIB_EXECUTE , HIGH );
    delay(1);

    digitalWrite( TANGLIB_EXECUTE , LOW );

}






// a 16 k buffer
uint8_t commandstream[TANGLIB_COMMANDSTREAM_MAX];

// the current position in the buffer
uint16_t commandstreamindex = 0;




void tanglib_commandstream_send() {

    for ( uint32_t i = 0 ; i < commandstreamindex ; i++ ) {
        tanglib_write( ( (uint16_t)i | TANG_CMD_START ) , commandstream[i] );
    }

}




// opcode commands

void tanglib_commandstream_reset( uint8_t databyte ) {
    for ( uint32_t i = 0 ; i < TANGLIB_COMMANDSTREAM_MAX ; i++ ) {
        commandstream[i] = databyte;
    }
    commandstreamindex = 0;
}




uint16_t tanglib_commandstream_getindex() {
    return commandstreamindex;
}









void command_0x00_noop() {
  commandstream[commandstreamindex++] = 0x00;
}


void command_0x01_halt() {
  commandstream[commandstreamindex++] = 0x01;
}



void command_0x10_load_to_bank_select( uint8_t databyte ) {
  commandstream[commandstreamindex++] = 0x10;
  commandstream[commandstreamindex++] = databyte;
}

void command_0x11_write_bank_select_to_src() {
  commandstream[commandstreamindex++] = 0x11;
}

void command_0x14_fill_bank_A( uint8_t databyte ) {
  commandstream[commandstreamindex++] = 0x14;
  commandstream[commandstreamindex++] = databyte;
}



void command_0x20_load_to_register_select( uint8_t databytehigh , uint8_t databytelow ) {
  commandstream[commandstreamindex++] = 0x20;
  commandstream[commandstreamindex++] = databytehigh;
  commandstream[commandstreamindex++] = databytelow;
}



void command_0x21_write_register_select_to_src() {
  commandstream[commandstreamindex++] = 0x21;
}


void command_0x23_write_rselA_to_rselB() {
  commandstream[commandstreamindex++] = 0x23;
}

void command_0x24_load_value_to_register( uint8_t rsel , uint8_t databyte ) {
  commandstream[commandstreamindex++] = 0x24;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = databyte;
}

void command_0x26_load_wideptr_to_rselA( uint8_t rsela , uint8_t rselb ) {
  commandstream[commandstreamindex++] = 0x26;
  commandstream[commandstreamindex++] = rsela;
  commandstream[commandstreamindex++] = rselb;
}


void command_0x30_inc( uint8_t rsel ) {
  commandstream[commandstreamindex++] = 0x30;
  commandstream[commandstreamindex++] = rsel;
}

void command_0x34_dec( uint8_t rsel ) {
  commandstream[commandstreamindex++] = 0x34;
  commandstream[commandstreamindex++] = rsel;
}


void command_0x38_add( uint8_t rselA , uint8_t rselB , uint8_t rselC ) {
  commandstream[commandstreamindex++] = 0x38;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
  commandstream[commandstreamindex++] = rselC;
}


void command_0x40_sub( uint8_t rselA , uint8_t rselB , uint8_t rselC ) {
  commandstream[commandstreamindex++] = 0x40;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
  commandstream[commandstreamindex++] = rselC;
}


void command_0x42_and( uint8_t rselA , uint8_t rselB , uint8_t rselC ) {
  commandstream[commandstreamindex++] = 0x42;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
  commandstream[commandstreamindex++] = rselC;  
}


void command_0x44_or( uint8_t rselA , uint8_t rselB , uint8_t rselC ) {
  commandstream[commandstreamindex++] = 0x44;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
  commandstream[commandstreamindex++] = rselC;
}


void command_0x46_not( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x46;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}




void command_0x48_xor( uint8_t rselA , uint8_t rselB , uint8_t rselC ) {
  commandstream[commandstreamindex++] = 0x48;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
  commandstream[commandstreamindex++] = rselC;
}






void command_0x50_jmp_immed( uint16_t address ) {
  commandstream[commandstreamindex++] = 0x50;
  commandstream[commandstreamindex++] = 0x02;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x50_jmp_rsel( uint8_t rsel ) {
  commandstream[commandstreamindex++] = 0x50;
  commandstream[commandstreamindex++] = 0x03;
  commandstream[commandstreamindex++] = rsel;
}


void command_0x50_jmpz_immed( uint8_t rsel , uint16_t address ) {
  commandstream[commandstreamindex++] = 0x50;
  commandstream[commandstreamindex++] = 0x08;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x50_jmpz_rsel( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x50;
  commandstream[commandstreamindex++] = 0x0C;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}

void command_0x50_jmpnz_immed( uint8_t rsel , uint16_t address ) {
  commandstream[commandstreamindex++] = 0x50;
  commandstream[commandstreamindex++] = 0x20;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x50_jmpnz_rsel( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x50;
  commandstream[commandstreamindex++] = 0x30;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}








void command_0x52_jmp_rel_fwd_immed( uint16_t address ) {
  commandstream[commandstreamindex++] = 0x52;
  commandstream[commandstreamindex++] = 0x02;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x52_jmp_rel_fwd_rsel( uint8_t rsel ) {
  commandstream[commandstreamindex++] = 0x52;
  commandstream[commandstreamindex++] = 0x03;
  commandstream[commandstreamindex++] = rsel;
}


void command_0x52_jmpz_rel_fwd_immed( uint8_t rsel , uint16_t address ) {
  commandstream[commandstreamindex++] = 0x52;
  commandstream[commandstreamindex++] = 0x08;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x52_jmpz_rel_fwd_rsel( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x52;
  commandstream[commandstreamindex++] = 0x0C;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}

void command_0x52_jmpnz_rel_fwd_immed( uint8_t rsel , uint16_t address ) {
  commandstream[commandstreamindex++] = 0x52;
  commandstream[commandstreamindex++] = 0x20;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x52_jmpnz_rel_fwd_rsel( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x52;
  commandstream[commandstreamindex++] = 0x30;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}





void command_0x54_jmp_bk_rel_immed( uint16_t address ) {
  commandstream[commandstreamindex++] = 0x54;
  commandstream[commandstreamindex++] = 0x02;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x54_jmp_bk_rel_rsel( uint8_t rsel ) {
  commandstream[commandstreamindex++] = 0x54;
  commandstream[commandstreamindex++] = 0x03;
  commandstream[commandstreamindex++] = rsel;
}


void command_0x54_jmpz_bk_rel_immed( uint8_t rsel , uint16_t address ) {
  commandstream[commandstreamindex++] = 0x54;
  commandstream[commandstreamindex++] = 0x08;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x54_jmpz_bk_rel_rsel( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x54;
  commandstream[commandstreamindex++] = 0x0C;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}

void command_0x54_jmpnz_bk_rel_immed( uint8_t rsel , uint16_t address ) {
  commandstream[commandstreamindex++] = 0x54;
  commandstream[commandstreamindex++] = 0x20;
  commandstream[commandstreamindex++] = rsel;
  commandstream[commandstreamindex++] = ( address >> 8 ) & 0xFF;
  commandstream[commandstreamindex++] = address & 0xFF;
}


void command_0x54_jmpnz_bk_rel_rsel( uint8_t rselA , uint8_t rselB ) {
  commandstream[commandstreamindex++] = 0x54;
  commandstream[commandstreamindex++] = 0x30;
  commandstream[commandstreamindex++] = rselA;
  commandstream[commandstreamindex++] = rselB;
}
















