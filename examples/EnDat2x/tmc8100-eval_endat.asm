;*******************************************************************************
;* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved. This software is
;* proprietary & confidential to Analog Devices, Inc. and its licensors.
;*******************************************************************************
;   EnDAT 2.x
;	author: GE, 2026-01-12
;
    
    SOFTWARE_VERSION_MAJOR = $01
    SOFTWARE_VERSION_MINOR = $00

	ENDAT_CLOCK_TOGGLE_DIV = 63 ; 128MHz / 64 = 2MHz toggle rate / 1MHz EnDAT clock
	ENDAT_BIT_LENGTH_DIV = 2 * (ENDAT_CLOCK_TOGGLE_DIV + 1) - 1

    PROTOCOL_3 = $45 ; "E"
    PROTOCOL_2 = $4E ; "N"
    PROTOCOL_1 = $44 ; "D"
    PROTOCOL_0 = $41 ; "A"
    
    ; system register
    SYSTEM_CORE             = $0
    SYSTEM_TIMER            = $1
    SYSTEM_CRC              = $2
    
    ; system core
    SYSTEM_CORE_MEMORY_SELECT_R         = $0

    SYSTEM_CORE_MEMORY_SELECT_W         = $0
    SYSTEM_CORE_INPUT_FILTER_W          = $1
    SYSTEM_CORE_TIMEOUT_ADDR_L_W        = $2
    SYSTEM_CORE_TIMEOUT_ADDR_H_W        = $3
    
    ; system timer unit
    SYSTEM_TIMER_COUNTER_R              = $0
    SYSTEM_TIMER_PULS_COUNTER_R         = $1
    SYSTEM_TIMER_R                      = $2
    SYSTEM_TIMER_TIMEOUT_R              = $3

    SYSTEM_TIMER_PRESCALER_LIMIT_W      = $0
    SYSTEM_TIMER_COUNTER_LIMIT_W        = $1
    SYSTEM_TIMER_PULS_COUNTER_LIMIT_W   = $2
    SYSTEM_TIMER_LIMIT_W                = $3
    SYSTEM_TIMEOUT_LIMIT_W              = $4
    SYSTEM_TIMER_CTRL_W                 = $5
    SYSTEM_TIMER_LIMIT_NO_RESET_W       = $7
    
    ; system crc unit
    SYSTEM_CRC_RESULT0_R                = $0
    SYSTEM_CRC_RESULT1_R                = $1
    SYSTEM_CRC_RESULT2_R                = $2
    SYSTEM_CRC_RESULT3_R                = $3

    SYSTEM_CRC_START_W                  = $0
    SYSTEM_CRC_POLYNOM_W                = $1
    SYSTEM_CRC_CTRL_W                   = $2
    
	
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

	; direct io
    ;DIO_POLARITY    = $40   ; 0100_0000
    ;DOUT_ALTF       = $41   ; 0100_0001

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
	
	; data memory
	DATA_MEM_ADDR			= $c0   ; 1100_0000

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

	; ********************************************************************************
	; configure GPIO(6) as output and spi_data_available
	; ********************************************************************************
    ;
    LD GPIO0_ALT1_FUNCTION, r0
    LD GPIO_OUT_ENABLE, r1
    SET $4, r0, r0  ; GPIO_ALT1_FUNCTION(5 downto 4) = "01" -> connect spi_data_available to GPIO(6)
    CLR $5, r0, r0
    ST GPIO0_ALT1_FUNCTION, r0
    SET $6, r1, r1  ; GPIO(6) / SPI_DATA_AVAILABLE -> output
    ST GPIO_OUT_ENABLE, r1
    
	; ********************************************************************************
	; configure PLL for 128MHz and 16MHz crystal clock
	; ********************************************************************************
    ;
    LDI $03, r0 ; enable input for GPIO0/GPIO1
    ST GPIO_IN, r0
    
    LDI $03, r0 ; disable pull-up for GPIO0/GPIO1
    ST GPIO_PU, r0
    
    LDI PLL_FB_CFG, r0 ; set pll feedback divider
    ST CLK_ADDR, r0
    LDI PLL_FB_128, r0
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
	; configure DIRECT_IO for the TMC8100-EVAL
	; RS485 CLOCK (idle "high" -> inverted)
    ; DIRECT_OUT(0) -> CLOCK out - generate clock signal
	; DIRECT_IN(0) <- CLOCK in / read-back
	; RS485 DATA (idle "low")
    ; DIRECT_IN(1) <- DATA in
    ; DIRECT_OUT(1) -> DATA out
    ; DIRECT_OUT(3) -> '0' (for DATA in) and '1' (for DATA out)
	; ********************************************************************************

    ; configure DIRECT_OUT(0) as inverted
    LDI $10, r0
    ST  DIRECT_POLARITY, r0
    ; set DIRECT_OUT(1) = 0, idle (non-inverted)
    SFCLR WAIT1SF NO_WAIT, 0, 1
    ; set DIRECT_OUT(3) = 0, DATA in 
    SFCLR WAIT1SF NO_WAIT, 0, 3
    ; configure DIRECT_OUT(3) as output
    LDI $00, r0
    ST  DIRECT_ALT_FUNCTION, r0

