/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Spring, 2024
* Author: Ruan Simo
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "    @@                             @@    �
# ECHO "    @@           %&@@@@@@@@@@@     @@    �
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    �
# ECHO "    @@      @& @   @ @       @     @@    �
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    �
# ECHO "    @@      & @ @  @@              @@    �
# ECHO "    @@       @/ @*@ @ @   @        @@    �
# ECHO "    @@           @@@@  @@ @ @      @@    �
# ECHO "    @@            /@@    @@@ @     @@    �
# ECHO "    @@     @      / /     @@ @     @@    �
# ECHO "    @@     @ @@   /@/   @@@ @      @@    �
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@         RUANSCRIPT           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Compilers.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12, A22, A32.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/*
 * ............................................................................
 * ADVICE 1:
 * Please check the "TODO" labels to develop your activity.
 *
 * ADVICE 2: This file must be updated according to each assignment
 * (see the progression: reader > scanner > parser).
 * ............................................................................
 */

/* TO_DO: Adjust your language (cannot be "sofia") */

/* Language name */
#define STR_LANGNAME	"RuanScript"

/* Logical constants - adapt for your language */
#define TRUE  1
#define FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/


/* TO_DO: Define your typedefs */
// typedef char			Rs_char;
// typedef char*			Rs_string;
// typedef int				  Rs_intg;
// typedef float			Rs_real;
// typedef void			Rs_void;

// typedef unsigned char	Rs_boln;
// typedef unsigned char	Rs_byte;

// typedef long			Rs_long;
// typedef double			Rs_doub;

/* TO_DO: Define your typedefs */
typedef char            Rs_char;      // Represents a single character (no direct equivalent in JavaScript, typically a string of length 1)
typedef char*           Rs_string;    // Represents JavaScript's String type
typedef double          Rs_number;    // Represents JavaScript's Number type (handles both integer and floating-point numbers)
typedef unsigned char   Rs_boln;      // Represents JavaScript's Boolean type
typedef unsigned char   Rs_byte;      // Represents a byte 
typedef long long       Rs_long;      // Represents JavaScript's Bigint type (for large integers)

typedef void*           Rs_undefined; // Represents JavaScript's Undefined type
typedef void*           Rs_null;      // Represents JavaScript's Null type

typedef int             Rs_intg;      // Specific integer type (part of the JavaScript Number type)
typedef float           Rs_float;     // Specific float type (part of the JavaScript Number type)
typedef double          Rs_double;    // Specific double type (part of the JavaScript Number type)
typedef void            Rs_void;      // Represents the absence of type (similar to undefined in JavaScript functions)


/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'r',
	PGM_SCANNER = 's',
	PGM_PARSER	= 'p'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
Rs_intg mainReader(Rs_intg argc, Rs_string* argv);

/* 
TO_DO: Include later mainScaner (A22) and mainParser (A32)
*/
Rs_void printLogo();

#endif
