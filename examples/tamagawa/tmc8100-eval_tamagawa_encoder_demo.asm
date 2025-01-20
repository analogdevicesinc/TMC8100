;*******************************************************************************
;* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
;* This software is proprietary to Analog Devices, Inc. and its licensors.
;*******************************************************************************
;   tamagawa t-format
;	author: GE, 2024-03-04
    
    SOFTWARE_VERSION_MAJOR = $01
    SOFTWARE_VERSION_MINOR = $00

    PROTOCOL_3 = $54 ; "T"
    PROTOCOL_2 = $41 ; "A"
    PROTOCOL_1 = $4D ; "M"
    PROTOCOL_0 = $54 ; "T"
    
    ; system register
    SYSTEM_CORE             = $0
    SYSTEM_TIMER            = $1
    SYSTEM_CRC              = $2
    
    ; system core
    SYSTEM_CORE_MODE_W              = $0
    SYSTEM_CORE_LOOP_COUNTER_R      = $0
    SYSTEM_CORE_MODE_R              = $1
    SYSTEM_CORE_COUNTER_LIMIT_W     = $1
    SYSTEM_CORE_INPUT_FILTER_W      = $2
    SYSTEM_CORE_TIMEOUT_L_W         = $3
    SYSTEM_CORE_TIMEOUT_H_W         = $4
    
    ; system timer unit
    SYSTEM_TIMER_COUNTER_R              = $0
    SYSTEM_TIMER_PRESCALER_LIMIT_W      = $0
    SYSTEM_TIMER_PULS_COUNTER_R         = $1
    SYSTEM_TIMER_COUNTER_LIMIT_W        = $1
    SYSTEM_TIMER_R                      = $2
    SYSTEM_TIMER_PULS_COUNTER_LIMIT_W   = $2
    SYSTEM_TIMER_TIMEOUT_R              = $3
    SYSTEM_TIMER_LIMIT_W                = $3
    SYSTEM_TIMEOUT_LIMIT_W              = $4
    SYSTEM_TIMER_CTRL_W                 = $5
    SYSTEM_TIMER_LIMIT_NO_RESET_W       = $7
    
    ; system crc unit
    SYSTEM_CRC_START_W                  = $0
    SYSTEM_CRC_POLYNOM_W                = $1
    SYSTEM_CRC_CTRL_W                   = $2
    SYSTEM_CRC_RESULT0_R                = $0
    SYSTEM_CRC_RESULT1_R                = $1
    SYSTEM_CRC_RESULT2_R                = $2
    SYSTEM_CRC_RESULT3_R                = $3
    
    ; clock control
    PLL_FB_CFG              = $00
    CLK_CTRL_SOURCE         = $04
    CLK_CTRL_PLL_CFG        = $08
    CLK_CTRL_OPT            = $0C
    CLK_CTRL_STATUS         = $30
    CLK_CTRL_LATCH_RE       = $34
    CLK_CTRL_LATCH_FE       = $38
    CLK_CTRL_INT_ENA_RE     = $40
    CLK_CTRL_INT_ENA_FE     = $44
    CLK_CTRL_FLT_ENA_RE     = $48
    CLK_CTRL_FLT_ENA_FE     = $4C
    CLK_CTRL_ERR_REPORT     = $50
    CLK_CTRL_STS_REPORT     = $54
    CLK_DET_CFG_0           = $70
    CLK_DET_CFG_1           = $74
    CLK_DET_CFG_2           = $78
    CLK_DET_CFG_3           = $7C
    TM_CLK_CTRL_0           = $80
    TM_CLK_CTRL_1           = $84
    TM_CLK_CTRL_2           = $88
    TM_CLK_CTRL_3           = $8C
    TM_CLK_CTRL_4           = $90
    
    PLL_FB_75               = $36
    PLL_FB_100              = $4f
    PLL_FB_128              = $6b

	; direct io configuration
	DIRECT_POLARITY         = $20	; 0010_0000
	DIRECT_ALT_FUNCTION     = $21
	DIRECT_PU               = $22
	DIRECT_PD               = $23
    
	; program memory access unit
	MEM_CTRL                = $18	; 0001_1000
	MEM_DATA_L              = $19
	MEM_DATA_H              = $1a
	MEM_ADDR_L              = $1b
	MEM_ADDR_H              = $1c

	; spi register address
    SPI_BUFFER_0            = $30   ; 0011_0000
    SPI_BUFFER_1            = $31
    SPI_BUFFER_2            = $32
    SPI_BUFFER_3            = $33
    SPI_CTRL                = $34
    SPI_STATUS              = $34
    
	; gpio
    GPIO_OUT                = $40   ; 0100_0000
    GPIO_IN                 = $40
    GPIO_POLARITY           = $41
    GPIO_OD_2               = $42
    GPIO0_ALT0_FUNCTION     = $43
    GPIO0_ALT1_FUNCTION     = $44
    GPIO_OUT_ENABLE         = $45
    GPIO_PU                 = $46
    GPIO_PD                 = $47
    SPI_PU_PD               = $48
    SPI_LINE_STATUS         = $48
    ; clk control
    CLK_ADDR                = $49
    CLK_DOUT                = $4a
    CLK_DIN                 = $4a
    ; otp access
    OTP_SEL_REG             = $4b
    OTP_REG                 = $4b

    ; <wait_flag>
    WAIT_IN0 = 0
    WAIT_IN1 = 1
    WAIT_IN2 = 2
    WAIT_IN3 = 3
    WAIT_OVERFLOW_COUNTER = 4
    WAIT_OVERFLOW_PULSE = 5
    WAIT_OVERFLOW_TIMER = 6
	NO_WAIT = 7
    
    ; <wait ctrl>
    WAIT_NO_ACTION = 0
    WAIT_START_TIMER = 1
    WAIT_STOP_TIMER = 2
    WAIT_IN0_INC_PULSE = 4
    WAIT_IN1_INC_PULSE = 5
    WAIT_IN2_INC_PULSE = 6
    WAIT_IN3_INC_PULSE = 7
    
    ; <out_flag>
    FLAG_OUT0 = 0
    FLAG_OUT1 = 1
    FLAG_OUT2 = 2
    FLAG_OUT3 = 3
    FLAG_OUT0_CRC = 4
    FLAG_OUT1_CRC = 5
    FLAG_OUT2_CRC = 6
    FLAG_OUT3_CRC = 7
    
    ; <in_flag>
    FLAG_IN0 = 0
    FLAG_IN1 = 1
    FLAG_IN2 = 2
    FLAG_IN3 = 3
    FLAG_IN0_CRC = 4
    FLAG_IN1_CRC = 5
    FLAG_IN2_CRC = 6
    FLAG_IN3_CRC = 7
    
    ; Data memory addresses / intermediate storage for ID3
    ADDR_ABS0 = $C0
    ADDR_ABS1 = $C1
    ADDR_ABS2 = $C2
    ADDR_ENID = $C3
    ADDR_ABM0 = $C4
    ADDR_ABM1 = $C5
    ADDR_ABM2 = $C6
    
    
	; ********************************************************************************
	; configure PLL for 100MHz and 16MHz XTAL
	; ********************************************************************************
    ;
    LDI $03, r0 ; enable input for GPIO0/GPIO1
    ST GPIO_IN, r0
    
    LDI $03, r0 ; disable pull-up for GPIO0/GPIO1
    ST GPIO_PU, r0
    
    LDI PLL_FB_CFG, r0 ; set pll feedback divider
    ST CLK_ADDR, r0
    LDI PLL_FB_100, r0
    ST CLK_DOUT, r0 ; will trigger write access to clk register
    
    LDI CLK_CTRL_SOURCE, r0
    ST CLK_ADDR, r0
    LDI $26, r0  ; use XTAL
    ;LDI $21, r0  ; use external clock
    ;LDI $00, r0 ;; use internal clock
    ST CLK_DOUT, r0 ; will trigger write access to clk register
    
    LDI CLK_CTRL_OPT, r0 ; enable clk fsm
    ST CLK_ADDR, r0
    LDI $40, r0
    ST CLK_DOUT, r0 ; will trigger write access to clk register
    
    LDI CLK_CTRL_PLL_CFG, r0
    ST CLK_ADDR, r0
    LDI %1011_1101, r0 ; RDIV = 15 (assuming 16MHz external / XTAL clock) and select PLL output, start FSM (commit = 1)
    ;LDI %1011_1001, r0 ; RDIV = 14 (assuming 15MHz internal clock) and select PLL output, start FSM (commit = 1)
    ST CLK_DOUT, r0 ; will trigger write access to clk register
    
    LDI CLK_CTRL_PLL_CFG, r0
    ST CLK_ADDR, r0
    NOP
    NOP
