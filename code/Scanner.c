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
# ECHO "    @@         S O F I A           @@    �
# ECHO "    @@                             @@    �
# ECHO "    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    �
# ECHO "                                         "
# ECHO "[READER SCRIPT .........................]"
# ECHO "                                         "
*/

/*
************************************************************
* File name: Scanner.c
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A22, A32.
* Date: May 01 2024
* Purpose: This file contains all functionalities from Scanner.
* Function list: (...).
************************************************************
*/

/* TO_DO: Adjust the function header */

 /* The #define _CRT_SECURE_NO_WARNINGS should be used in MS Visual Studio projects
  * to suppress the warnings about using "unsafe" functions like fopen()
  * and standard sting library functions defined in string.h.
  * The define does not have any effect in Borland compiler projects.
  */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>   /* standard input / output */
#include <ctype.h>   /* conversion functions */
#include <stdlib.h>  /* standard library functions and constants */
#include <string.h>  /* string functions */
#include <limits.h>  /* integer types constants */
#include <float.h>   /* floating-point types constants */



#include <stdbool.h>



#include <ctype.h>  /* conversion functions */
#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* #define NDEBUG to suppress assert() call */
#include <assert.h>  /* assert() prototype */

/* project header files */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef BUFFER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#include "Scanner.h"
#endif
#include <stdbool.h>

/*
----------------------------------------------------------------
TO_DO: Global vars definitions
----------------------------------------------------------------
*/
// Declare the missing functions if they are not in the header

int isIdentifier(const char *lexeme);

/* Global objects - variables */
/* This buffer is used as a repository for string literals. */
extern BufferPointer stringLiteralTable;	/* String literal table */
Rs_intg line;								/* Current line number of the source code */
extern Rs_intg errorNumber;				/* Defined in platy_st.c - run-time error number */

extern Rs_intg stateType[NUM_STATES];
extern Rs_string keywordTable[KWT_SIZE];
extern PTR_ACCFUN finalStateTable[NUM_STATES];
extern Rs_intg transitionTable[NUM_STATES][CHAR_CLASSES];

/* Local(file) global objects - variables */
static BufferPointer lexemeBuffer;			/* Pointer to temporary lexeme buffer */
static BufferPointer sourceBuffer;			/* Pointer to input source buffer */

/*
 ************************************************************
 * Intitializes scanner
 *		This function initializes the scanner using defensive programming.
 ***********************************************************
 */
 /* TO_DO: Follow the standard and adjust datatypes */

Rs_intg startScanner(BufferPointer psc_buf) {
	/* TO_DO: Start histogram */
	for (Rs_intg i=0; i<NUM_TOKENS;i++)
		scData.scanHistogram[i] = 0;
	/* Basic scanner initialization */
	/* in case the buffer has been read previously  */
	readerRecover(psc_buf);
	readerClear(stringLiteralTable);
	line = 1;
	sourceBuffer = psc_buf;
	return EXIT_SUCCESS; /*0*/
}

/*
 ************************************************************
 * Process Token
 *		Main function of buffer, responsible to classify a char (or sequence
 *		of chars). In the first part, a specific sequence is detected (reading
 *		from buffer). In the second part, a pattern (defined by Regular Expression)
 *		is recognized and the appropriate function is called (related to final states 
 *		in the Transition Diagram).
 ***********************************************************
 */

