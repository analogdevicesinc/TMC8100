/*******************************************************************************
* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: globals.cpp
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#include "globals.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

cString::cString()
{
	m_pName = new char[1];
	m_pName[0] = '\0';
	m_nParserIndex = 0;
	m_nLength = 0;
}

////////////////////////////////////////////////////////////////////////////////

cString::cString(const char* pName)
{
	m_nLength = 0;
	if (pName) { while (pName[m_nLength] != '\0') m_nLength++; }
	m_pName = new char[m_nLength + 1];
	for (int i = 0; i < m_nLength; i++) m_pName[i] = pName[i];
	m_pName[m_nLength] = '\0';
	m_nParserIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

cString::cString(char* pStart, char* pStop)
{
	m_nLength = pStop - pStart;
	if ((m_nLength <= 0) || (pStart == 0) || (pStop == 0)) m_nLength = 0;
	m_pName = new char[m_nLength + 1];
	for (int i = 0; i < m_nLength; i++) m_pName[i] = pStart[i];
	m_pName[m_nLength] = '\0';
	m_nParserIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

cString::cString(const cString& sName)
{
	m_nLength = sName.m_nLength;
	m_pName = new char[m_nLength + 1];
	for (int i = 0; i < m_nLength; i++) m_pName[i] = sName.m_pName[i];
	m_pName[m_nLength] = '\0';
	m_nParserIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

cString::cString(int nValue, int nRadix, int nDigits)
{
	m_nLength = 0;
	m_pName = new char[1];
	m_pName[0] = '\0';
	Append(nValue, nRadix, nDigits);
}

////////////////////////////////////////////////////////////////////////////////

cString::~cString()
{
	if (m_pName) delete[] m_pName;
	m_pName = 0;
	m_nLength = 0;
	m_nParserIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

bool cString::Insert(const cString & sName, int nOffset)
{
	int i;
	if ((nOffset < 0) || (nOffset > m_nLength)) return false;
	char* pChar = new char[m_nLength + sName.m_nLength + 1];
	// copy first part
	for (i = 0; i < nOffset; i++) pChar[i] = m_pName[i];
	// copy string to insert
	for (i = 0; i < sName.m_nLength; i++) pChar[nOffset + i] = sName.m_pName[i];
	// copy second part
	for (i = nOffset; i < m_nLength; i++) pChar[sName.m_nLength + i] = m_pName[i];
	pChar[m_nLength + sName.m_nLength] = '\0';
	delete[] m_pName;   // release old buffer
	m_pName = pChar;    // switch to new buffer
	m_nLength += sName.m_nLength; // adjust buffer length
	// reset token pointer
	m_nParserIndex = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cString::Insert(const char* pText, int nOffset)
{
	int i, nLength = 0;
	if ((nOffset < 0) || (nOffset > m_nLength)) return false;
	// get length of pText
	if (pText) { while (pText[nLength] != '\0') nLength++; }
	char* pChar = new char[m_nLength + nLength + 1];
	// copy first part
	for (i = 0; i < nOffset; i++) pChar[i] = m_pName[i];
	// copy *pText to insert
	for (i = 0; i < nLength; i++) pChar[nOffset + i] = pText[i];
	// copy second part
	for (i = nOffset; i < m_nLength; i++) pChar[nLength + i] = m_pName[i];
	pChar[m_nLength + nLength] = '\0';
	if (m_pName) delete[] m_pName;   // release old buffer
	m_pName = pChar;    // switch to new buffer
	m_nLength += nLength; // adjust buffer length
	// reset token pointer
	m_nParserIndex = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cString::Remove(int nOffset, int nCount)
{
	int i;
	if ((nOffset < 0) || (nCount < 0) || (nOffset + nCount > m_nLength)) return false;
	// allocate new buffer
	char* pChar = new char[m_nLength - nCount + 1];
	// copy remaining parts
	for (i = 0; i < nOffset; i++) pChar[i] = m_pName[i];
	for (i = nOffset + nCount; i < m_nLength; i++) pChar[i - nCount] = m_pName[i];
	m_nLength -= nCount;   // adjust buffer length
	pChar[m_nLength] = '\0';
	delete[] m_pName; // release old buffer
	m_pName = pChar;    // switch buffer
	// reset token pointer
	m_nParserIndex = 0;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

void cString::Append(const char* pText)
{
	int i, nLength = 0;
	// get length of pText
	if (pText) { while (pText[nLength] != '\0') nLength++; }
	char* pChar = new char[m_nLength + nLength + 1];
	for (i = 0; i < m_nLength; i++) pChar[i] = m_pName[i];
	for (i = 0; i < nLength; i++) pChar[i + m_nLength] = pText[i];
	pChar[m_nLength + nLength] = '\0';
	m_nLength = m_nLength + nLength;
	if (m_pName) delete[] m_pName;
	m_pName = pChar;
}

////////////////////////////////////////////////////////////////////////////////
// append integer
// binary, decimal and hexadecimal supported
void cString::Append(int nValue, int nRadix, int nWidth)
{
	if (nRadix == 2)
	{
		// find msb
		uint32_t nMask = 0x80000000;
		int nDigits = 32;
		int nZeros = 0;
		int i;
		while ((nDigits > 0) && ((nMask & (uint32_t)nValue) == 0)) { nDigits--; nMask = nMask >> 1; }
		if (nDigits == 0) nDigits = 1; // at least one digit
		if (nWidth > nDigits) nZeros = nWidth - nDigits;
		char* pChar = new char[m_nLength + nZeros + nDigits + 1];
		for (i = 0; i < m_nLength; i++) pChar[i] = m_pName[i];
		for (i = 0; i < nZeros; i++) pChar[i + m_nLength] = '0';
		for (i = 0; i < nDigits; i++)
		{
			if ((uint32_t)nValue & nMask) pChar[i + m_nLength + nZeros] = '1';
			else pChar[i + m_nLength + nZeros] = '0';
			nMask = nMask >> 1;
		}
		delete[] m_pName;
		m_pName = pChar;
		m_nLength = m_nLength + nZeros + nDigits;
		m_pName[m_nLength] = '\0';
		m_nParserIndex = 0;
	}
	else if (nRadix == 10)
	{
		// find msb
		int nLimit = 1000000000;
		int nDigits = 10;
		int nZeros = 0;
		int i;
		int nSign;
		if (nValue < 0) { nSign = 1; nValue = -1 * nValue; }
		else nSign = 0;
		while ((nDigits > 0) && (nValue < nLimit)) { nDigits--; nLimit = nLimit / 10; }
		if (nDigits == 0) {	nDigits = 1; nLimit = 1; } // at least one digit
		if (nWidth > nDigits) nZeros = nWidth - nDigits;
		char* pChar = new char[m_nLength + nZeros + nSign + nDigits + 1];
		for (i = 0; i < m_nLength; i++) pChar[i] = m_pName[i];
		for (i = 0; i < nZeros; i++) pChar[i + m_nLength] = '0';
		if (nSign == 1) { pChar[nZeros + m_nLength] = '-'; }
		for (i = 0; i < nDigits; i++)
		{
			pChar[i + m_nLength + nZeros + nSign] = nValue / nLimit + '0';
			nValue = nValue - ((nValue / nLimit) * nLimit);
			nLimit = nLimit / 10;
		}
		delete[] m_pName;
		m_pName = pChar;
		m_nLength = m_nLength + nZeros + nSign + nDigits;
		m_pName[m_nLength] = '\0';
		m_nParserIndex = 0;
	}
	else if (nRadix == 16)
	{
		// find msb
		uint32_t nMask = 0xf0000000;
		int nShift = 28;
		int nDigits = 8;
		int nZeros = 0;
		int i, nDigit;
		while ((nDigits > 0) && ((nMask & (uint32_t)nValue) == 0)) { nDigits--; nMask = nMask >> 4; nShift = nShift - 4; }
		if (nDigits == 0) nDigits = 1; // at least one digit
		if (nWidth > nDigits) nZeros = nWidth - nDigits;
		char* pChar = new char[m_nLength + nZeros + nDigits + 1];
		for (i = 0; i < m_nLength; i++) pChar[i] = m_pName[i];
		for (i = 0; i < nZeros; i++) pChar[i + m_nLength] = '0';
		for (i = 0; i < nDigits; i++)
		{
			nDigit = (((uint32_t)nValue & nMask) >> nShift);
			if (nDigit < 10) pChar[i + m_nLength + nZeros] =  nDigit + '0';
			else pChar[i + m_nLength + nZeros] = nDigit - 10 + 'A';
			nMask = nMask >> 4;
			nShift = nShift - 4;
		}
		delete[] m_pName;
		m_pName = pChar;
		m_nLength = m_nLength + nZeros + nDigits;
		m_pName[m_nLength] = '\0';
		m_nParserIndex = 0;
	}
	return;
}

////////////////////////////////////////////////////////////////////////////////
//
// check for "equivalent" strings
//  - string compare is not case sensitive
//  - number of leading / trailing or in-between spaces / tab-stops is not relevant
//
////////////////////////////////////////////////////////////////////////////////

bool cString::CompareNoCase(const cString& sReference)
{
	char char1, char2;
	int i, j;
	i = j = 0;
	while ((i < m_nLength) && (j < sReference.m_nLength))
	{
		if (((m_pName[i] == ' ') || (m_pName[i] == '\t')) && ((sReference.m_pName[j] == ' ') || (sReference.m_pName[j] == '\t')))
		{
			// skip spaces
			while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
			while ((j < sReference.m_nLength) && ((sReference.m_pName[j] == ' ') || (sReference.m_pName[j] == '\t'))) j++;
			if (((i == m_nLength) && (j != sReference.m_nLength)) || ((i != m_nLength) && (j == sReference.m_nLength))) return false;
			else if ((i == m_nLength) && (j == sReference.m_nLength)) return true;
		}
		// convert to capital letters
		char1 = m_pName[i]; char2 = sReference.m_pName[j];
		if ((char1 >= 'a') && (char1 <= 'z')) char1 = char1 - 'a' + 'A';
		if ((char2 >= 'a') && (char2 <= 'z')) char2 = char2 - 'a' + 'A';
		if (char1 != char2) return false;
		i++; j++;
	}
	if ((i == m_nLength) && (j == sReference.m_nLength)) return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////

cString cString::SubString(int nOffset, int nCount) const
{
	cString sEmpty;
	int i;
	if (nOffset < 0) return sEmpty;
	if (nOffset > m_nLength) return sEmpty;
	if (nOffset + nCount > m_nLength) return sEmpty;
	// allocate temporary buffer
	char* pChar = new char[nCount + 1];
	// copy partial string
	for (i = 0; i < nCount; i++) pChar[i] = m_pName[nOffset + i];
	pChar[nCount] = '\0'; // terminate buffer
	// create result object
	cString sName(pChar);
	delete[] pChar; // release temporary buffer
	return sName;
}

////////////////////////////////////////////////////////////////////////////////

int cString::FindFirst(const cString& sName) const
{
	int i, j;
	int nIndex = -1;
	j = 0;
	for (i = 0; i < m_nLength; i++)
	{
		if (m_pName[i] == sName.m_pName[j])
		{
			if (j == 0) nIndex = i;
			if (j == (sName.m_nLength - 1)) return nIndex;
			else j++;
		}
		else
		{
			j = 0;
			nIndex = -1;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////

int cString::FindLast(const cString& sName) const
{
	int i, j;
	j = sName.m_nLength - 1;
	for (i = m_nLength - 1; i >= 0; i--)
	{
		if (m_pName[i] == sName.m_pName[j])
		{
			if (j == 0) return i;
			else j--;
		}
		else j = sName.m_nLength - 1;
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////

void cString::ToUpper()
{
	for (int i = 0; i < m_nLength; i++)
	{
		if (m_pName[i] >= 'a' && m_pName[i] <= 'z') m_pName[i] -= ('a' - 'A');
	}
}
	
////////////////////////////////////////////////////////////////////////////////

void cString::ToLower()
{
	for (int i = 0; i < m_nLength; i++)
	{
		if (m_pName[i] >= 'A' && m_pName[i] <= 'Z') m_pName[i] += ('a' - 'A');
	}
}

////////////////////////////////////////////////////////////////////////////////

void cString::ReduceSpaces(void)
{
	int nChars = 0;
	int i = 0;
	// calculate length without leading and trailing spaces
	// skip leading spaces
	while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
	while (i < m_nLength)
	{
		if ((m_pName[i] == ' ') || (m_pName[i] == '\t'))
		{
			// remove any double / tripple etc. spaces within the string
			while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
		}
		else i++;
		nChars++;
	}
	// cut off any trailing space
	if ((nChars > 0) && ((m_pName[m_nLength-1] == ' ') || (m_pName[m_nLength-1] == '\t'))) nChars--;
	char* pChar = new char[nChars + 1];
	pChar[nChars] = '\0';
	int j = 0;
	i = 0;
	while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
	while (j < nChars)
	{
		if ((m_pName[i] == ' ') || (m_pName[i] == '\t'))
		{
			pChar[j++] = ' ';
			while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
		}
		else pChar[j++] = m_pName[i++];
	}
	delete[] m_pName;
	m_pName = pChar;
	m_nLength = nChars;
	m_nParserIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

void cString::Width(int nColumnWidth, bool bLeftAlign)
{
	int i, j;
	char* pChar;
	if (nColumnWidth <= 0) return;
	if (m_nLength > nColumnWidth) nColumnWidth = m_nLength;
	pChar = new char[nColumnWidth + 1];
	if (bLeftAlign)
	{
		i = 0;
		while (i < m_nLength) { pChar[i] = m_pName[i]; i++; }
		while (i < nColumnWidth) { pChar[i] = ' '; i++; }
	}
	else
	{
		i = m_nLength - 1;
		j = nColumnWidth - 1;
		while ((i >= 0) && (j >= 0)) { pChar[j] = m_pName[i]; i--; j--; }
		while (j >= 0) { pChar[j] = ' '; j--; }
	}
	delete[] m_pName;
	m_pName = pChar;
	m_nLength = nColumnWidth;
	pChar[nColumnWidth] = '\0';
	m_nParserIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////

cString cString::GetLeft(const int nCount) const
{
	int i;
	cString sEmpty;
	if (nCount <= 0) return sEmpty;
	// allocate temporary buffer
	char* pChar = new char[nCount + 1];
	// copy partial string
	for (i= 0; i < nCount; i++) 
	{
		if (i < m_nLength) pChar[i] = m_pName[i];
		else pChar[i] = ' '; // add spaces for fixed length
	}
	pChar[nCount] = '\0'; // terminate buffer
	// create result object
	cString sName(pChar);
	delete[] pChar; // release temporary buffer
	return sName;
}

////////////////////////////////////////////////////////////////////////////////

int cString::GetLeft(const cString& sEndToken)
{
	int i, j, nEnd = 0;
	int nStartIndex = -1;
	j = 0;
	if ((m_nLength == 0) || (sEndToken.m_nLength == 0)) return false;
	for (i = 0; i < m_nLength; i++)
	{
		if (m_pName[i] == sEndToken.m_pName[j])
		{
			if (nStartIndex == -1) nStartIndex = i;
			if (j == 0) nEnd = i;
			if (j == sEndToken.m_nLength - 1)
			{
				char* pChar = new char[nEnd + 1];
				for (i = 0; i < nEnd; i++) pChar[i] = m_pName[i];
				pChar[nEnd] = '\0';
				delete[] m_pName;
				m_pName = pChar;
				m_nLength = nEnd;
				m_nParserIndex = 0;
				return nStartIndex;
			}
			else j++;
		}
		else
		{
			j = 0;
			nStartIndex = -1;
		}
	}
	// no match found, leave string untouched
	return nStartIndex;
}

////////////////////////////////////////////////////////////////////////////////

int cString::GetLeftFindLast(const cString& sEndToken)
{
	int i, j = 0;
	int nEnd = 0;
	int nStartIndex = -1;
	int nStartIndexLast = nStartIndex;
	int nEndLast = nEnd;
	bool bFound = false;
	if ((m_nLength == 0) || (sEndToken.m_nLength == 0)) return false;
	for (i = 0; i < m_nLength; i++)
	{
		if (m_pName[i] == sEndToken.m_pName[j])
		{
			if (nStartIndex == -1) nStartIndex = i;
			if (j == 0) nEnd = i;
			if (j == sEndToken.m_nLength - 1)
			{
				bFound = true;
				nStartIndexLast = nStartIndex;
				nEndLast = nEnd;
				j = 0;
				nStartIndex = -1;
				nEnd = 0;
			}
			else j++;
		}
		else
		{
			j = 0;
			nStartIndex = -1;
		}
	}
	if (bFound)
	{
		char* pChar = new char[nEndLast + 1];
		for (i = 0; i < nEndLast; i++) pChar[i] = m_pName[i];
		pChar[nEndLast] = '\0';
		delete[] m_pName;
		m_pName = pChar;
		m_nLength = nEndLast;
		m_nParserIndex = 0;
		return nStartIndexLast;
	}
	// no match found, leave string untouched
	return nStartIndex;
}

////////////////////////////////////////////////////////////////////////////////

int cString::GetLeft(const cString& sDelimiterToken, cString& sRest)
{
	int i, j, nEnd = 0;
	int nStartIndex = -1;
	j = 0;
	if ((m_nLength == 0) || (sDelimiterToken.m_nLength == 0)) return false;
	for (i = 0; i < m_nLength; i++)
	{
		if (m_pName[i] == sDelimiterToken.m_pName[j])
		{
			if (nStartIndex == -1) nStartIndex = i;
			if (j == 0) nEnd = i;
			if (j == sDelimiterToken.m_nLength - 1)
			{
				// match - remember 
				// copy first part of string until delimiter token
				char* pHead = new char[nEnd + 1];
				for (j = 0; j < nEnd; j++) pHead[j] = m_pName[j];
				pHead[nEnd] = '\0';
				// copy second part of string after delimiter until end
				int nStart = i + 1;
				char* pTail = new char[m_nLength - nStart + 1];
				for (j = nStart; j < m_nLength; j++) pTail[j-nStart] = m_pName[j];
				pTail[m_nLength - nStart] = '\0';
				cString sTemp(pTail);
				sRest = sTemp;
				delete[] m_pName;
				m_pName = pHead;
				m_nLength = nEnd;
				m_nParserIndex = 0;
				break;
			}
			else j++;
		}
		else
		{
			j = 0;
			nStartIndex = -1;
		}
	}
	// no match found, leave string untouched
	return nStartIndex;
}

////////////////////////////////////////////////////////////////////////////////

cString cString::GetRight(const int nCount, const bool bDots = false) const
{
	int nStart = 0;
	int nSize = m_nLength;
	int nDots = 0;
	cString sEmpty;
	if (nCount <= 0) return sEmpty;
	if (nCount < m_nLength) 
	{
		// get partial string ...
		nSize = nCount;
		nStart = m_nLength - nCount;
		if (bDots)
		{
			if (nCount >= 10) nDots = 3;
			else if (nCount >= 5) nDots = 2;
			else nDots = 1;
		}
	}
	// allocate temporary buffer
	char* pChar = new char[nSize + 1];
	// add leading dots - when string is longer than nCount and bDots = true
	int i = 0;
	while (nDots)
	{
		pChar[i++] = '.';
		nDots--;
	}
	// copy partial string
	while (i < nSize)
	{
		pChar[i++] = m_pName[nStart++];
	}
	pChar[nSize] = '\0'; // terminate buffer
	// create result object
	cString sName(pChar);
	delete[] pChar; // release temporary buffer
	return sName;
}

////////////////////////////////////////////////////////////////////////////////

int cString::GetRight(const cString& sEndToken)
{
	int i, j, nStart = 0;
	int nEndIndex = -1;
	if ((m_nLength == 0) || (sEndToken.m_nLength == 0)) return false;
	j = sEndToken.m_nLength - 1;
	for (i = m_nLength - 1; i > 0; i--)
	{
		if (m_pName[i] == sEndToken.m_pName[j])
		{
			if (nEndIndex == -1) nEndIndex = i;
			if (j == (sEndToken.m_nLength - 1)) nStart = i + 1;
			if (j == 0)
			{
				char* pChar = new char[m_nLength - nStart + 1];
				for (i = nStart; i < m_nLength; i++) pChar[i-nStart] = m_pName[i];
				m_nLength = m_nLength - nStart;
				pChar[m_nLength] = '\0';
				delete[] m_pName;
				m_pName = pChar;
				m_nParserIndex = 0;
				return nEndIndex;
			}
			else j--;
		}
		else
		{
			j = sEndToken.m_nLength - 1;
			nEndIndex = -1;
		}
	}
	// no match found, leave string untouched
	return nEndIndex;
}

////////////////////////////////////////////////////////////////////////////////

char& cString::operator[] (int index)
{
	if (index < 0 || index >= m_nLength) throw out_of_range("Wrong index");
	return m_pName[index];
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// convert string to integer
// accept hex, binary and decimal values
//   0x123456789abcdef or $0123456789abcdef-> hex number
//   01234567 -> octal number
//   %01 -> binary number
//   decimal number
// skip leading spaces and move pointer "pInteger" to first non-digit character
//
////////////////////////////////////////////////////////////////////////////////

bool cString::GetValue(int& nValue)
{
	char* pChar = m_pName;
	int i = m_nParserIndex;
	nValue = 0;
	// skip any leading spaces
	while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
	if (i == m_nLength) return false;
	if (((i + 1) < m_nLength) && (m_pName[i] == '0') && (m_pName[i+1] == 'x'))
	{
		// hex number
		i += 2;
		if (i == m_nLength) return false;
		while (i < m_nLength)
		{
			if ((m_pName[i] >= '0') && (m_pName[i] <= '9')) nValue = (nValue << 4) + m_pName[i] - '0';
			else if ((m_pName[i] >= 'a') && (m_pName[i] <= 'f')) nValue = (nValue << 4) + m_pName[i] - 'a' + 10;
			else if ((m_pName[i] >= 'A') && (m_pName[i] <= 'F')) nValue = (nValue << 4) + m_pName[i] - 'A' + 10;
			else break;
			i++;
		}
	}
	else if (m_pName[i] == '$')
	{
		// hex number
		i++;
		if (i == m_nLength) return false;
		while (i < m_nLength)
		{
			if ((m_pName[i] >= '0') && (m_pName[i] <= '9')) nValue = (nValue << 4) + m_pName[i] - '0';
			else if ((m_pName[i] >= 'a') && (m_pName[i] <= 'f')) nValue = (nValue << 4) + m_pName[i] - 'a' + 10;
			else if ((m_pName[i] >= 'A') && (m_pName[i] <= 'F')) nValue = (nValue << 4) + m_pName[i] - 'A' + 10;
			else break;
			i++;
		}
	}
	else if (m_pName[i] == '%')
	{
		// binary
		i++;
		if (i == m_nLength) return false;
		while (i < m_nLength)
		{
			if ((m_pName[i] == '0') || (m_pName[i] == '1')) nValue = (nValue << 1) + m_pName[i] - '0';
			else if (m_pName[i] != '_') break; // allow '_' inside binary numbers for better readability
			i++;
		}
	}
	else if ((m_pName[i] >= '0') && (m_pName[i] <= '9'))
	{
		// decimal number
		while (i < m_nLength)
		{
			if ((m_pName[i] >= '0') && (m_pName[i] <= '9')) nValue = (nValue * 10) + m_pName[i] - '0';
			else break;
			i++;
		}
	}
	else
	{
		// unknown character
		return false;
	}
	// update parser position
	m_nParserIndex = i;
	return true;
} // bool cString::GetValue(int& nValue)

////////////////////////////////////////////////////////////////////////////////

int cString::ParseNext(cString& sToken, int& nValue)
{
	// skip leading spaces
	while ((m_nParserIndex < m_nLength) && ((m_pName[m_nParserIndex] == ' ') || (m_pName[m_nParserIndex] == '\t'))) m_nParserIndex++;
	if (m_nParserIndex == m_nLength) return PARSER_END_OF_STRING;
	if (m_pName[m_nParserIndex] == '(') { m_nParserIndex++; return PARSER_LEFT_PARENTHESIS; }
	else if (m_pName[m_nParserIndex] == ')') { m_nParserIndex++; return PARSER_RIGHT_PARENTHESIS; }
	else if (m_pName[m_nParserIndex] == '=') { m_nParserIndex++; return PARSER_EQUAL; }
	else if (m_pName[m_nParserIndex] == '+') { m_nParserIndex++; return PARSER_PLUS; }
	else if (m_pName[m_nParserIndex] == '-') { m_nParserIndex++; return PARSER_MINUS; }
	else if (m_pName[m_nParserIndex] == '*') { m_nParserIndex++; return PARSER_MUL; }
	else if (m_pName[m_nParserIndex] == '/') { m_nParserIndex++; return PARSER_DIV; }
	else if (m_pName[m_nParserIndex] == '^') { m_nParserIndex++; return PARSER_POWER; }
	else if (m_pName[m_nParserIndex] == ':') { m_nParserIndex++; return PARSER_COLON; }
	else if (m_pName[m_nParserIndex] == ',') { m_nParserIndex++; return PARSER_COMMA; }
	else if (m_pName[m_nParserIndex] == ';') { m_nParserIndex++; return PARSER_SEMICOLON; }
	else if (GetIdentifier(sToken))
	{
		if (m_pName[m_nParserIndex] == ':') { m_nParserIndex++; return PARSER_ADDRESS_LABEL; }
		else return PARSER_IDENTIFIER;
	}
	else if (GetValue(nValue)) return PARSER_VALUE;
	else
	{
		// unknown char
		if (sToken.m_pName) delete[] sToken.m_pName;
		sToken.m_pName = new char[2];
		sToken.m_pName[0] = m_pName[m_nParserIndex];
		sToken.m_pName[1] = '\0';
		sToken.m_nLength = 1;
		sToken.m_nParserIndex = 0;
		m_nParserIndex++;
		return PARSER_UNKNOWN_CHAR;
	}
}

////////////////////////////////////////////////////////////////////////////////
/*
int cString::ParseNext(cString& sToken, int& nValue, int& nLine)
{
	bool bBlockComment = false;
	int nStartLine = nLine;
	bool bLineComment = false;
	bool bStringQuotationMark = false;
	int nStringStart = 0;
	// skip leading spaces
	while ((m_nParserIndex < m_nLength) && ((m_pName[m_nParserIndex] == ' ') || (m_pName[m_nParserIndex] == '\t'))) m_nParserIndex++;
	if (m_nParserIndex == m_nLength) return PARSER_END_OF_STRING;
	while (m_nParserIndex < m_nLength)
	{
		if ((m_pName[m_nParserIndex] == '\n') || (m_pName[m_nParserIndex] == '\r'))
		{
			nLine++;
			m_nParserIndex++;
			bLineComment = false;
			if (!bBlockComment) return PARSER_END_OF_LINE;
		}
		else if (bBlockComment)
		{
			if ((m_pName[m_nParserIndex] == '*') && ((m_nParserIndex + 1) < m_nLength) && (m_pName[m_nParserIndex + 1] == '/'))
			{
				// end of block comment
				bBlockComment = false;
				m_nParserIndex += 2;
				if (nStartLine != nLine) return PARSER_END_OF_LINE;
			}
			else m_nParserIndex++;
		}
		else if (bLineComment)
		{
			m_nParserIndex++;
		}
		else if (bStringQuotationMark)
		{
			if (m_pName[m_nParserIndex] == '"')
			{
				// end of string " .. "
				if (sToken.m_pName) delete[] sToken.m_pName;
				int nSize = m_nParserIndex - nStringStart;
				sToken.m_pName = new char[nSize + 1];
				for (int i = 0; i < nSize; i++) sToken.m_pName[i] = m_pName[nStringStart + i];
				sToken.m_pName[nSize] = '\0';
				sToken.m_nLength = nSize;
				sToken.m_nParserIndex = 0;
				m_nParserIndex++;
				return PARSER_STRING_QUOTATION_MARK;
			}
			else m_nParserIndex++;
		}
		else if ((m_pName[m_nParserIndex] == '/') && ((m_nParserIndex + 1) < m_nLength) && (m_pName[m_nParserIndex] == '*')) { m_nParserIndex += 2; bBlockComment = true; }
		else if ((m_pName[m_nParserIndex] == '/') && ((m_nParserIndex + 1) < m_nLength) && (m_pName[m_nParserIndex] == '/')) { m_nParserIndex += 2; bLineComment = true; }
		else if (m_pName[m_nParserIndex] == ';') { m_nParserIndex++; bLineComment = true; }
		else if (m_pName[m_nParserIndex] == '"') { m_nParserIndex++; nStringStart = m_nParserIndex; bStringQuotationMark = true; }
		else if (m_pName[m_nParserIndex] == '(') { m_nParserIndex++; return PARSER_LEFT_PARENTHESIS; }
		else if (m_pName[m_nParserIndex] == ')') { m_nParserIndex++; return PARSER_RIGHT_PARENTHESIS; }
		else if (m_pName[m_nParserIndex] == '=') { m_nParserIndex++; return PARSER_EQUAL; }
		else if (m_pName[m_nParserIndex] == '+') { m_nParserIndex++; return PARSER_PLUS; }
		else if (m_pName[m_nParserIndex] == '-') { m_nParserIndex++; return PARSER_MINUS; }
		else if (m_pName[m_nParserIndex] == '*') { m_nParserIndex++; return PARSER_MUL; }
		else if (m_pName[m_nParserIndex] == '/') { m_nParserIndex++; return PARSER_DIV; }
		else if (m_pName[m_nParserIndex] == '^') { m_nParserIndex++; return PARSER_POWER; }
		else if (m_pName[m_nParserIndex] == ':') { m_nParserIndex++; return PARSER_COLON; }
		else if (m_pName[m_nParserIndex] == ',') { m_nParserIndex++; return PARSER_COMMA; }
		else if (GetIdentifier(sToken))
		{
			if (m_pName[m_nParserIndex] == ':') { m_nParserIndex++; return PARSER_ADDRESS_LABEL; }
			else return PARSER_IDENTIFIER;
		}
		else if (GetValue(nValue)) return PARSER_VALUE;
		else
		{
			// unknown char
			if (sToken.m_pName) delete[] sToken.m_pName;
			sToken.m_pName = new char[2];
			sToken.m_pName[0] = m_pName[m_nParserIndex];
			sToken.m_pName[1] = '\0';
			sToken.m_nLength = 1;
			sToken.m_nParserIndex = 0;
			m_nParserIndex++;
			return PARSER_UNKNOWN_CHAR;
		}
	}
}
*/
////////////////////////////////////////////////////////////////////////////////

