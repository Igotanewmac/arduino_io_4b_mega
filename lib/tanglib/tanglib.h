

#ifndef TANGLIB_HEADER_FLAG
#define TANGLIB_HEADER_FLAG 1

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
#define TANGLIB_SHIFTIN_DELAY_1 8
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


// rsel constants!

#define TANG_RSEL_DATA_0 0x00
#define TANG_RSEL_DATA_1 0x01
#define TANG_RSEL_DATA_2 0x02
#define TANG_RSEL_DATA_3 0x03
#define TANG_RSEL_DATA_4 0x04
#define TANG_RSEL_DATA_5 0x05
#define TANG_RSEL_DATA_6 0x06
#define TANG_RSEL_DATA_7 0x07
#define TANG_RSEL_DATA_8 0x08
#define TANG_RSEL_DATA_9 0x09
#define TANG_RSEL_DATA_A 0x0A
#define TANG_RSEL_DATA_B 0x0B
#define TANG_RSEL_DATA_C 0x0C
#define TANG_RSEL_DATA_D 0x0D
#define TANG_RSEL_DATA_E 0x0E
#define TANG_RSEL_DATA_F 0x0F


#define TANG_RSEL_WIDEPTR_0 0x80
#define TANG_RSEL_WIDEPTR_1 0x81
#define TANG_RSEL_WIDEPTR_2 0x82
#define TANG_RSEL_WIDEPTR_3 0x83
#define TANG_RSEL_WIDEPTR_4 0x84
#define TANG_RSEL_WIDEPTR_5 0x85
#define TANG_RSEL_WIDEPTR_6 0x86
#define TANG_RSEL_WIDEPTR_7 0x87
#define TANG_RSEL_WIDEPTR_8 0x88
#define TANG_RSEL_WIDEPTR_9 0x89
#define TANG_RSEL_WIDEPTR_A 0x8A
#define TANG_RSEL_WIDEPTR_B 0x8B
#define TANG_RSEL_WIDEPTR_C 0x8C
#define TANG_RSEL_WIDEPTR_D 0x8D
#define TANG_RSEL_WIDEPTR_E 0x8E
#define TANG_RSEL_WIDEPTR_F 0x8F

#define TANG_RSEL_WIDEPTR_LOW_0 0X40
#define TANG_RSEL_WIDEPTR_LOW_1 0X41
#define TANG_RSEL_WIDEPTR_LOW_2 0X42
#define TANG_RSEL_WIDEPTR_LOW_3 0X43
#define TANG_RSEL_WIDEPTR_LOW_4 0X44
#define TANG_RSEL_WIDEPTR_LOW_5 0X45
#define TANG_RSEL_WIDEPTR_LOW_6 0X46
#define TANG_RSEL_WIDEPTR_LOW_7 0X47
#define TANG_RSEL_WIDEPTR_LOW_8 0X48
#define TANG_RSEL_WIDEPTR_LOW_9 0X49
#define TANG_RSEL_WIDEPTR_LOW_A 0X4A
#define TANG_RSEL_WIDEPTR_LOW_B 0X4B
#define TANG_RSEL_WIDEPTR_LOW_C 0X4C
#define TANG_RSEL_WIDEPTR_LOW_D 0X4D
#define TANG_RSEL_WIDEPTR_LOW_E 0X4E
#define TANG_RSEL_WIDEPTR_LOW_F 0X4F

#define TANG_RSEL_ADDRESS_0 0X20
#define TANG_RSEL_ADDRESS_1 0X21
#define TANG_RSEL_ADDRESS_2 0X22
#define TANG_RSEL_ADDRESS_3 0X23
#define TANG_RSEL_ADDRESS_4 0X24
#define TANG_RSEL_ADDRESS_5 0X25
#define TANG_RSEL_ADDRESS_6 0X26
#define TANG_RSEL_ADDRESS_7 0X27
#define TANG_RSEL_ADDRESS_8 0X28
#define TANG_RSEL_ADDRESS_9 0X29
#define TANG_RSEL_ADDRESS_A 0X2A
#define TANG_RSEL_ADDRESS_B 0X2B
#define TANG_RSEL_ADDRESS_C 0X2C
#define TANG_RSEL_ADDRESS_D 0X2D
#define TANG_RSEL_ADDRESS_E 0X2E
#define TANG_RSEL_ADDRESS_F 0X2F


