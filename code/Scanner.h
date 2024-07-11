/*
************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2024
* Author: Ruan Simo F.
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
# ECHO "    @@        RUANSCRIPT           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
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
#define STR_LEN 100
#define CHARSEOF0 '\0'

#define RTE_CODE 1  /* Value for run-time error */

/* TO_DO: Define the number of tokens */
#define NUM_TOKENS 36

/* TO_DO: Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,      /* 0: Error token */
    MNID_T,     /* 1: Main identifier token */
    INL_T,      /* 2: Integer literal token */
    STR_T,      /* 3: String literal token */
    LPR_T,      /* 4: Left parenthesis token */
    RPR_T,      /* 5: Right parenthesis token */
    LBR_T,      /* 6: Left brace token */
    RBR_T,      /* 7: Right brace token */
    KW_T,       /* 8: Keyword token */
    EOS_T,      /* 9: End of statement token */
    RTE_T,      /* 10: Runtime error token */
    SEOF_T,     /* 11: Source end-of-file token */
    CMT_T,      /* 12: Comment token */
    LT_T,       /* 13: Less than token */
    EQ_T,       /* 14: Equal token */
    GT_T,       /* 15: Greater than token */
    ADD_T,      /* 16: Addition token */
    SUB_T,      /* 17: Subtraction token */
    MUL_T,      /* 18: Multiplication token */
    DIV_T,      /* 19: Division token */
    MOD_T,      /* 20: Modulus token */
    AND_T,      /* 21: Logical AND token */
    OR_T,       /* 22: Logical OR token */
    NOT_T,      /* 23: Logical NOT token */
    ASSIGN_T,   /* 24: Assignment token */
    ADD_ASSIGN_T, /* 25: Addition assignment token */
    SUB_ASSIGN_T, /* 26: Subtraction assignment token */
    MUL_ASSIGN_T, /* 27: Multiplication assignment token */
    DIV_ASSIGN_T, /* 28: Division assignment token */
    MOD_ASSIGN_T, /* 29: Modulus assignment token */
    SEMI_T,     /* 30: Semicolon token */
    COLON_T,    /* 31: Colon token */
    COMMA_T,    /* 32: Comma token */
	UNDERSCORE_T, /* 33: Underscore token */
    SHARP_T,    /* 34: Sharp token */
    MLC_T       /* 35: Multi-line comment token */
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
    "CMT_T",
    "LT_T",
    "EQ_T",
    "GT_T",
    "ADD_T",
    "SUB_T",
    "MUL_T",
    "DIV_T",
    "MOD_T",
    "AND_T",
    "OR_T",
    "NOT_T",
    "ASSIGN_T",
    "ADD_ASSIGN_T",
    "SUB_ASSIGN_T",
    "MUL_ASSIGN_T",
    "DIV_ASSIGN_T",
    "MOD_ASSIGN_T",
    "SEMI_T",
    "COLON_T",
	"COMMA_T",
    "UNDERSCORE_T",
    "SHARP_T",
    "MLC_T"
};

/* TO_DO: Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_MOD, OP_INC, OP_DEC  } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT, OP_GE, OP_LE } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT, OP_XOR  } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;

// #define ID_LEN 32
// #define STR_LEN 100
// #define ERR_LEN 20
// #define CHARSEOF0 '\0'

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
    Rs_char strLexeme[STR_LEN + 1];  // For string literals
} TokenAttribute;

/* TO_DO: Should be used if no symbol table is implemented */
//error in the declaration of the structure
typedef struct idAttributes {
	Rs_byte flags;			/* Flags information */
	union {
		Rs_intg intValue;				/* Integer value */
		Rs_float floatValue;			/* Float value */
		Rs_string stringContent;		/* String value */
	} values;
} IdAttributes;