WAIT_FOR_PLL:
    LD CLK_DIN, r0
    NOP
    TEST1 $7, r0
    JC WAIT_FOR_PLL
    ; sys_clk should be PLL output now
    
	; ********************************************************************************
	; configure DIRECT_IO for RS485 transceiver connection
    ; DIRECT_OUT(1) -> TXD
    ; DIRECT_OUT(3) -> TXD_EN
    ; DIRECT_IN(1) <- RXD
	; ********************************************************************************

    ; set TXD / DIRECT_OUT(1) = 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    ; set TXD_EN / DIRECT_OUT(3) = 0
    SFCLR WAIT1SF NO_WAIT, 0, 3
    ; configure TXD_EN / DIRECT_OUT(3) as output
    LDI $00, r0
    ST  DIRECT_ALT_FUNCTION, r0
CMD_LOOP:
    ; wait for SPI command
    LDI SPI_STATUS, r0
    WAIT1 $0, r0
	LD SPI_BUFFER_3, r0
    ; ID0 - read encoder absolute data in one revolution
    LDI $80, r1
    COMP EQ r0, r1
    JC tamagawa_id0
    ; ID1 - read encoder multi-turn data
    LDI $81, r1
    COMP EQ r0, r1
    JC tamagawa_id1
    ; ID2 - read encoder id
    LDI $82, r1
    COMP EQ r0, r1
    JC tamagawa_id2
    ; ID3 - read encoder data complete
    LDI $83, r1
    COMP EQ r0, r1
    JC tamagawa_id3
    ; ID6 - write 8bit of user data
    LDI $86, r1
    COMP EQ r0, r1
    JC tamagawa_id6
    ; ID7 - reset error flags
    LDI $87, r1
    COMP EQ r0, r1
    JC tamagawa_id7
    ; ID8 - reset ABS
    LDI $88, r1
    COMP EQ r0, r1
    JC tamagawa_id8
    ; IDC - reset ABM
    LDI $8C, r1
    COMP EQ r0, r1
    JC tamagawa_idc
    ; IDD - read 8bit of user data
    LDI $8D, r1
    COMP EQ r0, r1
    JC tamagawa_idd
    ; get software version
    LDI $FF, r1
    COMP EQ r0, r1
    JC software_version
    ; get protocol type
    LDI $FE, r1
    COMP EQ r0, r1
    JC protocol
	JA CMD_LOOP
	
