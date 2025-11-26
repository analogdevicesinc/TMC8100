/*******************************************************************************
* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: globals.h
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

enum { PARSER_START, PARSER_END_OF_STRING, PARSER_SPACE, PARSER_UNKNOWN_CHAR, PARSER_IDENTIFIER, PARSER_ADDRESS_LABEL, PARSER_VALUE, PARSER_COLON, PARSER_SEMICOLON,
	PARSER_COMMA, PARSER_EQUAL, PARSER_LEFT_PARENTHESIS, PARSER_RIGHT_PARENTHESIS, PARSER_PLUS, PARSER_MINUS, PARSER_MUL, PARSER_DIV, PARSER_POWER,
	PARSER_STRING_QUOTATION_MARK, PARSER_HASH, PARSER_END_OF_LINE
};

////////////////////////////////////////////////////////////////////////////////

class cString
{
public:
	cString();
	cString(const char* pName);
	cString(char* pStart, char* pStop);
	cString(const cString&);
	cString(int nValue, int nRadix, int nDigits);
	~cString();

	// public methods
	int Length() const { return m_nLength; }
	bool Insert(const cString&, int);
	bool Insert(const char*, int);
	bool Remove(int, int);
	void Append(const cString& sName) { Insert(sName, m_nLength); }
	void Append(const char*);
	void Append(int nValue, int nRadix, int nDigits);
	bool CompareNoCase(const cString&);
	cString SubString(int, int) const;
	int FindFirst(const cString&) const;
	int FindLast(const cString&) const;
	void ToUpper(void);
	void ToLower(void);
	void ReduceSpaces(void);
	void Width(int nColumnWidth, bool bLeftAlign);
	cString GetLeft(const int) const;
	int GetLeft(const cString&);
	int GetLeftFindLast(const cString&);
	int GetLeft(const cString&, cString&);
	cString GetRight(const int, bool) const;
	int GetRight(const cString&);
	bool IsEmpty(void) { if (m_nLength == 0) return true; else return false; }

	bool GetValue(int&);
	bool GetIdentifier(cString&);

	int ParseNext(cString&, int&);
	int ParseNext(cString&, int&, int&);
	char ParseNext(cString&, const cString&);
	//bool ParseNextLine(cString&);
	void ParserReset(void) { m_nParserIndex = 0; }
	int ParserGetIndex(void) { return m_nParserIndex; }
	void ParserSetPosition(int nPosition) { m_nParserIndex = nPosition; }


	// assignment operator
	cString& operator= (const cString&);

	// subscript operator
	char& operator[] (int index);

	// typ conversion to const char*
	operator const char* () const { return m_pName; }

	// string concatenation
	friend cString operator+ (const cString& sName1, const cString& sName2) { cString sName(sName1); sName.Append(sName2); return sName; }
	friend const cString& operator+= (cString& sName1, const cString& sName2) { sName1.Append(sName2); return sName1; }

	// comparison operators
	friend bool operator== (const cString&, const cString&);
	friend bool operator== (const cString&, const char*);
	friend bool operator!= (const cString& sName1, const cString& sName2) { return !(sName1 == sName2); }

	// input/output
	friend std::ostream& operator<< (std::ostream&, const cString&);
	friend std::istream& operator>> (std::istream&, cString&);

private:
	char* m_pName;
	int m_nLength;

	int m_nParserIndex; // start index for ParseNext(), GetValue() and GetIdentifier()
}; // class cString

////////////////////////////////////////////////////////////////////////////////

class cSourceCodeLine
{
public:
	cSourceCodeLine() { m_pNext = 0; m_sLine = ""; m_nLineNumber = 0; m_bFileName = false; m_bInstruction = false;  }
	~cSourceCodeLine() { if (m_pNext) delete m_pNext; m_pNext = 0; }
	cString m_sLine;
	int m_nLineNumber;
	bool m_bFileName;
	int m_bInstruction;
	cSourceCodeLine* m_pNext;
}; // class cSourceCodeLine

////////////////////////////////////////////////////////////////////////////////

class cSourceCodeLineList
{
public:
	cSourceCodeLineList() {
		m_pList = 0; m_pCurrent = 0; m_pLastLine = 0; }
	~cSourceCodeLineList() { if (m_pList) delete m_pList; m_pList = 0; }

	bool AddLine(const cString&, const int);
	bool AddAddress(const int);
	bool AddFileName(const cString&, int nLength);
	bool GetLastFileName(cString&);
	bool GetNextLine(cString&, int&, bool&);
	bool GetNextLine(cString&, int&, bool&, bool&);
	bool SetInstructionLastLine(const bool);
	void ResetGetNextLine(void) { m_pCurrent = m_pList; m_pLastLine = m_pList; }

private:
	cSourceCodeLine* m_pList;
	cSourceCodeLine* m_pCurrent;
	cSourceCodeLine* m_pLastLine;
}; // class cSourceCodeLineList

////////////////////////////////////////////////////////////////////////////////

#endif
