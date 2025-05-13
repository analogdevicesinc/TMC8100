;*******************************************************************************
;* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved. This software is
;* proprietary & confidential to Analog Devices, Inc. and its licensors.
;*******************************************************************************
;   BiSS-C
;	author: GE, 2025-03-24
;
    
    SOFTWARE_VERSION_MAJOR = $01
    SOFTWARE_VERSION_MINOR = $00
	
	; frequency divider for 100MHz system clock
	; BISS_FREQ_DIV = 200 - 1 ;  500kHz BiSS clock -> 100Mhz / 200
	BISS_FREQ_DIV = 100 - 1 ;  1MHz BiSS clock -> 100Mhz / 100
	; BISS_FREQ_DIV = 49 ;  2MHz BiSS clock -> 100Mhz / 50
	; BISS_FREQ_DIV = 19 ;  5MHz BiSS clock -> 100Mhz / 20
	; BISS_FREQ_DIV =  9 ; 10MHz BiSS clock -> 100Mhz / 10
	
	BISS_TOGGLE_DIV = (BISS_FREQ_DIV + 1) / 2 - 1 
	
	; number of clock edges:
	; 7 + 2(Start) + 2(CDS) + 2x13 ST-bits + 4(nWarn, nErr) + 12(6bit CRC) + 1
	;  -> 54 rising + falling edges (with CDM = 0)
	; encoder processing delay requires more clock cycles at higher frequencies
	; BISS_CLK_EDGES = 52 ; 500kHz BiSS clock -> rising and falling edges
	BISS_CLK_EDGES = 54 ;  1MHz BiSS clock -> rising and falling edges
	; BISS_CLK_EDGES = 58 ;  2MHz BiSS clock -> rising and falling edges
	; BISS_CLK_EDGES = 64 ;  5MHz BiSS clock -> rising and falling edges
	; BISS_CLK_EDGES = 76 ; 10MHz BiSS clock -> rising and falling edges

    PROTOCOL_3 = $42 ; "B"
    PROTOCOL_2 = $49 ; "I"
    PROTOCOL_1 = $53 ; "S"
    PROTOCOL_0 = $53 ; "S"
    
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
    ; DIRECT_OUT(0) -> MA - generate clock signal
    ; DIRECT_OUT(3) -> '0' - switch RS485 transceiver in RX mode permanently
    ; DIRECT_IN(1) <- SLO - data in
    ; DIRECT_OUT(1) <- '0'
	; ********************************************************************************

    ; configure DIRECT_OUT(0) as inverted
    LDI $10, r0
    ST  DIRECT_POLARITY, r0
    ; set DIRECT_OUT(1) = 0 -> always low
    SFCLR WAIT1SF NO_WAIT, 0, 1
    ; set DIRECT_OUT(3) = 0 -> always low
    SFCLR WAIT1SF NO_WAIT, 0, 3
    ; configure DIRECT_OUT(3) as output
    LDI $00, r0
    ST  DIRECT_ALT_FUNCTION, r0
	; enable input filter for DIRECT_IN
	; LDI %0000_0001, r0
	; STS r0, SYSTEM_CORE, SYSTEM_CORE_INPUT_FILTER_W

CMD_LOOP:
    ; wait for SPI command
    LDI SPI_STATUS, r0
    WAIT1 $0, r0
	LD SPI_BUFFER_3, r0
    ; Read ST, Flags and CRC, CDM = 0
    LDI $80, r1
    COMP EQ r0, r1
    JC BISS_encoder
    ; get software version
    LDI $FF, r1
    COMP EQ r0, r1
    JC software_version
    ; get protocol type
    LDI $FE, r1
    COMP EQ r0, r1
    JC protocol
	JA CMD_LOOP	
	
