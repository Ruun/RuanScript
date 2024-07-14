/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: TO_DO
* Professors: Paulo Sousa
************************************************************
#
# ECHO "=---------------------------------------="
# ECHO "|  COMPILERS - ALGONQUIN COLLEGE (S24)  |"
# ECHO "=---------------------------------------="
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    î
# ECHO "    @@                             @@    î
# ECHO "    @@           %&@@@@@@@@@@@     @@    î
# ECHO "    @@       @%% (@@@@@@@@@  @     @@    î
# ECHO "    @@      @& @   @ @       @     @@    î
# ECHO "    @@     @ @ %  / /   @@@@@@     @@    î
# ECHO "    @@      & @ @  @@              @@    î
# ECHO "    @@       @/ @*@ @ @   @        @@    î
# ECHO "    @@           @@@@  @@ @ @      @@    î
# ECHO "    @@            /@@    @@@ @     @@    î
# ECHO "    @@     @      / /     @@ @     @@    î
# ECHO "    @@     @ @@   /@/   @@@ @      @@    î
# ECHO "    @@     @@@@@@@@@@@@@@@         @@    î
# ECHO "    @@                             @@    î
# ECHO "    @@         S O F I A           @@    î
# ECHO "    @@                             @@    î
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    î
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ñ Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 13

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T		/* 12: Comment token */
};

/* TO_DO: Define the list of keywords */
static Rs_string tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

/* TO_DO: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	Rs_intg codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
	Rs_intg intValue;				/* integer literal attribute (value) */
	Rs_intg keywordIndex;			/* keyword index in the keyword table */
	Rs_intg contentString;			/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	Rs_float floatValue;				/* floating-point literal attribute (value) */
	Rs_char idLexeme[VID_LEN + 1];	/* variable identifier token attribute */
	Rs_char errLexeme[ERR_LEN + 1];	/* error token attribite */
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	Rs_byte flags;			/* Flags information */
	union {
		Rs_intg intValue;				/* Integer value */
		Rs_float floatValue;			/* Float value */
		Rs_string stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	Rs_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	Rs_intg scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* TO_DO: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '_'
#define CHRCOL3 '&'
#define CHRCOL4 '\''
#define CHRCOL6 '/' //was # put back

/* These constants will be used on VID / MID function */
#define MNID_SUF '&'
//#define COMM_SYM '/' //was # put back

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

 /* TO_DO: State transition table definition */
#define NUM_STATES		10 // was 10
#define CHAR_CLASSES	8


/*might delete latter*/

/* Constants for the comment symbols */
#define COMM_SYM1 '/'
#define COMM_SYM2 '*'

/* TO_DO: State transition table definition */
#define NUM_STATES		12
#define CHAR_CLASSES	8
/*might delete later*/

/* TO_DO: Transition table - type of states defined in separate table */
static Rs_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    &,   \', SEOF,    /, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */
	{     1, ESNR, ESNR, ESNR,    4, ESWR,    8, ESNR},	// S0: NOAS
	{     1,    1,    1,    2,	  3,    3,   3,    3},	// S1: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S2: ASNR (MVID)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S3: ASWR (KEY)
	{     4,    4,    4,    4,    5, ESWR,	  4,    4},	// S4: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S5: ASNR (SL)
	{     6,    6,    6,    6,    6, ESWR,	  7,    6},	// S6: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S7: ASNR (COM)
	{     8,    8,    8,    8,    8,    8,	  9,    8},	// S8: NOAS (Single-line comment start)
	{     9,    9,    9,    9,    9,   10,    9,    9},	// S9: NOAS (Inside single-line comment)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S10: ASNR (Single-line comment end)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S11: ASNR (Multi-line comment end)
};


// /* TO_DO: Transition table - type of states defined in separate table */
// static Rs_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
// /*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
// 	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */
// 	{     1, ESNR, ESNR, ESNR,    4, ESWR,	  6, ESNR},	// S0: NOAS
// 	{     1,    1,    1,    2,	  3,    3,   3,    3},	// S1: NOAS
// 	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S2: ASNR (MVID)
// 	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S3: ASWR (KEY)
// 	{     4,    4,    4,    4,    5, ESWR,	  4,    4},	// S4: NOAS
// 	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S5: ASNR (SL)
// 	{     6,    6,    6,    6,    6, ESWR,	  7,    6},	// S6: NOAS
// 	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S7: ASNR (COM)
// 	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S8: ASNR (ES)
// 	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS}  // S9: ASWR (ER)
//  };

