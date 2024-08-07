/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Fall, 2023
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
=---------------------------------------=
|  COMPILERS - ALGONQUIN COLLEGE (F23)  |
=---------------------------------------=
|              ....                     |
|          ........::.::::::.           |
|        .:........::.:^^^~~~:          |
|        :^^::::::^^^::^!7??7~^.        |
|       .:^~~^!77777~~7?YY?7??7^.       |
|       :.^~!??!^::::^^~!?5PY??!~.      |
|       ~!!7J~.:::^^^^~!!~~?G5J?~       |
|       :^~?!~7?Y57^^?PP5YJ!J5Y?:       |
|       .~!!.:^!7!:.:7JYYJ7~7Y7^        |
|       .~77..    . .~^:^^^~7?:         |
|       .^!^~:::.:^!7?~^~!77J:          |
|        ^^!Y~^^^^~?YJ77??7JJ^          |
|       .^7J?~^~~^~7??7??7JY?~:         |
|        ::^^~^7?!^~~!7???J?J7~:.       |
|         ^~~!.^7YPPPP5Y?7J7777~.       |
|        ..:~..:^!JPP5YJ?!777!^.        |
| .~?JJJJJJJJJJYYYYYPPPPPPPPPPPP5PPYY~  |
|  :!Y5GGG.___ YYYYYY__._.PPGGGGGG5!.   |
|   :!Y5G / __| ___ / _(_)__ _ PGP5.    |
|    :~75 \__ \/ _ \  _| / _` | 5?.     |
|     7~7 |___/\___/_| |_\__,_| Y5?.    |
|    .^~!~.....................P5YY7.   |
|   .:::::::::::::?JJJJYYYYYYYYYJJJJ7.  |
|                                       |
=---------------------------------------=
*/

/*
************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A32.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Parser (.h)
************************************************************
*/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferPointer	stringLiteralTable;
extern Rs_intg		line;
extern Token			tokenizer(Rs_void);
extern Rs_string		keywordTable[KWT_SIZE];
static Rs_intg		syntaxErrorNumber = 0;

#define LANG_WRTE		"print("
#define LANG_READ		"input("
#define LANG_MAIN		"main("

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */

/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_const,
	KW_array,
	KW_int,
	KW_float,
	KW_string,
	KW_if,
	KW_then,
	KW_else,
	KW_while,
	KW_do,
	KW_return,
	KW_function,
	KW_add,
	KW_sub,
	KW_mul,
	KW_div,
	KW_and,
	KW_or,
	KW_not,
	KW_true,
	KW_false,
	KW_sqrt

};

/* TO_DO: Define the number of BNF rules */
#define NUM_BNF_RULES 12

/* Parser */
typedef struct parserData {
	Rs_intg parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
Rs_intg numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
Rs_void startParser();
Rs_void matchToken(Rs_intg, Rs_intg);
Rs_void syncErrorHandler(Rs_intg);
Rs_void printError();
Rs_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
	BNF_dataSession,								/*  3 */
	BNF_optVarListDeclarations,						/*  4 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_statement,									/*  9 */
	BNF_statements,									/* 10 */
	BNF_statementsPrime								/* 11 */
};


/* TO_DO: Define the list of keywords */
static Rs_string BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_comment",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime"

};

/* TO_DO: Place ALL non-terminal function declarations */

Rs_void comment();

Rs_void optVarListDeclarations();
Rs_void optionalStatements();
Rs_void outputStatement();
Rs_void outputVariableList();
Rs_void program();
Rs_void statement();
Rs_void statements();
Rs_void statementsPrime();

#endif