/* Token declaration */
typedef struct Token {
	Rs_intg code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttributes   idAttribute;	/* not used in this scanner implementation - for further use */
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
#define CHRCOL6 '#'

/* These constants will be used on VID / MID function */
//#define MNID_SUF '&'
#define LPR_SUF '('
#define RPR_SUF ')'
#define COMM_SYM '#'

/* TO_DO: Error states and illegal state */
#define ESNR	8		/* Error state with no retract */
#define ESWR	9		/* Error state with retract */
#define FS		10		/* Illegal state */

/* Define tokens for single-line and multi-line comments */
#define SINGLE_LINE_COMMENT '#'
#define MULTI_LINE_COMMENT_START "/*"
#define MULTI_LINE_COMMENT_END "*/"

/* Define tokens for keywords */
#define KEYWORD_FLOAT "float"
#define KEYWORD_INT "int"
#define KEYWORD_WHILE "while"
#define KEYWORD_FOR "for"
#define KEYWORD_IF "if"
#define KEYWORD_ELSE "else"

/* Define tokens for keywords that output mnid_T */
#define MNID_MAIN "main"
#define MNID_PRINT "print"
#define MNID_INPUT "input"

/* Define tokens for single-quoted string literals */
#define SINGLE_QUOTE_STRING_LITERAL_START '\''
#define SINGLE_QUOTE_STRING_LITERAL_END '\''

/* Define tokens for double-quoted string literals */
#define DOUBLE_QUOTE_STRING_LITERAL_START '"'
#define DOUBLE_QUOTE_STRING_LITERAL_END '"'

/* Define tokens for parentheses and braces */
#define LEFT_PARENTHESIS '('
#define RIGHT_PARENTHESIS ')'
#define LEFT_BRACE '{'
#define RIGHT_BRACE '}'

/* Define tokens for mathematical operators */
#define OPERATOR_ASSIGN '='
#define OPERATOR_ADD '+'
#define OPERATOR_SUBTRACT '-'
#define OPERATOR_MULTIPLY '*'
#define OPERATOR_DIVIDE '/'

/* Define tokens for semicolons */
#define SEMICOLON ';'

 /* TO_DO: State transition table definition */
#define NUM_STATES		10
#define CHAR_CLASSES	8

/* TO_DO: Transition table - type of states defined in separate table */
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
// };

/* TO_DO: Transition table - type of states defined in separate table */
static Rs_intg transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
       L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */
    {     1, ESNR, ESNR, ESNR,    4, ESWR,	  6, ESNR},	// S0: NOAS
    {     1,    1,    1,    2,	  3,    3,   3,    3},	// S1: NOAS
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S2: ASNR (MVID)
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S3: ASWR (KEY)
    {     4,    4,    4,    4,    5, ESWR,	  4,    4},	// S4: NOAS
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S5: ASNR (SL)
    {     6,    6,    6,    6,    6, ESWR,	  7,    6},	// S6: NOAS
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S7: ASNR (COM)
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S8: ASNR (ES)
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS}  // S9: ASWR (ER)
};

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
	FSNR, /* 08 (Err1 - no retract) */
	FSWR  /* 09 (Err2 - retract) */
};

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
	funcErr,	/* ERR1 [06] */
	funcErr		/* ERR2 [07] */
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO: Define the number of Keywords from the language */
#define KWT_SIZE 23

/* TO_DO: Define the list of keywords */
static Rs_string keywordTable[KWT_SIZE] = {
	"main",		/* KW00 */
	"input",	/* KW01 */
	"int",		/* KW02 */
	"float",	/* KW03 */
	"string",	/* KW04 */
	"if",		/* KW05 */
	"then",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
	"do",		/* KW09 */
	"for",       /* KW10 */
	"return",    /* KW11 */
	"break",     /* KW12 */
	"continue",  /* KW13 */
	"let",       /* KW14 */
	"const",     /* KW15 */
	"function",  /* KW16 */
	"true",      /* KW17 */
	"false",     /* KW18 */
	"null",      /* KW19 */
	"typeof",    /* KW20 */
	"this",      /* KW21 */
	"print"      /* KW22 */
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
	Rs_boln isIndentation;
} LanguageAttributes;

/* Number of errors */
Rs_intg numScannerErrors;

/* Scanner data */
ScannerData scData;

/* Function to determine the character class */
static Rs_intg nextClass(Rs_char c) {
    if (isalpha(c)) {
        return 0; // Letter
    } else if (isdigit(c)) {
        return 1; // Digit
    } else if (c == CHRCOL2) {
        return 2; // Underscore
    } else if (c == CHRCOL3) {
        return 3; // Ampersand
    } else if (c == CHRCOL4) {
        return 4; // Single Quote
    } else if (c == CHRCOL6) {
        return 6; // Hash
    } else if (isspace(c)) {
        return 5; // Whitespace (SEOF)
    } else {
        return 7; // Other
    }
}

#endif