#define TANG_RSEL_ADDRESS_LOW_0 0X10
#define TANG_RSEL_ADDRESS_LOW_1 0X11
#define TANG_RSEL_ADDRESS_LOW_2 0X12
#define TANG_RSEL_ADDRESS_LOW_3 0X13
#define TANG_RSEL_ADDRESS_LOW_4 0X14
#define TANG_RSEL_ADDRESS_LOW_5 0X15
#define TANG_RSEL_ADDRESS_LOW_6 0X16
#define TANG_RSEL_ADDRESS_LOW_7 0X17
#define TANG_RSEL_ADDRESS_LOW_8 0X18
#define TANG_RSEL_ADDRESS_LOW_9 0X19
#define TANG_RSEL_ADDRESS_LOW_A 0X1A
#define TANG_RSEL_ADDRESS_LOW_B 0X1B
#define TANG_RSEL_ADDRESS_LOW_C 0X1C
#define TANG_RSEL_ADDRESS_LOW_D 0X1D
#define TANG_RSEL_ADDRESS_LOW_E 0X1E
#define TANG_RSEL_ADDRESS_LOW_F 0X1F


#define TANGLIB_COMMANDSTREAM_MAX 4096






// function declarations

/// @brief sets up the pins for tanglib
void tanglib_setup();



/// @brief pulse the reset line for 1ms
void tanglib_reset();




void tanglib_write( uint16_t wideaddress , uint8_t databyte );



uint8_t tanglib_read( uint16_t wideaddress );



void tanglib_execute_and_wait();

void tanglib_execute();







// opcode commands

/// @brief send the command stream to the tang command memory bank
void tanglib_commandstream_send();



/// @brief reset the internal commandstring to the given byte
void tanglib_commandstream_reset( uint8_t databyte );


/// @brief returns the current commandstreamindex value
uint16_t tanglib_commandstream_getindex();






/// @brief A no operation
void command_0x00_noop();


/// @brief halt the processor and signal finished
void command_0x01_halt();



/// @brief write a value to the bank select register
/// @param databyte the value to write
void command_0x10_load_to_bank_select( uint8_t databyte );

/// @brief write bank select to src 0x0000
void command_0x11_write_bank_select_to_src();

/// @brief fills bankA with a given value
/// @param databyte the value to write to bankA
void command_0x14_fill_bank_A( uint8_t databyte );



/// @brief Copy the given value to the register select register
/// @param databytehigh The rsel value for bankA
/// @param databytelow  the rsel value for bankB
void command_0x20_load_to_register_select( uint8_t databytehigh , uint8_t databytelow );


/// @brief copy the register select register to src 0x0000
void command_0x21_write_register_select_to_src();

/// @brief write the byte bankA to the wideptr bankB
void command_0x23_write_rselA_to_rselB();

/// @brief write databyte into the register selected by rsel
/// @param rsel the register to write to
/// @param databyte the value to write
void command_0x24_load_value_to_register( uint8_t rsel , uint8_t databyte );

/// @brief load from memory into a register
/// @param rsela the wideptr to load from
/// @param rselb the data register to write to
void command_0x26_load_wideptr_to_rselA( uint8_t rsela , uint8_t rselb );


/// @brief increment a register
/// @param rsel the register to increment
void command_0x30_inc( uint8_t rsel );

/// @brief decrement a register
/// @param rsel the register to decrement
void command_0x34_dec( uint8_t rsel );


/// @brief add, A + B = C
/// @param rselA the rsel of the first argument
/// @param rselB the rsel of the second argument
/// @param rselC the rsel to store the result
void command_0x38_add( uint8_t rselA , uint8_t rselB , uint8_t rselC );


/// @brief sub, A - B = C
/// @param rselA the rsel of the first argument
/// @param rselB the rsel of the second argument
/// @param rselC the rsel to store the result
void command_0x40_sub( uint8_t rselA , uint8_t rselB , uint8_t rselC );


/// @brief and, A & B = C
/// @param rselA the rsel of the first argument
/// @param rselB the rsel of the second argument
/// @param rselC the rsel to store the result
void command_0x42_and( uint8_t rselA , uint8_t rselB , uint8_t rselC );


/// @brief or, A | B = C
/// @param rselA the rsel of the first argument
/// @param rselB the rsel of the second argument
/// @param rselC the rsel to store the result
void command_0x44_or( uint8_t rselA , uint8_t rselB , uint8_t rselC );


