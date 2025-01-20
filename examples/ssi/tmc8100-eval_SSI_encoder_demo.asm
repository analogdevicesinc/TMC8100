;*******************************************************************************
;* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
;* This software is proprietary to Analog Devices, Inc. and its licensors.
;*******************************************************************************
;   SSI
;	author: GE, 2024-12-06
;
    
    SOFTWARE_VERSION_MAJOR = $01
    SOFTWARE_VERSION_MINOR = $00

    PROTOCOL_3 = $53 ; "S"
    PROTOCOL_2 = $53 ; "S"
    PROTOCOL_1 = $49 ; "I"
    PROTOCOL_0 = $20 ; " "
    
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
    
	; i2c
    
	; spi
	; timer_encoder

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
	; configure PLL for 100MHz and 16MHz crystal clock
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
	; configure DIRECT_IO for the TMC8100-EVAL
    ; DIRECT_OUT(0) -> CLK - generate clock signal
    ; DIRECT_IN(0) <- CLK - read back clock signal for better delay compensation
    ; DIRECT_OUT(3) -> '0' - switch RS485 transceiver in RX mode permanently
    ; DIRECT_IN(1) <- DATA
    ; DIRECT_OUT(1) <- '0'
	; ********************************************************************************

    ; configure DIRECT_OUT(0) as inverted
    LDI $10, r0
    ST DIRECT_POLARITY, r0
    ; set DIRECT_OUT(1) = 0 -> always low
    SFCLR WAIT1SF NO_WAIT, 0, 1
    ; set DIRECT_OUT(3) = 0 -> always low
    SFCLR WAIT1SF NO_WAIT, 0, 3
    ; configure DIRECT_OUT(0) as clock output of the system timer and DIRECT_OUT(3) as output
    LDI $01, r0
    ST DIRECT_ALT_FUNCTION, r0
	; enable input filter for DIRECT_IN
	LDI %0000_0001, r0
	STS r0, SYSTEM_CORE, SYSTEM_CORE_INPUT_FILTER_W

CMD_LOOP:
    ; wait for SPI command
    LDI SPI_STATUS, r0
    WAIT1 $0, r0
	LD SPI_BUFFER_3, r0
    ; read encoder position data
    LDI $80, r1
    COMP EQ r0, r1
    JC read_encoder_data
    ; get software version
    LDI $FF, r1
    COMP EQ r0, r1
    JC software_version
    ; get protocol type
    LDI $FE, r1
    COMP EQ r0, r1
    JC protocol
	JA CMD_LOOP

read_encoder_data:
	; init register
	LDI 0, r2 ; error flags
	LDI 0, r7 ; multi turn (not used)
	LDI 0, r3 ; single turn 
	LDI 0, r4
    ; init counter 
	; set timer to 100MHz / 50 = 2MHz clock toggle rate -> 1MHz SSI clock
	LDI 49, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_COUNTER_LIMIT_W
	; number of clock edges: 52 (25 x 2 + falling edge at the beginning and rising edge at the end)
  	LDI 52, r0
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_PULS_COUNTER_LIMIT_W
    LDI 1, r0 ; enable counter
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W

	; wait for clock signal low / start of transmission
	WAIT0SF WAIT_IN0, WAIT_NO_ACTION ; wait for CLK signal low
	
    ; shift in error flags on fallling edge of clock
	REP 3, 2
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for CLK signal high
	SHLI WAIT0SF WAIT_IN0, r2, FLAG_IN1 ; shift DATA in MSB first on falling edge of clock signal

    ; shift in absolute multi turn counter value (not used)
	REP 6, 2
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for CLK signal high
	SHLI WAIT0SF WAIT_IN0, r7, FLAG_IN1 ; shift DATA in MSB first

    ; shift in single turn counter value - MSB
	REP 8, 2
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for CLK signal high
	SHLI WAIT0SF WAIT_IN0, r3, FLAG_IN1 ; shift DATA in MSB first
	OR r3, r3, r5 ; copy original value to r5

    ; shift in single turn counter value - LSB
	REP 8, 2
	WAIT1SF WAIT_IN0, WAIT_NO_ACTION ; wait for CLK signal high
	SHLI WAIT0SF WAIT_IN0, r4, FLAG_IN1 ; shift DATA in MSB first
	OR r4, r4, r6 ; copy original value to r6
	
	; convert ST value gray code in r3|r4 to binary
	; upper byte in r3 - in place conversion
	TEST1 7, r3
    MOVF 0, r0
	TEST1 6, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 6, r3
	
	TEST1 6, r3
    MOVF 0, r0
	TEST1 5, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 5, r3
	
	TEST1 5, r3
    MOVF 0, r0
	TEST1 4, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 4, r3
	
	TEST1 4, r3
    MOVF 0, r0
	TEST1 3, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 3, r3
	
	TEST1 3, r3
    MOVF 0, r0
	TEST1 2, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 2, r3
	
	TEST1 2, r3
    MOVF 0, r0
	TEST1 1, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 1, r3
	
	TEST1 1, r3
    MOVF 0, r0
	TEST1 0, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 0, r3

	; lower byte in r4 - in place conversion
	TEST1 0, r3
    MOVF 0, r0
	TEST1 7, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 7, r4

	TEST1 7, r4
    MOVF 0, r0
	TEST1 6, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 6, r4

	TEST1 6, r4
    MOVF 0, r0
	TEST1 5, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 5, r4

	TEST1 5, r4
    MOVF 0, r0
	TEST1 4, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 4, r4

	TEST1 4, r4
    MOVF 0, r0
	TEST1 3, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 3, r4

	TEST1 3, r4
    MOVF 0, r0
	TEST1 2, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 2, r4

	TEST1 2, r4
    MOVF 0, r0
	TEST1 1, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 1, r4

	TEST1 1, r4
    MOVF 0, r0
	TEST1 0, r4
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 0, r4

    ; ****************************************
    ; copy reply to SPI transmit buffer
    ; $10 -> ST (Gray)
    ; $20 -> ST (binary)
    ; $70 -> Flags
    ; copy single turn 16bit raw value from encoder to SPI transmit buffer
    LDI %0001_0000, r0 ; ST value
    ST SPI_BUFFER_3, r0 ; 1 -> ST (raw)
	LDI $0, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r5 ; ST - MSB
    ST SPI_BUFFER_0, r6 ; ST - LSB
    ; copy single turn 16bit value converted from gray code to binary to SPI transmit buffer
    LDI %0010_0000, r0 ; 
    ST SPI_BUFFER_3, r0 ; 2 -> ST (binary)
	LDI $0, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r3
    ST SPI_BUFFER_0, r4
    ; copy error flags to SPI transmit buffer
    LDI %0111_0000, r0 ; flag value
    ST SPI_BUFFER_3, r0
    ST SPI_BUFFER_2, r2 ; flags
	LDI $0, r0
    ST SPI_BUFFER_1, r0 ; no CRC
    ST SPI_BUFFER_0, r0 ; no CRC
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
    