int cString::ParseNext(cString& sString, int& nValue, int& nLine)
{
	bool bBlockComment = false;
	int nStartLine = nLine;
	bool bLineComment = false;
	bool bStringQuotationMark = false;
	bool bStringLTGT = false;
	int nStringStart = 0;
	// skip leading spaces
	while ((m_nParserIndex < m_nLength) && ((m_pName[m_nParserIndex] == ' ') || (m_pName[m_nParserIndex] == '\t'))) m_nParserIndex++;
	if (m_nParserIndex == m_nLength) return PARSER_END_OF_STRING;
	while (m_nParserIndex < m_nLength)
	{
		if ((m_pName[m_nParserIndex] == '\n') || (m_pName[m_nParserIndex] == '\r'))
		{
			// CR -> \r
			// LF -> \n
			nLine++;
			if ((m_pName[m_nParserIndex] == '\r') && ((m_nParserIndex+1) < m_nLength) && (m_pName[m_nParserIndex+1] == '\n')) m_nParserIndex+=2;
			else m_nParserIndex++;
			bLineComment = false;
			if (!bBlockComment) return PARSER_END_OF_LINE;
		}
		else if (bBlockComment)
		{
			if ((m_pName[m_nParserIndex] == '*') && ((m_nParserIndex + 1) < m_nLength) && (m_pName[m_nParserIndex + 1] == '/'))
			{
				// end of block comment
				bBlockComment = false;
				m_nParserIndex += 2;
				if (nStartLine != nLine) return PARSER_END_OF_LINE;
			}
			else m_nParserIndex++;
		}
		else if (bLineComment) m_nParserIndex++;
		else if (bStringQuotationMark)
		{
			if (m_pName[m_nParserIndex] == '"')
			{
				// end of string " .. "
				if (sString.m_pName) delete[] sString.m_pName;
				int nSize = m_nParserIndex - nStringStart;
				sString.m_pName = new char[nSize + 1];
				for (int i = 0; i < nSize; i++) sString.m_pName[i] = m_pName[nStringStart + i];
				sString.m_pName[nSize] = '\0';
				sString.m_nLength = nSize;
				sString.m_nParserIndex = 0;
				m_nParserIndex++;
				return PARSER_STRING_QUOTATION_MARK;
			}
			m_nParserIndex++;
		}
		else if ((m_pName[m_nParserIndex] == '/') && ((m_nParserIndex + 1) < m_nLength) && (m_pName[m_nParserIndex + 1] == '*')) { m_nParserIndex += 2; bBlockComment = true; }
		else if ((m_pName[m_nParserIndex] == '/') && ((m_nParserIndex + 1) < m_nLength) && (m_pName[m_nParserIndex + 1] == '/')) { m_nParserIndex += 2; bLineComment = true; }
		else if (m_pName[m_nParserIndex] == ';') { m_nParserIndex++; bLineComment = true; }
		else if (m_pName[m_nParserIndex] == '"') 
		{ 
			m_nParserIndex++;
			nStringStart = m_nParserIndex; 
			bStringQuotationMark = true; 
		}
		else if (m_pName[m_nParserIndex] == '(') { m_nParserIndex++; return PARSER_LEFT_PARENTHESIS; }
		else if (m_pName[m_nParserIndex] == ')') { m_nParserIndex++; return PARSER_RIGHT_PARENTHESIS; }
		else if (m_pName[m_nParserIndex] == '=') { m_nParserIndex++; return PARSER_EQUAL; }
		else if (m_pName[m_nParserIndex] == '+') { m_nParserIndex++; return PARSER_PLUS; }
		else if (m_pName[m_nParserIndex] == '-') { m_nParserIndex++; return PARSER_MINUS; }
		else if (m_pName[m_nParserIndex] == '*') { m_nParserIndex++; return PARSER_MUL; }
		else if (m_pName[m_nParserIndex] == '/') { m_nParserIndex++; return PARSER_DIV; }
		else if (m_pName[m_nParserIndex] == '^') { m_nParserIndex++; return PARSER_POWER; }
		else if (m_pName[m_nParserIndex] == ':') { m_nParserIndex++; return PARSER_COLON; }
		else if (m_pName[m_nParserIndex] == ',') { m_nParserIndex++; return PARSER_COMMA; }
		else if (m_pName[m_nParserIndex] == '#') { m_nParserIndex++; return PARSER_HASH; }
		else if (GetIdentifier(sString))
		{
			if (m_pName[m_nParserIndex] == ':') { m_nParserIndex++; return PARSER_ADDRESS_LABEL; }
			else return PARSER_IDENTIFIER;
		}
		else if (GetValue(nValue)) return PARSER_VALUE;
		else 
		{ 
			if ((m_pName[m_nParserIndex] > 32) && (m_pName[m_nParserIndex] < 127))
			{
				// printable char
				nValue = m_pName[m_nParserIndex];
				m_nParserIndex++;
				return PARSER_UNKNOWN_CHAR;
			}
			m_nParserIndex++; // in case of an unreadable character just skip this character
		}
	}
	return PARSER_END_OF_STRING;
}