BISS_encoder:
	; read encoder value with CDM = 1 / nCDM = 0
    ; configure DIRECT_OUT(0) as clock output
    LDI $01, r0
    ST  DIRECT_ALT_FUNCTION, r0
	; init register
    ; initialize crc block
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_CTRL_W ; reset CRC block
	LDI $0, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W ; LSB, initialize CRC start with zero
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_START_W ; MSB
	LDI %0100_0011, r0 ; CRC polynomial: x^6 + x^1 + x^0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; LSB
	LDI %0000_0000, r0
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W
	STS r0, SYSTEM_CRC, SYSTEM_CRC_POLYNOM_W ; MSB
    ; init counter 
	LDI BISS_TOGGLE_DIV, r0 ; set toggle rate for BiSS clock generator
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_COUNTER_LIMIT_W
	; number of clock edges:
  	LDI BISS_CLK_EDGES, r0 ; number of rising and falling edges
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_PULS_COUNTER_LIMIT_W
    LDI 1, r0 ; enable counter
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
    ; HEADER
	; '0'
	LDI BISS_TOGGLE_DIV, r0 ; from rising edge of start bit to middle of start bit / half a clock cycle
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_W
	WAIT0SF WAIT_IN1, WAIT_NO_ACTION ; wait for falling edge of data signal '0'
	WAIT1SF WAIT_IN1, WAIT_START_TIMER ; wait for rising edge of start bit '1' and start timer
	; wait until middle of start bit
	WAIT1SF WAIT_OVERFLOW_TIMER, WAIT_NO_ACTION
	LDI BISS_FREQ_DIV, r0 ; set sample point to middle of next bit / 1 clock cycle
	STS r0, SYSTEM_TIMER, SYSTEM_TIMER_LIMIT_NO_RESET_W
	LDI 0, r1
	; middle of CDS - shift CDS into r1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r1, FLAG_IN1
    ; encoder data 13bit
	; MSB - shift upper 5bit of encoder data into r2
	LDI 0, r2
	REP 5, 1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r2, FLAG_IN1_CRC
	; LSB - shift lower 8bit of encoder data into r3
	LDI 0, r3
	REP 8, 1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r3, FLAG_IN1_CRC
	; Error + Warning - shift bits into r4
	LDI 0, r4
	REP 2, 1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r4, FLAG_IN1_CRC
	; CRC - shift 6 CRC bits into r5 / received CRC
	LDI 0, r5
	REP 6, 1
	SHLI WAIT1SF WAIT_OVERFLOW_TIMER, r5, FLAG_IN1
	; middle of last bit - wait for data signal = 0
	WAIT0SF WAIT_IN1, WAIT_NO_ACTION
	; wait for rising edge of data signal (timeout)
    WAIT1SF WAIT_IN1, WAIT_NO_ACTION
	; disable (and reset) counter & timer
    LDI 0, r0 ; disable counter & timer
    STS r0, SYSTEM_TIMER, SYSTEM_TIMER_CTRL_W
    ; ****************************************
	; convert encoder data gray code (r2|r3) -> binary code (r2|r3)

	ST DATA_MEM_ADDR, r2 ; copy original (raw) MSB encoder value from r2 to data memory
	ST DATA_MEM_ADDR + 1, r3 ; copy original (raw) LSB encoder value from r3 to data memory

	; upper byte in r2 - in place conversion
	TEST1 7, r2
    MOVF 0, r0
	TEST1 6, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 6, r2
	
	TEST1 6, r2
    MOVF 0, r0
	TEST1 5, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 5, r2
	
	TEST1 5, r2
    MOVF 0, r0
	TEST1 4, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 4, r2
	
	TEST1 4, r2
    MOVF 0, r0
	TEST1 3, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 3, r2
	
	TEST1 3, r2
    MOVF 0, r0
	TEST1 2, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 2, r2
	
	TEST1 2, r2
    MOVF 0, r0
	TEST1 1, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 1, r2
	
	TEST1 1, r2
    MOVF 0, r0
	TEST1 0, r2
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 0, r2

	; lower byte in r3 - in place conversion
	TEST1 0, r2
    MOVF 0, r0
	TEST1 7, r3
    MOVF 0, r1
	XOR r0, r1, r0
	TEST1 0, r0
    MOVF 7, r3

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
	
    ; ****************************************
    ; copy reply to SPI transmit buffer
    ; $10 -> ST (Gray)
    ; $20 -> ST (binary)
    ; $70 -> Flags
	
	; copy ST / raw / gray code to SPI transmit buffer
    LDI $10, r0
    ST SPI_BUFFER_3, r0
	LDI $0, r0
    ST SPI_BUFFER_2, r0
    LD DATA_MEM_ADDR, r0
	LD DATA_MEM_ADDR + 1, r1
    ST SPI_BUFFER_1, r0
    ST SPI_BUFFER_0, r1
	
	; copy ST / binary code to SPI transmit buffer
    LDI $20, r0
    ST SPI_BUFFER_3, r0
	LDI $0, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r2
    ST SPI_BUFFER_0, r3
    
	; copy status and crc value to SPI transmit buffer
    LDI $70, r0 ; crc values
    ST SPI_BUFFER_3, r0 ; 7 -> CRC + STATUS Field
    ST SPI_BUFFER_2, r4 ; Error + Warning
    LDS SYSTEM_CRC, SYSTEM_CRC_RESULT0_R, r0
    ST SPI_BUFFER_1, r5 ; CRC received
	LDI %0011_1111, r1
    XOR r0, r1, r0 ; CRC is inverted
    ST SPI_BUFFER_0, r0 ; CRC calculated
	
	; copy number of clock edges (r7) to SPI transmit buffer
    LDI $71, r0 ; clock edges values
    ST SPI_BUFFER_3, r0 ;
	LDI $0, r0
    ST SPI_BUFFER_2, r0
    ST SPI_BUFFER_1, r0
	LDI BISS_CLK_EDGES, r0
    ST SPI_BUFFER_0, r0
	
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
    