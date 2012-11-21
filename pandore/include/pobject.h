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
 * @author Régis Clouard - 1999-10-08
 * @author Francois Angot - 1999-10-08
 * @author Alexandre Duret-Lutz - 1999-10-08
 * @author Régis Clouard - 2002-12-09 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file pobject.h
 * @brief The definition of the base class Pobject. 
 */

#ifndef __PPOBJECTH__
#define __PPOBJECTH__

#include <stdio.h>
#include <string>

namespace pandore {

   /**
    * Gets the local date and sets the given parameter.
    * The date is in English format: year/month/day.
    * @param date	an array where to set the date.
    */
   void Date(Char* date);

#define PLOAD 0
#define PSAVE 1

   /**
    * Just open a Pandore file.
    * Checks filename consistency.
    * @param filename
    * @param mode	between (PLOAD / PSAVE)
    */
   FILE* Pfopen( const char *filename , int mode );

   /**
    * Reads the header of the given filename.
    * Check the file format from its magic number.
    * In case of bad format, set the potype to object (= unknown object).
    * @param stream	the input stream.
    * @param version	the read Pandore version header format.
    * @param invertBytes	return true if the Low/High bytes will be inverted (mismatch LSB/MSB).
    * @return	the read header struct.
    */
   Po_header ReadHeader( FILE *stream, int &version, bool &invertBytes );

   /**
    * Saves the header for the specied Pandore type
    * in the specified file.
    * @param stream	the output stream.
    * @param type	the type of the Pandore object.
    */
   void SaveHeader( FILE *stream, Typobj type );

   /**
    * The enumeration of all known color spaces. 
    */
   enum  PColorSpace {
      RGB, XYZ, LUV, LAB, HSL, AST, I1I2I3, LCH, WRY, RNGNBN, YCBCR, YCH1CH2, YIQ, YUV, HSI, UNKNOWN };

   /** @brief The common attributes structure.
    *
    * Gathered all properties for any Pandore objects.
    */
   struct PobjectProps {
   public:
      /** The number of bands.*/
      Long nbands;
      /** The number of columns. */
      Long ncol;
      /** The number of rows. */
      Long nrow;
      /** The number of planes. */
      Long ndep;
      /** The color space. */
      PColorSpace colorspace;
      /** The number of labels in a region map. */
      Ulong nlabels;
      /** The number of nodes in a graph. */
      Long size;
      /** The flag that indicates if the graph is directed or undirected. */
      bool directed;

      /**
       * Creates a new <code>PobjectProps</code> with the specified attrubute values.
       * @param nb	the number of bands.
       * @param nc	the number of columns (width).
       * @param nr	the number of rows (height).
       * @param nd	the number of plans (depth).
       * @param c	the color space.
       * @param l	the number of labels (for a region map).
       * @param s	the number of nodes (for a graph).
       */
      PobjectProps(Long nb, Long nc, Long nr, Long nd, PColorSpace c, Ulong l, Long s, bool d=false): nbands(nb), ncol(nc), nrow(nr), ndep(nd), colorspace(c), nlabels(l), size(s), directed(d) {}
   };

   /* @brief A trait that returns the magic number of the T object.
    *
    * The magic number is an integer that is is used to
    * identify the Pandore type.
    * <i>Remark</i>: This trait is noit used as such,
    * but via the method Type() of the related object.
    */
   template< class T > struct Po_type{ };

   /** @brief A trait that returns the name of the type
    * T which is either a primitive type or a Pandore object.
    *
    * For example, the following trait returns "Uchar":
    * <pre>
    * TypeName<Uchar>::Name();
    * </pre>
    * and the following trait returns "Imx2dsf":
    * <pre>
    * TypeName<Imx2dsf>::Name();
    * </pre>
    */
   template< class T > struct TypeName{};

   /** @brief The base class of all Pandore objects.
    *
    * Pobject is the base class of all the Pandore objects.
    * A Pobject is an object that can be saved (and loaded) in a file.
    * It is identified
    * by a magic number that can be accessed by the method Type().
    */
   class Pobject {
   protected :
      /**
       * Creates a new empty Pobject.
       */
      Pobject() : _inversionMode(false) {}
   
   public :
      /**
       * Deletes the Pandore object.
       */
      virtual ~Pobject(){}
   
      /**
       * Returns the identifier of the object.
       * @return	 the magic number. 
       */
      virtual Typobj Type() const = 0;
   
      /**
       * Returns the type name.
       * @return	the string.
       */
      virtual std::string Name() const =0;
   
      /**
       * Creates a new Pobject of the same type but
       * where the data are masked by the given mask.
       * It means that value are set to 0 when the related
       * label in the mask is 0.
       * @param mask	the region map that is used as a mask. 
       * @return	the new Pobject.
       */
      virtual Pobject* Mask( const Pobject *mask ) = 0;

      /**
       * Creates a new Pobject of the same type but where the data
       * are ummasked by the given mask and the given reference image.
       * It means that values are set to the value of the
       * reference object when the related label in the mask is 0.
       * @param mask	the region map that is used as a mask. 
       * @param reference	the object that is used as a reference. 
       * @return	the new Pobject.
       */
      virtual Pobject* UnMask( const Pobject *mask,const Pobject *reference )  = 0;

      /**
       * Creates and returns a distinct copy of this object.
       * @return	the new object.
       */
      virtual Pobject* Clone() const = 0;
   