////////////////////////////////////////////////////////////////////////////////

char cString::ParseNext(cString& sName, const cString& sDelimiter)
{
	int i, j, k;
	// skip leading spaces
	while ((m_nParserIndex < m_nLength) && ((m_pName[m_nParserIndex] == ' ') || (m_pName[m_nParserIndex] == '\t'))) m_nParserIndex++;
	i = m_nParserIndex; j = 0;
	while (i < m_nLength)
	{
		for (j = 0; j < sDelimiter.m_nLength; j++) if (m_pName[i] == sDelimiter.m_pName[j]) goto match_or_end;
		i++;
	}
match_or_end:
	char* pChar = new char[i - m_nParserIndex + 1];
	for (k = m_nParserIndex; k < i; k++) pChar[k - m_nParserIndex] = m_pName[k];
	pChar[i - m_nParserIndex] = '\0';
	sName.m_nLength = i - m_nParserIndex;
	delete[] sName.m_pName;
	sName.m_pName = pChar;
	sName.m_nParserIndex = 0;
	if (i == m_nLength) { m_nParserIndex = m_nLength; return 0; }
	else m_nParserIndex = i + 1;
	return sDelimiter.m_pName[j];
}

////////////////////////////////////////////////////////////////////////////////
/*
bool cString::ParseNextLine(cString& sName)
{
	int i, j;
	// empty string - return false
	if (m_nParserIndex == m_nLength) return false;
	i = m_nParserIndex;
	while (i < m_nLength)
	{
		if ((m_pName[i] == '\n') || (m_pName[i] == '\r')) break; // cover windows and unix end of line
		i++;
	}
	char* pChar = new char[i - m_nParserIndex + 1];
	for (j = m_nParserIndex; j < i; j++) pChar[j - m_nParserIndex] = m_pName[j];
	pChar[i - m_nParserIndex] = '\0';
	sName.m_nLength = i - m_nParserIndex;
	delete[] sName.m_pName;
	sName.m_pName = pChar;
	sName.m_nParserIndex = 0;
	if (i == m_nLength) m_nParserIndex = m_nLength;
	else if (m_pName[i] == '\n') // LF
	{
		i++; m_nParserIndex = i;
	}
	else if ((m_pName[i] == '\r') && (m_pName[i + 1] == '\n')) // CR + LF
	{
		i++; i++;  m_nParserIndex = i;
	}
	return true;
}
*/
////////////////////////////////////////////////////////////////////////////////

