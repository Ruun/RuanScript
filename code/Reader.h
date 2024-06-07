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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 � Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2024
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
//commented this out caused some errors changed with stdlib.h
//#include <malloc.h> /* for dynamic memory allocation*/ 
#include <stdlib.h>
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'f', /* Fixed mode (constant size) */
	MODE_ADDIT = 'a', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'm'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (Rs) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */

/* TO_DO: BIT 3: END = End of buffer flag */
/* TO_DO: BIT 2: REL = Rellocation memory flag */
/* TO_DO: BIT 2: EMP = Buffer empty flag */
/* TO_DO: BIT 0: FUL = Buffer full flag */

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (Rs) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct position {
	Rs_intg mark;			/* the offset to the mark position (in chars) */
	Rs_intg read;			/* the offset to the get a char position (in chars) */
	Rs_intg wrte;			/* the offset to the add chars (in chars) */
} Position;

/* Buffer structure */
typedef struct bufferReader {
	Rs_string	content;			/* pointer to the beginning of character array (character buffer) */
	Rs_intg		size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	Rs_intg		increment;			/* character array increment factor */
	Rs_intg		mode;				/* operational mode indicator */
	Rs_byte		flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Position		position;				/* Offset / position field */
	Rs_intg		histogram[NCHAR];	/* Statistics of chars */
	Rs_intg		numReaderErrors;	/* Number of errors from Reader */
} Buffer, *BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
BufferPointer	readerCreate		(Rs_intg, Rs_intg, Rs_intg);
BufferPointer	readerAddChar		(BufferPointer const, Rs_char);
Rs_boln		readerClear		    (BufferPointer const);
Rs_boln		readerFree		    (BufferPointer const);
Rs_boln		readerIsFull		(BufferPointer const);
Rs_boln		readerIsEmpty		(BufferPointer const);
Rs_boln		readerSetMark		(BufferPointer const, Rs_intg);
Rs_intg		readerPrint		    (BufferPointer const);
Rs_intg		readerLoad			(BufferPointer const, FILE* const);
Rs_boln		readerRecover		(BufferPointer const);
Rs_boln		readerRetract		(BufferPointer const);
Rs_boln		readerRestore		(BufferPointer const);
Rs_void		readerChecksum		(BufferPointer const);
/* Getters */
Rs_char		readerGetChar		(BufferPointer const);
Rs_string	readerGetContent	(BufferPointer const, Rs_intg);
Rs_intg		readerGetPosRead	(BufferPointer const);
Rs_intg		readerGetPosWrte	(BufferPointer const);
Rs_intg		readerGetPosMark	(BufferPointer const);
Rs_intg		readerGetSize		(BufferPointer const);
Rs_intg		readerGetInc		(BufferPointer const);
Rs_intg		readerGetMode		(BufferPointer const);
Rs_byte		readerGetFlags		(BufferPointer const);
Rs_void		readerPrintStat		(BufferPointer const);
Rs_intg		readerNumErrors		(BufferPointer const);

#endif
