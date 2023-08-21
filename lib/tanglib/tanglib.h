



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


#define TANGLIB_SHIFTIN_DELAY_0 100
#define TANGLIB_SHIFTIN_DELAY_1 100
#define TANGLIB_SHIFTIN_DELAY_2 100

#define TANGLIB_COMMIT_DELAY_0 100
#define TANGLIB_COMMIT_DELAY_1 100
#define TANGLIB_COMMIT_DELAY_2 100







// function declarations

/// @brief sets up the pins for tanglib
void tanglib_setup();



/// @brief pulse the reset line for 1ms
void tanglib_reset();




void tanglib_write( uint16_t wideaddress , uint8_t databyte );



uint8_t tanglib_read( uint16_t wideaddress );



void tanglib_execute_and_wait();

















































