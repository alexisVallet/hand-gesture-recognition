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
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2006-11-10 (fix bug on object deletion)
 */

/**
 * @file bundled.h
 * @brief The definition of all BundledObject classes for Collections.
 */

#ifndef __PBUNDLEDH__
#define __PBUNDLEDH__

namespace pandore {
   
   /** @brief A bundled object for collection.
    *
    * A <code>BundledObject</code> is a bundle that contains
    * either: a simple value (Char, Slong...), an array of simple
    * values, a Pandore object (Image, Region, Collection, ..) or an array
    * of Pandore objects.
    */
   class BundledObject {
      protected :
   
	 /**
	  * Creates a new  <code>BundledObject</code>.
	  */
	 BundledObject () : _inversionMode(false), _valid(true) {}

      public :

	 /**
	  * Returns the name of the type of the value in the bundle.
	  * @return	the type of the value.
	  */
	 virtual std::string Type() const = 0;
   
	 /**
	  * Returns a distinct copy of the bundle.
	  * @return	a new bundle.
	  */
	 virtual BundledObject* Clone() const = 0;
   
	 /**
	  * Loads the value in the bundle from the specified file.
	  * @param df	the file descriptor.
	  * @param invert	if true invert low/high bytes.
	  * @return SUCCESS or FAILURE.
	  */
	 virtual Errc Load( FILE *df, bool invert ) = 0;
   
	 /**
	  * Saves the value of the bundle in the specified file.
	  * @param df	the file descriptor.
	  * @return SUCCESS or FAILURE.
	  */
	 virtual Errc Save( FILE *df ) const = 0;
   
	 /**
	  * Returns the number of bytes of the value
	  * stored in the bundle.
	  * @return	the number of bytes.
	  */
	 virtual Long ByteSize() const = 0;

	 /**
	  * Returns the number of elements.
	  * @return	the number of elements.
	  */
	 virtual Long NbrElements() const = 0;
   
	 /**
	  * Appends the given bundle values to the current bundle values
	  * in case of arays.
	  */
	 virtual void Append( BundledObject * ) { }
   
	 /**
	  * Converts the value as a new array of size 1.
	  * @return	a <code>BundledObject</code> with the value.
	  */
	 virtual BundledObject *ToArray()  { return this; }  
   
	 /**
	  * Deletes the bundle.
	  */
	 virtual ~BundledObject() {}

	 /**
	  * Is the value be considered as a valid value?
	  * (e.g. valid() returns true after a successfully loading or a setting).
	  * @return	true if the value is valid.
	  */
	 bool valid() const { return _valid; }
   
   
      protected :
	 /**
	  * Redefines the fread function to be hardware independant.
	  * @param ptr	array to store read elements.
	  * @param size	size of each element
	  * @param nitems	number of element to read.
	  * @param stream	the stream to read. 
	  * @return	the number bytes read.
	  */
	 size_t fdecode( void *ptr, size_t  size,  size_t  nitems,  FILE *stream );
	 /**
	  * Redefines the fwrite function to be hardware independant.
	  * @param ptr	array that contains the elements to write.
	  * @param size	size of each element.
	  * @param nitems	number of element to read.
	  * @param stream	the stream to write. 
	  * @return	the number of byte written.
	  */
	 size_t fencode( void *ptr, size_t size,  size_t  nitems, FILE *stream ) const;
      
	 /** Does it use byte inversion? (big or little endian) */
	 bool _inversionMode;
      
	 /** Is the data be considered as valid (for example after loading)? */
	 bool _valid;
   };

   template<typename T>
   class BundledArray;

   /** @brief A bundled value for collection.
    *
    * A <code>BundledValue</code> is a bundle of a simple value
    * (e.g., Char, Ulong,...).
    */
   template< typename T >
   class BundledValue : public BundledObject {
      public :
   
	 /**
	  * Creates a new bundle with the given value.
	  * @param val	the given value.
	  */
	 BundledValue( const T& val=0 ) : BundledObject(), _val(val) { }
   
	 /**
	  * Deletes the bundle.
	  */
	 ~BundledValue() {}
   
	 /**
	  * Returns a distinct copy of the bundle.
	  * @return	a new bundle.
	  */
	 BundledObject* Clone() const { return new BundledValue( _val ); }
	 
	 /**
	  * Returns the name of the type of the value in the bundle.
	  * @return	the type of the value.
	  */
	 std::string Type() const { return TypeName< T >::Name(); }
   
	 /**
	  * Loads the value in the bundle from the specified file.
	  * @param df	the file descriptor.
	  * @param invert	if true invert low/high bytes.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Load( FILE *df, bool invert ) {
	    _inversionMode=invert;
	    return (_valid = !(this->fdecode((void*)&_val,sizeof(T),1,df) < 1));
	 }

	 /**
	  * Saves the value of the bundle in the specified file.
	  * @param df	the file descriptor.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Save( FILE *df ) const {
	    return (fencode((void*)&_val,sizeof(_val),1,df) < 1)?FAILURE:SUCCESS; 
	 }
   
	 /**
	  * Returns the number of bytes of the value (e.g., sizeof(type)).
	  * @return	the number of bytes.
	  */
	 Long ByteSize() const { return sizeof(T); }
   
