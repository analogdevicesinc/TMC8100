/*******************************************************************************
* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved. This software is
* proprietary & confidential to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: stack.cpp
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#include "globals.h"
#include "stack.h"

////////////////////////////////////////////////////////////////////////////////

#define EXPRESSION_EVALUATION

////////////////////////////////////////////////////////////////////////////////

int cCalcStack::push(int nType, int nValue)
{
    if (m_nTopNext == m_nSize)
    {
        // increase stack size
        int* pTypeTemp = new int[m_nSize + CALC_STACK_SIZE];
        int* pValueTemp = new int[m_nSize + CALC_STACK_SIZE];
        for (int i = 0; i < m_nSize; i++)
        {
            pTypeTemp[i] = m_pType[i];
            pValueTemp[i] = m_pValue[i];
        }
        delete[] m_pType; m_pType = pTypeTemp;
        delete[] m_pValue; m_pValue = pValueTemp;
        m_nSize += CALC_STACK_SIZE;
    }
    m_pType[m_nTopNext] = nType;
    m_pValue[m_nTopNext] = nValue;
    m_nTopNext++;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////

int cCalcStack::pop(int& nType, int& nValue)
{
    if (m_nTopNext == 0) return 0;
    m_nTopNext--;
    nType = m_pType[m_nTopNext];
    nValue = m_pValue[m_nTopNext];
    return 1;
}

////////////////////////////////////////////////////////////////////////////////

int cCalcStack::top(int& nType, int& nValue)
{
    if (m_nTopNext == 0) return 0;
    nType = m_pType[m_nTopNext - 1];
    nValue = m_pValue[m_nTopNext - 1];
    return 1;
}

////////////////////////////////////////////////////////////////////////////////

void cCalcStack::clear(void)
{
    m_nTopNext = 0;
    m_nIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

void cCalcStack::resetIndex(void)
{
    m_nIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

int cCalcStack::nextIndex(int& nType, int& nValue)
{
    if (m_nIndex == m_nTopNext) return 0; // no further entries
    nType = m_pType[m_nIndex];
    nValue = m_pValue[m_nIndex];
    m_nIndex++;
    return 1;
}

////////////////////////////////////////////////////////////////////////////////
// for debug purposes
int cCalcStack::print(std::ostream* m_pMsgOut)
{
    if (m_pMsgOut)
    {
        for (int i = 0; i < m_nTopNext; i++)
        {
            if (i != 0) *m_pMsgOut << ", ";
            if (m_pType[i] == CALC_INT) *m_pMsgOut << m_pValue[i];
            else if (m_pType[i] == CALC_PLUS) *m_pMsgOut << '+';
            else if (m_pType[i] == CALC_MINUS) *m_pMsgOut << '-';
            else if (m_pType[i] == CALC_MUL) *m_pMsgOut << '*';
            else if (m_pType[i] == CALC_DIV) *m_pMsgOut << '/';
            else if (m_pType[i] == CALC_POWER) *m_pMsgOut << '^';
            else *m_pMsgOut << "ERR";
        }
        *m_pMsgOut << std::endl;
        return 1;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