tamagawa_id0:
    ; id0: read encoder absolute data in one revolution
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id0 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; id0 + parity
    LDI %0000_0000, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID0 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
tamagawa_abs_reply:
    ; prepare for reply
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    
    
    ; ****************************************
    ; prepare for reply CF (control field)
    ; 0         - start bit
    ; 010       - sync code
    ; cc0..cc4  - ID code
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in sync code 010 and cc0..cc4
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r1 ; CF -> r1
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply SF (status field)
    ; 0         - start bit
    ; dd0..dd3  - Information code
    ; ea0..ea1  - encoder error
    ; ca0..ca1  - communication alarm
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in dd0..dd3, ea0..ea1, ca0..ca1
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r2 ; SF -> r2
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF0 (data field) - ABS0
    ; 0         - start bit
    ; ABS0..7   - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABS0 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF1 (data field) - ABS1
    ; 0         - start bit
    ; ABS8..15  - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r4 ; ABS1 -> r4
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF2 (data field) - ABS2
    ; 0         - start bit
    ; ABS16..23 - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r5 ; ABS2 -> r5
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply CRC (CRC field)
    ; 0         - start bit
    ; rc0..rc7  - CRC field
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in rc0..rc7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1, r6 ; CRC -> r6
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; copy reply to SPI transmit buffer
    LDI %0001_0000, r0 ; its the ABS value
    ST SPI_BUFFER_3, r0 ; 1 -> ABS
    ST SPI_BUFFER_2, r3 ; ABS0
    ST SPI_BUFFER_1, r4 ; ABS1
    ST SPI_BUFFER_0, r5 ; ABS2
    ; copy crc value to SPI transmit buffer
    LDI %0111_0000, r0 ; crc values
    ST SPI_BUFFER_3, r0 ; 7 -> CRC + STATUS Field
    ST SPI_BUFFER_2, r2 ; 
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r6 ; CRC received
    REV r0, r0
    ST SPI_BUFFER_0, r0 ; CRC calculated
    JA CMD_LOOP

