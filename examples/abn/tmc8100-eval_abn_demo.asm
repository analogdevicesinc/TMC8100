;*******************************************************************************
;* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved. This software is
;* proprietary & confidential to Analog Devices, Inc. and its licensors.
;*******************************************************************************
;   abn encoder
;	author: GE, 2023-02-23
    
    SOFTWARE_VERSION_MAJOR = $00
    SOFTWARE_VERSION_MINOR = $01

    PROTOCOL_3 = $20 ; SPACE
    PROTOCOL_2 = $41 ; "A"
    PROTOCOL_1 = $42 ; "B"
    PROTOCOL_0 = $4E ; "N"
    
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
    GPIO_ALT0_FUNCTION      = $43
    GPIO_ALT1_FUNCTION      = $44
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
    
    ; timer encoder counter
    TIM_ENC_COUNTER0        = $60   ; 0110_0000
    TIM_ENC_COUNTER1        = $61
    TIM_ENC_COUNTER2        = $62
    TIM_ENC_COUNTER3        = $63
    TIM_ENC_LIMIT0          = $60
    TIM_ENC_LIMIT1          = $61
    TIM_ENC_LIMIT2          = $62
    TIM_ENC_LIMIT3          = $63
    TIM_ENC_START0          = $64
    TIM_ENC_START1          = $65
    TIM_ENC_START2          = $66
    TIM_ENC_START3          = $67
    TIM_ENC_CAP0            = $64
    TIM_ENC_CAP1            = $65
    TIM_ENC_CAP2            = $66
    TIM_ENC_CAP3            = $67
    TIM_ENC_IN_SCALER_LIM   = $68
    TIM_ENC_HOME_SCALER_LIM = $69
    TIM_ENC_AB_EVENT_CFG    = $6a
    TIM_ENC_ZH_EVENT_CFG    = $6b
    TIM_ENC_CTRL            = $6c
    TIM_ENC_STATUS          = $6c
    TIM_ENC_COMP0_0         = $6d
    TIM_ENC_COMP0_1         = $6e
    TIM_ENC_COMP0_2         = $6f
    TIM_ENC_COMP0_3         = $70
    TIM_ENC_COMP1_0         = $71
    TIM_ENC_COMP1_1         = $72
    TIM_ENC_COMP1_2         = $73
    TIM_ENC_COMP1_3         = $74
    TIM_ENC_COMP_PULS_LIMIT0 = $75
    TIM_ENC_COMP_PULS_LIMIT1 = $76
    TIM_ENC_COMP_PULS_CFG   = $77
    TIM_ENC_DEC_PULS_LIMIT  = $78

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
	; configure DIRECT_IO for A/B/N encoder interface
    ; DIRECT_IN(2) <- ENC_A
    ; DIRECT_IN(3) <- ENC_B
    ; DIRECT_OUT(2) <- ENC_Z
	; ********************************************************************************
    ; DIRECT_OUT(2) -> input ENC_Z
    LDI %0010_0000, r0
    ST  DIRECT_ALT_FUNCTION, r0
    ; gpio5 -> DECODER_OUT
    ; gpio6 -> SPI_DATA_AVAILABLE
    ;LD GPIO_ALT1_FUNCTION, r0
    ;LDI %0001_1100, r1
    ;OR r0, r1, r0
    ;LDI %1101_1111, r1
    ;AND r0, r1, r0
    ;ST GPIO_ALT1_FUNCTION, r0
    ; capture on n-channel high and channel b rising edge
    LDI %0001_0111, r0
    ST TIM_ENC_AB_EVENT_CFG, r0
    LDI %0011_1001, r0
    ST TIM_ENC_ZH_EVENT_CFG, r0
    ; select x4 code, capture on n-channel
    LDI %0010_0010, r0
    ST TIM_ENC_CTRL, r0
    ; set length of decode output signal
    LDI %0000_0010, r0
    ST TIM_ENC_DEC_PULS_LIMIT, r0
    ; set counter limit to max and reset counter
    LDI $ff, r0
    ST TIM_ENC_LIMIT0, r0
    ST TIM_ENC_LIMIT1, r0
    ST TIM_ENC_LIMIT2, r0
    ST TIM_ENC_LIMIT3, r0

CMD_LOOP:
    ; wait for SPI command
    LDI SPI_STATUS, r0
    WAIT1 $0, r0
	LD SPI_BUFFER_3, r0
    ; read encoder counter 32bit value
    LDI $80, r1
    COMP EQ r0, r1
    JC ABN_ENCODER
    ; get software version
    LDI $FF, r1
    COMP EQ r0, r1
    JC software_version
    ; get protocol type
    LDI $FE, r1
    COMP EQ r0, r1
    JC protocol
	JA CMD_LOOP
	
ABN_ENCODER:
    ; ****************************************
    ; copy abn encoder value to SPI transmit buffer
    LD TIM_ENC_COUNTER0, r0
    LD TIM_ENC_COUNTER1, r1
    LD TIM_ENC_COUNTER2, r2
    LD TIM_ENC_COUNTER3, r3
    ST SPI_BUFFER_3, r3
    ST SPI_BUFFER_2, r2
    ST SPI_BUFFER_1, r1
    ST SPI_BUFFER_0, r0
    ; end of transition
    JA CMD_LOOP
    
software_version:
    ; copy reply to SPI transmit buffer
    LDI $FF, r0 ; $FF -> software version
    ST SPI_BUFFER_3, r0
    LDI $00, r0
    ST SPI_BUFFER_2, r0
    LDI SOFTWARE_VERSION_MAJOR, r0
    ST SPI_BUFFER_1, r0
    LDI SOFTWARE_VERSION_MINOR, r0
    ST SPI_BUFFER_0, r0
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