bool cString::GetIdentifier(cString& sIdentifier)
{
	int i = m_nParserIndex;
	int nStart, nLength;
	// skip leading spaces
	while ((i < m_nLength) && ((m_pName[i] == ' ') || (m_pName[i] == '\t'))) i++;
	if (i == m_nLength) return false;
	if ((m_pName[i] == '_') || 
		((m_pName[i] >= 'a') && (m_pName[i] <= 'z')) || 
		((m_pName[i] >= 'A') && (m_pName[i] <= 'Z')))
	{
		// start either '_', a-z or A-Z
		nStart = i;
		while ((i < m_nLength) &&
			((m_pName[i] == '_') ||
			((m_pName[i] >= 'a') && (m_pName[i] <= 'z')) ||
			((m_pName[i] >= 'A') && (m_pName[i] <= 'Z')) ||
			((m_pName[i] >= '0') && (m_pName[i] <= '9'))))
		{
			i++;
		}
		nLength = i - nStart;
		// copy identifer
		delete[] sIdentifier.m_pName;
		sIdentifier.m_pName = new char[nLength+1];
		for (i = 0; i < nLength; i++)
		{
			sIdentifier.m_pName[i] = m_pName[nStart + i];
		}
		sIdentifier.m_nLength = nLength;
		sIdentifier.m_nParserIndex = 0;
		sIdentifier.m_pName[nLength] = '\0';
		m_nParserIndex = nStart + nLength;
		return true;
	}
	return false;
} // bool cString::GetIdentifier(cString& sIdentifier)