tamagawa_id1:
    ; id1: read encoder multi-turn data
    ; 0     - start bit
    ; 010   - sync code
    ; 10001 - cc0 .. cc4 - id1 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; id1 + parity
    LDI %0001_0001, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID1 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command, switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
    ; prepare for reply
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    
    ; ****************************************
    ; prepare for reply CF (control field)
    ; 0         - start bit
    ; 010       - sync code
    ; cc0..cc4  - ID code
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in sync code 010 and cc0..cc4
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r1 ; CF -> r1
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply SF (status field)
    ; 0         - start bit
    ; dd0..dd3  - Information code
    ; ea0..ea1  - encoder error
    ; ca0..ca1  - communication alarm
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in dd0..dd3, ea0..ea1, ca0..ca1
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r2 ; r2 contains SF
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF0 (data field) - ABM0
    ; 0         - start bit
    ; ABM0..7   - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABM0 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF1 (data field) - ABM1
    ; 0         - start bit
    ; ABM8:15   - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r4 ; ABM1 -> r4
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF2 (data field) - ABM2
    ; 0         - start bit
    ; ABM16:23  - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r5 ; ABM2 -> r5
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply CRC (CRC field)
    ; 0         - start bit
    ; rc0..rc7  - CRC field
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in rc0..rc7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1, r6 ; CRC -> r6
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; copy reply to SPI transmit buffer
    LDI %0010_0000, r0 ; its the ABM value
    ST SPI_BUFFER_3, r0 ; 2 -> ABS
    ST SPI_BUFFER_2, r3 ; ABM0
    ST SPI_BUFFER_1, r4 ; ABM1
    ST SPI_BUFFER_0, r5 ; ABM2
    ; copy crc value to SPI transmit buffer
    LDI %0111_0000, r0 ; crc values
    ST SPI_BUFFER_3, r0 ; 7 -> CRC + STATUS Field
    ST SPI_BUFFER_2, r2 ; SF
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r6 ; CRC received
    REV r0, r0
    ST SPI_BUFFER_0, r0 ; CRC calculated
    JA CMD_LOOP
    
tamagawa_id2:
    ; id2: read encoder id
    ; 0     - start bit
    ; 010   - sync code
    ; 01001 - cc0 .. cc4 - id2 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; id2 + parity
    LDI %0001_0010, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID2 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    ; end of command
    
    ; prepare for reply
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB

    ; ****************************************
    ; prepare for reply CF (control field)
    ; 0         - start bit
    ; 010       - sync code
    ; cc0..cc4  - ID code
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in sync code 010 and cc0..cc4
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r1 ; CF -> r1
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply SF (status field)
    ; 0         - start bit
    ; dd0..dd3  - Information code
    ; ea0..ea1  - encoder error
    ; ca0..ca1  - communication alarm
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in dd0..dd3, ea0..ea1, ca0..ca1
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r2 ; r2 contains SF
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF (data field)
    ; 0         - start bit
    ; ENID      - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; r3 contains ENID
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply CRC (CRC field)
    ; 0         - start bit
    ; rc0..rc7  - CRC field
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in rc0..rc7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1, r4 ; r4 contains CRC
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; copy reply to SPI transmit buffer
    LDI %0100_0000, r0 ; its the encoder ID (ENID)
    ST SPI_BUFFER_3, r0 ; 4 -> ENID
    LDI $00, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r0
    ST SPI_BUFFER_0, r3 ; ENID
    ; copy crc value to SPI transmit buffer
    LDI %0111_0000, r0 ; crc values
    ST SPI_BUFFER_3, r0 ; 7 -> CRC + STATUS Field
    ST SPI_BUFFER_2, r2 ; SF
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r4 ; CRC received
    REV r0, r0
    ST SPI_BUFFER_0, r0 ; CRC calculated
    JA CMD_LOOP
	