Token tokenizer(Rs_void) {

	/* TO_DO: Follow the standard and adjust datatypes */

	Token currentToken = { 0 }; /* token to return after pattern recognition. Set all structure members to 0 */
	Rs_char c;	/* input symbol */
	Rs_intg state = 0;		/* initial state of the FSM */
	Rs_intg lexStart;		/* start offset of a lexeme in the input char buffer (array) */
	Rs_intg lexEnd;		/* end offset of a lexeme in the input char buffer (array)*/

	Rs_intg lexLength;		/* token length */
	Rs_intg i;				/* counter */
	//Rs_char newc;			// new char

	while (1) { /* endless loop broken by token returns it will generate a warning */
		c = readerGetChar(sourceBuffer);

		/* ------------------------------------------------------------------------
			Part 1: Implementation of token driven scanner.
			Every token is possessed by its own dedicated code
			-----------------------------------------------------------------------
		*/

		/* TO_DO: All patterns that do not require accepting functions */
		switch (c) {

		/* Cases for spaces */
		case ' ':
		case '\t':
		case '\f':
			break;
		case '\n':
			line++;
			break;

		/* Cases for symbols */
		case ';':
			currentToken.code = EOS_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '(':
			currentToken.code = LPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ')':
			currentToken.code = RPR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '{':
			currentToken.code = LBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '}':
			currentToken.code = RBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '+':
		c = readerGetChar(sourceBuffer);
		if (c == '+') {
			currentToken.code = INC_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		} else {
			currentToken.code = ADD_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		}
		case '-':
			c = readerGetChar(sourceBuffer);
			if (c == '-') {
				currentToken.code = DEC_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			} else {
			currentToken.code = SUB_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
			}
		case '*':
			currentToken.code = MUL_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '[':
			currentToken.code = SBL_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case ']':
			currentToken.code = SBR_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '/':
			c = readerGetChar(sourceBuffer);
			if (c == '/') {
				// Single-line comment
				while ((c = readerGetChar(sourceBuffer)) != '\n' && c != EOF);
				currentToken.code = CMT_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			} else if (c == '*') {
				// Multi-line comment
				while (1) {
					c = readerGetChar(sourceBuffer);
					if (c == '*' && (c = readerGetChar(sourceBuffer)) == '/') {
						currentToken.code = CMT_T;
						scData.scanHistogram[currentToken.code]++;
						return currentToken;
						//break; // End of multi-line comment
					}
					if (c == EOF) {
						// Handle unterminated comment error
						currentToken.code = ERR_T;
						return currentToken;
					}
				}
			} else {
				readerRetract(sourceBuffer);
				currentToken.code = DIV_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
		case '=':
			currentToken.code = EQ_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '!':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {
				currentToken.code = NE_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			} else {
				readerRetract(sourceBuffer);
				currentToken.code = NOT_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			}
		case '^':
			currentToken.code = POW_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '%':
			currentToken.code = MOD_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		case '>':
		c = readerGetChar(sourceBuffer);
		if (c == '=') {
			currentToken.code = GE_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		} else {
			currentToken.code = GT_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		}
		case '<':
			c = readerGetChar(sourceBuffer);
			if (c == '=') {
				currentToken.code = LE_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			} else {
			currentToken.code = LT_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
			}
		case '&':
			c = readerGetChar(sourceBuffer);
			if (c == '&') {
				currentToken.code = AND_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			} else {
				readerRetract(sourceBuffer);
				// handle error
			}
		case '|':
			c = readerGetChar(sourceBuffer);
			if (c == '|') {
				currentToken.code = OR_T;
				scData.scanHistogram[currentToken.code]++;
				return currentToken;
			} else {
				readerRetract(sourceBuffer);
				// handle error
			}
		case ',':
			currentToken.code = CMA_T;
			scData.scanHistogram[currentToken.code]++;
			return currentToken;
		/* Cases for END OF FILE */
		case CHARSEOF0:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_0;
			return currentToken;
		case CHARSEOF255:
			currentToken.code = SEOF_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.seofType = SEOF_255;
			return currentToken;

		/* ------------------------------------------------------------------------
			Part 2: Implementation of Finite State Machine (DFA) or Transition Table driven Scanner
			Note: Part 2 must follow Part 1 to catch the illegal symbols
			-----------------------------------------------------------------------
		*/

		/* TO_DO: Adjust / check the logic for your language */
		  default: // general case
                if (isdigit(c)) {
                    state = 1; // Initial state for number recognition
                    lexStart = readerGetPosRead(sourceBuffer) - 1;
                    readerSetMark(sourceBuffer, lexStart);
                    int isFloat = 0;

                    while (1) {
                        c = readerGetChar(sourceBuffer);
                        if (isdigit(c)) {
                            // Stay in the same state
                        } else if (c == '.' && !isFloat) {
                            isFloat = 1;
                            state = 2; // Transition to float state
                        } else {
                            readerRetract(sourceBuffer);
                            break;
                        }
                    }

                    lexEnd = readerGetPosRead(sourceBuffer);
                    lexLength = lexEnd - lexStart;
                    lexemeBuffer = readerCreate((Rs_intg)lexLength + 2, 0, MODE_FIXED);

                    if (!lexemeBuffer) {
                        fprintf(stderr, "Scanner error: Can not create buffer\n");
                        exit(1);
                    }
                    readerRestore(sourceBuffer);
                    for (i = 0; i < lexLength; i++)
                        readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
                    readerAddChar(lexemeBuffer, READER_TERMINATOR);

                    if (isFloat) {
                        currentToken.code = FLT_T;
                        currentToken.attribute.floatValue = atof(readerGetContent(lexemeBuffer, 0));
                    } else {
                        currentToken.code = INL_T;
                        currentToken.attribute.intValue = atoi(readerGetContent(lexemeBuffer, 0));
                    }

                    scData.scanHistogram[currentToken.code]++;
                    readerRestore(lexemeBuffer);
                    return currentToken;
				}
                 else {
					state = nextState(state, c);
			        lexStart = readerGetPosRead(sourceBuffer) - 1;
			        readerSetMark(sourceBuffer, lexStart);
			       while (stateType[state] == NOFS) {
				c = readerGetChar(sourceBuffer);
				state = nextState(state, c);
				
			}
			if (stateType[state] == FSWR)
				readerRetract(sourceBuffer);
			lexEnd = readerGetPosRead(sourceBuffer);
			lexLength = lexEnd - lexStart;
			lexemeBuffer = readerCreate((Rs_intg)lexLength + 2, 0, MODE_FIXED);
			if (!lexemeBuffer) {
				fprintf(stderr, "Scanner error: Can not create buffer\n");
				exit(1);
			}
			readerRestore(sourceBuffer);
			for (i = 0; i < lexLength; i++)
				readerAddChar(lexemeBuffer, readerGetChar(sourceBuffer));
			readerAddChar(lexemeBuffer, READER_TERMINATOR);
			currentToken = (*finalStateTable[state])(readerGetContent(lexemeBuffer, 0));
			readerRestore(lexemeBuffer);
			return currentToken;
 		} // switch
	} //while
        }
 } // switch

/*
 ************************************************************
 * Get Next State
	The assert(int test) macro can be used to add run-time diagnostic to programs
	and to "defend" from producing unexpected results.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	(*) assert() is a macro that expands to an if statement;
	if test evaluates to false (zero) , assert aborts the program
	(by calling abort()) and sends the following message on stderr:
	(*) Assertion failed: test, file filename, line linenum.
	The filename and linenum listed in the message are the source file name
	and line number where the assert macro appears.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	If you place the #define NDEBUG directive ("no debugging")
	in the source code before the #include <assert.h> directive,
	the effect is to comment out the assert statement.
	- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
	The other way to include diagnostics in a program is to use
	conditional preprocessing as shown bellow. It allows the programmer
	to send more details describing the run-time problem.
	Once the program is tested thoroughly #define DEBUG is commented out
	or #undef DEBUG is used - see the top of the file.
 ***********************************************************
 */
 /* TO_DO: Just change the datatypes */

Rs_intg nextState(Rs_intg state, Rs_char c){
	Rs_intg col;
	Rs_intg next;
	col = nextClass(c);
	next = transitionTable[state][col];
	if (DEBUG)
		printf("Input symbol: %c Row: %d Column: %d Next: %d \n", c, state, col, next);
	assert(next != FS);
	if (DEBUG)
		if (next == FS) {
			printf("Scanner Error: Illegal state:\n");
			printf("Input symbol: %c Row: %d Column: %d\n", c, state, col);
			exit(1);
		}
	return next;
}

/*
 ************************************************************
 * Get Next Token Class
	* Create a function to return the column number in the transition table:
	* Considering an input char c, you can identify the "class".
	* For instance, a letter should return the column for letters, etc.
 ***********************************************************
 */
/* TO_DO: Use your column configuration */

/* Adjust the logic to return next column in TT */
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */

Rs_intg nextClass(Rs_char c) {
	Rs_intg val = -1;
	 if (isalpha(c))
        val = 0;
    else if (isdigit(c))
        val = 1;
    else {
	switch (c) {
	 case '.':
            val = 2;
            break;
	case CHRCOL2:
		val = 2;
		break;
	case CHRCOL3:
		val = 3;
		break;
	case CHRCOL4:
		val = 4;
		break;
	case CHRCOL6:
		val = 6;
		break;
	case CHARSEOF0:
	case CHARSEOF255:
		val = 5;
		break;
	//case '/':
		//val = 6;
		//break;
	default:
			val = 7;
	}
	}
	return val;
}

/*
 ************************************************************
 * Acceptance State Function COM
 *		Function responsible to identify COM (comments).
 ***********************************************************
 */
 /* TO_DO: Adjust the function for IL */

//come back to this please
 Token funcCMT(Rs_string lexeme) {
    Token currentToken = { 0 };
    Rs_intg i = 0, len = (Rs_intg)strlen(lexeme);

	    // Validate if the lexeme is a comment
    if (lexeme[0] != '/' || lexeme[1] != '/') {
        // If not a comment, return an error token or handle appropriately
        currentToken.code = ERR_T;
        return currentToken;
    }
    
    // Adjust initialization and usage of currentToken
    currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);

    for (i = 1; i < len - 1; i++) {
        if (lexeme[i] == '\n') {
            line++;
        }
    }


    // Set code for comment token and update scanHistogram
    currentToken.code = CMT_T;
    scData.scanHistogram[currentToken.code]++;
    
    return currentToken;
}



 /*
  ************************************************************
  * Acceptance State Function IL
  *		Function responsible to identify IL (integer literals).
  * - It is necessary respect the limit (ex: 2-byte integer in C).
  * - In the case of larger lexemes, error shoul be returned.
  * - Only first ERR_LEN characters are accepted and eventually,
  *   additional three dots (...) should be put in the output.
  ***********************************************************
  */
  /* TO_DO: Adjust the function for IL */

