/*******************************************************************************
* Copyright © 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: identifiers.cpp
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#include "globals.h"
#include "identifiers.h"
#include "stack.h"

#define EXPRESSION_EVALUATION

////////////////////////////////////////////////////////////////////////////////

bool cIdentifierList::AddIdentifier(const cString& sName)
{
	int nValue = 0;
	bool bValid = false;

	if (GetIdentifier(sName, nValue, bValid)) return false; // identifier with same name already exists
	cIdentifier* pIdentifier;
	pIdentifier = new cIdentifier;
	pIdentifier->sName = sName;
	pIdentifier->nValue = 0;
	pIdentifier->nPass = m_nPass;
	pIdentifier->bValid = false;
	pIdentifier->pNext = m_pIdentifierList;
	m_pIdentifierList = pIdentifier;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cIdentifierList::AddIdentifier(const cString& sName, int nValue)
{
	// search for identifier in list
	cIdentifier* pIdentifier = m_pIdentifierList;
	while (pIdentifier)
	{
		if (pIdentifier->sName.CompareNoCase(sName)) break;
		pIdentifier = pIdentifier->pNext;
	}
	if (pIdentifier && pIdentifier->bValid)
	{
		// identifier already exists
		if (pIdentifier->nValue != nValue)
		{
			// ambiguous value definition
			if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": identifier " << sName << " already defined with different value." << std::endl;
			return false;
		}
		else if ((pIdentifier->nPass == m_nPass) && (m_nPass == 1))
		{
			// same value but, defined more than once, report during second pass, only
			if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Info line " << m_nLine << ": identifier " << sName << " already defined with same value." << std::endl;
		}
	}
	if (pIdentifier == 0)
	{
		pIdentifier = new cIdentifier;
		pIdentifier->sName = sName;
		pIdentifier->pNext = m_pIdentifierList;
		m_pIdentifierList = pIdentifier;
	}
	pIdentifier->nValue = nValue;
	pIdentifier->nPass = m_nPass;
	pIdentifier->bValid = true;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

void cIdentifierList::InitIdentifierList(void)
{
	// add register names
	AddIdentifier("r0", 0);
	AddIdentifier("r1", 1);
	AddIdentifier("r2", 2);
	AddIdentifier("r3", 3);
	AddIdentifier("r4", 4);
	AddIdentifier("r5", 5);
	AddIdentifier("r6", 6);
	AddIdentifier("r7", 7);
}

////////////////////////////////////////////////////////////////////////////////

int cIdentifierList::EvaluateExpression(cString& sExpression, int& nReturnValue)
{
#ifndef EXPRESSION_EVALUATION
	cString sName;
	int nValue, nReturn;

	nReturn = sExpression.ParseNext(sName, nValue);
	if (nReturn == PARSER_VALUE) { nReturnValue = nValue; return EVALUATION_OK; }
	else if (nReturn == PARSER_IDENTIFIER)
	{
		bool bValid, bExists;
		bExists = GetIdentifier(sName, nValue, bValid);
		if (bValid && bExists) { nReturnValue = nValue; return EVALUATION_OK; }
		else if (m_pMsgOut)
		{
			if (!bExists && m_pMsgOut && (m_nPass == 1)) *m_pMsgOut << "Error in line " << m_nLine << ": unknwon identifier " << sName << "." << std::endl;
			else if (m_pMsgOut && (m_nPass == 1)) *m_pMsgOut << "Error in line " << m_nLine << ": identifier " << sName << " unknown value." << std::endl;
			return EVALUATION_UNKNOWN_IDENTIFIER;
		}
	}
	else if (nReturn == PARSER_UNKNOWN)
	{
		if (m_pMsgOut) *m_pMsgOut << "Warning in line " << m_nLine << ": unexpected character \"" << sName << "\"." << std::endl;
	}
	return EVALUATION_OK;
#else
	class cCalcStack postfixStack;
	class cCalcStack operandStack;
	int nTempType, nTempValue;
	int nReturn;
	cString sName;
	int nValue;

	while ((nReturn = sExpression.ParseNext(sName, nValue)) != PARSER_END_OF_STRING)
	{
		if (nReturn == PARSER_VALUE)
		{
			postfixStack.push(CALC_INT, nValue);
		}
		else if (nReturn == PARSER_IDENTIFIER)
		{
			bool bValid, bExists;
			bExists = GetIdentifier(sName, nValue, bValid);
			if (bValid && bExists) postfixStack.push(CALC_INT, nValue);
			else
			{
				if (!bExists && m_pMsgOut && (m_nPass == 1)) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": unknwon identifier " << sName << "." << std::endl;
				else if (m_pMsgOut && (m_nPass == 1)) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": identifier " << sName << " unknown value." << std::endl;
				return EVALUATION_UNKNOWN_IDENTIFIER;
			}
		}
		else if (nReturn == PARSER_LEFT_PARENTHESIS)
		{
			operandStack.push(CALC_OPEN, 0);
		}
		else if (nReturn == PARSER_POWER)
		{
			operandStack.push(CALC_POWER, 0);
		}
		else if (nReturn == PARSER_RIGHT_PARENTHESIS)
		{
			while (operandStack.pop(nTempType, nTempValue))
			{
				if (nTempType == CALC_OPEN) break;
				else postfixStack.push(nTempType, nTempValue);
			}
		}
		else if ((nReturn == PARSER_MUL) || (nReturn == PARSER_DIV) || (nReturn == PARSER_PLUS) || (nReturn == PARSER_MINUS))
		{
			while (operandStack.top(nTempType, nTempValue))
			{
				if ((nTempType == CALC_MUL) || (nTempType == CALC_DIV))
				{
					operandStack.pop(nTempType, nTempValue);
					postfixStack.push(nTempType, nTempValue);
				}
				else if (((nTempType == CALC_PLUS) || (nTempType == CALC_MINUS)) && ((nReturn == PARSER_PLUS) || (nReturn == PARSER_MINUS)))
				{
					operandStack.pop(nTempType, nTempValue);
					postfixStack.push(nTempType, nTempValue);
				}
				else break;
			}
			if (nReturn == PARSER_PLUS) operandStack.push(CALC_PLUS, 0);
			else if (nReturn == PARSER_MINUS) operandStack.push(CALC_MINUS, 0);
			else if (nReturn == PARSER_MUL) operandStack.push(CALC_MUL, 0);
			else if (nReturn == PARSER_DIV) operandStack.push(CALC_DIV, 0);
		}
		else if (nReturn == PARSER_UNKNOWN_CHAR)
		{
			if (m_pMsgOut && (m_nPass == 1)) *m_pMsgOut << "\"" << m_sFileName << "\" Warning in line " << m_nLine << ": unexpected character \"" << sName << "\"." << std::endl;
		}
	}
	// copy remaining values
	while (operandStack.pop(nTempType, nTempValue)) postfixStack.push(nTempType, nTempValue);
	// output postfix stack for debug
	// if (m_pMsgOut) *m_pMsgOut << "Info: postfix stack contents: ";
	// postfixStack.print(m_pMsgOut);
	// process postfix stack
	operandStack.clear();
	postfixStack.resetIndex();
	while (postfixStack.nextIndex(nTempType, nTempValue))
	{
		if (nTempType == CALC_INT) operandStack.push(nTempType, nTempValue);
		else
		{
			int nValue1, nValue2, nResult = 0, nDummyType;
			if (operandStack.pop(nDummyType, nValue2) && operandStack.pop(nDummyType, nValue1))
			{
				if (nTempType == CALC_MUL) nResult = nValue1 * nValue2;
				else if (nTempType == CALC_DIV) nResult = nValue1 / nValue2;
				else if (nTempType == CALC_PLUS) nResult = nValue1 + nValue2;
				else if (nTempType == CALC_MINUS) nResult = nValue1 - nValue2;
				else if (nTempType == CALC_POWER)
				{
					nResult = 1;
					for (int i = 0; i < nValue2; i++) nResult *= nValue1;
				}
				operandStack.push(CALC_INT, nResult);
			}
			else
			{
				if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": operand missing" << std::endl;
				return EVALUATION_SYNTAX_ERROR;
			}
		}
	}
	if (operandStack.pop(nTempType, nTempValue))
	{
		nReturnValue = nTempValue;
	}
	if (operandStack.pop(nTempType, nTempValue))
	{
		if (m_pMsgOut) *m_pMsgOut << "\"" << m_sFileName << "\" Error in line " << m_nLine << ": too many operands" << std::endl;
		return EVALUATION_SYNTAX_ERROR;
	}
	return EVALUATION_OK;
#endif
}

////////////////////////////////////////////////////////////////////////////////

bool cIdentifierList::GetIdentifier(const cString& sName, int& nValue, bool& bValid)
{
	cIdentifier* pIdentifier = m_pIdentifierList;
	while (pIdentifier)
	{
		if (pIdentifier->sName.CompareNoCase(sName))
		{
			nValue = pIdentifier->nValue;
			bValid = pIdentifier->bValid;
			return true;
		}
		pIdentifier = pIdentifier->pNext;
	}
	bValid = false;
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cIdentifierList::GetNextIdentifier(cString& sName, int& nValue, bool& bValid)
{
	if (m_pCurrentIdentifier)
	{
		sName = m_pCurrentIdentifier->sName;
		nValue = m_pCurrentIdentifier->nValue;
		bValid = m_pCurrentIdentifier->bValid;
		m_pCurrentIdentifier = m_pCurrentIdentifier->pNext;
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//
//	cDefineList
//
////////////////////////////////////////////////////////////////////////////////

bool cDefineList::AddDefine(const cString& sName, const cString& sReplaceText)
{
	cDefine* pDefine = new cDefine;
	pDefine->m_sName = sName;
	pDefine->m_sReplaceText = sReplaceText;
	pDefine->m_pNext = m_pDefineList;
	m_pDefineList = pDefine;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineList::IsDefine(const cString& sName)
{
	cDefine* pDefine = m_pDefineList;
	while (pDefine)
	{
		if (pDefine->m_sName == sName) return true;
		pDefine = pDefine->m_pNext;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineList::RemoveDefine(const cString& sName)
{
	cDefine* pDefine = m_pDefineList;
	cDefine* pDefinePrevious = 0;
	while (pDefine)
	{
		if (pDefine->m_sName == sName)
		{
			if (pDefinePrevious == 0) m_pDefineList = pDefine->m_pNext;
			else pDefinePrevious = pDefine->m_pNext;
			delete pDefine;
			return true;
		}
		pDefinePrevious = pDefine;
		pDefine = pDefine->m_pNext;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineList::GetDefine(const cString& sName, cString& sReplacementText)
{
	cDefine* pDefine = m_pDefineList;
	while (pDefine)
	{
		if (pDefine->m_sName == sName)
		{
			sReplacementText = pDefine->m_sReplaceText;
			return true;
		}
		pDefine = pDefine->m_pNext;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineStack::Push(const cString& sName, bool bSkipLine)
{
	cDefine* pDefine = new cDefine;
	pDefine->m_sName = sName;
	pDefine->m_bSkipLine = bSkipLine;
	pDefine->m_sReplaceText = "";
	pDefine->m_pNext = m_pTopOfStack;
	m_pTopOfStack = pDefine;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineStack::GetSkipLine(bool& bSkipLine)
{
	if (!m_pTopOfStack) return false;
	bSkipLine = m_pTopOfStack->m_bSkipLine;
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineStack::SetSkipLine(const bool bSkipLine)
{
	if (!m_pTopOfStack) return false;
	m_pTopOfStack->m_bSkipLine = bSkipLine;
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineStack::IsStackEmpty(void)
{
	if (m_pTopOfStack) return false;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cDefineStack::Pop(void)
{
	if (m_pTopOfStack)
	{
		cDefine* pDefine = m_pTopOfStack;
		m_pTopOfStack = m_pTopOfStack->m_pNext;
		delete pDefine;
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