tamagawa_id3:
    ; id3: read encoder absolute data in one revolution
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id0 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; id3 + parity
    LDI %0000_0011, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID3 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
    ; prepare for reply
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    
    ; ****************************************
    ; prepare for reply CF (control field)
    ; 0         - start bit
    ; 010       - sync code
    ; cc0..cc4  - ID code
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in sync code 010 and cc0..cc4
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r1 ; CF -> r1
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply SF (status field)
    ; 0         - start bit
    ; dd0..dd3  - Information code
    ; ea0..ea1  - encoder error
    ; ca0..ca1  - communication alarm
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in dd0..dd3, ea0..ea1, ca0..ca1
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r6 ; SF -> r6
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply DF0 (data field) - ABS0
    ; 0         - start bit
    ; ABS0..7   - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABS0 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ABS0, r3

    ; ****************************************
    ; prepare for reply DF1 (data field) - ABS1
    ; 0         - start bit
    ; ABS8..15  - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABS1 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ABS1, r3

    ; ****************************************
    ; prepare for reply DF2 (data field) - ABS2
    ; 0         - start bit
    ; ABS16..23 - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABS2 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ABS2, r3

    ; ****************************************
    ; prepare for reply DF3 (data field) - ENID
    ; 0         - start bit
    ; ENID      - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; r3 contains ENID
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ENID, r3

    ; ****************************************
    ; prepare for reply DF4 (data field) - ABM0
    ; 0         - start bit
    ; ABM0..7   - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABM0 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ABM0, r3

    ; ****************************************
    ; prepare for reply DF5 (data field) - ABM1
    ; 0         - start bit
    ; ABM8:15   - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABM1 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ABM1, r3

    ; ****************************************
    ; prepare for reply DF6 (data field) - ABM2
    ; 0         - start bit
    ; ABM16:23  - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; ABM2 -> r3
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
    ST ADDR_ABM2, r3

    ; ****************************************
    ; prepare for reply DF7 (data field) - ALMC
    ; 0         - start bit
    ; ALMC      - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r4 ; ALMC -> r4
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply CRC (CRC field)
    ; 0         - start bit
    ; rc0..rc7  - CRC field
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in rc0..rc7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1, r5 ; r5 contains CRC
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; copy reply to SPI transmit buffer
    ; ABS value
    LDI %0001_0000, r0 ; its the ABS value
    ST SPI_BUFFER_3, r0 ; $10 -> ABS
    LD ADDR_ABS0, r0
    LD ADDR_ABS1, r1
    LD ADDR_ABS2, r2
    ST SPI_BUFFER_2, r0 ; ABS0
    ST SPI_BUFFER_1, r1 ; ABS1
    ST SPI_BUFFER_0, r2 ; ABS2
    ; ENID value
    LDI %0100_0000, r0 ; its the encoder ID (ENID)
    ST SPI_BUFFER_3, r0 ; $40 -> ENID
    LD ADDR_ENID, r1
    LDI $00, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r0
    ST SPI_BUFFER_0, r1 ; ENID
    ; ABM value
    LDI %0010_0000, r0 ; its the ABM value
    ST SPI_BUFFER_3, r0 ; $20 -> ABM
    LD ADDR_ABM0, r0
    LD ADDR_ABM1, r1
    LD ADDR_ABM2, r2
    ST SPI_BUFFER_2, r0 ; ABM0
    ST SPI_BUFFER_1, r1 ; ABM1
    ST SPI_BUFFER_0, r2 ; ABM2
    ; ENID value
    LDI %0101_0000, r0 ; its the encoder ID (ALMC)
    ST SPI_BUFFER_3, r0 ; $50 -> ALMC
    LDI $00, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r0
    ST SPI_BUFFER_0, r4 ; ALMC
    ; CRC values
    LDI %0111_0000, r0 ; crc values
    ST SPI_BUFFER_3, r0 ; $70 -> CRC + STATUS Field
    ST SPI_BUFFER_2, r6 ; ; SF
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r5 ; CRC received
    REV r0, r0
    ST SPI_BUFFER_0, r0 ; CRC calculated
    JA CMD_LOOP
    
