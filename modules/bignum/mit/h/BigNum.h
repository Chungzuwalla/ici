/* Copyright     Digital Equipment Corporation & INRIA     1988, 1989 */
/* Last modified_on Wed Mar  7 23:22:25 GMT+1:00 1990 by shand */
/*      modified_on Wed Jul  5 10:19:33 GMT+2:00 1989 by bertin */
/*      modified_on Fri Apr 28 20:03:23 GMT+2:00 1989 by herve */


/* BigN.h - Types and structures for clients of BigNum */



		/******** representation of a bignum ******/
/*
**  <--------------------------- nl ---------------------------->
**  |   Least                                           Most    |
**  |Significant|           |           |           |Significant|
**  |BigNumDigit|           |           |           |BigNumDigit|
**  |___________|___________|___________|___________|___________|
**        ^                                          (sometimes
**        |                                            is zero)
**       nn
*/

#include <string.h>

/* signals BigNum.h already included */
#define BIGNUM

		/*************** sizes ********************/

#define BN_BYTE_SIZE			8
#define BN_WORD_SIZE			(sizeof (int) * BN_BYTE_SIZE)
#define BN_DIGIT_SIZE			(sizeof (BigNumDigit) * BN_BYTE_SIZE)

/* notes: */
/* BN_BYTE_SIZE: number of bits in a byte */
/* BN_WORD_SIZE: number of bits in an "int" in the target language */
/* BN_DIGIT_SIZE: number of bits in a digit of a BigNum */


		/****** results of compare functions ******/

 /* Note: we don't use "enum" to interface with Modula2+, Lisp, ... */
#define BN_LT				-1
#define BN_EQ				0
#define BN_GT				1

		/*************** boolean ******************/

#define TRUE				1
#define FALSE				0


		/* if DIGITon16BITS is defined, a single digit is on 16 bits */
		/* otherwise (by default) a single digit is on 32 bits *****/
		/* Note: on 32 bit machine it makes little sense to mix */
		/* longs and short, so we define Boolean & BigNumCmp to be */
		/* int usually */

#ifdef DIGITon16BITS
typedef unsigned short			BigNumDigit;
typedef short				Boolean;
#else
typedef unsigned int 			BigNumDigit;
typedef int				Boolean;
#endif


		/* bignum types: digits, big numbers, carries ... */

typedef BigNumDigit * 	BigNum;		/* A big number is a digit pointer */
typedef BigNumDigit	BigNumCarry;	/* Either 0 or 1 */
typedef unsigned long 	BigNumProduct;	/* The product of two digits */
typedef unsigned long	BigNumLength;	/* The length of a bignum */
#ifdef DIGITon16BITS
typedef short		BigNumCmp;	/* result of comparison */
#else
typedef int		BigNumCmp;	/* result of comparison */
#endif


/**/


		/************ functions of bn.c ***********/

extern void             BnnInit 			();
extern void             BnnClose 			();

extern Boolean		BnnIsZero 			();
extern BigNumCarry 	BnnMultiply			();
extern void		BnnDivide			();
extern BigNumCmp	BnnCompare			();


		/*********** functions of KerN.c **********/

extern void 		BnnSetToZero			();
extern void 		BnnAssign			();
extern void 		BnnSetDigit			();
extern BigNumDigit 	BnnGetDigit			();
extern BigNumLength	BnnNumDigits			();
extern BigNumDigit	BnnNumLeadingZeroBitsInDigit	();
extern Boolean 		BnnDoesDigitFitInWord 		();
extern Boolean		BnnIsDigitZero 			();
extern Boolean		BnnIsDigitNormalized 		();
extern Boolean 		BnnIsDigitOdd			();
extern BigNumCmp		BnnCompareDigits		();
extern void 		BnnComplement			();
extern void 		BnnAndDigits			();
extern void		BnnOrDigits			();
extern void		BnnXorDigits			();
extern BigNumDigit	BnnShiftLeft			();
extern BigNumDigit	BnnShiftRight			();
extern BigNumCarry 	BnnAddCarry			();
extern BigNumCarry 	BnnAdd				();
extern BigNumCarry 	BnnSubtractBorrow		();
extern BigNumCarry 	BnnSubtract			();
extern BigNumCarry 	BnnMultiplyDigit		();
extern BigNumDigit	BnnDivideDigit			();

/**/

		/* some functions can be written with macro-procedures */


#ifndef BNNMACROS_OFF
/* the functions BnnIsZero and BnnCompareDigits are not macro procedures
since they use parameters twice, and that can produce some bugs if
you pass a parameter like x++, the increment will be executed twice ! */
#define BnnSetToZero(nn,nl)             memset (nn, 0, (nl)*BN_DIGIT_SIZE/BN_BYTE_SIZE)
#define BnnSetDigit(nn,d) 		(*(nn) = (d))
#define BnnGetDigit(nn)			((unsigned)(*(nn)))
#define BnnDoesDigitFitInWord(d)	(BN_DIGIT_SIZE > BN_WORD_SIZE ? ((d) >= 1 << BN_WORD_SIZE ? FALSE : TRUE) : TRUE)
#define BnnIsDigitZero(d)		((d) == 0)
#define BnnIsDigitNormalized(d)		((d) & (1 << (BN_DIGIT_SIZE - 1)) ? TRUE : FALSE)
#define BnnIsDigitOdd(d) 		((d) & 1 ? TRUE : FALSE)
#define BnnAndDigits(nn, d)		(*(nn) &= (d))
#define BnnOrDigits(nn, d)		(*(nn) |= (d))
#define BnnXorDigits(nn, d)		(*(nn) ^= (d))

#endif