	 /**
	  * Returns the number of elements.
	  * @return	the number of elements.
	  */
	 Long NbrElements() const { return 1; }

	 /**
	  * Converts the value as a new array of size 1.
	  * @return	a <code>BundledArray</code> with the current value.
	  */
	 BundledObject *ToArray() {
	    T *z = new T[1];
	    *z = _val;
	    return new BundledArray<T>(z,1,true);
	 }

	 /**
	  * Returns the value in the bundle.
	  * @return	the current value.
	  */
	 T& Value() { return _val; }
   
      private :
	 /** The value. */
	 T _val;
   };

   /** @brief A bundled array of values for collection.
    *
    * A <code>BundledArray</code> is a bundle of an array of
    * simple values (e.g., Uchar, Ulong).
    */
   template< typename T >
   class BundledArray : public BundledObject {
      public :
   
	 /**
	  * Creates a new bundle with the given value.
	  * @param array	the given value.
	  * @param nbelt	the maximum number of elements.
	  * @param allocated	is the data be allocated by the bundle?
	  */
	 BundledArray( T *array, Long nbelt, bool allocated =false ) : BundledObject(), _val(array), _s(nbelt*sizeof(T)), _allocated(allocated) { }
	 
	 /**
	  * Deletes the bundle and its array if
	  * if it was allocated by the bundle.
	  */
	 ~BundledArray() {
	    if (_allocated)
	       delete[] _val;
	 }
   
	 /**
	  * Returns a distinct copy of the bundle.
	  * @return	a new bundle.
	  */
	 BundledObject* Clone() const {
	    T *t = new T[_s/sizeof(T)];
	    for (int i = 0; i < (int)(_s/sizeof(T)); ++i)
	       t[i] = _val[i];
	    return new BundledArray( t, _s/sizeof(T),true );
	 }

	 /**
	  * Appends the given bundle values to the current bundle values.
	  * @param bo	the given bundle.
	  */
	 void Append(BundledObject *bo);

	 /**
	  * Returns the name of the type of the value in the bundle.
	  * @return	the type of the value.
	  */
	 std::string Type() const {
	    return "Array:" + TypeName< T >::Name(); 
	 }
   
	 /**
	  * Loads the array of values in the bundle from the specified file.
	  * @param df	the file descriptor.
	  * @param invert	if true invert low/high bytes.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Load( FILE *df, bool invert ) {
	    _inversionMode=invert;
	    _valid = !(this->fdecode((void*)_val,sizeof(T),_s/sizeof(T),df) < 1);
	    return _valid;
	 }
	 
	 /**
	  * Saves the arrau of values of the bundle in the specified file.
	  * @param df	the file descriptor.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Save( FILE *df ) const { 
	    return (fencode((void*)_val,_s/sizeof(T),sizeof(T),df) < 1)?FAILURE:SUCCESS; 
	 }
	 
	 
	 /**
	  * Returns the number of bytes of the array (e.g., sizeof(type)*NbrElements()).
	  * @return	the number of bytes.
	  */
	 Long ByteSize() const {
	    return _s;
	 }
	 
	 /**
	  * Returns the number of elements in the array.
	  * @return	the number of elements.
	  */
	 Long NbrElements() const {
	    return _s/sizeof(T);
	 }
	 
	 /**
	  * Returns the current array.
	  * @return	the current array.
	  */
	 T* Array() { return _val; }
   
      private :
	 /** The array of values. */
	 T* _val;
   
	 /** The length of the array. */
	 Long _s;
   
	 /** Is the array allocated by the bundle? */
	 bool _allocated;
   };

   /** @brief A bundled Pandore object for collection.
    *
    * <code>BundledPobject</code> is a bundle of a Pobject value
    * (e.g., Imx2duc, Reg2d, ...).
    */
   class BundledPobject : public BundledObject {
      public :
   
	 /**
	  * Creates a new bundle with the given Pobject.
	  * @param po	the given pobject.
	  * @param allocated	is the data be allocated by the bundle?
	  */
	 BundledPobject( Pobject* po , bool allocated =false ) : BundledObject(),_val(po), _allocated(allocated) { }
	 /**
	  * Deletes the bundle and the Pobject if it
	  * was allocated by the bundle.
	  */
	 ~BundledPobject() { if (_allocated) delete _val; }
   
	 /**
	  * Returns a distinct copy of the bundle.
	  * @return	a new bundle.
	  */
	 BundledObject* Clone() const{
	    return new BundledPobject( (_val->Clone()), true);
	 } 
   
	 /**
	  * Returns the name of the type of the value in the bundle.
	  * @return	the type of the value.
	  */
	 std::string Type() const {
	    return "Pobject:" + _val->Name(); 
	 } 
	 