////////////////////////////////////////////////////////////////////////////////

// assignment operator
cString& cString::operator= (const cString & sName)
{
	if (this != &sName)
	{
		// delete old string
		delete[] m_pName;
		// allocate new buffer
		m_nLength = sName.m_nLength;
		m_pName = new char[m_nLength + 1];
		// reset token pointer
		m_nParserIndex = 0;
		// deep copy
		for (int i = 0; i < m_nLength; i++) m_pName[i] = sName.m_pName[i];
		m_pName[m_nLength] = '\0';
	}
	return *this;
} // cString & cString::operator= (const cString & sName)

////////////////////////////////////////////////////////////////////////////////
// comparison operators

bool operator== (const cString& sName1, const cString& sName2)
{
	if (sName1.m_nLength != sName2.m_nLength) return false;
	for (int i = 0; i < sName1.m_nLength; i++)
	{
		if (sName1.m_pName[i] != sName2.m_pName[i]) return false;
	}
	return true;
} // bool operator== (const cString& sName1, const cString& sName2)

////////////////////////////////////////////////////////////////////////////////

bool operator== (const cString& sName1, const char* pName2)
{
	int i = 0;
	while (sName1.m_pName[i] != '\0')
	{
		if (sName1.m_pName[i] != pName2[i]) return false;
		i++;
	}
	if (pName2[i] != '\0') return false;
	return true;
} // bool operator== (const cString& sName1, const char* pName2)

