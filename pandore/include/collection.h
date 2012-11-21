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
 * @author Alexandre Duret-Lutz - 1999-10-08
 * @author Régis Clouard - 2001-04-10
 * @author Régis Clouard - 2005-10-12 (change type of __dummy)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2007-02-12 (GetPObject() add casting for the return values)
 * @author Régis Clouard - 2008-09-18 (add destructor)
 */

/**
 * @file collection.h
 * @brief The definition of the class Collection.
 */

#ifndef __PCOLLECTIONH__
#define __PCOLLECTIONH__

#include <map>
#include <string>
#include <list>
#include "bundled.h"

namespace pandore {

   // Because of VisualC++ cannot use template as: method<Type>(...)
   // we use the dummy 0 with the convenient casting.
   // So: change the prototype to: method(..., (type)0);
#define SETVALUE(name,type,val) SetValue((name),(val))
#define GETVALUE(name,type)     GetValue((name),(type*)0)

#define SETARRAY(name,type,val,size) SetArray((name),(val),(size))
#define GETARRAY(name,type)     GetArray((name),(type*)0)
#define GETARRAYSIZE(name,type) GetArraySize((name),(type*)0)
#define GETNARRAYS(name,type,number,minsize_out) GetNArrays((name),(number),(minsize_out),(type*)0)

#define SETPOBJECT(name,type,val) SetPobject((name),(val))
#define GETPOBJECT(name,type)     GetPobject((name),(type*)0)

#define SETPARRAY(name,type,val,size) SetPArray((name),(val),(size))
#define GETPARRAY(name,type)    GetPArray((name),(type*)0)
#define GETPARRAYSIZE(name,type) GetPArraySize((name),(type*)0)

   class Collection;


   /* @brief A trait that returns the name of the object Collection.
    *
    * TypeName is a trait that returns the name
    * of the object Collection.
    */
   template<>
   struct TypeName< Collection > {
      /*
       * Returns the name of the type.
       * @return	the string with the name.
       */
      static std::string Name() { return "Collection";}
   };

   /** @brief A collection of Pandore objects.
    *
    * A Collection is a bundle of heterogeneous
    * data (<i>a la</i> struct C). Each data in a collection is
    * indexed by a name. Available types of data are:
    * - primitive C types (Uchar, Char, Short, Long, Uchar ... - except int);
    * - arrays of primitive C types;
    * - Pandore objects (Pobject)
    * - arrays of Pandore objects (even collection!).
    *
    * <br>For the use of Collection see @ref collection_page.
    */
   class Collection : public Pobject {
   public :

      ~Collection() { Delete(); }

      /**
       * Returns the identifier of the type Collection (for instance Po_Collection).
       * @return	 the related magic number (an integer). 
       */
      Typobj Type() const { return Po_Collection; }
   
      /**
       * Returns the type name of the type collection (for instance "Collection").
       * @return	the string that contains "Collection".
       */
      std::string Name() const { return TypeName< Collection >::Name(); }
   
      /**
       * Creates and returns a distinct copy of this object.
       * @return	the new object.
       */
      Pobject* Clone() const;
   
      /**
       * Sets the Collection with the specified collection values.
       * Deletes old values if necessary.
       * @returns the collection itself with its new values.
       */
      Collection &operator=( const Collection &col ) {
	 this->Delete();
	 std::map< std::string, BundledObject * >::const_iterator i;
	 for (i = col._objs.begin(); i != col._objs.end(); ++i) {
	    this->Set( i->first, i->second->Clone() );
	 }
	 return *this;
      }

      /**
       * Erases the specified data from the collection.
       * @param name	the name of the data to be erased.
       */
      void Erase( const std::string &name );
      
      /**
       * Deletes all data in the collection.
       */
      void Delete( );
   
      /**
       * Renames the specified data with the specified name.
       * e.g.: col.Rename("foo", "bar");
       * @param oldname	the name of the data to be renamed.
       * @param newname	the new name of the data.
       */
      void Rename( const std::string &oldname, const std::string &newname );