/// @brief not, A ~ B = C
/// @param rselA the rsel of the argument
/// @param rselB the rsel to store the result
void command_0x46_not( uint8_t rselA , uint8_t rselB );



/// @brief xor, A ^ B = C
/// @param rselA the rsel of the first argument
/// @param rselB the rsel of the second argument
/// @param rselC the rsel to store the result
void command_0x48_xor( uint8_t rselA , uint8_t rselB , uint8_t rselC );




/// @brief jump to the given address
/// @param address the address to jump to
void command_0x50_jmp_immed( uint16_t address );

/// @brief jump to the address in the given register
/// @param rsel the register containing the address to jump to
void command_0x50_jmp_rsel( uint8_t rsel );

/// @brief jump to the given address if the given register is zero
/// @param rsel the register to test
/// @param address the address to jump to
void command_0x50_jmpz_immed( uint8_t rsel , uint16_t address );

/// @brief jump to the address in the given rselB if the given rselA is zero
/// @param rselA the register to test
/// @param rselB the register containing the address to jump to
void command_0x50_jmpz_rsel( uint8_t rselA , uint8_t rselB );

/// @brief jump to the given address if the given rsel is not zero
/// @param rsel the register to test
/// @param address the address to jump to
void command_0x50_jmpnz_immed( uint8_t rsel , uint16_t address );

/// @brief jump to the address in the given rselB if the given rselA is not zero
/// @param rselA the register to test
/// @param rselB the register containing the address to jump to
void command_0x50_jmpnz_rsel( uint8_t rselA , uint8_t rselB );



/// @brief jump forward by the given offset
/// @param address the offset to add to the program counter
void command_0x52_jmp_rel_fwd_immed( uint16_t address );


/// @brief jump forward by the offset in the given register
/// @param rsel the register containing the offset to add to the program counter
void command_0x52_jmp_rel_fwd_rsel( uint8_t rsel );


/// @brief jump forward by the given offset, if the given register is zero
/// @param rsel the register to test
/// @param address the offset to add to the programcounter
void command_0x52_jmpz_rel_fwd_immed( uint8_t rsel , uint16_t address );


/// @brief jump forward by the value in the given registerB, if the given registerA is zero
/// @param rselA the register to test
/// @param rselB the register containing the offset to add to programcounter
void command_0x52_jmpz_rel_fwd_rsel( uint8_t rselA , uint8_t rselB );

/// @brief jump forward by the given offset, if the given register is not zero
/// @param rsel the register to test
/// @param address the offset to add to the program counter
void command_0x52_jmpnz_rel_fwd_immed( uint8_t rsel , uint16_t address );


/// @brief jump forward by the value in the give registerB, if the given registerA is not zero
/// @param rselA the register to test
/// @param rselB the register containing the offset to add to the programcounter
void command_0x52_jmpnz_rel_fwd_rsel( uint8_t rselA , uint8_t rselB );



/// @brief jump backward by the given offset
/// @param address the offset to add to the program counter
void command_0x54_jmp_bk_rel_immed( uint16_t address );

/// @brief jump backward by the offset in the given register
/// @param rsel the register containing the offset to add to the program counter
void command_0x54_jmp_bk_rel_rsel( uint8_t rsel );

/// @brief jump backward by the given offset, if the given register is zero
/// @param rsel the register to test
/// @param address the offset to add to the programcounter
void command_0x54_jmpz_bk_rel_immed( uint8_t rsel , uint16_t address );


/// @brief jump backward by the value in the given registerB, if the given registerA is zero
/// @param rselA the register to test
/// @param rselB the register containing the offset to add to programcounter
void command_0x54_jmpz_bk_rel_rsel( uint8_t rselA , uint8_t rselB );

/// @brief jump backward by the given offset, if the given register is not zero
/// @param rsel the register to test
/// @param address the offset to add to the program counter
void command_0x54_jmpnz_bk_rel_immed( uint8_t rsel , uint16_t address );

/// @brief jump backward by the value in the give registerB, if the given registerA is not zero
/// @param rselA the register to test
/// @param rselB the register containing the offset to add to the programcounter
void command_0x54_jmpnz_bk_rel_rsel( uint8_t rselA , uint8_t rselB );

























#endif
















