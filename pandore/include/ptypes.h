/* -*- mode: c++; c-basic-offset: 3 -*-
 *
 * PANDORE (PANTHEON Project)
 *
 * GREYC IMAGE
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex France
 *
 * This file is free software. You can use it, distribute it
 * and/or modify it. However, the entire risk to the quality
 * and performance of this program is with you.
 *
 *
 * For more information, refer to:
 * http://www.greyc.ensicaen.fr/EquipeImage/Pandore/
 */

/**
 * @author Régis Clouard - 1999-10-08
 * @author Régis Clouard - 2001-04-03 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file ptypes.h
 * @brief The basic Pandore types.
 */

#ifndef __PPTYPESH__
#define __PPTYPESH__

namespace pandore {

#ifdef _MSC_VER
   typedef __int8	int8_t;
   typedef unsigned __int8	uint8_t;
   typedef __int16	int16_t;
   typedef unsigned __int16	uint16_t;
   typedef __int32	int32_t;
   typedef unsigned __int32	uint32_t;
   typedef __int64	int64_t;
   typedef unsigned __int64	uint64_t;
#else
   #include <stdint.h>
#endif

/*
 * The basic scalar types.
 *
 * DO NOT DELETE the following inline comments (BASE and BASE IMAGE)!
 * (`BASE' is a flag for the preprocessor macro `forallbase')
 * (`BASE IMAGE' is a flag for the preprocessor macro `forallbaseimage')
 */
typedef char		Char;	// BASE
typedef	unsigned char	Uchar;	// BASE IMAGE
typedef	int16_t		Short;	// BASE
typedef	uint16_t	Ushort;	// BASE
typedef	int32_t		Long;	// BASE IMAGE
typedef	uint32_t	Ulong;  // BASE
typedef	int64_t		Llong;  // BASE
typedef	uint64_t	Ullong; // BASE
typedef	float		Float;	// BASE IMAGE
typedef	double		Double;	// BASE

#define POINTERSIZE	4

#ifndef FLT_EPSILON
#define	FLT_EPSILON	1.1920928955078125000000E-07F
#endif
#ifndef DBL_EPSILON
#define	DBL_EPSILON	2.2204460492503130808473E-16
#endif

/*
 * Definition of max and min values for each types.
 */

#ifndef MININT1
#define	MININT1 (-128)		/* min value of a "int 1 byte" */
#endif

#ifndef MAXINT1
#define	MAXINT1 127		/* max value of a "int 1 byte" */
#endif

#ifndef MAXUINT1
#define	MAXUINT1 255		/* max value of an "unsigned int 1 byte" */
#endif

#ifndef MININT2
#define	MININT2 (-32768)	/* min value of a "int 2 bytes" */
#endif

#ifndef MAXINT2
#define	MAXINT2	32767		/* max value of a "int 2 bytes" */
#endif

#ifndef MAXUINT2
#define	MAXUINT2 65535		/* max value of "unsigned int 2 bytes" */
#endif

#ifndef MININT4
#define	MININT4 (-2147483647-1)	/* min value of an "int 4 bytes" */
#endif

#ifndef MAXINT4
#define	MAXINT4 2147483647	/* max value of an "int 4 bytes" */
#endif

#ifndef MAXUINT4
#define	MAXUINT4 4294967295U	/* max value of an "unsigned int 4 bytes" */
#endif

#ifndef MINFLOAT4
#define	MINFLOAT4 1.175494351E-38F /* max precision between 2 floats */
#endif

#ifndef MAXFLOAT4
#define	MAXFLOAT4 3.402823466E+38F
#endif

#ifndef MINFLOAT8
#define	MINFLOAT8 2.2250738585072014E-308 /* max precision between 2 floats */
#endif

#ifndef MAXFLOAT8
#define	MAXFLOAT8 1.7976931348623157E+308
#endif

// Kept for compatibility
#ifndef MINCHAR
#define	MINCHAR (-128)		/* min value of a "signed char" */
#endif

#ifndef MAXCHAR
#define	MAXCHAR 127		/* max value of a "signed char" */
#endif

#ifndef MAXUCHAR
#define	MAXUCHAR 255		/* max value of an "unsigned char" */
#endif


#ifndef MINSHORT
#define	MINSHORT (-32768)	/* min value of a "short int" */
#endif

#ifndef MAXSHORT
#define	MAXSHORT 32767		/* max value of a "short int" */
#endif

#ifndef MAXUSHORT
#define	MAXUSHORT 65535		/* max value of "unsigned short int" */
#endif


#ifndef MINLONG
#define	MINLONG (-2147483647-1)	/* min value of an "int 4 bytes" */
#endif

#ifndef MAXLONG
#define	MAXLONG 2147483647	/* max value of an "int 4 bytes" */
#endif

#ifndef MAXULONG
#define	MAXULONG 4294967295U	/* max value of an "unsigned long int" */
#endif

#ifndef MINFLOAT
#define	MINFLOAT 1.175494351E-38F
#endif
#ifndef MAXFLOAT
#define	MAXFLOAT 3.402823466E+38F
#endif
#ifndef MINDOUBLE
#define	MINDOUBLE 2.2250738585072014E-308
#endif

#ifndef MAXDOUBLE
#define	MAXDOUBLE 1.7976931348623157E+308
#endif

#ifndef MAXLLONG
#define	MAXLLONG 9223372036854775807LL
#endif

#ifndef MAXULLONG
#define	MAXULLONG 18446744073709551615ULL
#endif

} //End of pandore:: namespace

#endif
