/*******************************************************************************
* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: stack.h
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _STACK_H_
#define _STACK_H_

////////////////////////////////////////////////////////////////////////////////

enum { CALC_INT, CALC_PLUS, CALC_MINUS, CALC_MUL, CALC_DIV, CALC_POWER, CALC_OPEN };

////////////////////////////////////////////////////////////////////////////////

#define CALC_STACK_SIZE 10

////////////////////////////////////////////////////////////////////////////////

class cCalcStack
{
public:
    cCalcStack() { m_pType = new int[CALC_STACK_SIZE]; m_pValue = new int[CALC_STACK_SIZE]; m_nSize = CALC_STACK_SIZE; m_nTopNext = 0; m_nIndex = 0; };
    ~cCalcStack() { if (m_pType) delete[] m_pType; if (m_pValue) delete[] m_pValue; }
    int push(int nType, int nValue);
    int pop(int& nType, int& nValue);
    int top(int& nType, int& nValue);
    void clear(void);
    void resetIndex(void);
    int nextIndex(int& nType, int& nValue);
    int print(std::ostream* m_pMsgOut);
protected:
    int* m_pType;
    int* m_pValue;
    int m_nSize;
    int m_nTopNext;
    int m_nIndex;
};

////////////////////////////////////////////////////////////////////////////////

#endif