tamagawa_id7:
    ; id7: reset error flags
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id0 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; id7 + parity
    LDI %0001_0111, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID7 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
    JA tamagawa_abs_reply
    
    
tamagawa_id8:
    ; id8: reset encoder absolute position counter
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id0 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; id8 + parity
    LDI %0001_1000, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID7 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
    JA tamagawa_abs_reply
    
tamagawa_idc:
    ; idc: reset encoder multi-turn counter
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id0 + parity
    ; 1     - stop bit
    ;
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; DIRECT_OUT(1) = 1 -> start bit
    ; start bit + sync code
    LDI %0000_0100, r0
    ; idc + parity
    LDI %0000_1100, r1
    REP 4, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out start bit + sync code
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_OUT1 ; shift out ID7 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
    JA tamagawa_abs_reply

tamagawa_id6:
    ; id6: write 8bit data to 7bit address
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id + parity
    ; 1     - stop bit
    ;
    ; load address
    LD SPI_BUFFER_0, r2
    ; load write data
    LD SPI_BUFFER_1, r3
    ; set MSB of address to zero (Busy bit)
    LDI $7f, r0
    AND r2, r0, r2
    
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; transmit command
    ; CF - control field
    ; ADF - address field
    ; EDF EEPROM field / 8bit data
    ; CRC - CRC field
    
    ; CF control field
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    ; sync code
    LDI %0000_0010, r0
    REP 3, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1_CRC ; shift out sync code
    ; id6 + parity
    LDI %0000_0110, r0
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1_CRC ; shift out ID6 + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop bit
    SFSET WAIT1SF NO_WAIT, 0, 1
    ;WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION ; wait time for stop bit

    ; ADF address field
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    REP 8, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r2, FLAG_OUT1_CRC ; shift out address (7bit) and busy flag ('0')
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop bit
    SFSET WAIT1SF NO_WAIT, 0, 1
    ;WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION ; wait time for stop bit
    
    ; EDF - data field
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    REP 8, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r3, FLAG_OUT1_CRC ; shift out data (8bit)
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop bit
    SFSET WAIT1SF NO_WAIT, 0, 1
    ; WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION ; wait time for stop bit
    
    ; CRC field
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    REV r0, r0
    REP 8, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out data (8bit)
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3

tamagawa_read_write_reply:
    ; prepare for reply
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB

    ; ****************************************
    ; prepare for reply CF (control field)
    ; 0         - start bit
    ; 010       - sync code
    ; cc0..cc4  - ID code
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in sync code 010 and cc0..cc4
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r1 ; CF -> r1
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply ADF (address field)
    ; 0           - start bit
    ; add0..add6  - address (LSB first)
    ; busy        - busy bit
    ; 1           - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in add0..add6, busy
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r2 ; r2 contains ADF
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply EDF (EEPROM field)
    ; 0         - start bit
    ; d0..d7    - data
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in d0..d7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3 ; r3 contains EDF
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; prepare for reply CRC (CRC field)
    ; 0         - start bit
    ; rc0..rc7  - CRC field
    ; 1         - stop bit
    ; reset timer and set timer limit to middle of bit
	LDI 18, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    ; wait for falling edge (start bit)
    WAIT0SF WAIT_IN1, WAIT_START_TIMER
    ; wait for middle of start bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	; set limit to 100MHz / 39 = 2.5MHz and no timer reset
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
    REP 8, 1
    ; wait for timer overflow and shift in rc0..rc7
    SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1, r4 ; r4 contains CRC
    ; wait for timer overflow, stop bit
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER

    ; ****************************************
    ; copy reply to SPI transmit buffer
    LDI %0101_0000, r0 ; 5 -> its data EDF and address ADF
    ST SPI_BUFFER_3, r0
    LDI $00, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r3 ; EDF - data
    ST SPI_BUFFER_0, r2 ; ADF - address
    ; copy crc value to SPI transmit buffer
    LDI %0111_0000, r0 ; crc values
    ST SPI_BUFFER_3, r0 ; 7 -> CRC + STATUS Field
    LDI $00, r0
    ST SPI_BUFFER_2, r0 ; SF = 0
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r4 ; CRC received
    REV r0, r0
    ST SPI_BUFFER_0, r0 ; CRC calculated
    JA CMD_LOOP