Token funcIL(Rs_string lexeme) {
	Token currentToken = { 0 };
	Rs_long tlong;
	if (lexeme[0] != '\0' && strlen(lexeme) > NUM_LEN) {
		currentToken = (*finalStateTable[ESNR])(lexeme);
	}else {
		tlong = atol(lexeme);
		if (tlong >= 0 && tlong <= SHRT_MAX) {
			currentToken.code = INL_T;
			scData.scanHistogram[currentToken.code]++;
			currentToken.attribute.intValue = (Rs_intg)tlong;
		}
		else {
			currentToken = (*finalStateTable[ESNR])(lexeme);
		}
	}
	return currentToken;
}

/*
 ************************************************************
 * Acceptance State Function ID
 *		In this function, the pattern for IDs must be recognized.
 *		Since keywords obey the same pattern, is required to test if
 *		the current lexeme matches with KW from language.
 *	- Remember to respect the limit defined for lexemes (VID_LEN) and
 *	  set the lexeme to the corresponding attribute (vidLexeme).
 *    Remember to end each token with the \0.
 *  - Suggestion: Use "strncpy" function.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for ID */

Token funcID(Rs_string lexeme) {
    Token currentToken = { 0 };
    size_t length = strlen(lexeme);
    Rs_char lastch = lexeme[length - 1];
    Rs_intg isID = FALSE;

    switch (lastch) {
        case MNID_SUF:
            currentToken.code = MNID_T;
            scData.scanHistogram[currentToken.code]++;
            isID = TRUE;
            break;
        default:
		// Test if the lexeme is a keyword
        lexeme[length - 1] = '\0';
        currentToken = funcKEY(lexeme);
	}
 
    return currentToken;
}


