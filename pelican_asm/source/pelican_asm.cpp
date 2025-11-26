/*******************************************************************************
* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved.
* This software is proprietary to Analog Devices, Inc. and its licensors.
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
//
// file: pelican_asm.cpp
// 
// author: GE
//
////////////////////////////////////////////////////////////////////////////////

#include "globals.h"
#include "identifiers.h"
#include "instructions.h"
#include <fstream>
#include <ctime>
#include <iomanip>

#define PELICAN_ASM_VERSION "1.0"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

void CommandLineHelp(void)
{
	std::cout << "pelican_asm.exe <file_name>[.asm] [-m|M TM02|TM10] [-i] [-l] [-c] [-rom] [-h]" << std::endl;
	std::cout << "				  <file_name>[.asm]: input ASCII text file" << std::endl;
	std::cout << "				     [-m TM02|TM10]: machine type - either TM02 (default) or TM10" << std::endl;
	std::cout << "				               [-i]: generate intermediate / pre-processor output file" << std::endl;
	std::cout << "				               [-l]: generate log file" << std::endl;
	std::cout << "				               [-c]: generate c code file" << std::endl;
	std::cout << "				             [-rom]: generate \"pelican_bootloader\" output files for simulation / FPGA / synthesis" << std::endl;
	std::cout << "				               [-h]: help" << std::endl;
	std::cout << "output files:" << std::endl;
	std::cout << "  <file_name>.i (requires -i option): intermediate file - merged input files with all pre-processor commands #.. removed" << std::endl;
	std::cout << "  <file_name>.log (requires -l): log file - input file contents + instruction code / memory address" << std::endl;
	std::cout << "  <file_name>.c (requires -c): C language source file - C-array with instruction code" << std::endl;
	std::cout << "  <file_name>.hex: intel hex format file" << std::endl;
	std::cout << "  pelican_bootloader.hex: (requires -rom option) ROM hex format file - one line per instruction (16bit hex format)" << std::endl;
	std::cout << "  pelican_bootloader.bin: (requires -rom option) ROM binary format file - one line per instruction (16bit binary format)" << std::endl;
	std::cout << "  pelican_bootloader.vhd: (requires -rom option) vhdl file - vhdl entity logic replacement for ROM" << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void PreProcessString(cSourceCodeLineList& codeList, cDefineList& defineList, cString& sFileContents, int& nErrorCount)
{
	int nReply, nValue, nLine = 1;
	cDefineStack defineStack;
	bool bSkipCodeLine = false;
	bool bAddressLabel = false;
	cString sLine, sString, sFileName;

	// remember file name
	if (!codeList.GetLastFileName(sFileName)) sFileName = "";
	sLine = "";
	while (true)
	{
		// search for pre-processor command starting with '#'
		nReply = sFileContents.ParseNext(sString, nValue, nLine);
		if (nReply == PARSER_END_OF_STRING) 
		{ 
			if (!sLine.IsEmpty())
			{
				sLine.ReduceSpaces();
				if (!bAddressLabel) sLine.Insert("  ", 0); // do some pretty printing
				codeList.AddLine(sLine, nLine - 1);
			}
			if (!defineStack.IsStackEmpty()) { std::cerr << "\"" << sFileName << "\" Warning in line " << (nLine - 1) << ": #endif missing." << std::endl; }
			return; 
		}
		else if (!bSkipCodeLine && (nReply == PARSER_STRING_QUOTATION_MARK)) { sLine.Append("\""); sLine.Append(sString); sLine.Append("\""); }
		else if (!bSkipCodeLine && (nReply == PARSER_LEFT_PARENTHESIS)) sLine.Append("(");
		else if (!bSkipCodeLine && (nReply == PARSER_RIGHT_PARENTHESIS)) sLine.Append(")");
		else if (!bSkipCodeLine && (nReply == PARSER_RIGHT_PARENTHESIS)) sLine.Append(")");
		else if (!bSkipCodeLine && (nReply == PARSER_EQUAL)) sLine.Append("=");
		else if (!bSkipCodeLine && (nReply == PARSER_PLUS)) sLine.Append("+");
		else if (!bSkipCodeLine && (nReply == PARSER_MINUS)) sLine.Append("-");
		else if (!bSkipCodeLine && (nReply == PARSER_MUL)) sLine.Append("*");
		else if (!bSkipCodeLine && (nReply == PARSER_DIV)) sLine.Append("/");
		else if (!bSkipCodeLine && (nReply == PARSER_POWER)) sLine.Append("^");
		else if (!bSkipCodeLine && (nReply == PARSER_COLON)) sLine.Append(":");
		else if (!bSkipCodeLine && (nReply == PARSER_COMMA)) sLine.Append(",");
		else if (nReply == PARSER_HASH)
		{
			// pre processor command
			if (sFileContents.ParseNext(sString, nValue, nLine) != PARSER_IDENTIFIER)
			{
				std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": pre-processor command expected after '#'" << std::endl;
				nErrorCount++;
			}
			else if (!bSkipCodeLine && (sString == "include"))
			{
				cString sIncludeFileName, sIncludeFileContents;
				if (sFileContents.ParseNext(sIncludeFileName, nValue, nLine) != PARSER_STRING_QUOTATION_MARK)
				{
					std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": filename in quotation marks expected after pre-processor command #include" << std::endl;
					nErrorCount++;
				}
				else
				{
					ifstream asmFile(sIncludeFileName, ios::binary);
					if (!asmFile.is_open()) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": File not found." << std::endl; nErrorCount++; }
					else
					{
						codeList.AddFileName(sIncludeFileName, 20);
						asmFile >> sIncludeFileContents;
						PreProcessString(codeList, defineList, sIncludeFileContents, nErrorCount);
						if (!sFileName.IsEmpty()) codeList.AddFileName(sFileName, 20); // repeat last filename 
					}
				}
			}
			else if (!bSkipCodeLine && (sString == "define"))
			{
				cString sIdentifier, sReplaceText(""), sReplacement;
				if (sFileContents.ParseNext(sIdentifier, nValue, nLine) != PARSER_IDENTIFIER) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": identifer expected after pre-processor command #define" << std::endl; nErrorCount++; }
				else
				{
					int nErrorCountStart = nErrorCount;
					while (true)
					{
						nReply = sFileContents.ParseNext(sString, nValue, nLine);
						if ((nReply == PARSER_END_OF_LINE) || (nReply == PARSER_END_OF_STRING)) break;
						else if (nReply == PARSER_STRING_QUOTATION_MARK) { sReplaceText.Append("\""); sReplaceText.Append(sString); sReplaceText.Append("\""); }
						else if (nReply == PARSER_LEFT_PARENTHESIS) sReplaceText.Append("(");
						else if (nReply == PARSER_RIGHT_PARENTHESIS) sReplaceText.Append(")");
						else if (nReply == PARSER_RIGHT_PARENTHESIS) sReplaceText.Append(")");
						else if (nReply == PARSER_EQUAL) sReplaceText.Append("=");
						else if (nReply == PARSER_PLUS) sReplaceText.Append("+");
						else if (nReply == PARSER_MINUS) sReplaceText.Append("-");
						else if (nReply == PARSER_MUL) sReplaceText.Append("*");
						else if (nReply == PARSER_DIV) sReplaceText.Append("/");
						else if (nReply == PARSER_POWER) sReplaceText.Append("^");
						else if (nReply == PARSER_COLON) sReplaceText.Append(":");
						else if (nReply == PARSER_COMMA) sReplaceText.Append(",");
						else if (nReply == PARSER_HASH) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": '#' within pre-processor command not supported" << std::endl; nErrorCount++; break; }
						else if (nReply == PARSER_ADDRESS_LABEL) 
						{ 
							// check for any #define
							if (defineList.GetDefine(sString, sReplacement)) { sReplaceText.Append(" "); sReplaceText.Append(sReplacement); sReplaceText.Append(": "); }
							else { sReplaceText.Append(" "); sReplaceText.Append(sString); sReplaceText.Append(": "); }
						}
						else if (nReply == PARSER_IDENTIFIER)
						{
							// check for any #define
							if (defineList.GetDefine(sString, sReplacement)) { sReplaceText.Append(" "); sReplaceText.Append(sReplacement); sReplaceText.Append(" "); }
							else { sReplaceText.Append(" "); sReplaceText.Append(sString); sReplaceText.Append(" "); }
						}
						else if (nReply == PARSER_VALUE) { sReplaceText.Append(" $"); sReplaceText.Append(nValue, 16, 0); sReplaceText.Append(" "); }
						else if (nReply == PARSER_UNKNOWN_CHAR) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": unsupported char '" << (char)nValue << "'" << std::endl; nErrorCount++; break; }
					}
					if (nErrorCount == nErrorCountStart)
					{
						// no additoinal errors
						defineList.AddDefine(sIdentifier, sReplaceText);
					}
				}
			}
			else if (sString == "ifdef")
			{
				cString sIdentifier;
				if (sFileContents.ParseNext(sIdentifier, nValue, nLine) != PARSER_IDENTIFIER) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": identifer expected after pre-processor command #ifdef" << std::endl; nErrorCount++; }
				else
				{
					cString sDummy;
					// check for any #define
					if (defineList.GetDefine(sIdentifier, sDummy)) { defineStack.Push(sIdentifier, false); bSkipCodeLine = false; }
					else { defineStack.Push(sIdentifier, true); bSkipCodeLine = true; }
				}
			}
			else if (sString == "ifndef")
			{
				cString sIdentifier;
				if (sFileContents.ParseNext(sIdentifier, nValue, nLine) != PARSER_IDENTIFIER) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": identifer expected after pre-processor command #ifdef" << std::endl; nErrorCount++; }
				else
				{
					cString sDummy;
					// check for any #define
					if (defineList.GetDefine(sIdentifier, sDummy)) { defineStack.Push(sIdentifier, true); bSkipCodeLine = true; }
					else { defineStack.Push(sIdentifier, false); bSkipCodeLine = false; }
				}
			}
			else if (sString == "else")
			{
				if (!defineStack.SetSkipLine(!bSkipCodeLine)) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": unexpected #else." << std::endl; nErrorCount++; }
				else bSkipCodeLine = !bSkipCodeLine;
			}
			else if (sString == "endif")
			{
				if (!defineStack.Pop()) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": unexpected #endif." << std::endl; nErrorCount++; }
				if (!defineStack.GetSkipLine(bSkipCodeLine)) { bSkipCodeLine = false; }
			}
			else if (!bSkipCodeLine)
			{ 
				std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": unknown pre-processor command" << std::endl; 
				nErrorCount++; 
				// skip rest of the line

			}
		}
		else if (!bSkipCodeLine && (nReply == PARSER_ADDRESS_LABEL)) { sLine.Append(" "); sLine += sString; sLine.Append(": "); bAddressLabel = true; }
		else if (!bSkipCodeLine && (nReply == PARSER_IDENTIFIER))
		{
			// check for any #define
			cString sReplacement;
			sLine.Append(" ");
			if (defineList.GetDefine(sString, sReplacement)) sLine += sReplacement;
			else sLine += sString;
			sLine.Append(" ");
		}
		else if (!bSkipCodeLine && (nReply == PARSER_VALUE)) { sLine.Append(" $"); sLine.Append(nValue, 16, 0); sLine.Append(" "); }
		else if (!bSkipCodeLine && (nReply == PARSER_UNKNOWN_CHAR)) { std::cerr << "\"" << sFileName << "\" Error in line " << nLine << ": unsupported char '" << (char)nValue << "'" << std::endl; nErrorCount++; }
		else if (nReply == PARSER_END_OF_LINE)
		{
			if (!sLine.IsEmpty()) 
			{
				sLine.ReduceSpaces();
				if (!bAddressLabel) sLine.Insert("  ", 0); // do some pretty printing
				codeList.AddLine(sLine, nLine - 1); 
				bAddressLabel = false;
				sLine = "";
			}
		}
	}
}

int main(int argc, char** argv)
{
    class cInstructionList instructionList;
    class cIdentifierList identifierList;
	bool bGenerateIntermediateFile = false;
	bool bGenerateLogFile = false;
	bool bGenerateCFile = false;
	bool bGenerateROMFiles = false;
	instructionList.SetMachine(MACHINE_TM02, "TM02");
	std::cout << "Copyright (C) 2024 Analog Devices Inc. All Rights Reserved." << std::endl;
	std::cout << "This software is proprietary to Analog Devices, Inc. and its licensors." << std::endl;
    std::cout << "pelican_asm: assembler for the pelican processor, version " << PELICAN_ASM_VERSION << std::endl;
	std::cout << "(build: " << __DATE__ << " " << __TIME__ << ")" << std::endl;
	int nArgument = 1;
	bool bFileNameFound = false;
	cString sFileName;
	// default machine type is TM02
	instructionList.SetMachine(MACHINE_TM02, "TM02");
	while (nArgument < argc)
	{
		if ((argv[nArgument][0] == '-') && (argv[nArgument][1] == 'i') && (argv[nArgument][2] == 0))
		{
			// -i option - generate additional intermediate / pre-processor output file
			bGenerateIntermediateFile = true;
		}
		else if ((argv[nArgument][0] == '-') && (argv[nArgument][1] == 'l') && (argv[nArgument][2] == 0))
		{
			// -l option - generate log output file
			bGenerateLogFile = true;

		}
		else if ((argv[nArgument][0] == '-') && (argv[nArgument][1] == 'c') && (argv[nArgument][2] == 0))
		{
			// -c option - generate c code output file
			bGenerateCFile = true;

		}
		else if ((argv[nArgument][0] == '-') && (argv[nArgument][1] == 'm') && (argv[nArgument][2] == 0))
		{
			// -m or -M option / definition of machine architecture
			nArgument++;
			if (nArgument < (argc - 1))
			{
				cString sArg(argv[nArgument]);
				if (sArg.CompareNoCase("TM02")) instructionList.SetMachine(MACHINE_TM02, "TM02");
				else if (sArg.CompareNoCase("TM10")) instructionList.SetMachine(MACHINE_TM10, "TM10");
				else
				{
					std::cerr << "Error: Unknown machine type \"" << argv[nArgument] << "\"" << std::endl;
					return 0;
				}
			}
			else
			{
				std::cerr << "Error: Missing argument for parameter -" << argv[nArgument - 1][1] << std::endl;
				return 0;
			}
		}
		else if ((argv[nArgument][0] == '-') && (argv[nArgument][1] == 'r') && (argv[nArgument][2] == 'o') && (argv[nArgument][3] == 'm') && (argv[nArgument][4] == 0))
		{
			// -rom option - generate additional output files "pelican_bootloader"
			bGenerateROMFiles = true;
		}
		else if ((argv[nArgument][0] == '-') && (argv[nArgument][1] == 'h') && (argv[nArgument][2] == 0))
		{
			// -h option / help
			CommandLineHelp();
			return 0;
		}
		else if (bFileNameFound == false)
		{
			// filename
			bFileNameFound = true;
			sFileName = argv[nArgument];
		}
		else
		{
			std::cerr << "Error: More than one file name is not supported or unknown argument \"" << argv[nArgument] << "\"" << std::endl;
			return 0;
		}
		nArgument++;
	}
	if (bFileNameFound == false)
	{
		std::cerr << "Error: Input file name missing" << std::endl;
		return 0;
	}

	std::cout << "Info: Selected machine type: " << instructionList.GetMachineName() << std::endl;

	// try to open input file
	ifstream asmFile(sFileName, ios::binary); // binary is important here as otherwise we do not get the file size estimation right
	if (!asmFile.is_open())
	{
		// could not open file, try with .asm extension
		sFileName += ".asm";
		asmFile.open(sFileName, ios::binary);
		if (!asmFile.is_open())
		{
			std::cout << "Error: Could not open file." << std::endl;
			return 0;
		}
	}
	std::cout << "Info: Input file name: \"" << sFileName << "\"." << std::endl;
	// input asm file
	cString sFileContents;
	asmFile >> sFileContents;
	asmFile.close();

	// pre-processor
	std::cout << "Info: Pre-processor running ..." << std::endl;
	int nErrorCount = 0;
	cDefineList defineList;
	cSourceCodeLineList codeList;
	cString sLine;
	int nLine;
	bool bFileName;

	int nLastIndex = sFileName.Length() - 1;
	cString sFileNameWithoutExtension;
	if ((nLastIndex >= 3) && (sFileName[nLastIndex] == 'm') && (sFileName[nLastIndex - 1] == 's') && (sFileName[nLastIndex - 2] == 'a') && (sFileName[nLastIndex - 3] == '.'))
	{
		sFileNameWithoutExtension = sFileName.GetLeft(nLastIndex - 3);
	}
	else sFileNameWithoutExtension = sFileName;
	codeList.AddFileName(sFileName, 20);
	PreProcessString(codeList, defineList, sFileContents, nErrorCount);
	if (bGenerateIntermediateFile)
	{
		// generate intermediate output file for debug purposes ... <filename>.i
		ofstream intermediateFile;
		intermediateFile.open(sFileNameWithoutExtension + ".i");
		if (intermediateFile.is_open())
		{
			codeList.ResetGetNextLine();
			while (codeList.GetNextLine(sLine, nLine, bFileName))
			{
				if (bFileName) intermediateFile << ";<<<< file: \"" << sLine << "\" >>>>>" << std::endl;
				else intermediateFile << cString(nLine, 10, 4) + ": " << sLine << std::endl;
			}
			intermediateFile.close();
			std::cout << "Info: Pre-processor output file: \"" << sFileNameWithoutExtension << ".i\" generated." << std::endl;
		}
	}

	if (nErrorCount)
	{
		std::cerr << "Pre-processor reported " << nErrorCount << (nErrorCount == 1 ? " Error" : " Errors") << ". No output generated. Code generation stopped." << std::endl;
		return 0;
	}

	// assembler
	std::cout << "Info: Assembler running ..." << std::endl;
	identifierList.SetMessageOutput(&std::cerr);
	instructionList.SetMessageOutput(&std::cerr);
	int nValue;
	int nPass = 0;
	int nAddress = 0;
	cString sString, sCurrentFileName;
	int nReply;
	while (nPass < 2)
	{
		nLine = 1;  nAddress = 0; nErrorCount = 0; codeList.ResetGetNextLine(); // reset counters ...
		identifierList.SetPass(nPass);
		while (codeList.GetNextLine(sLine, nLine, bFileName))
		{
			if (bFileName) { sCurrentFileName = sLine; continue; }
			identifierList.SetLine(nLine);
			identifierList.SetFileName(sCurrentFileName);
			instructionList.SetLine(nLine);
			instructionList.SetFileName(sCurrentFileName);
			// expect one command per line
			nReply = sLine.ParseNext(sString, nValue, nLine);
			if (nReply == PARSER_IDENTIFIER)
			{
				// either instruction or identifier
				if (instructionList.IsInstr(sString))
				{
					// instruction
					cString sInstruction = sString;
					cString sAddOn;
					if (instructionList.IsInstrAddOn(sInstruction)) nReply = sLine.ParseNext(sAddOn, nValue, nLine); // get second part of instruction name
					if (instructionList.IsInstr(sInstruction, sAddOn))
					{
						int nParameterCount = instructionList.GetParameterCount(sInstruction, sAddOn); // get number of parameters
						int nParameterIndex = 0;
						cString sParameter[3];
						int nParameter[3];
						int nReturn = EVALUATION_OK;
						int nReturnTemp;
						bool bParameterFound;
						while (nParameterIndex < nParameterCount) // get parameter
						{
							bParameterFound = false;
							sParameter[nParameterIndex] = "";
							while (true)
							{
								nReply = sLine.ParseNext(sString, nValue, nLine);
								if (nReply == PARSER_LEFT_PARENTHESIS) sParameter[nParameterIndex].Append("(");
								else if (nReply == PARSER_RIGHT_PARENTHESIS) sParameter[nParameterIndex].Append(")");
								else if (nReply == PARSER_EQUAL)
								{
									std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": unexpected '='." << std::endl;
									nReturn = EVALUATION_SYNTAX_ERROR;
									nErrorCount++;
								}
								else if (nReply == PARSER_PLUS) sParameter[nParameterIndex].Append("+");
								else if (nReply == PARSER_MINUS) sParameter[nParameterIndex].Append("-");
								else if (nReply == PARSER_MUL) sParameter[nParameterIndex].Append("*");
								else if (nReply == PARSER_DIV) sParameter[nParameterIndex].Append("/");
								else if (nReply == PARSER_POWER) sParameter[nParameterIndex].Append("^");
								else if (nReply == PARSER_IDENTIFIER)
								{
									sParameter[nParameterIndex].Append(" "); sParameter[nParameterIndex].Append(sString); sParameter[nParameterIndex].Append(" ");
									bParameterFound = true;
								}
								else if (nReply == PARSER_VALUE)
								{
									sParameter[nParameterIndex].Append(" $"); sParameter[nParameterIndex].Append(nValue, 16, 0); sParameter[nParameterIndex].Append(" ");
									bParameterFound = true;
								}
								else if (nReply == PARSER_COMMA)
								{
									if (!bParameterFound)
									{
										// end of parameter but no parameter found
										std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": no valid parameter before ','." << std::endl;
										nReturn = EVALUATION_SYNTAX_ERROR;
										nErrorCount++;
										goto PARAMETER_COLLECTED;
									}
									else if (nParameterIndex == (nParameterCount - 1))
									{
										// no more parameter expected
										identifierList.EvaluateExpression(sParameter[nParameterIndex], nParameter[nParameterIndex]);
										std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": unexpected ',' after last parameter." << std::endl;
										nReturn = EVALUATION_SYNTAX_ERROR;
										nErrorCount++;
										goto PARAMETER_COLLECTED;
									}
									else
									{
										// more parameter expected
										nReturnTemp = identifierList.EvaluateExpression(sParameter[nParameterIndex], nParameter[nParameterIndex]);
										if ((nPass == 0) && (nReturnTemp == EVALUATION_SYNTAX_ERROR)) nErrorCount++;
										if ((nPass == 1) && (nReturnTemp != EVALUATION_OK)) nErrorCount++;
										if (nReturn == EVALUATION_OK) nReturn = nReturnTemp;
										break;
									}
								}
								else if ((nReply == PARSER_END_OF_LINE) || (nReply == PARSER_END_OF_STRING))
								{
									if (!bParameterFound || (nParameterIndex < (nParameterCount - 1)))
									{
										// either invalid parameter or more parameter expected
										std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": missing / invalid parameter." << std::endl;
										nReturn = EVALUATION_SYNTAX_ERROR;
										nErrorCount++;
									}
									else
									{
										// last parameter
										nReturnTemp = identifierList.EvaluateExpression(sParameter[nParameterIndex], nParameter[nParameterIndex]);
										if ((nPass == 0) && (nReturnTemp == EVALUATION_SYNTAX_ERROR)) nErrorCount++;
										if ((nPass == 1) && (nReturnTemp != EVALUATION_OK)) nErrorCount++;
										if (nReturn == EVALUATION_OK) nReturn = nReturnTemp;
									}
									goto PARAMETER_COLLECTED;
								}
							}
							nParameterIndex++;
						}
					PARAMETER_COLLECTED:
						if ((nPass == 1) && (nReturn == EVALUATION_OK))
						{
							// add to instruction list
							if (instructionList.AddInstr(nLine, sLine, sInstruction, nAddress, sAddOn, nParameter)) codeList.SetInstructionLastLine(true);
							else nErrorCount++;
						}
						nAddress++;
					}
					else
					{
						std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": unknown 2nd part of instruction " << sInstruction << " " << sAddOn << std::endl;
						nErrorCount++;
					}
				}
				else
				{
					// has to be identifier - search for '='
					cString sIdentifier = sString;
					if (sLine.ParseNext(sString, nValue, nLine) == PARSER_EQUAL)
					{
						// fetch value
						bool bValueFound = false;
						cString sValue("");
						while (true)
						{
							nReply = sLine.ParseNext(sString, nValue, nLine);
							if (nReply == PARSER_LEFT_PARENTHESIS) sValue.Append("(");
							else if (nReply == PARSER_RIGHT_PARENTHESIS) sValue.Append(")");
							else if (nReply == PARSER_PLUS) sValue.Append("+");
							else if (nReply == PARSER_MINUS) sValue.Append("-");
							else if (nReply == PARSER_MUL) sValue.Append("*");
							else if (nReply == PARSER_DIV) sValue.Append("/");
							else if (nReply == PARSER_POWER) sValue.Append("^");
							else if (nReply == PARSER_IDENTIFIER)
							{
								sValue.Append(" "); sValue.Append(sString); sValue.Append(" ");
								bValueFound = true;
							}
							else if (nReply == PARSER_VALUE)
							{
								sValue.Append(" $"); sValue.Append(nValue, 16, 0); sValue.Append(" ");
								bValueFound = true;
							}
							else if ((nReply == PARSER_END_OF_LINE) || (nReply == PARSER_END_OF_STRING)) break;
							else
							{
								std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": unexpected character assigned." << std::endl;
								nErrorCount++; break;
							}
						}
						if (!bValueFound)
						{
							// end of parameter but no parameter found
							std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": no valid parameter assigned." << std::endl;
							nErrorCount++;
						}
						nReply = identifierList.EvaluateExpression(sValue, nValue);
						if ((nPass == 0) && (nReply == EVALUATION_SYNTAX_ERROR)) nErrorCount++;
						if ((nPass == 1) && (nReply != EVALUATION_OK)) nErrorCount++;
						if (nReply == EVALUATION_OK)
						{
							if (!identifierList.AddIdentifier(sIdentifier, nValue)) nErrorCount++;
						}
					}
					else
					{
						std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": assignment operator \"=\" expected after identifier " << sIdentifier << "." << std::endl;
						nErrorCount++;
					}
				}
			}
			else if (nReply == PARSER_ADDRESS_LABEL)
			{
				// address label
				if (!identifierList.AddIdentifier(sString, nAddress)) nErrorCount++;
			}
			else
			{
				std::cerr << "\"" << sCurrentFileName << "\" Error in line " << nLine << ": unexpected character at start of line." << std::endl; nErrorCount++;
			}
		}
		if (nErrorCount)
		{
			std::cerr << nErrorCount << (nErrorCount == 1 ? " Error" : " Errors") << " during pass " << nPass + 1 << ". No output generated. Assembler stopped." << std::endl;
			return 0;
		}
		nPass++;
	}
	std::cout << "Info: code generation successful. Instruction count: " << nAddress << " (" << setprecision(2) << (float)nAddress / 2048 * 100 << "% of 2Kx16 program memory)" << std::endl;
	int nInstrCount = nAddress;

	if (bGenerateLogFile)
	{
		// log file
		ofstream logFile;
		logFile.open(sFileNameWithoutExtension + ".log");
		if (logFile.is_open())
		{
			int nLine, nInstrLine, nAddress, nCode, nParameterCount, nParameter[3];
			bool bInstruction;
			cString sCmd, sCmdAddOn, sLine, sLogLine, sParam1, sParam2, sParam3;
			codeList.ResetGetNextLine();
			instructionList.ResetInstrList();
			nLine = 1; nInstrLine = 0;
			while (codeList.GetNextLine(sLine, nLine, bFileName, bInstruction))
			{
				if (bFileName)
				{
					logFile << ";<<<< file: \"" << sLine << "\" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
				}
				else
				{
					sLine.ReduceSpaces();
					sLogLine = cString(nLine, 10, 4) + ": ";
					if (bInstruction)
					{
						instructionList.GetNextInstr(nInstrLine, nAddress, nCode, sCmd, sCmdAddOn, nParameterCount, nParameter);
						sLogLine += "@0x" + cString(nAddress, 16, 4) + " 0x" + cString(nCode, 16, 4) + " " + sCmd + " ";
						if (sCmdAddOn.Length()) sLogLine += sCmdAddOn + " ";
						if (nParameterCount > 0) sLogLine += cString(nParameter[0], 10, 0);
						if (nParameterCount > 1) sLogLine += ", " + cString(nParameter[1], 10, 0);
						if (nParameterCount > 2) sLogLine += ", " + cString(nParameter[2], 10, 0);
					}
					sLogLine.Width(50, true);
					logFile << sLogLine << sLine << endl;
				}
			}
			logFile << endl << "; List of identifiers with values:" << endl << "; ================================" << endl;
			// list identifier
			cString sIdentifier;
			int nValue;
			bool bValid;
			identifierList.ResetIdentifierList();
			while (identifierList.GetNextIdentifier(sIdentifier, nValue, bValid))
			{
				logFile << "; " << sIdentifier << " = 0x" << cString(nValue, 16, 0) << "(" << nValue << ")";
				if (bValid) logFile << " (valid)" << endl;
				else logFile << " (invalid)" << endl;
			}
			logFile.close();
			cout << "Info: log file \"" << sFileNameWithoutExtension << ".log\" generated." << endl;
		}
		else
		{
			cout << "Error: could not open output log file " << sFileNameWithoutExtension << ".log." << endl;
			return 0;
		}
	}

	if (bGenerateCFile)
	{
		// c code file
		ofstream cCodeFile;
		cCodeFile.open(sFileNameWithoutExtension + ".c");
		if (cCodeFile.is_open())
		{
			char sTime[255];
			time_t currentTime = time(NULL);
			ctime_s(sTime, 255, &currentTime);
			cCodeFile << "/*******************************************************************************" << endl;
			cCodeFile << "* Copyright (C) 2024 Analog Devices Inc. All Rights Reserved." << endl;
			cCodeFile << "* This software is proprietary to Analog Devices, Inc. and its licensors." << endl;
			cCodeFile << "********************************************************************************" << endl;
			cCodeFile << "* This file has been generated automatically on " << sTime;
			cCodeFile << "* Generator: pelican_asm.exe (build: " << __DATE__ << " " << __TIME__ << ")" << endl;
			cCodeFile << "********************************************************************************" << endl;
			cCodeFile << "* source file: \"" << sFileName << endl;
			cCodeFile << "********************************************************************************" << endl;
			cCodeFile << "* Notes:" << endl;
			cCodeFile << "*   - The array nProgramCodeArray contains the program code starting" << endl;
			cCodeFile << "*     at program memory address zero with one byte per value / two bytes" << endl;
			cCodeFile << "*     per instruction" << endl;
			cCodeFile << "*   - Each instruction consists of two consecutive bytes in the array," << endl;
			cCodeFile << "*     LSB first and then MSB" << endl;
			cCodeFile << "*   - Number of bytes in nProgramCodeArray is nProgramCodeArraySize" << endl;
			cCodeFile << "*   - Number of instructions is nProgramCodeArraySize / 2" << endl;
			cCodeFile << "*******************************************************************************/" << endl;
			cCodeFile << endl;
			cCodeFile << "static int nProgramCodeArraySize = " << nInstrCount * 2 << ";" << endl;
			cCodeFile << "static unsigned char nProgramCodeArray[" << nInstrCount * 2 << "] = {" << endl;
			instructionList.ResetInstrList();
			int nAddress, nNextAddress = 0, nCode, nBytes = 0;
			uint8_t nChecksum = 0;
			cString sLine;
			while (instructionList.GetNextInstr(nAddress, nCode))
			{
				if (nBytes == 16)
				{
					// next line
					cCodeFile << "," << endl;
					nBytes = 0; // reset byte counter
				}
				if (nBytes == 0)
				{
					// insert spaces for better readability
					cCodeFile << "    ";
				}
				else
				{
					// nBytes != 0 -> not the first entry in a row
					cCodeFile << ", ";
				}
				cCodeFile << "0x" << cString(nCode & 0xff, 16, 2) << ", 0x" << cString((nCode >> 8) & 0xff, 16, 2);
				nBytes += 2;
			}
			cCodeFile << endl;
			cCodeFile << "};" << endl;
			cCodeFile.close();
			cout << "Info: C code output file \"" << sFileNameWithoutExtension << ".c\" generated." << endl;
		}
		else
		{
			cout << "Error: could not open C code output file " << sFileNameWithoutExtension << ".c." << endl;
			return 0;
		}
	}


	// intel hex file - always generated
	ofstream intelhexFile;
	intelhexFile.open(sFileNameWithoutExtension + ".hex");
	if (intelhexFile.is_open())
	{
		instructionList.ResetInstrList();
		int nAddress, nNextAddress = 0, nCode, nBytes = 0;
		int nByteAddress;
		uint8_t nChecksum = 0;
		cString sLine;
 		while (instructionList.GetNextInstr(nAddress, nCode))
		{
			if (((nAddress != nNextAddress) && nBytes) || (nBytes == 16))
			{
				// write last line
				// add number of bytes to checksum
				nChecksum += nBytes;
				nChecksum = ~nChecksum + 1;
				intelhexFile << ":" << cString(nBytes, 16, 2) << sLine << cString(nChecksum & 0xff, 16, 2) << endl;
				nBytes = 0; // reset byte counter
			}
			if (nBytes == 0)
			{
				// new line, start with address, for intel hex format use byte address and not word (16bit) address
				nByteAddress = nAddress * 2;
				sLine = cString(nByteAddress, 16, 4) + "00"; // "00" is data record
				nChecksum = ((nByteAddress >> 8) & 0xff) + (nByteAddress & 0xff);
			}
			sLine += cString(nCode & 0xff, 16, 2) + cString((nCode >> 8) & 0xff, 16, 2);
			nChecksum += (nCode & 0xff) + ((nCode >> 8) & 0xff);
			nBytes += 2;
			nNextAddress = nAddress + 1;
		}
		if (nBytes)
		{
			// write remaining bytes / last line
			// add number of bytes to checksum
			nChecksum += nBytes;
			nChecksum = ~nChecksum + 1;
			intelhexFile << ":" << cString(nBytes, 16, 2) << sLine << cString(nChecksum & 0xff, 16, 2) << endl;
		}
		// write start address record type (start address = 0x0000) "03"
		intelhexFile << ":0400000300000000F9" << endl;
		// write file end record type "01"
		intelhexFile << ":00000001FF" << endl;
		intelhexFile.close();
		cout << "Info: Intel hex format file \"" << sFileNameWithoutExtension << ".hex\" generated." << endl;
	}
	else
	{
		cout << "Error: could not open output intel hex file" << sFileNameWithoutExtension << ".hex." << endl;
	}
	if (bGenerateROMFiles)
	{
		// hex file for ROM - generated with "-rom" option
		ofstream hexFile;
		hexFile.open("pelican_bootloader.hex");
		if (hexFile.is_open())
		{
			instructionList.ResetInstrList();
			int nAddress, nCode, nWords = 0;
			while (instructionList.GetNextInstr(nAddress, nCode))
			{
				//hexFile << cString((nCode >> 8) & 0xff, 16, 2);
				hexFile << cString(nCode, 16, 4);
				hexFile << endl;
				nWords++;
			}
			if (instructionList.GetMachineName() == "TM02")
			{
				while (nWords < 1024)
				{
					hexFile << "FFFF" << endl;
					nWords++;
				}
			}
			else if (instructionList.GetMachineName() == "TM10")
			{
				while (nWords < 2048)
				{
					hexFile << "FFFF" << endl;
					nWords++;
				}
			}
			hexFile.close();
			cout << "Info: ROM hex file \"pelican_bootloader.hex\" generated." << endl;
		}
		else
		{
			cout << "Error: could not open output hex file pelican_bootloader.hex." << endl;
		}
	}

	if (bGenerateROMFiles)
	{
		// bin file for ROM generated with "-rom" option
		ofstream binFile;
		binFile.open("pelican_bootloader.bin");
		if (binFile.is_open())
		{
			instructionList.ResetInstrList();
			int nAddress, nCode, nWords = 0;
			while (instructionList.GetNextInstr(nAddress, nCode))
			{
				binFile << cString(nCode, 2, 16);
				binFile << endl;
				nWords++;
			}
			if (instructionList.GetMachineName() == "TM02")
			{
				while (nWords < 1024)
				{
					binFile << "1111111111111111" << endl;
					nWords++;
				}
			}
			else if (instructionList.GetMachineName() == "TM10")
			{
				while (nWords < 2048)
				{
					binFile << "1111111111111111" << endl;
					nWords++;
				}
			}
			binFile.close();
			cout << "Info: ROM bin file \"pelican_bootloader.bin\" generated." << endl;
		}
		else
		{
			cout << "Error: could not open output bin file pelican_bootloader.bin." << endl;
		}
	}

	if (bGenerateROMFiles)
	{
		// vhdl file - generated with "-rom" option
		ofstream vhdlFile;
		vhdlFile.open("pelican_bootloader.vhd");
		if (vhdlFile.is_open())
		{
			char sTime[255];
			time_t currentTime = time(NULL);
			ctime_s(sTime, 255, &currentTime);
			vhdlFile << "---------------------------------------------------------------------------------------" << endl;
			vhdlFile << "-- Copyright (C) 2024 Analog Devices Inc. All Rights Reserved." << endl;
			vhdlFile << "-- This software is proprietary to Analog Devices, Inc. and its licensors." << endl;
			vhdlFile << "---------------------------------------------------------------------------------------" << endl;
			vhdlFile << "-- This file has been generated automatically on " << sTime;
			vhdlFile << "-- Generator: pelican_asm.exe (build: " << __DATE__ << " " << __TIME__ << ")" << endl;
			vhdlFile << "---------------------------------------------------------------------------------------" << endl;
			vhdlFile << "" << endl;
			vhdlFile << "-- source file: \"" << sFileName << endl;
			instructionList.ResetInstrList();
			codeList.ResetGetNextLine();
			int nLine = 1, nAddress, nCode, nParameterCount, nParameter[3];
			cString sVHDLFileLine, sLine, sCmd, sCmdAddOn;
			bool bInstruction = false;
			while (codeList.GetNextLine(sLine, nLine, bFileName, bInstruction))
			{
				if (bFileName)
				{
					vhdlFile << "-- <<<< file: \"" << sLine << "\" >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
				}
				else if (bInstruction)
				{
					sLine.ReduceSpaces();
					sVHDLFileLine = "-- " + cString(nLine, 10, 4) + ": ";
					if (instructionList.GetNextInstr(nLine, nAddress, nCode, sCmd, sCmdAddOn, nParameterCount, nParameter))
					{
						sVHDLFileLine += "@0x" + cString(nAddress, 16, 4) + " 0x" + cString(nCode, 16, 4) + " " + sCmd + " ";
						if (sCmdAddOn.Length()) sVHDLFileLine += sCmdAddOn + " ";
						if (nParameterCount > 0) sVHDLFileLine += cString(nParameter[0], 10, 0);
						if (nParameterCount > 1) sVHDLFileLine += ", " + cString(nParameter[1], 10, 0);
						if (nParameterCount > 2) sVHDLFileLine += ", " + cString(nParameter[2], 10, 0);
					}
					sVHDLFileLine.Width(50, true);
					vhdlFile << sVHDLFileLine << sLine << endl;
				}
			}
			vhdlFile << "" << endl;
			vhdlFile << "library ieee;" << endl;
			vhdlFile << "use ieee.std_logic_1164.all;" << endl;
			vhdlFile << "use ieee.numeric_std.all;\n" << endl;
			vhdlFile << "entity pelican_bootloader is" << endl;
			vhdlFile << "port (" << endl;
			vhdlFile << "    CLK     : in std_logic;" << endl;
			vhdlFile << "    nRST    : in std_logic;" << endl;
			vhdlFile << "    DOUT    : out std_logic_vector(15 downto 0);" << endl;
			vhdlFile << "    ADDR    : in std_logic_vector(10 downto 0)" << endl;
			vhdlFile << ");" << endl;
			vhdlFile << "end entity pelican_bootloader;\n" << endl;
			vhdlFile << "architecture RTL of pelican_bootloader is" << endl;
			vhdlFile << "    type bootloader_type is array(0 to 2047) of std_logic_vector(15 downto 0);" << endl;
			vhdlFile << "    signal bootloader : bootloader_type;\n" << endl;
			// instruction list end
			// fill rest of array with zeros
			vhdlFile << "begin" << endl;
			vhdlFile << "    -- initialize memory" << endl << "    ";
			instructionList.ResetInstrList();
			int nCounter = 0;
			while (instructionList.GetNextInstr(nAddress, nCode))
			{
				vhdlFile << "bootloader(" << dec << nAddress << ") <= x\"" << cString(nCode, 16, 4) << "\"; ";
				if (nCounter % 8 == 7)	vhdlFile << endl << "    ";
				nCounter++;
			}
			vhdlFile << endl << "    -- fill unused memory with zeros" << endl << "    ";
			if (nCounter == 0) nAddress = 0;	// file does not contain any instructions
			else { nCounter = 0; nAddress++; }
			while (nAddress < 2048)
			{
				vhdlFile << "bootloader(" << dec << nAddress << ") <= x\"0000\"; ";
				if (nCounter % 8 == 7) vhdlFile << endl << "    ";
				nCounter++; nAddress++;
			}
			vhdlFile << "\n    -- instruction fetch / memory read access" << endl;
			vhdlFile << "    process (CLK, nRST)" << endl;
			vhdlFile << "    begin" << endl;
			vhdlFile << "        if nRST = '0' then" << endl;
			vhdlFile << "            DOUT <= x\"0000\";" << endl;
			vhdlFile << "        elsif Rising_edge(CLK) then" << endl;
			vhdlFile << "            DOUT <= bootloader(to_integer(unsigned(ADDR)));" << endl;
			vhdlFile << "        end if;" << endl;
			vhdlFile << "    end process;" << endl;
			vhdlFile << "end architecture RTL;\n" << endl;
			vhdlFile.close();
			cout << "Info: vhdl file \"pelican_bootloader.vhd\" generated." << endl;
		}
		else
		{
			cout << "Error: could not open output VHDL file pelican_bootloader.vhd." << endl;
		}
	}
	return 0;
}