CMD_LOOP:
    ; wait for SPI command
    LDI SPI_STATUS, r0
    WAIT1 $0, r0
	LD SPI_BUFFER_3, r0
    ; Read encoder data
    LDI $80, r1
    COMP EQ r0, r1
    JC EnDAT_encoder
    ; get software version
    LDI $FF, r1
    COMP EQ r0, r1
    JC software_version
    ; get protocol type
    LDI $FE, r1
    COMP EQ r0, r1
    JC protocol
	JA CMD_LOOP	
	
EnDAT_encoder:
	; read encoder value
    ; initialize CRC for 5bit CRC
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI $ff, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W ; LSB
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W ; MSB
	LDI %0010_1011, r0 ; CRC polynomial: x^5 + x^3 + x^1 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    ; configure DIRECT_OUT(0) as clock output
    LDI $01, r0
    ST  DIRECT_ALT_FUNCTION, r0
    ; set DATA = '0' - DIRECT_OUT(1) = '0', idle (non-inverted)
    SFCLR WAIT1SF NO_WAIT, 0, 1
	; configure DATA as output - DIRECT_OUT(3) = '1'
    SFSET WAIT1SF NO_WAIT, 0, 3
    ; init counter 
	LDI ENDAT_CLOCK_TOGGLE_DIV, r0 ; set toggle rate for EnDAT clock generator
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_COUNTER_LIMIT_W
    LDI 1, r0 ; enable counter
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
    ; 2T clock cycles
	WAIT0SF WAIT_IN0, WAIT_NO_ACTION ; wait for falling edge of clock signal
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for rising edge of clock signal
	WAIT0SF WAIT_IN0, WAIT_NO_ACTION ; wait for falling edge of clock signal
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for rising edge of clock signal
	; shift out MODE command
	LDI %0011_1000, r0
	REP 7, 2
	SHRO WAIT1SF WAIT_OVERFLOW_COUNTER, r0, FLAG_OUT1
	WAIT1SF WAIT_OVERFLOW_COUNTER, WAIT_NO_ACTION
	; 2T clock cycles
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for rising edge of clock signal
	WAIT0SF WAIT_IN0, WAIT_NO_ACTION ; wait for falling edge of clock signal
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for rising edge of clock signal
	WAIT0SF WAIT_IN0, WAIT_NO_ACTION ; wait for falling edge of clock signal
	; configure DATA as input - DIRECT_OUT(3) = '0' 
    SFCLR WAIT1SF NO_WAIT, 0, 3
	; prepare for encoder reply / data
	LDI ENDAT_CLOCK_TOGGLE_DIV - 1, r0 ; from rising edge of start bit to middle of start bit / half a clock cycle
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
	WAIT1SF WAIT_IN1, WAIT_START_TIMER ; wait for rising edge of start DATA bit '1' and start timer
	; wait until middle of start bit
	WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	LDI ENDAT_BIT_LENGTH_DIV, r0 ; set sample point to middle of next bit / 1 clock cycle
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
	; middle of F1 error bit - shift in F1 error bit
	LDI 0, r1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_IN1_CRC
	; encoder single turn data 23bits, LSB first
	LDI 0, r2
	REP 8, 1
	SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r2
	LDI 0, r3
	REP 8, 1
	SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r3
	LDI 0, r4
	REP 7, 1
	SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r4
	; encoder multi turn data 12bits
	LDI 0, r5
	REP 8, 1
	SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r5
	LDI 0, r6
	REP 4, 1
	SHRI WAIT1SF WAIT_OVERFLOW_TIMER, FLAG_IN1_CRC, r6
	; encoder CRC checksum 5bits
	LDI 0, r7
	REP 5, 1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r7, FLAG_IN1
	; wait for rising edge of clock signal
    WAIT1SF WAIT_IN0, WAIT_NO_ACTION
	; disable (and reset) counter & timer
    LDI 0, r0 ; disable counter & timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
	
    ; ****************************************
    ; copy reply to SPI transmit buffer
    ; $10 -> ST
    ; $20 -> MT
    ; $70 -> Flags + CRC
    ; ST / Single turn value
    LDI %0001_0000, r0
    ST SPI_BUFFER_3, r0
	; shift right MSB of ST 1x
	SHRI WAIT1SF NO_WAIT, FLAG_IN3, r4   
	LDI %0111_1111, r0
	AND r4, r0, r4
    ST SPI_BUFFER_2, r4
    ST SPI_BUFFER_1, r3
    ST SPI_BUFFER_0, r2
    ; MT / Multiturn value
    LDI %0010_0000, r0
    ST SPI_BUFFER_3, r0
    LDI $0, r0
    ST SPI_BUFFER_2, r0
	; shift right MSB of MT 4x
	SHRI WAIT1SF NO_WAIT, FLAG_IN3, r6 
	SHRI WAIT1SF NO_WAIT, FLAG_IN3, r6 
	SHRI WAIT1SF NO_WAIT, FLAG_IN3, r6 
	SHRI WAIT1SF NO_WAIT, FLAG_IN3, r6 
	LDI %0000_1111, r0
	AND r6, r0, r6
    ST SPI_BUFFER_1, r6
    ST SPI_BUFFER_0, r5
    ; CRC values + flags
    LDI %0111_0000, r0
    ST SPI_BUFFER_3, r0
	; status flags SF
    ST SPI_BUFFER_2, r1 ; status flags
	; load calculated CRC
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r7 ; received CRC
	LDI %0001_1111, r1
	XOR r1, r0, r0
    ST SPI_BUFFER_0, r0 ; calculated CRC
    ; end of transition
    JA CMD_LOOP
    
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
    