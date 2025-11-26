/*******************************************************************************
* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: instructions.cpp
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#include "instructions.h"

////////////////////////////////////////////////////////////////////////////////

bool regx(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 0) || (nParameter > 7)) return false; // parameter out of range
	nInstr = (nInstr & ~(0x0007 << 6)) | ((nParameter & 0x0007) << 6);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool regy(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 0) || (nParameter > 7)) return false; // parameter out of range
	nInstr = (nInstr & ~(0x0007 << 3)) | ((nParameter & 0x0007) << 3);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool repCount(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 1) || (nParameter > 8)) return false; // parameter out of range
    // -> regy
    nInstr = (nInstr & ~(0x0007 << 3)) | (((nParameter - 1) & 0x0007) << 3);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool regz(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 0) || (nParameter > 7)) return false; // parameter out of range
	nInstr = (nInstr & ~(0x0007)) | (nParameter & 0x0007);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool repLoopLength(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 1) || (nParameter > 4)) return false; // parameter out of range
    // -> regz
	nInstr = (nInstr & ~(0x0007)) | ((nParameter - 1) & 0x0007);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool immediateAddress(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 0) || (nParameter > 2047)) return false; // parameter out of range
	nInstr = (nInstr & ~(0x07ff)) | (nParameter & 0x07ff);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool immediateData(uint16_t& nInstr, uint16_t nParameter)
{
	if ((nParameter < 0) || (nParameter > 255)) return false; // parameter out of range
	nInstr = (nInstr & ~(0x00ff << 3)) | ((nParameter & 0x00ff) << 3);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::InitInstructionInfoList(void)
{
    // instructions with immediate address (11bit) or immediate data (8bit) and register (3bit)
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "JA", "", "%0100_0000_0000_0000", immediateAddress);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "JC", "", "%1100_0000_0000_0000", immediateAddress);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "JFA", "", "%0100_1000_0000_0000", immediateAddress);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "JFC", "", "%1100_1000_0000_0000", immediateAddress);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CALL", "", "%0101_0000_0000_0000", immediateAddress);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CCALL", "", "%1101_0000_0000_0000", immediateAddress);
    //  AddInstrInfo(MACHINE_TM02, "CALL",        "",         "%0101_1000_0000_0000", immediateAddress);
    //  AddInstrInfo(MACHINE_TM02, "CCALL",       "",         "%1101_1000_0000_0000", immediateAddress);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "LD", "", "%0110_0000_0000_0000", immediateData, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CLD", "", "%1110_0000_0000_0000", immediateData, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "ST", "", "%0110_1000_0000_0000", immediateData, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CST", "", "%1110_1000_0000_0000", immediateData, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "LDI", "", "%0111_0000_0000_0000", immediateData, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CLDI", "", "%1111_0000_0000_0000", immediateData, regz);
    //  AddInstrInfo("CALL",        "",         "%0111_1000_0000_0000", immediateData);
    //  AddInstrInfo("CCALL",       "",         "%1111_1000_0000_0000", immediateData);

        // instructions with 3 registers
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "AND", "", "%0001_0000_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CAND", "", "%1001_0000_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "OR", "", "%0001_0010_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "COR", "", "%1001_0010_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "XOR", "", "%0001_0100_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CXOR", "", "%1001_0100_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM10, "ROL", "", "%0001_0110_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM10, "CROL", "", "%1001_0110_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "ADD", "", "%0001_1000_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CADD", "", "%1001_1000_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SUB", "", "%0001_1010_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSUB", "", "%1001_1010_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "LDS", "", "%0001_1100_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CLDS", "", "%1001_1100_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "STS", "", "%0001_1110_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSTS", "", "%1001_1110_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SET", "", "%0010_0000_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSET", "", "%1010_0000_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CLR", "", "%0010_0010_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CCLR", "", "%1010_0010_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "MOVB0", "", "%0010_0100_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CMOVB0", "", "%1010_0100_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "MOVB7", "", "%0010_0110_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CMOVB7", "", "%1010_0110_0000_0000", regx, regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHLO", "WAIT0SF", "%0010_1000_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHLO", "WAIT0SF", "%1010_1000_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHLO", "WAIT1SF", "%0010_1010_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHLO", "WAIT1SF", "%1010_1010_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHLI", "WAIT0SF", "%0010_1100_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHLI", "WAIT0SF", "%1010_1100_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHLI", "WAIT1SF", "%0010_1110_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHLI", "WAIT1SF", "%1010_1110_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHRO", "WAIT0SF", "%0011_0000_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHRO", "WAIT0SF", "%1011_0000_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHRO", "WAIT1SF", "%0011_0010_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHRO", "WAIT1SF", "%1011_0010_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHRI", "WAIT0SF", "%0011_0100_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHRI", "WAIT0SF", "%1011_0100_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SHRI", "WAIT1SF", "%0011_0110_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSHRI", "WAIT1SF", "%1011_0110_0000_0000", regy, regx, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SFSET", "WAIT0SF", "%0011_1000_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSFSET", "WAIT0SF", "%1011_1000_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SFSET", "WAIT1SF", "%0011_1010_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSFSET", "WAIT1SF", "%1011_1010_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SFCLR", "WAIT0SF", "%0011_1100_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSFCLR", "WAIT0SF", "%1011_1100_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SFCLR", "WAIT1SF", "%0011_1110_0000_0000", regy, regz, regx);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSFCLR", "WAIT1SF", "%1011_1110_0000_0000", regy, regz, regx);

    // instructions with 2 registers or less
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "NOP", "", "%0000_0000_0000_0000");
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CNOP", "", "%1000_0000_0000_0000");
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "RSUB", "", "%0000_0000_0100_0000");
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CRSUB", "", "%1000_0000_0100_0000");
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "HALT", "", "%0000_0000_1000_0000");
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CHALT", "", "%1000_0000_1000_0000");
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "REP", "", "%0000_0000_1100_0000", repCount, repLoopLength);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CREP", "", "%1000_0000_1100_0000", repCount, repLoopLength);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "WAIT0", "", "%0000_0001_0000_0000", regz, regy);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CWAIT0", "", "%1000_0001_0000_0000", regz, regy);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "WAIT1", "", "%0000_0001_0100_0000", regz, regy);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CWAIT1", "", "%1000_0001_0100_0000", regz, regy);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "WAIT0SF", "", "%0000_0001_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CWAIT0SF", "", "%1000_0001_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "WAIT1SF", "", "%0000_0001_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CWAIT1SF", "", "%1000_0001_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "COMP", "LT", "%0000_0010_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CCOMP", "LT", "%1000_0010_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "COMP", "LE", "%0000_0010_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CCOMP", "LE", "%1000_0010_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "COMP", "EQ", "%0000_0010_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CCOMP", "EQ", "%1000_0010_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "COMP", "NE", "%0000_0010_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CCOMP", "NE", "%1000_0010_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM10, "XAL", "", "%0000_0011_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM10, "CXAL", "", "%1000_0011_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "COMP",      "NE",       "%0000_0011_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CCOMP",     "NE",       "%1000_0011_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "COMP",      "NE",       "%0000_0011_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CCOMP",     "NE",       "%1000_0011_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "COMP",      "NE",       "%0000_0011_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CCOMP",     "NE",       "%1000_0011_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "NOT", "", "%0000_0100_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CNOT", "", "%1000_0100_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "REV", "", "%0000_0100_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CREV", "", "%1000_0100_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "REV",       "",         "%0000_0100_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CREV",      "",         "%1000_0100_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "REV",       "",         "%0000_0100_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CREV",      "",         "%1000_0100_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "INC", "", "%0000_0101_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CINC", "", "%1000_0101_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "DEC", "", "%0000_0101_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CDEC", "", "%1000_0101_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "DEC",       "",         "%0000_0101_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CDEC",      "",         "%1000_0101_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "DEC",       "",         "%0000_0101_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CDEC",      "",         "%1000_0101_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "TEST0", "", "%0000_0110_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CTEST0", "", "%1000_0110_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "TEST1", "", "%0000_0110_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CTEST1", "", "%1000_0110_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "MOVF", "", "%0000_0110_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CMOVF", "", "%1000_0110_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "MOVNF", "", "%0000_0110_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CMOVNF", "", "%1000_0110_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SFTEST0", "", "%0000_0111_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSFTEST0", "", "%1000_0111_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "SFTEST1", "", "%0000_0111_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSFTEST1", "", "%1000_0111_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "MOVCRC", "", "%0000_0111_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CMOVCRC", "", "%1000_0111_1000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "MOVNCRC", "", "%0000_0111_1100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CMOVNCRC", "", "%1000_0111_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "MOVNCRC",   "",         "%0000_1000_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CMOVNCRC",  "",         "%1000_1000_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "LDR", "", "%0000_1000_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CLDR", "", "%1000_1000_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "MOVNCRC",   "",         "%0000_1000_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CMOVNCRC",  "",         "%1000_1000_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "MOVNCRC",   "",         "%0000_1000_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CMOVNCRC",  "",         "%1000_1000_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "MOVNCRC",   "",         "%0000_1001_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CMOVNCRC",  "",         "%1000_1001_0000_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "STR", "", "%0000_1001_0100_0000", regy, regz);
    AddInstrInfo(MACHINE_TM02 | MACHINE_TM10, "CSTR", "", "%1000_1001_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1001_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1001_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1001_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1001_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1010_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1010_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1010_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1010_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1010_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1010_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1010_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1010_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1011_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1011_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1011_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1011_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1011_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1011_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1011_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1011_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1100_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1100_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1100_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1100_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1100_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1100_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1100_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1100_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1101_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1101_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1101_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1101_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1101_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1101_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1101_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1101_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1110_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1110_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1110_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1110_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1110_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1110_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1110_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1110_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1111_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1111_0000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1111_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1111_0100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1111_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1111_1000_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "STR",       "",         "%0000_1111_1100_0000", regy, regz);
    //    AddInstrInfo(MACHINE_TM02, "CSTR",      "",         "%1000_1111_1100_0000", regy, regz);

    if (CheckInstrList()) return true;
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::AddInstrInfo(const int nMachine, const cString& sCmd, const cString& sCmdAddOn, cString sCode, bool (*pParam1)(uint16_t&, uint16_t), bool (*pParam2)(uint16_t&, uint16_t), bool (*pParam3)(uint16_t&, uint16_t))
{
	int nCode;
	cInstructionInfo* pInstrInfo = new cInstructionInfo;
    pInstrInfo->nMachine = nMachine;
	pInstrInfo->sCmd = sCmd;
	pInstrInfo->sCmdAddOn = sCmdAddOn;
	sCode.GetValue(nCode);
	pInstrInfo->nCode = uint16_t(nCode);
	pInstrInfo->pParam1 = pParam1;
	pInstrInfo->pParam2 = pParam2;
	pInstrInfo->pParam3 = pParam3;
	pInstrInfo->pNext = m_pInstructionInfoList;
    m_pInstructionInfoList = pInstrInfo;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::AddInstrInfoText(const cString& sCmd, const cString& sCmdAddOn, cString sInfo)
{
    cInstructionInfo* pInstrInfo = m_pInstructionInfoList;
    while (pInstrInfo)
    {
        if (pInstrInfo->sCmd.CompareNoCase(sCmd) && pInstrInfo->sCmdAddOn.CompareNoCase(sCmdAddOn))
        {
            pInstrInfo->sInfoText = sInfo;
            return true;
        }
        pInstrInfo = pInstrInfo->pNext;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::GetInstrInfo(const cString& sCmd, const cString& sCmdAddOn, uint16_t& nCode, bool (*&pParam1)(uint16_t&, uint16_t), bool (*&pParam2)(uint16_t&, uint16_t), bool (*&pParam3)(uint16_t&, uint16_t))
{
	cInstructionInfo* pInstrInfo = m_pInstructionInfoList;
	while (pInstrInfo)
	{
		if (pInstrInfo->sCmd.CompareNoCase(sCmd) && pInstrInfo->sCmdAddOn.CompareNoCase(sCmdAddOn))
		{
			// command found
            nCode = pInstrInfo->nCode;
            pParam1 = pInstrInfo->pParam1;
            pParam2 = pInstrInfo->pParam2;
            pParam3 = pInstrInfo->pParam3;
            return true;
		}
        pInstrInfo = pInstrInfo->pNext;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::IsInstr(const cString& sCmd)
{
	cInstructionInfo* pInstrInfo = m_pInstructionInfoList;
	while (pInstrInfo)
	{
        if (pInstrInfo->sCmd.CompareNoCase(sCmd))
        {
            if (pInstrInfo->nMachine & m_nMachine) return true;
            else if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Warning in line " << m_nLine << ": instruction " << sCmd << " not supported for machine architecture " << m_sMachine << "."  << std::endl;
        }
		pInstrInfo = pInstrInfo->pNext;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::IsInstr(const cString& sCmd, const cString& sCmdAddOn)
{
    cInstructionInfo* pInstrInfo = m_pInstructionInfoList;
    while (pInstrInfo)
    {
        if (pInstrInfo->sCmd.CompareNoCase(sCmd)) return true;
        pInstrInfo = pInstrInfo->pNext;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::IsInstrAddOn(const cString& sCmd)
{
    cInstructionInfo* pInstrInfo = m_pInstructionInfoList;
    while (pInstrInfo)
    {
        if (pInstrInfo->sCmd.CompareNoCase(sCmd))
        {
            if (pInstrInfo->sCmdAddOn.Length() == 0) return false;
            else return true;
        }
        pInstrInfo = pInstrInfo->pNext;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

int cInstructionList::GetParameterCount(const cString& sCmd, const cString& sCmdAddOn)
{
    cInstructionInfo* pInstrInfo = m_pInstructionInfoList;
    while (pInstrInfo)
    {
        if (pInstrInfo->sCmd.CompareNoCase(sCmd) && pInstrInfo->sCmdAddOn.CompareNoCase(sCmdAddOn))
        {
            int nParameter = 0;
            if (pInstrInfo->pParam1 != 0) nParameter++;
            if (pInstrInfo->pParam2 != 0) nParameter++;
            if (pInstrInfo->pParam3 != 0) nParameter++;
            return nParameter;
        }
        pInstrInfo = pInstrInfo->pNext;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::AddInstr(int nLine, const cString& sLine, const cString& sCmd, int nAddress, const cString& sCmdAddOn, int* nParameter)
{
    uint16_t nCode;
    bool (*pParam1)(uint16_t & nCode, uint16_t nParamater1);
    bool (*pParam2)(uint16_t & nCode, uint16_t nParamater2);
    bool (*pParam3)(uint16_t & nCode, uint16_t nParamater3);
    pParam1 = 0; pParam2 = 0; pParam3 = 0;
    if (!GetInstrInfo(sCmd, sCmdAddOn, nCode, pParam1, pParam2, pParam3))
    {
        if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": unknown instruction " << sCmd << " " << sCmdAddOn << "." << std::endl;
        return false;
    }
    // update code with parameter info
    int nParameterCount = 0;
    if (pParam1)
    {
        if (!pParam1(nCode, nParameter[0]))
        {
            if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": instruction parameter 1 '" << nParameter[0] << "' out of range." << std::endl;
            return false;
        }
        nParameterCount++;
    }
    if (pParam2) 
    {
        if (!pParam2(nCode, nParameter[1]))
        {
            if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": instruction parameter 2 '" << nParameter[1] << "' out of range." << std::endl;
            return false;
        }
        nParameterCount++;
    }
    if (pParam3)
    {
        if (!pParam3(nCode, nParameter[2]))
        {
            if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": instruction parameter 3 '" << nParameter[2] << "' out of range." << std::endl;
            return false;
        }
        nParameterCount++;
    }
    cInstructionLine* pInstr;
    pInstr = new cInstructionLine;
    pInstr->nLine = nLine;
    pInstr->sLine = sLine;
    pInstr->sCmd = sCmd;
    pInstr->nAddress = nAddress;
    pInstr->sCmdAddOn = sCmdAddOn;
    pInstr->nParameter[0] = nParameter[0];
    pInstr->nParameter[1] = nParameter[1];
    pInstr->nParameter[2] = nParameter[2];
    pInstr->nParameterCount = nParameterCount;
    pInstr->nCode = nCode;
    pInstr->pNext = 0;
    // add new instruction to end of line
    if (m_pInstructions == 0) m_pInstructions = pInstr;
    else
    {
        cInstructionLine* pInstrTemp = m_pInstructions;
        while (pInstrTemp->pNext) pInstrTemp = pInstrTemp->pNext;
        pInstrTemp->pNext = pInstr;
    }
    // update pointer for next instruction
    m_pCurrentInstr = m_pInstructions;
    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::GetNextInstr(int& nLine, int& nAddress, int& nCode, cString& sCmd, cString& sCmdAddOn, int& nParameterCount, int* nParameter)
{
    if (m_pCurrentInstr)
    {
        nLine = m_pCurrentInstr->nLine;
        nAddress = m_pCurrentInstr->nAddress;
        nCode = m_pCurrentInstr->nCode;
        sCmd = m_pCurrentInstr->sCmd;
        sCmdAddOn = m_pCurrentInstr->sCmdAddOn;
        nParameterCount = m_pCurrentInstr->nParameterCount;
        nParameter[0] = m_pCurrentInstr->nParameter[0];
        nParameter[1] = m_pCurrentInstr->nParameter[1];
        nParameter[2] = m_pCurrentInstr->nParameter[2];
        m_pCurrentInstr = m_pCurrentInstr->pNext;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cInstructionList::GetNextInstr(int& nAddress, int& nCode)
{
    if (m_pCurrentInstr)
    {
        nAddress = m_pCurrentInstr->nAddress;
        nCode = m_pCurrentInstr->nCode;
        m_pCurrentInstr = m_pCurrentInstr->pNext;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// code for each instruction should be unique 
// -> check instruction list for same code

bool cInstructionList::CheckInstrList(void)
{
	cInstructionInfo* pInstrInfoRef = m_pInstructionInfoList;
	cInstructionInfo* pInstrInfo;
	int nCodeRef;
	while (pInstrInfoRef)
	{
		nCodeRef = pInstrInfoRef->nCode;
		pInstrInfo = pInstrInfoRef->pNext;
		while (pInstrInfo)
		{
            if (pInstrInfoRef->sCmd.CompareNoCase(pInstrInfo->sCmd) && pInstrInfoRef->sCmdAddOn.CompareNoCase(pInstrInfo->sCmdAddOn))
            {
                if (m_pMsgOut) *m_pMsgOut << "Internal error in instruction table: instruction " << pInstrInfoRef->sCmd << " " << pInstrInfoRef->sCmdAddOn << " found more than once." << std::endl;
                return false;
            }
            if (nCodeRef == pInstrInfo->nCode)
            {
                if (m_pMsgOut) *m_pMsgOut << "Internal error in instruction table: instruction " << pInstrInfo->sCmd << " has same code as instruction " << pInstrInfoRef->sCmd << "." << std::endl;
                return false;
            }
			pInstrInfo = pInstrInfo->pNext;
		}
		pInstrInfoRef = pInstrInfoRef->pNext;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