tamagawa_idd:
    ; idd: read 8bit data from 7bit address
    ; 0     - start bit
    ; 010   - sync code
    ; 00000 - cc0 .. cc4 - id + parity
    ; 1     - stop bit
    ;
    ; load address
    LD SPI_BUFFER_0, r2
    ; set MSB of address to zero (Busy bit)
    LDI $7f, r0
    AND r2, r0, r2
    
    ; initialize CRC for 8bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0001, r0 ; CRC polynomial: x^8 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    
	; set timer to 100MHz / 40 = 2.5MHz
	LDI 39, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
    LDI 2, r0 ; enable timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	; switch on driver + wait for 1.2us (min 1us min according to spec)
    SFSET WAIT1SF NO_WAIT, 0, 3
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    
    ; transmit command
    ; CF - control field
    ; ADF - address field
    ; EDF EEPROM field / 8bit data
    ; CRC - CRC field
    
    ; CF control field
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    ; sync code
    LDI %0000_0010, r0
    REP 3, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1_CRC ; shift out sync code
    ; idd + parity
    LDI %0001_1101, r0
    REP 5, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1_CRC ; shift out IDD + parity
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop bit
    SFSET WAIT1SF NO_WAIT, 0, 1
    ;WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION ; wait time for stop bit

    ; ADF address field
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    REP 8, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r2, FLAG_OUT1_CRC ; shift out address (7bit) and busy flag ('0')
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop bit
    SFSET WAIT1SF NO_WAIT, 0, 1
    ;WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION ; wait time for stop bit
    
    ; CRC field
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ; start bit
    SFCLR WAIT1SF WAIT_OVERFLOW_TIMER, 0, 1
    REV r0, r0
    REP 8, 1
    SHRO WAIT1SF WAIT_OVERFLOW_TIMER, r0, FLAG_OUT1 ; shift out data (8bit)
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION     ; wait time for last bit before stop bit
	; stop + 4 bits - all 1
    SFSET WAIT1SF NO_WAIT, 0, 1
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
    WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_STOP_TIMER
	; end of command - switch off driver
    SFCLR WAIT1SF NO_WAIT, 0, 3
    
    ; same reply as for writing data
    JA tamagawa_read_write_reply
    
software_version:
    ; copy reply to SPI transmit buffer
    LDI $FF, r0 ; $FF -> its the software version
    ST SPI_BUFFER_3, r0
    LDI $00, r0
    ST SPI_BUFFER_2, r0
    LDI SOFTWARE_VERSION_MAJOR, r0
    ST SPI_BUFFER_1, r0
    LDI SOFTWARE_VERSION_MINOR, r0
    ST SPI_BUFFER_0, r0 ; software version
    JA CMD_LOOP

protocol:
    ; copy reply to SPI transmit buffer
    LDI PROTOCOL_3, r0 ; protocol MSB
    ST SPI_BUFFER_3, r0
    LDI PROTOCOL_2, r0
    ST SPI_BUFFER_2, r0
    LDI PROTOCOL_1, r0
    ST SPI_BUFFER_1, r0
    LDI PROTOCOL_0, r0 ; protocol LSB
    ST SPI_BUFFER_0, r0
    JA CMD_LOOP
