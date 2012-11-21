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

/*
 * @author Alexandre Duret-Lutz - 1999-10-14
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 */

/**
 * @file plimits.h
 * @brief Traits that defines the limits of a primitive type.
 */

#ifndef __PPLIMITSH__
#define __PPLIMITSH__

namespace pandore {

/** @brief A trait that returns the max and min limits of the type T.
 * 
 * For example:
 * <pre>
 * Limits<Uchar>::max() returns the max value of type Char: +255.
 * Limits<Uchar>::min() returns the min value of type Char: 0.
 * </pre>
 */
template< typename T > struct Limits {
   // Defines as a shadow for unknown types.
   // unknown
};

/* @brief The max and min limits of the type Uchar.
 *
 * Stores the max and min values for the type Uchar.
 */
template<> struct Limits<Uchar> {
   /* @return the max value. */
   static Uchar max() { return (Uchar)MAXUCHAR; }
   /* @return the min value. */
   static Uchar min() { return 0; }
};

/* @brief The max and min limits of the type Char.
 *
 * Stores the max and min values for the type Char.
 */
template<> struct Limits<Char> {
   /* @return the max value. */
   static Char max() { return (Char)MAXCHAR; }
   /* @return the min value. */
   static Char min() { return (Char)MINCHAR; }
};

/* @brief The max and min limits of the type Ushort.
 *
 * Stores the max and min values for the type Ushort.
 */
template<> struct Limits<Ushort> {
   /* @return the max value. */
   static Ushort max() { return (Ushort)MAXUSHORT; }
   /* @return the min value. */
   static Ushort min() { return 0; }
};

/* @brief The max and min limits of the type Short.
 *
 * Stores the max and min values for the type Short.
 */
template<> struct Limits<Short> {
   /* @return the max value. */
   static Short max() { return (Short)MAXSHORT; }
   /* @return the min value. */
   static Short min() { return (Short)MINSHORT; }
};

/* @brief The max and min limits of the type Ulong.
 *
 * Stores the max and min values for the type Ulong.
 */
template<> struct Limits<Ulong> {
   /* @return the max value. */
   static Ulong max() { return (Ulong)MAXULONG; }
   /* @return the min value. */
   static Ulong min() { return 0; }
};

/* @brief The max and min limits of the type Long.
 *
 * Stores the max and min values for the type Long.
 */
template<> struct Limits<Long> {
   /* @return the max value. */
   static Long max() { return (Long)MAXLONG; }
   /* @return the min value. */
   static Long min() { return (Long)MINLONG; }
};

/* @brief The max and min limits of the type Float.
 *
 * Stores the max and min values for the type Float.
 */
template<> struct Limits<Float> {
   /* @return the max value. */
   static Float max() { return (float)MAXFLOAT; }
   /* @return the min value. */
   static Float min() { return -(float)MAXFLOAT; }
};

/* @brief The max and min limits of the type Double.
 *
 * Stores the max and min values for the type Double.
 */
template<> struct Limits<Double> {
   /* @return the max value. */
   static Double max() { return (double)MAXDOUBLE; }
   /* @return the min value. */
   static Double min() { return -(double)MAXDOUBLE; }
};


/* @brief The max and min limits of the type long long int.
 *
 * Stores the max and min values for the type long long int.
 */
template<> struct Limits<Llong> {
   /* @return the max value. */
   static Llong max() { return (Llong)MAXLLONG; }
   /* @return the min value. */
   static Llong min() { return -(Llong)MAXLLONG; }
};

/* @brief The max and min limits of the type unsigned long long int.
 *
 * Stores the max and min values for the type unsigned long long int.
 */
template<> struct Limits<Ullong> {
   /* @return the max value. */
   static Ullong max() { return (Ullong)MAXULLONG; }
   /* @return the min value. */
   static Ullong min() { return 0; }
};

} //End of pandore:: namespace

#endif // __PPLIMITSH__