	 /**
	  * Loads a pobject in the bundle from the specified file.
	  * @param df	the file descriptor.
	  * @param invert	if true invert low/high bytes.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Load( FILE *df, bool invert ) {
	    _inversionMode=invert;
	    return (_valid= (_val->Load(df,invert)==SUCCESS));
	 }
	 
	 /**
	  * Saves the current pobject in the specified file.
	  * @param df	the file descriptor.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Save( FILE* df ) const {
	    return (_val->Save(df)); 
	 }
	 
	 /**
	  * Converts the value as a new array of size 1.
	  * @return	a <code>BundledPArray</code> with the value.
	  */
	 BundledObject *ToArray();

	 /**
	  * Returns the number of bytes of the object.
	  * @return	the number of bytes.
	  */
	    Long ByteSize() const {
	    return ((Imx3duc*)_val)->VectorSize();
	 } 
	 
	 /**
	  * Returns the number of elements.
	  * @return	the number of elements.
	  */
	 Long NbrElements() const { return 1; }

	 /**
	  * Returns the current pobject in the bundle.
	  * @return the current pobject.
	  */
	 Pobject* Object() { return _val;}
   
      private :
	 /** The current pobject. */
	 Pobject* _val;
   
	 /** Is the pobject allocated by the bundle or not? */
	 bool _allocated;
   };

   /** @brief A bundled array of Pandore objects for collection.
    *
    * <code>BundledPArray</code>.is a bundle of an array
    * of a Pobject value (e.g., Imx2duc, Reg2d, ...).
    */
   class BundledPArray : public BundledObject {
      public :
   
	 /**
	  * Creates a new bundle with the given value.
	  * @param po	the given value.
	  * @param nbelt	the maximum number of elements.
	  * @param allocated	is the array be allocated by the bundle?
	  */
	 BundledPArray( Pobject **po, Long nbelt, bool allocated =false ): BundledObject(), _val(po), _s(nbelt*sizeof(Pobject*)), _allocated(allocated) { }

	 /**
	  * Deletes the bundle and the array
	  * if it was allocated by the bundle.
	  */
	 ~BundledPArray() {
	    if (_allocated) {
	       for (int i = 0 ; i < (int)(_s/sizeof(Pobject*)); ++i)
		  delete _val[i];
	       delete[] _val;
	    }
	 }
	 
	 /**
	  * Returns a distinct copy of the bundle.
	  * @return	a new bundle.
	  */
	 BundledObject* Clone() const {
	    Pobject **t = new Pobject*[_s/sizeof(Pobject*)];
	    for (int i = 0; i < (int)(_s/sizeof(Pobject*)); ++i)
	       t[i] = (Pobject*)(_val[i]->Clone());
	    return new BundledPArray( t, _s/sizeof(Pobject*),true);
	 }
   
	 /**
	  * Returns the name of the type of the value in the bundle.
	  * @return	the type of the value.
	  */
	 std::string Type() const {
	    return "PArray:" + _val[0]->Name(); 
	 }

	 /**
	  * Appends the given bundle values to the current bundle values.
	  * @param bo	the given bundle.
	  */
	 void Append( BundledObject* bo );
   
	 /**
	  * Loads an array of pobject in the bundle from the specified file.
	  * @param df	the file descriptor.
	  * @param invert	if true invert low/high bytes.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Load( FILE *df, bool invert ) {
	    _inversionMode=invert;
	    _valid = true;
	    for (int i = 0; i< (int)(_s/sizeof(Pobject*)) && _valid; ++i) {
	       if (_val[i]->Load(df,invert) == FAILURE)
		  _valid = false;
	    }
	    return _valid;
	 }

	 /**
	  * Saves the current array of pobject in the specified file.
	  * @param df	the file descriptor.
	  * @return SUCCESS or FAILURE.
	  */
	 Errc Save( FILE *df ) const  {
	    for (int i = 0; i< (int)(_s/sizeof(Pobject*)); ++i)
	       if (_val[i]->Save(df) == FAILURE)
		  return FAILURE;
	    return SUCCESS; 
	 }

	 /**
	  * Returns the number of bytes of the array of object.
	  * @return	the number of bytes.
	  */
	 Long ByteSize() const {
	    return _s;
	 }

	 /**
	  * Returns the current number of elements in the array.
	  * @return	the number of elements in the array.
	  */
	 Long NbrElements() const {
	    return _s/sizeof(Pobject*);
	 }

	 /**
	  * Returns the current array of pobject.
	  * @return	the array of pobject.
	  */
	 Pobject** PArray() { return _val; }
   
      private :
	 /** The array of pobject. */
	 Pobject** _val;
   
	 /** The size of the array. */
	 Long _s;
   
	 /** Is the array allocated by the bundle? */
	 bool _allocated;
   };
   
   BundledObject* LoadBundledObject( FILE* df,  const std::string& s, Long size , bool inversionMode);
   
} //End of pandore:: namespace

#endif // __PBUNDLEDH__