/* Define accepting states types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/* TO_DO: Define list of acceptable states */
static Rs_intg stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	FSWR, /* 03 (KEY) */
	NOFS, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSNR, /* 07 (COM) */
	NOFS, /* 08 (Single-line comment start) */
	FSNR, /* 09 (Single-line comment inside) */
	FSNR, /* 10 (Single-line comment end) */
	FSNR, /* 11 (Multi-line comment end) */
};



// /* TO_DO: Define list of acceptable states */
// /* TO_DO: Define list of acceptable states */
// static Rs_intg stateType[NUM_STATES] = {
// 	NOFS, /* 00 */
// 	NOFS, /* 01 */
// 	FSNR, /* 02 (MID) - Methods */
// 	FSWR, /* 03 (KEY) */
// 	NOFS, /* 04 */
// 	FSNR, /* 05 (SL) */
// 	NOFS, /* 06 */
// 	FSNR, /* 07 (COM) */
// 	FSNR, /* 08 (Err1 - no retract) */
// 	FSWR  /* 09 (Err2 - retract) */
// };


/*
-------------------------------------------------
TO_DO: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
Rs_intg			startScanner(BufferPointer psc_buf);
static Rs_intg	nextClass(Rs_char c);					/* character class function */
static Rs_intg	nextState(Rs_intg, Rs_char);		/* state machine function */
Rs_void			printScannerData(ScannerData scData);
Token				tokenizer(Rs_void);

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(Rs_string lexeme);

/* Declare accepting states functions */
Token funcSL	(Rs_string lexeme);
Token funcIL	(Rs_string lexeme);
Token funcID	(Rs_string lexeme);
Token funcCMT   (Rs_string lexeme);
Token funcKEY	(Rs_string lexeme);
Token funcErr	(Rs_string lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* Define accepting function (action) callback table (array) definition */
/* TO_DO: Define final state table */

/* TO_DO: Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
	funcID,		/* MNID	[02] */
	funcKEY,	/* KEY  [03] */
	NULL,		/* -    [04] */
	funcSL,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcCMT,	/* COM  [07] */
	NULL,		/* -    [08] */
	funcCMT,	/* COM  [09] */
	funcCMT,	/* COM  [10] */
	funcCMT		/* COM  [11] */
};

/* TO_DO: Define the functions for the new comment states */

// Token funcSL(Rs_string lexeme) {
// 	Token t;
// 	t.code = STR_T;
// 	t.attribute.intValue = 0; // Adjust as necessary
// 	return t;
// }

// Token funcCMT(Rs_string lexeme) {
// 	Token t;
// 	t.code = CMT_T;
// 	t.attribute.intValue = 0; // Adjust as necessary
// 	return t;
// }

// Token funcErr(Rs_string lexeme) {
// 	Token t;
// 	t.code = ERR_T;
// 	strncpy(t.attribute.errLexeme, lexeme, ERR_LEN);
// 	t.attribute.errLexeme[ERR_LEN] = '\0';  // Ensure null-terminated string
// 	return t;
// }


// static PTR_ACCFUN finalStateTable[NUM_STATES] = {
// 	NULL,		/* -    [00] */
// 	NULL,		/* -    [01] */
// 	funcID,		/* MNID	[02] */
// 	funcKEY,	/* KEY  [03] */
// 	NULL,		/* -    [04] */
// 	funcSL,		/* SL   [05] */
// 	NULL,		/* -    [06] */
// 	funcCMT,	/* COM  [07] */
// 	funcErr,	/* ERR1 [06] */
// 	funcErr		/* ERR2 [07] */
// };

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 10

/* TO_DO: Define the list of keywords */
static Rs_string keywordTable[KWT_SIZE] = {
	"data",		/* KW00 */
	"code",		/* KW01 */
	"int",		/* KW02 */
	"real",		/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do"		/* KW09 */
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/* TO_DO: Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	Rs_char indentationCharType;
	Rs_intg indentationCurrentPos;
	/* TO_DO: Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
Rs_intg numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif
