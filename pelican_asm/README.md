# pelican_asm.exe

This is the assembler for the 8-Bit RISC processor inside [TMC8100](https://www.analog.com/en/products/tmc8100.html) and TMC6460. It has been written in C++ and compiled as PC Windows command line executable (*.exe). As command line parameter the assembler source file is expected. From this input file the assembler will generate the output file in hex file format - using the same file name but with the extension ".hex".

The assembler supports a number of flags / options:

    pelican_asm.exe <file_name>[.asm] [-m|M TMC8100|TMC6460] [-i] [-l] [-c] [-h]
                    <file_name>[.asm]: input ASCII text file
                 [-m TMC8100|TMC6460]: machine type - either TMC8100 (default) or TMC6460
                                 [-i]: generate intermediate / pre-processor output file
                                 [-l]: generate log file
                                 [-c]: generate C code file
                                 [-h]: help
    output files:
      <file_name>.hex: intel hex format file
      <file_name>.i (requires -i): intermediate file - merged input files with all pre-processor commands #.. removed
      <file_name>.log (requires -l): log file - input file contents + instruction code / memory address
      <file_name>.c (requires -c): C language source file - C-array with instruction code


## Pre-Processor Syntax
### Comments
The pre-processor within pelican_asm is executed first and will remove all comments from the input file(s). Currently, the following options for comments are supported:

* `/* <comment> */` - block comments - can include more than one line (C-language style)
* `// <comment>` - comment until end of line (C/C++ - language style)
* `; <comment>` - comment until end of line (assembly file style)

### #include
`#include "<filename>"`

The file `<filename>` will be inserted at the position of the #include pre-processor directive. The line with the #include directive will be removed. 

Please note: only quotation marks are allowed and there should be no other commands / assignments within this line as they will be removed / ignored from further processing

### #define
`#define <label> <replacement text>`

The pre-processor will replace any `<label>` found in the source file (+ files included with the #include statement) after this define statement with `<replacement text>`. `<replacement text>` has to be separated with at least one space from `<label>` and will include all text until end of line (or start of comment). Only comments and text in quotation marks will be excluded from replacement. Label(s) maybe be re-defined afterwards in the source file using another #define with the same `<label>` name.

### #ifdef, #ifndef, #else, #endif
`#ifdef <label> <code block 1> #else <code block 2> #endif`

In case `<label>` has been defined before contents of`<code block 1>` will be interpreted and assembler output generated and `<code block 2>` will be skipped / ignored. The intermediate file `<filename>.i` will just show `<code block 1>` and not `<code block 2>`. The code blocks may contain several lines of assembler instructions etc. In case `<label>` has not been defined it will be the other way round.

`#ifndef <label> <code block 1> #else <code block 2> #endif`

In case `<label>` has been defined before the contents of `<code block 2>` will be interpreted and assembler output generated and `<code block 1>` will be ignored. The intermediate file `<filename>.i` will just show `<code block 2>` and not `<code block 1>`. The code blocks may contain several lines of assembler instructions etc. In case `<label>` has not been defined it will be the other way round.

Please note that it is sufficient to mention the `<label>` name before using `#define <label>` - it is not necessary to actually assign a value / text.

The #else part is optional. #ifdef or #ifndef blocks maybe nested.

## Assembler Syntax

The assembler currently supports all instructions available for TMC8100 and also the additional commands for TMC6460 (with the machine flag -m TMC6460).

### Numbers
In order to simplify specification of numbers as binary, decimal and hexadecimal different formats are supported:

* 0x123.. or $123.. are interpreted as hexadecimal numbers (character expected: 0-9, a-f or A-F)
* %1010.. is interpreted as binary number (characters expected: 0 and 1). The character '_' may be inserted for better readability - e.g. %1010_0011 for an 8-bit number
* 123.. is interpreted as decimal number (characters expected: 0-9)

### Identifiers
Identifiers may be used for better readability instead of numbers. Identifiers have to start with a letter (a-z / A-Z) or '_'. As second character and beyond numbers are allowed (0-9). Please note that character names are not case sensitive.

Identifier may be assigned a value using the equal sign - e.g.:

	BOOTLOADER_VERSION = $b4

Some names should not be used as identifiers:

* assembly instructions - this includes the assembly instructon names preceded with a 'C' - indicating conditional execution of the command immediately following the 'C'.
* Identifier r0..r7 have pre-defined values (0..7) for specifying all general purpose registers available
* address labels and identifiers should not have the same name

### Address Labels
Address labels are used as placeholders for program memory addresses. The program memory address will be assigned automatically during code assemmbly to the label.

Example for an endless loop:

	WAIT:
	  JA WAIT

Please note the ':' character after the label name. The assembler will automatically initialize the label WAIT with the program memory address of the next instruction - which in this case is the JA WAIT command. Jump backs (as shown above) where the label is initialized before it is used inside a command and jump forwards - where the label is initialized after it is used inside the command - are both supported.

## Source Code
pelican_asm has been compiled using MinGW toolchain on PC Windows environment together with VSCode editor.

1. Install Visual Studio Code
2. Follow tutorial [Using GCC with MinGW](https://code.visualstudio.com/docs/cpp/config-mingw)
3. modify .vscode/tasks.json to include all *.cpp files (after tutorial) - e.g.:

```
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: g++.exe build active file",
            "command": "C:\\msys64\\ucrt64\\bin\\g++.exe",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${workspaceFolder}\\globals.cpp",
                "${workspaceFolder}\\identifiers.cpp",
                "${workspaceFolder}\\instructions.cpp",
                "${workspaceFolder}\\stack.cpp",
                "${workspaceFolder}\\pelican_asm.cpp",
                "-o",
                "${fileDirname}\\${fileBasenameNoExtension}.exe"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Task generated by Debugger."
        }
    ],
    "version": "2.0.0"
}
```