/*
************************************************************
 * Acceptance State Function SL
 *		Function responsible to identify SL (string literals).
 * - The lexeme must be stored in the String Literal Table 
 *   (stringLiteralTable). You need to include the literals in 
 *   this structure, using offsets. Remember to include \0 to
 *   separate the lexemes. Remember also to incremente the line.
 ***********************************************************
 */
/* TO_DO: Adjust the function for SL */

Token funcSL(Rs_string lexeme) {
    Token currentToken = { 0 };
    Rs_intg i = 0, len = (Rs_intg)strlen(lexeme);
    
    // Adjust initialization and usage of currentToken
    currentToken.attribute.contentString = readerGetPosWrte(stringLiteralTable);

    for (i = 1; i < len - 1; i++) {
        if (lexeme[i] == '\n') {
            line++;
        }

        // Incorporate logic for adding characters to stringLiteralTable
        if (!readerAddChar(stringLiteralTable, lexeme[i])) {
            currentToken.code = RTE_T;
            scData.scanHistogram[currentToken.code]++;
            strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
            errorNumber = RTE_CODE;
            return currentToken;
        }
    }

    // Check for end of string literal and handle errors
    if (!readerAddChar(stringLiteralTable, CHARSEOF0)) {
        currentToken.code = RTE_T;
        scData.scanHistogram[currentToken.code]++;
        strcpy(currentToken.attribute.errLexeme, "Run Time Error:");
        errorNumber = RTE_CODE;
        return currentToken;
    }

    // Set code for string literal token and update scanHistogram
    currentToken.code = STR_T;
    scData.scanHistogram[currentToken.code]++;

    return currentToken;
}


