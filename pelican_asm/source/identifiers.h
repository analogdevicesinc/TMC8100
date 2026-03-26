/*******************************************************************************
* Copyright © 2024 Analog Devices, Inc.
*******************************************************************************/

#ifndef _IDENTIFIERS_H_
#define _IDENTIFIERS_H_

#include "globals.h"

////////////////////////////////////////////////////////////////////////////////

enum { EVALUATION_OK, EVALUATION_SYNTAX_ERROR, EVALUATION_UNKNOWN_IDENTIFIER };

////////////////////////////////////////////////////////////////////////////////
// identifier

class cIdentifier
{
public:
	cIdentifier() { nValue = 0; nPass = 0; bValid = false; pNext = 0; }
	~cIdentifier() { if (pNext) delete pNext; pNext = 0; }
	cString sName;
	int nValue;
	int nPass;
	bool bValid;
	class cIdentifier* pNext;
};

////////////////////////////////////////////////////////////////////////////////
// list of identifiers

class cIdentifierList
{
public:
	cIdentifierList() { m_pIdentifierList = 0; m_nLine = -1; m_pMsgOut = &std::cerr; InitIdentifierList(); m_nLevel = 0; m_pCurrentIdentifier = 0; m_sFileName = "";  m_nPass = 0; }
	~cIdentifierList() { if (m_pIdentifierList) { delete m_pIdentifierList; m_pIdentifierList = 0; } }
	bool AddIdentifier(const cString& sName);
	bool AddIdentifier(const cString& sName, int nValue);
	int EvaluateExpression(cString& sExpression, int& nValue);
	bool GetIdentifier(const cString& sName, int& nValue, bool& bValid);
	void ResetIdentifierList(void) { m_pCurrentIdentifier = m_pIdentifierList; }
	void DeleteIdentifierList(void) { if (m_pIdentifierList) { delete m_pIdentifierList; m_pIdentifierList = 0; } m_nLine = -1; m_pMsgOut = &std::cerr; InitIdentifierList(); m_nLevel = 0; m_pCurrentIdentifier = 0; m_nPass = 0; }
	bool GetNextIdentifier(cString& sName, int& nValue, bool& bValid);

	void SetLine(int nLine) { m_nLine = nLine; }
	void SetPass(int nPass) { m_nPass = nPass; }
	void SetFileName(const cString& sFileName) { m_sFileName = sFileName; }
	void SetMessageOutput(std::ostream* pOut) { m_pMsgOut = pOut; }
private:
	void InitIdentifierList(void);
	class cIdentifier* m_pIdentifierList;
	class cIdentifier* m_pCurrentIdentifier;
	int m_nLevel;
	int m_nLine;
	cString m_sFileName;
	int m_nPass;
	std::ostream* m_pMsgOut;
};

////////////////////////////////////////////////////////////////////////////////
// #define

class cDefine
{
public:
	cDefine() 
	{
		cString sEmpty; m_sName = sEmpty; m_sReplaceText = sEmpty; m_pNext = 0;
	}
	~cDefine() { if (m_pNext) delete m_pNext; m_pNext = 0; }
	cString m_sName;
	cString m_sReplaceText;
	class cDefine* m_pNext;
};

////////////////////////////////////////////////////////////////////////////////
// list of #define

class cDefineList
{
public:
	cDefineList() { m_pDefineList = 0; }
	~cDefineList() { if (m_pDefineList) { delete m_pDefineList; m_pDefineList = 0; } }
	bool AddDefine(const cString&, const cString&);
	bool IsDefine(const cString&);
	bool RemoveDefine(const cString&);
	bool GetDefine(const cString&, cString&);
private:
	class cDefine* m_pDefineList;
};

////////////////////////////////////////////////////////////////////////////////
// stack for #ifdef, #ifndef and #else

enum {
	IF_DEF_STACK_EMPTY, IF_DEF_STACK_IF, IF_DEF_STACK_ELSE
};

////////////////////////////////////////////////////////////////////////////////

class cIfDef
{
public:
	cIfDef()
	{
		m_nIfDefStackType = IF_DEF_STACK_EMPTY; m_bBlockValid = true; m_bBlockValidEval = true; m_pNext = 0;
	}
	~cIfDef() { if (m_pNext) delete m_pNext; m_pNext = 0; }
	int m_nIfDefStackType;
	bool m_bBlockValid;
	bool m_bBlockValidEval;
	class cIfDef* m_pNext;
};

////////////////////////////////////////////////////////////////////////////////

class cIfDefStack
{
public:
	cIfDefStack() { m_pTopOfStack = 0; }
	~cIfDefStack() { if (m_pTopOfStack) { delete m_pTopOfStack; m_pTopOfStack = 0; } }
	bool Push(int, bool);
	bool Push(int);
	bool IsBlockValid(void);
	int GetLastIfDef(void);
	bool Pop(void);
private:
	class cIfDef* m_pTopOfStack;
};

////////////////////////////////////////////////////////////////////////////////

#endif