////////////////////////////////////////////////////////////////////////////////
// output operator

ostream& operator<< (ostream& os, const cString& sName)
{
	for (int i = 0; i < sName.m_nLength; i++)
	{
		os << sName.m_pName[i];
	}
	return os;
}

////////////////////////////////////////////////////////////////////////////////
// input operator

istream& operator>> (istream& is, cString& sName)
{
	if (is)
	{
		is.seekg(0, is.beg);
		int nBegin = is.tellg();
		is.seekg(0, is.end);
		int nEnd = is.tellg();
		is.seekg(0, is.beg);
		int nLength = nEnd - nBegin;
		char* pChar = new char[nLength + 1];
		is.read(pChar, nLength);
		pChar[nLength] = '\0';
		delete[] sName;
		sName.m_pName = pChar;
		sName.m_nLength = nLength;
		sName.m_nParserIndex = 0;
	}
	return is;
}

////////////////////////////////////////////////////////////////////////////////
//
// cSourceCodeLineList
// 
////////////////////////////////////////////////////////////////////////////////
 
bool cSourceCodeLineList::AddLine(const cString& sLine, const int nLineNumber)
{
	cSourceCodeLine* pNewLine = new cSourceCodeLine;
	pNewLine->m_nLineNumber = nLineNumber;
	pNewLine->m_sLine = sLine;
	pNewLine->m_bFileName = false;
	pNewLine->m_bInstruction = false;
	pNewLine->m_pNext = 0;
	// add new line always to the end of the list
	if (m_pCurrent == 0)
	{
		// list is empty / first line
		m_pList = pNewLine;
		m_pCurrent = pNewLine;
	}
	else
	{
		// add to end of list
		m_pCurrent->m_pNext = pNewLine;
		m_pCurrent = pNewLine;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cSourceCodeLineList::SetInstructionLastLine(const bool bInstruction)
{
	if (m_pLastLine && !m_pLastLine->m_bFileName)
	{
		m_pLastLine->m_bInstruction = bInstruction;
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

bool cSourceCodeLineList::AddFileName(const cString& sFileName, int nLength)
{
	cSourceCodeLine* pNewLine = new cSourceCodeLine;
	pNewLine->m_nLineNumber = 0;
	pNewLine->m_sLine = sFileName.GetRight(nLength, true);
	pNewLine->m_bFileName = true;
	pNewLine->m_pNext = 0;
	// add new line always to the end of the list
	if (m_pCurrent == 0)
	{
		// list is empty / first line
		m_pList = pNewLine;
		m_pCurrent = pNewLine;
	}
	else
	{
		// add to end of list
		m_pCurrent->m_pNext = pNewLine;
		m_pCurrent = pNewLine;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cSourceCodeLineList::GetLastFileName(cString& sText)
{
	if (m_pCurrent == 0) return false;
	if (!m_pCurrent->m_bFileName) return false;
	sText = m_pCurrent->m_sLine;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cSourceCodeLineList::GetNextLine(cString& sText, int& nLineNumber, bool& bFileName)
{
	if (m_pCurrent == 0) return false;
	sText = m_pCurrent->m_sLine;
	nLineNumber = m_pCurrent->m_nLineNumber;
	bFileName = m_pCurrent->m_bFileName;
	m_pLastLine = m_pCurrent;
	m_pCurrent = m_pCurrent->m_pNext;
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool cSourceCodeLineList::GetNextLine(cString& sText, int& nLineNumber, bool& bFileName, bool& bInstruction)
{
	if (m_pCurrent == 0) return false;
	sText = m_pCurrent->m_sLine;
	nLineNumber = m_pCurrent->m_nLineNumber;
	bFileName = m_pCurrent->m_bFileName;
	bInstruction = m_pCurrent->m_bInstruction;
	m_pCurrent = m_pCurrent->m_pNext;
	return true;
}

////////////////////////////////////////////////////////////////////////////////
