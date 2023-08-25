



// definitions!

#define TANGLIB_SHIFTIN 38
#define TANGLIB_READWRITE 40
#define TANGLIB_COMMIT 42
#define TANGLIB_RESET 44
#define TANGLIB_EXECUTE 46
#define TANGLIB_ISFINISHED 48
#define TANGLIB_ISERROR 50


#define TANGLIB_DATAIN_0 22
#define TANGLIB_DATAIN_1 24
#define TANGLIB_DATAIN_2 26
#define TANGLIB_DATAIN_3 28
#define TANGLIB_DATAIN_4 30
#define TANGLIB_DATAIN_5 32
#define TANGLIB_DATAIN_6 34
#define TANGLIB_DATAIN_7 36


#define TANGLIB_DATAOUT_0 23
#define TANGLIB_DATAOUT_1 25
#define TANGLIB_DATAOUT_2 27
#define TANGLIB_DATAOUT_3 29
#define TANGLIB_DATAOUT_4 31
#define TANGLIB_DATAOUT_5 33
#define TANGLIB_DATAOUT_6 35
#define TANGLIB_DATAOUT_7 37


#define TANGLIB_SHIFTIN_DELAY_0 1
#define TANGLIB_SHIFTIN_DELAY_1 7
#define TANGLIB_SHIFTIN_DELAY_2 1

#define TANGLIB_COMMIT_DELAY_0 1
#define TANGLIB_COMMIT_DELAY_1 1
#define TANGLIB_COMMIT_DELAY_2 1


#define TANG_SRC_START 0b0000000000000000
#define   TANG_SRC_END 0b0011111111111111
#define TANG_KEY_START 0b0100000000000000
#define   TANG_KEY_END 0b0111111111111111
#define TANG_CMD_START 0b1000000000000000
#define   TANG_CMD_END 0b1011111111111111
#define TANG_DST_START 0b1100000000000000
#define   TANG_DST_END 0b1111111111111111


#define TANG_BANKA_SRC 0b00000000
#define TANG_BANKA_KEY 0b01000000
#define TANG_BANKA_CMD 0b10000000
#define TANG_BANKA_DST 0b11000000
#define TANG_BANKB_SRC 0b00000000
#define TANG_BANKB_KEY 0b00010000
#define TANG_BANKB_CMD 0b00100000
#define TANG_BANKB_DST 0b00110000
#define TANG_BANKC_SRC 0b00000000
#define TANG_BANKC_KEY 0b00000100
#define TANG_BANKC_CMD 0b00001000
#define TANG_BANKC_DST 0b00001100
#define TANG_BANKD_SRC 0b00000000
#define TANG_BANKD_KEY 0b00000001
#define TANG_BANKD_CMD 0b00000010
#define TANG_BANKD_DST 0b00000011






// function declarations

/// @brief sets up the pins for tanglib
void tanglib_setup();



/// @brief pulse the reset line for 1ms
void tanglib_reset();




void tanglib_write( uint16_t wideaddress , uint8_t databyte );



uint8_t tanglib_read( uint16_t wideaddress );



void tanglib_execute_and_wait();

void tanglib_execute();
















