/*
************************************************************
 * This function checks if one specific lexeme is a keyword.
 * - Tip: Remember to use the keywordTable to check the keywords.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Keywords */

Token funcKEY(Rs_string lexeme) {
    Token currentToken = { 0 };
    Rs_intg kwindex = -1;
    Rs_intg len = (Rs_intg)strlen(lexeme);

    // Ensure the lexeme is null-terminated properly
	 if (lexeme[len] != '\0') {
        lexeme[len] = '\0';
    }
    // lexeme[len - 1] = '\0';

    // Search for the keyword in the keyword table
    for (int j = 0; j < KWT_SIZE; j++) {
        if (!strcmp(lexeme, keywordTable[j])) {
            kwindex = j;
            break;
        }
    }

    if (kwindex != -1) {
        // Keyword found
        currentToken.code = KW_T;
        //scData.scanHistogram[currentToken.code]++;
        currentToken.attribute.codeType = kwindex;
	} else if (isIdentifier(lexeme)) {
		// Lexeme is an identifier
		currentToken.code = ID_T;
		strncpy(currentToken.attribute.idLexeme, lexeme, sizeof(currentToken.attribute.idLexeme) - 1);
		currentToken.attribute.idLexeme[sizeof(currentToken.attribute.idLexeme) - 1] = '\0';
	} else {
		// Keyword not found, treat as an error
		currentToken = funcErr(lexeme);
	}

    return currentToken;
}



/*
************************************************************
 * Acceptance State Function Error
 *		Function responsible to deal with ERR token.
 * - This function uses the errLexeme, respecting the limit given
 *   by ERR_LEN. If necessary, use three dots (...) to use the
 *   limit defined. The error lexeme contains line terminators,
 *   so remember to increment line.
 ***********************************************************
 */
 /* TO_DO: Adjust the function for Errors */
Token funcErr(Rs_string lexeme) {
    Token currentToken = { 0 };
    Rs_intg i = 0, len = (Rs_intg)strlen(lexeme);
    
    // Handling lexeme longer than ERR_LEN
    if (len > ERR_LEN) {
        strncpy(currentToken.attribute.errLexeme, lexeme, ERR_LEN - 3);
        currentToken.attribute.errLexeme[ERR_LEN - 3] = CHARSEOF0;
        strcat(currentToken.attribute.errLexeme, "...");
    } else {
        strcpy(currentToken.attribute.errLexeme, lexeme);
    }
    
    // Count lines if lexeme contains newline characters
    for (i = 0; i < len; i++) {
        if (lexeme[i] == '\n') {
            line++;
        }
    }
    
    // Set token code for error and update scanHistogram
    currentToken.code = ERR_T;
    scData.scanHistogram[currentToken.code]++;
    
    return currentToken;
}