      /**
       * Checks if the specified data exist in the collection.
       * e.g.: if (col.Exists("foo")) ...
       * @param name	the name of the data to be checked.
       * @return true if data exists in the collection.
       */
      bool Exists( const std::string &name ) const;
   
      /**
       * Returns the number of arrays in a collection of arrays.
       * Each array is named, foo.1, foo.2, ..., if foo is the name of arrays.
       * @param name		the name of arrays.
       * @param type_out		use to return the type of the arrays (out)
       * @param number_out		use to return the number of arrays.
       * @param minsize_out	use to return the min size of arrays.
       * @return SUCCESS.
       */
      Errc NbOf( const std::string &name, std::string &type_out,Long &number_out, Long &minsize_out ) const;
   
      /**
       * Returns the type of the data specified by its name.
       * @param name	the name of the data.
       * @return	the name of the type.
       */
      std::string GetType( const std::string &name ) const;
      
      /**
       * Returns the list of all data names in the collection.
       * @return	 a list of names.
       */
      std::list< std::string > List() const;
   
      /**
       * Loads attribute values from the specified file.
       * Allocates therefrom the related data.
       * @param file	the file where to read attributes values. 
       * @return	SUCCESS or FAILURE in case of I/O errors.
       */
      Errc LoadAttributes( FILE * /*file*/ ) { return SUCCESS; }
   
      /**
       * Saves the current attribute values in the specified file.
       * @param file	the file to be read.
       * @return	SUCCESS or FAILURE in case of I/O errors.
       */
      Errc SaveAttributes( FILE *file ) const {
	 Long attr;

	 attr = _objs.size(); 
	 if (Fencode((void*)&attr,sizeof(attr),1,file) < 1)
	    return FAILURE;
	 return SUCCESS;
      }

      /**
       * Loads data from the specified file.
       * @param file	the file where to read data. 
       * @return	SUCCESS or FAILURE in case of I/O errors.
       */
      Errc LoadData( FILE *file );

      /**
       * Saves data in the specified file.
       * @param file	the file where to save data. 
       * @return	SUCCESS or FAILURE in case of I/O errors.
       */
      Errc SaveData( FILE *file ) const;
   
      /**
       * Creates a new collection with the same type but
       * where the data are masked by the given mask.
       * It means that values are set to 0 when the related
       * label in the mask is 0.
       * <i>Not implemented</i>.
       * @param mask	the region map that is used as a mask. 
       * @return	the new collection.
       */
      Pobject* Mask( const Pobject * /*mask*/ ) { return this; }

      /**
       * Creates a new collection with the same type but where the data
       * are ummasked by the given mask and the given reference image.
       * It means that values are set to the value of the
       * reference object when the related label in the mask is 0.
       * <i>Not implemented</i>.
       * @param mask	the region map that is used as a mask. 
       * @param reference	the object that is used as a reference. 
       * @return	the collection itself.
       */
      Pobject* UnMask( const Pobject * /*mask*/, const Pobject * /*reference*/ ) { return this; }

      /**
       * Sets the given data with the specified name in the collection.
       * @param name	the name of data in the collection.
       * @param bo	the data.
       */
      void Set( const std::string &name, BundledObject *bo );

      /**
       * Returns the data with the specified name from the collection.
       * @param name	the name of data in the collection.
       * @return the related data.
       */
      BundledObject *Get( const std::string &name ) const;
   
      /**
       * Sets the given primitive data with the specified name in the collection.
       * Available primitive types are Uchar, Char, Short, Float...
       * <br>Prefer the use of the macro: SETVALUE(name,type,value).
       * <br>See @ref collection_page.
       * @param name	the name of data in the collection.
       * @param val	the primitive value.
       */
      template< typename T >
      void SetValue( const std::string &name, const T &val ) {
	 Set(name,new BundledValue< T >(val));
      }
   