      /**
       * Loads object from the specified filename.
       * @param filename	the file where to read data. 
       * @return SUCCESS or FAILURE.
       */
      virtual Errc LoadFile( const char* filename );
   
      /**
       * Saves object in the specified filename.
       * @param filename	the file where to save data. 
       * @return SUCCESS or FAILURE.
       */
      virtual Errc SaveFile( const char* filename ) const;
   
      /**
       * Loads the object from the specified file.
       * @param df	the file where to read data. 
       * @param invert	if true invert low/high bytes.
       * @return SUCCESS or FAILURE.
       */
      virtual Errc Load( FILE *df , bool invert);

      /**
       * Saves the object in the specified filename.
       * @param df	the file where to save data. 
       * @return SUCCESS or FAILURE.
       */
      virtual Errc Save( FILE* df ) const;

      /**
       * Loads attribute values from the given file.
       * Allocates therefrom the related data.
       * @param df	the file where to read attribute values. 
       * @return SUCCESS or FAILURE.
       */
      virtual Errc LoadAttributes( FILE* df ) = 0;

      /**
       * Saves the current attribute values.
       * @param df	the file.
       * @return SUCCESS or FAILURE.
       */
      virtual Errc SaveAttributes( FILE* df ) const = 0;

      /**
       * Loads data from the given file.
       * @param df	the file where to read data. 
       * @return SUCCESS or FAILURE.
       */
      virtual Errc LoadData( FILE* df ) = 0;

      /**
       * Saves data in the given file.
       * @param df	the file where to save data. 
       * @return SUCCESS or FAILURE.
       */
      virtual Errc SaveData( FILE* df ) const = 0;

      /**
       * Returns the related vector of properties.
       * @return the vector of properties.
       */
      virtual PobjectProps Props( ) const { return PobjectProps(0,0,0,0,UNKNOWN,0,0 ); };

      /**
       * Redefines the fread function to be hardware independant.
       * @param ptr	array to store read elements.
       * @param size	size of each element
       * @param nitems	number of element to read.
       * @param stream	the stream to read. 
       * @return	the number of bytes read.
       */
      size_t Fdecode( void *ptr, size_t  size,  size_t  nitems,  FILE *stream );

      /**
       * Redefines the fwrite function to be hardware independant.
       * @param ptr	array that contains the elements to write.
       * @param size	size of each element
       * @param nitems	number of element to read.
       * @param stream	the stream to read. 
       * @return	the number of byte written.
       */
      size_t Fencode( const void *ptr, size_t size,  size_t  nitems, FILE *stream ) const ;

      /**
       * Sets the inversion mode to true.
       * @param value	new inversion mode.
       */
      void setInversionMode( bool value ) { _inversionMode=value; }

   protected:
      /** Flag that indicates whether bytes should be inverted or not. */
      bool _inversionMode;
   };

   /**
    * Creates a new object from the data
    * loaded in the specified file. If the filename is NULL
    * than the object is read from the standard input.
    * @param filename	the file name (can be NULL).
    * @param imperative if true generates an error in case of failure.
    * @return	the new object or NULL.
    */
   Pobject* LoadFile( const char* filename, bool imperative =true );

   /**
    * Saves the data of the given object in
    * the specified file.If the filename is NULL
    * than the object is saved in the standard output.
    * @param object	the object to be saved (can be NULL).
    * @param filename	the file.
    * @return SUCCESS or FAILURE.
    */
   Errc SaveFile( const Pobject* object,const char* filename );

   /**
    * Creates a new object of the specified type.
    * @param type	the type number of the object.
    * @return	the new object.
    */
   Pobject* NewObject( Typobj type );

   /*
    * A trait that returns the name of a primitive type. 
    */
   template<>
   struct TypeName< Char >{
      /* @returns the name as a string of the type Char. */
      static std::string Name() { return "Char"; }
   };
   template<>
   struct TypeName< Uchar >{
      /* @returns the name as a string of the type Uchar. */
      static std::string Name() { return "Uchar"; }
   };
   template<>
   struct TypeName< Short >{
      /* @returns the name as a string of the type Short. */
      static std::string Name() { return "Short"; }
   };
   template<>
   struct TypeName< Ushort >{
      /* @returns the name as a string of the type Ushort. */
      static std::string Name() { return "Ushort"; }
   };
   template<>
   struct TypeName< Long >{
      /* @returns the name as a string of the type Long. */
      static std::string Name() { return "Long"; }
   };
   template<>
   struct TypeName< Ulong >{
      /* @returns the name as a string of the type Ulong. */
      static std::string Name() { return "Ulong"; }
   };
   template<>
   struct TypeName< Llong >{
      /* @returns the name as a string of the type Llong. */
      static std::string Name() { return "Llong"; }
   };
   template<>
   struct TypeName< Ullong >{
      /* @returns the name as a string of the type Ullong. */
      static std::string Name() { return "Ullong"; }
   };
   template<>
   struct TypeName< Float >{
      /* @returns the name as a string of the type Float. */
      static std::string Name() { return "Float"; }
   };
   template<>
   struct TypeName< Double >{
      /* @returns the name as a string of the type Double. */
      static std::string Name() { return "Double"; }
   };

} //End of pandore:: namespace

#endif // __PPOBJECTH__
