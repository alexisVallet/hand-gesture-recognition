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
 * http://www.greyc.ensicaen.fr/EquipeImage/Pandore
 */

/**
 * @author Alexandre Duret-Lutz - 1999-10-14
 * @author Régis Clouard - 2001-04-03 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2006-09-04 (fix bug on Windows version)
 * @author Cyril Bazin - Jan 17, 2012 (getenv + parallelism)
 */

/**
 * @file errc.h
 * @brief The definition of the type Errc which holds any primitive
 * type value.
 */

#ifndef __PERRCH__
#define __PERRCH__

#include <memory.h>

#ifdef _WIN32
#define HOME "USERPROFILE"
#else
#define HOME "HOME"
#endif

#define PANDORE_TMP "PANDORE_TMP"

namespace pandore {
/** @enum FS_t Enumeration of predefined values for error codes. */
typedef enum { FAILURE=0, SUCCESS } FS_t;

class Errc;

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>The value is stored in the USEHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param e	the error code.
 */
void Exit( const Errc &e );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( FS_t v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	an integer value.
 */
void Exit( int v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Char v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Uchar v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Short v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Ushort v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Long v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Ulong v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Llong v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Ullong v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Float v );

/**
 * Terminates the current execution and returns the specified
 * value as the error code.
 * Overloads the C-function exit().
 * <br>This value is stored in the USERHOME/.pandore file.
 * This allows to handle Errc values, while the C exit() command
 * can only store a char value.
 * The error code can then be read with the
 * Pandore operator: @b pstatus.
 * @param v	the error code.
 */
void Exit( Double v );


/** @brief A type that contains any primitive type value.
 *
 * The class Errc defines a type of any value type.
 * It can be set with any primitive type value
 * (Uchar, Slong, Float, bool, ... - Except int)
 * or one of the predefined values: SUCCESS or FAILURE.
 *
 * The actual type of Errc is defined by setting.
 * <br>For example, the following lines set the variable a to the 
 * integer 12 and then change it to the predefined value SUCCESS
 * or to the float value 12.5:
 * @code
 * Errc a; a=12;
 * if (a==12) then a=SUCCESS else a=12.5;
 * @endcode
 *
 * This type mainly used for the return type of the operator functions:
 * @code Errc function(<parameters>*) {
 *    < instruction >*;
 *    return SUCCESS;
 * } @endcode
 */
class Errc {
private:
   enum { FS_RET
	  ,Char_RET
	  ,Uchar_RET
	  ,Short_RET
	  ,Ushort_RET
	  ,Long_RET
	  ,Ulong_RET
	  ,Llong_RET
	  ,Ullong_RET
	  ,Float_RET
	  ,Double_RET
   } _ret; 
   
public :
   /*
    * Creates a value from the specified predefined error code.
    * The type <code>FS_t</code> allows only two predefined
    * values : {SUCCESS, FAILURE}
    * @param value	the specified error code between {SUCCESS, FAILURE}.
    */
   Errc( const FS_t value = SUCCESS ) {
      _ret = FS_RET;
      _val.fs = value;
   }
   
   /*
    * Creates a value from the specified boolean value.
    * @param value	the specified boolean value.
    */
   Errc( bool value ) {
      _ret = FS_RET;
      _val.fs = (value)? SUCCESS: FAILURE;
   }

   /*
    * Creates a value from the specified Char value.
    * @param value	the specified Char value.
    */
    Errc( Char value ) {
      _ret = Char_RET;
      _val.v_Char = value;
    }
   /*
    * Creates a value from the specified Uchar value.
    * @param value	the specified Uchar value.
    */
    Errc( Uchar value ) {
      _ret = Uchar_RET;
      _val.v_Uchar = value;
    }
   /*
    * Creates a value from the specified Short value.
    * @param value	the specified Short value.
    */
    Errc( Short value ) {
      _ret = Short_RET;
      _val.v_Short = value;
    }
   /*
    * Creates a value from the specified Ushort value.
    * @param value	the specified Ushort value.
    */
    Errc( Ushort value ) {
      _ret = Ushort_RET;
      _val.v_Ushort = value;
    }
   /*
    * Creates a value from the specified Long value.
    * @param value	the specified Long value.
    */
    Errc( Long value ) {
      _ret = Long_RET;
      _val.v_Long = value;
    }
   /*
    * Creates a value from the specified Ulong value.
    * @param value	the specified Ulong value.
    */
    Errc( Ulong value ) {
      _ret = Ulong_RET;
      _val.v_Ulong = value;
    }
   /*
    * Creates a value from the specified Llong value.
    * @param value	the specified Llong value.
    */
    Errc( Llong value ) {
      _ret = Llong_RET;
      _val.v_Llong = value;
    }
   /*
    * Creates a value from the specified Ullong value.
    * @param value	the specified Ullong value.
    */
    Errc( Ullong value ) {
      _ret = Ullong_RET;
      _val.v_Ullong = value;
    }
   /*
    * Creates a value from the specified Float value.
    * @param value	the specified Float value.
    */
    Errc( Float value ) {
      _ret = Float_RET;
      _val.v_Float = value;
    }
   /*
    * Creates a value from the specified Double value.
    * @param value	the specified Double value.
    */
    Errc( Double value ) {
      _ret = Double_RET;
      _val.v_Double = value;
    }

    /*
     * Creates a value from the specified Errc.
     * @param error	the specified Errc.
     */
    Errc( const Errc &error ) {
       _ret = error._ret;
       memcpy(&_val,&error._val,sizeof(_val));
    }

   /**
    * Sets the error value with the specified value.
    * @param error	the specified value
    */   
   Errc& operator =( const Errc &error ) {
      _ret = error._ret;
      memcpy(&_val,&error._val,sizeof(_val));
      return *this;
   }
   
   /*
    * Converts the value to a boolean value.
    * @return	true if the current value is SUCCESS or a numerical value !=0.
    */
   operator bool() { 
      switch(_ret) {
      case FS_RET: return _val.fs == SUCCESS;
      case Char_RET: return 1;
      case Uchar_RET: return 1;
      case Short_RET: return 1;
      case Ushort_RET: return 1;
      case Long_RET: return 1;
      case Ulong_RET: return 1;
      case Llong_RET: return 1;
      case Ullong_RET: return 1;
      case Float_RET: return 1;
      case Double_RET: return 1;
      default: return false;
      }
   }

   /*
    * Converts the current value to an error code value;
    * i.e., a value in the predefined set {SUCCESS, FAILURE}.
    * @return	FAILURE if the current value is any form of 0, SUCCESS otherwise.
    */
   operator FS_t() { return _val.fs; }

   /*
    * Converts the value to a Char value.
    * @return	the related value.
    */
   operator Char() { 
      switch(_ret) {
	 case FS_RET: return (Char)(_val.fs==SUCCESS);
	 case Char_RET: return (Char)_val.v_Char;
	 case Uchar_RET: return (Char)_val.v_Uchar;
	 case Short_RET: return (Char)_val.v_Short;
	 case Ushort_RET: return (Char)_val.v_Ushort;
	 case Long_RET: return (Char)_val.v_Long;
	 case Ulong_RET: return (Char)_val.v_Ulong;
	 case Float_RET: return (Char)_val.v_Float;
	 case Double_RET : return (Char)_val.v_Double;
	 case Llong_RET : return (Char)_val.v_Double;
	 case Ullong_RET : return (Char)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Uchar value.
    * @return	the related value.
    */
   operator Uchar() { 
      switch(_ret) {
	 case FS_RET: return (Uchar)(_val.fs==SUCCESS);
	 case Char_RET: return (Uchar)_val.v_Char;
	 case Uchar_RET: return (Uchar)_val.v_Uchar;
	 case Short_RET: return (Uchar)_val.v_Short;
	 case Ushort_RET: return (Uchar)_val.v_Ushort;
	 case Long_RET: return (Uchar)_val.v_Long;
	 case Ulong_RET: return (Uchar)_val.v_Ulong;
	 case Float_RET: return (Uchar)_val.v_Float;
	 case Double_RET : return (Uchar)_val.v_Double;
	 case Llong_RET : return (Uchar)_val.v_Double;
	 case Ullong_RET : return (Uchar)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Short value.
    * @return	the related value.
    */
   operator Short() { 
      switch(_ret) {
	 case FS_RET: return (Short)(_val.fs==SUCCESS);
	 case Char_RET: return (Short)_val.v_Char;
	 case Uchar_RET: return (Short)_val.v_Uchar;
	 case Short_RET: return (Short)_val.v_Short;
	 case Ushort_RET: return (Short)_val.v_Ushort;
	 case Long_RET: return (Short)_val.v_Long;
	 case Ulong_RET: return (Short)_val.v_Ulong;
	 case Float_RET: return (Short)_val.v_Float;
	 case Double_RET : return (Short)_val.v_Double;
	 case Llong_RET : return (Short)_val.v_Double;
	 case Ullong_RET : return (Short)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Ushort value.
    * @return	the related value.
    */
   operator Ushort() { 
      switch(_ret) {
	 case FS_RET: return (Ushort)(_val.fs==SUCCESS);
	 case Char_RET: return (Ushort)_val.v_Char;
	 case Uchar_RET: return (Ushort)_val.v_Uchar;
	 case Short_RET: return (Ushort)_val.v_Short;
	 case Ushort_RET: return (Ushort)_val.v_Ushort;
	 case Long_RET: return (Ushort)_val.v_Long;
	 case Ulong_RET: return (Ushort)_val.v_Ulong;
	 case Float_RET: return (Ushort)_val.v_Float;
	 case Double_RET : return (Ushort)_val.v_Double;
	 case Llong_RET : return (Ushort)_val.v_Double;
	 case Ullong_RET : return (Ushort)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Long value.
    * @return	the related value.
    */
   operator Long() { 
      switch(_ret) {
	 case FS_RET: return (Long)(_val.fs==SUCCESS);
	 case Char_RET: return (Long)_val.v_Char;
	 case Uchar_RET: return (Long)_val.v_Uchar;
	 case Short_RET: return (Long)_val.v_Short;
	 case Ushort_RET: return (Long)_val.v_Ushort;
	 case Long_RET: return (Long)_val.v_Long;
	 case Ulong_RET: return (Long)_val.v_Ulong;
	 case Float_RET: return (Long)_val.v_Float;
	 case Double_RET : return (Long)_val.v_Double;
	 case Llong_RET : return (Long)_val.v_Double;
	 case Ullong_RET : return (Long)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Ulong value.
    * @return	the related value.
    */
   operator Ulong() { 
      switch(_ret) {
	 case FS_RET: return (Ulong)(_val.fs==SUCCESS);
	 case Char_RET: return (Ulong)_val.v_Char;
	 case Uchar_RET: return (Ulong)_val.v_Uchar;
	 case Short_RET: return (Ulong)_val.v_Short;
	 case Ushort_RET: return (Ulong)_val.v_Ushort;
	 case Long_RET: return (Ulong)_val.v_Long;
	 case Ulong_RET: return (Ulong)_val.v_Ulong;
	 case Float_RET: return (Ulong)_val.v_Float;
	 case Double_RET : return (Ulong)_val.v_Double;
	 case Llong_RET : return (Ulong)_val.v_Double;
	 case Ullong_RET : return (Ulong)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Llong value.
    * @return	the related value.
    */
   operator Llong() { 
      switch(_ret) {
	 case FS_RET: return (Llong)(_val.fs==SUCCESS);
	 case Char_RET: return (Llong)_val.v_Char;
	 case Uchar_RET: return (Llong)_val.v_Uchar;
	 case Short_RET: return (Llong)_val.v_Short;
	 case Ushort_RET: return (Llong)_val.v_Ushort;
	 case Long_RET: return (Llong)_val.v_Long;
	 case Ulong_RET: return (Llong)_val.v_Ulong;
	 case Float_RET: return (Llong)_val.v_Float;
	 case Double_RET : return (Llong)_val.v_Double;
	 case Llong_RET : return (Llong)_val.v_Double;
	 case Ullong_RET : return (Llong)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Ullong value.
    * @return	the related value.
    */
   operator Ullong() { 
      switch(_ret) {
	 case FS_RET: return (Ullong)(_val.fs==SUCCESS);
	 case Char_RET: return (Ullong)_val.v_Char;
	 case Uchar_RET: return (Ullong)_val.v_Uchar;
	 case Short_RET: return (Ullong)_val.v_Short;
	 case Ushort_RET: return (Ullong)_val.v_Ushort;
	 case Long_RET: return (Ullong)_val.v_Long;
	 case Ulong_RET: return (Ullong)_val.v_Ulong;
	 case Float_RET: return (Ullong)_val.v_Float;
	 case Double_RET : return (Ullong)_val.v_Double;
	 case Llong_RET : return (Ullong)_val.v_Double;
	 case Ullong_RET : return (Ullong)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Float value.
    * @return	the related value.
    */
   operator Float() { 
      switch(_ret) {
	 case FS_RET: return (Float)(_val.fs==SUCCESS);
	 case Char_RET: return (Float)_val.v_Char;
	 case Uchar_RET: return (Float)_val.v_Uchar;
	 case Short_RET: return (Float)_val.v_Short;
	 case Ushort_RET: return (Float)_val.v_Ushort;
	 case Long_RET: return (Float)_val.v_Long;
	 case Ulong_RET: return (Float)_val.v_Ulong;
	 case Float_RET: return (Float)_val.v_Float;
	 case Double_RET : return (Float)_val.v_Double;
	 case Llong_RET : return (Float)_val.v_Double;
	 case Ullong_RET : return (Float)_val.v_Double;
	 default: return 0;
      }
   }
   /*
    * Converts the value to a Double value.
    * @return	the related value.
    */
   operator Double() { 
      switch(_ret) {
	 case FS_RET: return (Double)(_val.fs==SUCCESS);
	 case Char_RET: return (Double)_val.v_Char;
	 case Uchar_RET: return (Double)_val.v_Uchar;
	 case Short_RET: return (Double)_val.v_Short;
	 case Ushort_RET: return (Double)_val.v_Ushort;
	 case Long_RET: return (Double)_val.v_Long;
	 case Ulong_RET: return (Double)_val.v_Ulong;
	 case Float_RET: return (Double)_val.v_Float;
	 case Double_RET : return (Double)_val.v_Double;
	 case Llong_RET : return (Double)_val.v_Double;
	 case Ullong_RET : return (Double)_val.v_Double;
	 default: return 0;
      }
   }

   /**
    * Returns the logical negation of the current value.
    */
   bool operator !() {
      bool b= *this;
      return !b;
   }
   
   /**
    * Terminates the current execution and returns the 
    * current value as the error code.
    * Overloads the C-function exit().
    * The error code can then be read with the
    * Pandore operator: @b pstatus.
    */
   void Exit() const;

   friend bool operator !=( Errc &e1, FS_t value ) ;
   friend bool operator !=( FS_t value, Errc &e1 ) ;
   friend bool operator ==( Errc &e1, FS_t value ) ;
   friend bool operator ==( FS_t value, Errc &e1 ) ;
   friend bool operator &&( Errc &e1, Errc &e2 ) ;
   friend bool operator &&( Errc &e, bool b ) ;
   friend bool operator &&( bool b, Errc &e );

   friend bool operator ||( Errc &e1, Errc &e2 ) ;
   friend bool operator ||( Errc &e, bool b ) ;
   friend bool operator ||( bool b, Errc &e );
   
private:
   /** The current value. */
   union {
      FS_t fs;
      Char v_Char;
      Uchar v_Uchar;
      Short v_Short;
      Ushort v_Ushort;
      Long v_Long;
      Ulong v_Ulong;
      Llong v_Llong;
      Ullong v_Ullong;
      Float v_Float;
      Double v_Double;
   } _val;
};

   inline bool operator ==( Errc &e, FS_t value ) {
      if (e._ret == Errc::FS_RET) return e._val.fs == value;
      else return 0;
   }

   inline bool operator ==( FS_t value, Errc &e ) {
      if (e._ret == Errc::FS_RET) return e._val.fs == value;
      else return 0;
   }

   inline bool operator !=( Errc &e, FS_t value ) {
      if (e._ret == Errc::FS_RET) return e._val.fs != value;
      else return 1;
   }

   inline bool operator !=( FS_t value, Errc &e ) {
      if (e._ret == Errc::FS_RET) return e._val.fs != value;
      else return 1;
   }
  
   /**
    * Performs logical et between 2 errc. 
    * @param e1 the first operand.
    * @param e2 the second operand.
    */
   inline bool operator &&( Errc &e1, Errc &e2 ) {
      bool b1 = e1;
      bool b2 = e2;
      return b1 && b2;
   }

   /**
    * Performs logical et between an  errc and a boolean.  
    * @param e an errc.
    * @param b a boolean
    */
   inline bool operator &&( Errc &e, bool b ) {
      bool b1=e;
      return b1 && b;
   }

   /**
    * Performs logical et between an  errc and a boolean. 
    * @param b a boolean
    * @param e an errc.
    */
   inline bool operator &&( bool b, Errc &e ) {
      bool b1=e;
      return b && b1;
   }
   
   /**
    * Performs logical or between 2 errc. 
    * @param e1 the first operand.
    * @param e2 the second operand.
    */
   inline bool operator ||( Errc &e1, Errc &e2 ) {
      bool b1 = e1;
      bool b2 = e2;
      return b1 || b2;
   }

   /**
    * Performs logical or between an  errc and a boolean. 
    * @param e an errc.
    * @param b a boolean
    */
   inline bool operator ||( Errc &e, bool b ) {
      bool b1=e;
      return b1 || b;
   }

   /**
    * Performs logical or between an  errc and a boolean. 
    * @param b a boolean
    * @param e an errc.
    */
   inline bool operator ||( bool b, Errc &e ) {
      bool b1=e;
      return b || b1;
   }

} //End of pandore:: namespace

#endif // __PERRCH__