      /**
       * Gets the given primitive data with the specified name in the collection.
       * Available primitive types are Uchar, Char, Slong, Float...
       * <br>Prefer the use of the macro: GETVALUE(name,type);
       * <br>See @ref collection_page.
       * @param name	the name of data in the collection.
       * @param val	the primitive value.
       * @return	the value.
       */
      template< typename T >
      T &GetValue( const std::string & name, const T * /*val*/ ) const {
	 BundledValue<T>* bvp = dynamic_cast< BundledValue<T>* >(Get(name));
	 if (!bvp) { // Panic
	    std::cerr << "Error: cannot convert `"<< name.c_str() <<"' to `" 
		      << TypeName<T>::Name().c_str() << "'." << std::endl;
	    Exit(FAILURE);
	 }
	 return bvp->Value();
      } 
   
      /**
       * Sets the given array of primitive data with the specified name
       * in the collection.
       * Available primitive type are Uchar, Char, Short, Float...
       * <br>Prefer the use of the macro: SETARRAY(name,type,pointer_to_array,number_of_items).
       * <br>See @ref collection_page.
       * @param name	the name of the array of data in the collection.
       * @param val	the array of primitive data.
       * @param size	the size of the array of primitive data.
       */
      template< typename T >
      void SetArray( const std::string &name, T *val, Long size ) {
	 Set(name, new BundledArray< T >(val,size));
      }
   
      /**
       * Returns the array of data with the specified name from the collection.
       * <br>Prefer the use of the macro: GETARRAY(name,type) and
       * GETARRAYSIZE(name,type).
       * <br>See @ref collection_page.
       * @param name	the name of array of data in the collection.
       * @param val	the data.
       * @return	the related array of data.
       */
      template< typename T >
      T* GetArray( const std::string &name, const T * /*val*/ ) const {
	 BundledArray<T>* bap = dynamic_cast< BundledArray<T>* >(Get(name));
	 if (!bap) { // Panic
	    std::cerr << "Error: cannot convert `"<< name.c_str() <<"' to `Array:" 
		      << TypeName<T>::Name().c_str() << "'." << std::endl;
	    Exit(FAILURE);
	 }
	 return bap->Array();
      } 
   
      /**
       * Returns the size of the array of data with the specified name
       * in the collection.
       * @param name	the name of array of data in the collection.
       * <br>Prefer the use of the macro: GETARRAYSIZE(name,type).
       * <br>See @ref collection_page.
       * @param val 	the array of data in the collection.
       * @return	the size of the array.
       */
      template< typename T >
      Long GetArraySize( const std::string &name, const T * /*val*/ ) const {
	 BundledArray<T>* bap = dynamic_cast< BundledArray<T>* >(Get(name));
	 if (!bap) { // Panic
	    std::cerr << "Error: cannot convert `"<< name.c_str() <<"' to `Array:" 
		      << TypeName<T>::Name().c_str() << "'." <<std::endl;
	    Exit(FAILURE);
	 }
	 return bap->NbrElements();
      }
   
      /**
       * Sets the given Pandore object with the specified name in the collection.
       * Available Pandore object is any Pobject.
       * <br>Prefer the use of the macro: SETPOBJECT(name,type,pointer_to_object).
       * <br>See @ref collection_page.
       * @param name	the name of the Pandore object in the collection.
       * @param val	the Pandore object.
       */
      template< typename T >
      void SetPobject( const std::string &name, T *val ) {
	 Set(name,new BundledPobject(val));
      }
   
      /**
       * Returns the Pandore object with the specified name from the collection.
       * <br>Prefer the use of the macro: GETPOBJECT(name,type).
       * <br>See @ref collection_page.
       * @param name	the name of Pandore object in the collection.
       * @param val 	a dummy used for polymorphim issue (<i>not used</i>).
       * @return the Pandore object or NULL.
       */
      template< typename T >
      T* GetPobject( const std::string &name, const T * /*val*/ ) const {
	 BundledPobject* bap = dynamic_cast< BundledPobject* >(Get(name));
	 if (!bap) { // Panic
	    std::cerr << "Error: cannot convert `"<< name.c_str() <<"' to `Pobject:" 
		      << TypeName<T>::Name().c_str() << "'." << std::endl;
	    Exit(FAILURE);
	 }
	 return (T*)bap->Object();
      } 
   