/*
 ************************************************************
 * The function prints the token returned by the scanner
 ***********************************************************
 */

Rs_void printToken(Token t) {
	extern Rs_string keywordTable[]; /* link to keyword table in */
	switch (t.code) {
	case RTE_T:
		printf("RTE_T\t\t%s", t.attribute.errLexeme);
		/* Call here run-time error handling component */
		if (errorNumber) {
			printf("%d", errorNumber);
			exit(errorNumber);
		}
		printf("\n");
		break;
	case ERR_T:
		printf("ERR_T\t\t%s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T\t\t%d\t ", (Rs_intg)t.attribute.codeType);
		printf("%s\n", readerGetContent(stringLiteralTable, (Rs_intg)t.attribute.codeType));
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case KW_T:
		printf("KW_T\t\t%s\n", keywordTable[t.attribute.codeType]);
		break;
	case CMT_T:
		printf("CMT_T\n");
		break;
	case EOS_T:
		printf("EOS_T\n");
		break;
	case ADD_T:
		printf("ADD_T\n");
		break;
	case SUB_T:
		printf("SUB_T\n");
		break;
	case MUL_T:
		printf("MUL_T\n");
		break;
	case DIV_T:
		printf("DIV_T\n");
		break;
	case EQ_T:
		printf("EQ_T\n");
		break;
	case NE_T:
		printf("NE_T\n");
		break;
	case GT_T:
		printf("GT_T\n");
		break;
	case LT_T:
		printf("LT_T\n");
		break;
	case AND_T:
		printf("AND_T\n");
		break;
	case OR_T:
		printf("OR_T\n");
		break;
	case NOT_T:
		printf("NOT_T\n");
		break;
	case INL_T:
		printf("INL_T\t\t%d\n", t.attribute.intValue);
		break;
	case ID_T:
		printf("ID_T\t\t%s\n", t.attribute.idLexeme);
		break;
	case FLT_T:
		printf("FLT_T\t\t%f\n", t.attribute.floatValue);
		break;
	case INT_T:
		printf("INT_T\t\t%d\n", t.attribute.intValue);
		break;
	case NUM_T:
		printf("NUM_T\t\t%d\n", t.attribute.intValue);
		break;
	case CMA_T:
		printf("CMA_T\n");
		break;
	case POW_T:
		printf("POW_T\n");
		break;
	case MOD_T:
		printf("MOD_T\n");
		break;
	case SBL_T:
		printf("SBL_T\n");
		break;
	case SBR_T:
		printf("SBR_T\n");
		break;
	case GE_T:
		printf("GE_T\n");
		break;
	case LE_T:
		printf("LE_T\n");
		break;
	case INC_T:
		printf("INC_T\n");
		break;
	case DEC_T:
		printf("DEC_T\n");
		break;
	default:
		printf("Scanner error: invalid token code: %d\n", t.code);
	}
}

/*
 ************************************************************
 * The function prints statistics of tokens
 * Param:
 *	- Scanner data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
Rs_void printScannerData(ScannerData scData) {
	/* Print Scanner statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_TOKENS; cont++) {
		if (scData.scanHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", tokenStrTable[cont], "]=", scData.scanHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

/*
TO_DO: (If necessary): HERE YOU WRITE YOUR ADDITIONAL FUNCTIONS (IF ANY).
*/


// Function to check if a lexeme is a valid identifier
int isIdentifier(const char *lexeme) {
    if (!isalpha(lexeme[0]) && lexeme[0] != '_') {
        return 0;
    }
    for (int i = 1; lexeme[i] != '\0'; i++) {
        if (!isalnum(lexeme[i]) && lexeme[i] != '_') {
            return 0;
        }
    }
    return 1;
}

