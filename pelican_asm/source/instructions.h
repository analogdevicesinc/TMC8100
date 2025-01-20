/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: instructions.h
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INSTRUCTIONS_H_
#define _INSTRUCTIONS_H_

#include "globals.h"

////////////////////////////////////////////////////////////////////////////////

const int MACHINE_TM02 = 0x00000001;
const int MACHINE_TM10 = 0x00000002;

////////////////////////////////////////////////////////////////////////////////

bool regx(uint16_t& nInstr, uint16_t nParameter);
bool regy(uint16_t& nInstr, uint16_t nParameter);
bool repCount(uint16_t& nInstr, uint16_t nParameter);
bool regz(uint16_t& nInstr, uint16_t nParameter);
bool repLoopLength(uint16_t& nInstr, uint16_t nParameter);

bool immediateAddress(uint16_t& nInstr, uint16_t nParameter);
bool immediateData(uint16_t& nInstr, uint16_t nParameter);

////////////////////////////////////////////////////////////////////////////////

class cInstructionInfo
{
public:
	cInstructionInfo() { nMachine = MACHINE_TM02;  pParam1 = 0; pParam2 = 0; pParam3 = 0; nCode = 0; pNext = 0; }
	~cInstructionInfo() { if (pNext) delete pNext; }
	int nMachine;
	cString sCmd;
	cString sCmdAddOn;
	cString sInfoText;
	uint16_t nCode;
	bool (*pParam1)(uint16_t&, uint16_t);
	bool (*pParam2)(uint16_t&, uint16_t);
	bool (*pParam3)(uint16_t&, uint16_t);
	cInstructionInfo* pNext;
};

////////////////////////////////////////////////////////////////////////////////

class cInstructionLine
{
public:
	cInstructionLine() { nLine = 0; nAddress = 0; nParameterCount = 0;  nParameter[0] = nParameter[1] = nParameter[2] = 0; nCode = 0; pNext = 0; }
	~cInstructionLine() { if (pNext) delete pNext; }
	int nLine;
	int nAddress;
	cString sLine;
	cString sCmd;
	cString sCmdAddOn;
	int nParameterCount;
	int nParameter[3];
	int nCode;
	class cInstructionLine* pNext;
};

////////////////////////////////////////////////////////////////////////////////

class cInstructionList
{
public:
	cInstructionList() { m_pInstructionInfoList = 0; m_pInstructions = 0; m_pCurrentInstr = 0; m_nLine = 0; m_sFileName = "";  m_pMsgOut = &(std::cout); InitInstructionInfoList(); }
	~cInstructionList() { if (m_pInstructionInfoList) delete m_pInstructionInfoList; if (m_pInstructions) delete m_pInstructions; }
	bool GetInstrInfo(const cString& sCmd, const cString& sCmdAddOn, uint16_t& nCode, bool (*&pParam1)(uint16_t&, uint16_t), bool (*&pParam2)(uint16_t&, uint16_t), bool (*&pParam3)(uint16_t&, uint16_t));
	bool IsInstr(const cString& sCmd);
	bool IsInstr(const cString& sCmd, const cString& sCmdAddOn);
	bool IsInstrAddOn(const cString& sCmd);
	int GetParameterCount(const cString& sCmd, const cString& sCmdAddOn);

	// transform assembler file into list of instructions
	bool AddInstr(int nLine, const cString& sLine, const cString& sCmd, int nAddress, const cString& sCmdAddOn, int* nParameter);
	void ResetInstrList(void) { m_pCurrentInstr = m_pInstructions; }
	bool GetNextInstr(int& nLine, int& nAddress, int& nCode, cString& sCmd, cString& sCmdAddOn, int& nParameterCount, int* nParameter);
	bool GetNextInstr(int& nAddress, int&nCode);

	void SetLine(int nLine) { m_nLine = nLine; }
	void SetFileName(const cString& sFileName) { m_sFileName = sFileName; }
	void SetMessageOutput(std::ostream *pOut) { m_pMsgOut = pOut; }

	void SetMachine(const int nMachine, const cString sMachine) { m_nMachine = nMachine; m_sMachine = sMachine; }
	cString GetMachineName(void) { return m_sMachine; }

protected:
	bool InitInstructionInfoList(void);
	bool AddInstrInfo(const int nMachine, const cString& sCmd, const cString& sCmdAddOn, cString sCode) { return AddInstrInfo(nMachine, sCmd, sCmdAddOn, sCode, 0, 0, 0); }
	bool AddInstrInfo(const int nMachine, const cString& sCmd, const cString& sCmdAddOn, cString sCode, bool (*pParam1)(uint16_t&, uint16_t)) { return AddInstrInfo(nMachine, sCmd, sCmdAddOn, sCode, pParam1, 0, 0); }
	bool AddInstrInfo(const int nMachine, const cString& sCmd, const cString& sCmdAddOn, cString sCode, bool (*pParam1)(uint16_t&, uint16_t), bool (*pParam2)(uint16_t&, uint16_t)) { return AddInstrInfo(nMachine, sCmd, sCmdAddOn, sCode, pParam1, pParam2, 0); }
	bool AddInstrInfo(const int nMachine, const cString& sCmd, const cString& sCmdAddOn, cString sCode, bool (*pParam1)(uint16_t&, uint16_t), bool (*pParam2)(uint16_t&, uint16_t), bool (*pParam3)(uint16_t&, uint16_t));
	bool AddInstrInfoText(const cString& sCmd, const cString& sCmdAddOn, cString sInfo);
	bool CheckInstrList(void);

	cInstructionInfo* m_pInstructionInfoList;
	cInstructionLine* m_pInstructions;
	cInstructionLine* m_pCurrentInstr;
	int m_nLine;
	cString m_sFileName;
	std::ostream* m_pMsgOut;
	int m_nMachine;
	cString m_sMachine;
};

////////////////////////////////////////////////////////////////////////////////

#endif