      /**
       * Sets the given array of Pandore objects with the specified name
       * in the collection.
       * Available Pandore object are any Pobject.
       * <br>Prefer the use of the macro: SETPARRAY(name,type,pointer_to_object_array,number_of_items).
       * <br>See @ref collection_page.
       * @param name	the name of the array of Pobject in the collection.
       * @param val	the array of Pandore objects.
       * @param size	the size of the array.
       */
      template< typename T >
      void SetPArray( const std::string &name, T *val, Long size ) {
	 Set(name,new BundledPArray((Pobject**)val,size));
      }
   
      /**
       * Returns the array of Pandore objects with the specified name
       * from the collection.
       * <br>Prefer the use of the macro: GETPARRAY(name,type) and
       * GETPARRAYSIZE(name,type).
       * <br>See @ref collection_page.
       * @param name	the name of array of Pobjects in the collection.
       * @param val	the data.
       * @return the related array of Pobject.
       */
      template< typename T >
      T** GetPArray( const std::string &name, const T * /*val*/ ) const {
	 BundledPArray* bap = dynamic_cast< BundledPArray* >(Get(name));
	 if (!bap) { // Panic
	    std::cerr << "Error: cannot convert `"<< name.c_str() <<"' to `PArray:" 
		      << TypeName<T>::Name().c_str() << "'." << std::endl;
	    Exit(FAILURE);
	 }
	 return (T**)bap->PArray();
      } 
   
      /**
       * Returns the size of the Pandore object array with the specified name
       * in the collection.
       * <br>Prefer the use of the macro: GETPARRAYSIZE(name,type).
       * <br>See @ref collection_page.
       * @param name	the name of the object array in the collection.
       * @param val 	the object array in the collection.
       * @return	the size of the array.
       */
      template< typename T >
      Long GetPArraySize( const std::string &name, const T * /*val*/ ) const {
	 BundledPArray* bap = dynamic_cast< BundledPArray* >(Get(name));
	 if (!bap) { // Panic
	    std::cerr << "Error: cannot convert `"<< name.c_str() <<"' to `PArray:" 
		      << TypeName<T>::Name().c_str() << "'." << std::endl;
	    Exit(FAILURE);
	 }
	 return bap->NbrElements();
      } 
   
      /**
       * Returns the list of primitive type arrays with the specified 
       * prefix name in the collection.
       * For a given name "foo", each array is named : foo.0, foo.1,  ...
       * @param name	the prefix name of the arrays in the collection.
       * @param n		the number of arrays to get.
       * @param min_out	use to return the min size of arrays.
       * @param val 	a dummy used for polymorphim issue (<i>not used</i>).
       * @return	the list of arrays.
       */
      template< typename T >
      T** GetNArrays( const std::string &name, Long n, Long &min_out, const T * /*val*/ ) const {
	 char name_in[255]; 
	 T **tmp = NULL;
	 Long nin = MAXLONG;
	 Long n_= MAXLONG;

	 tmp=new T*[n];
	 for (int i = 0; i < n; ++i) {
	    sprintf(name_in, "%s.%d", name.c_str(), i + 1);
	    tmp[i] = this->GETARRAY(name_in,T);
	    n_ = this->GETARRAYSIZE(name_in,T);
	    if (n_ < nin)
	       nin = n_;
	 }
	 min_out = nin;
	 return tmp;
      }
   
   private :
      std::map< std::string, BundledObject* > _objs;
   };

} //End of pandore:: namespace

#endif // __PCOLLECTIONH__
