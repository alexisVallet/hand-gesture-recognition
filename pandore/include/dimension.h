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
 * @author Francois Angot - 1999-10-08
 * @author Alexandre Duret-Lutz. 1999-10-08
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 * @author Régis Clouard - 2004-06-30 (add operators *=, /=...)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file dimension.h
 * @brief The definition of the classes Dimensions.
 */

#ifndef __PDIMENSIONH__
#define __PDIMENSIONH__

namespace pandore {

class Dimension1d;
class Dimension2d;
class Dimension3d;

/* @brief A trait that returns the name of the object Dimension1d.
 *
 * TypeName is a trait that returns the name
 * of the object Dimension1d.
 */
template<>
struct TypeName< Dimension1d >{
   /*
    * Returns the name of the type.
    * @return	the string with the name.
    */
   static ::std::string Name() { return "Dimension1d"; }
};

/* @brief A trait that returns the name of the object Dimension2d.
 *
 * TypeName is a trait that returns the name
 * of the object Dimension2d.
 */
template<>
struct TypeName< Dimension2d >{
   /*
    * Returns the name of the type.
    * @return	the string with the name.
    */
   static std::string Name() { return "Dimension2d"; }
};

/* @brief A trait that returns the name of the object Dimension3d.
 *
 * TypeName is a trait that returns the name
 * of the object Dimension3d.
 */
template<>
struct TypeName< Dimension3d >{
   /*
    * Returns the name of the type.
    * @return	the string with the name.
    */
   static std::string Name() { return "Dimension3d"; }
};

/** @brief The base abstract class of all nD-dimensions.
 *
 * This is the abstract class of all the dimension classes.
 * Concrete classes are:
 * - Dimension1d
 * - Dimension2d
 * - Dimension3d
 *
 * A dimension encapusles size measures specified in Long precision.
 * A Dimension is a Pobject, and thus can be saved in and load from a file.
 * <br>For the use of Dimension see @ref dimension_page.
 */
class Dimension: public Pobject {
protected:
   Dimension(){}
   
public:
   ~Dimension(){}

   /**
    * Not implemented. Returns the objet itself.
    * @param mask	the region map that is used as a mask. 
    * @return	the objet itself.
    */
   Pobject* Mask( const Pobject * /*mask*/ ) { return this; }

   /**
    * Not implemented. Returns the objet itself.
    * @param mask	the region map that is used as a mask. 
    * @param reference	the object that is used as a reference. 
    * @return	the object itself.
    */
   Pobject* UnMask( const Pobject * /*mask*/ ,const Pobject * /*reference*/ ) { return this; } 

   /**
    * Loads attribute values from the given file.
    * Allocates therefrom the related data.
    * @param df	the file where to read attributes values. 
    * @return	SUCCESS or FAILURE  in case of IO errors.
    */
   Errc LoadAttributes( FILE* /*df*/ ){ return SUCCESS; }

   /**
    * Saves the current attribute values.
    * @param df	the file.
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveAttributes( FILE* /*df*/ ) const { return SUCCESS; }
};

/** @brief A 1D dimension.
 *
 * The Dimension1d class encapsulates the width
 * of a component (in Long precision) in a single object.
 * <br>Use of Dimension1d:
 * @code
 * Dimension1d d1(10);
 * Dimension1d * d2 = new Dimension1d(10);
 * Dimension1d d3; d3.w=10;
 * Dimension1d d4 = d3 * 2;
 * if (d4==d3) { ... }
 * @endcode
 * <br>For the use of Dimension1d see @ref dimension_page.
 */
class Dimension1d: public Dimension {
public:
   /** The width dimension; negative values can be used. */
   Long w;

   /**
    * Returns the magic number of the object
    * (for instance Po_Dimension1d).
    * @return	the magic number. 
    */
   Typobj Type() const { return(Po_Dimension1d); } 
   
   /**
    * Returns the type name (for instance "Dimension1d").
    * @return	the name in a string.
    */
   std::string Name() const { return TypeName< Dimension1d >::Name();}

   /**
    * Creates a 1D dimension with a width of zero.
    */
   Dimension1d(): Dimension(), w(0) {}
   
   /**
    * Creates a 1D dimension with the specified width value.
    * @param width	the specified width value.
    */
   Dimension1d( Long width ): Dimension(), w(width) {}

   /**
    * Creates a 1D dimension with the specified dimension.
    * @param d	the specified dimension.
    */
   Dimension1d( const Dimension1d& d ): Dimension(), w(d.w) {}

   /**
    * Sets the new dimension value with the specified dimension value.
    * @param d	the specified dimension.
    * @return the specified dimension.
    */
   const Dimension1d& operator=( const Dimension1d& d ){ w=d.w; return *this; }

   /**
    * Checks if the dimension is equal to a reference dimension.
    * @param d	the reference dimension.
    * @return true if dimensions are equal.
    */
   bool operator==( const Dimension1d& d ) const { return d.w == w; }

   /**
    * Checks if the dimension is different from a reference dimension.
    * @param d	the reference dimension.
    * @return true if dimensions are different.
    */
   bool operator!=( const Dimension1d& d ) const { return !(d==*this); }

   /**
    * Creates a new 1D dimension from the addition
    * of the dimension value by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension1d operator+( int x ) const { return Dimension1d(w+x); }

   /**
    * Creates a new 1D dimension from the subtraction
    * of the dimension value by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension1d operator-( int x ) const { return Dimension1d(w-x); }


   /**
    * Creates a new 1D dimension from the multiplication
    * of the dimension value by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension1d operator*( int x ) const { return Dimension1d(w*x); }

   /**
    * Creates a new 1D dimension from the division
    * of the dimension value by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension1d operator/( int x ) const { return Dimension1d(w/x); }

   /**
    * Creates and returns a distinct copy of this object.
    */
   Pobject* Clone() const { return new Dimension1d(w); }   

   /**
    * Loads data from the given file.
    * @param df	the file where to read data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc LoadData( FILE *df ) {
      if (this->Fdecode(&w,sizeof(w),1,df)<1)
	 return FAILURE;
      return SUCCESS;
   }
  
   /**
    * Saves data in the given file.
    * @param df	the file where to save data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveData( FILE *df ) const {
      if (this->Fencode(&w,sizeof(w),1,df)<1)
	 return FAILURE;
      return SUCCESS;
   }
};

/**
 * Creates a new 1D dimension that results from the multiplication
 * of the specified dimension by x.
 * @param d	the dimension.
 * @param x	the multiplier.
 * @return	a new dimension.
 */
inline const Dimension1d operator*( int x, const Dimension1d &d ){ return Dimension1d(d.w*x);}

/** @brief A 2D dimension.
 *
 * The <code>Dimension2d</code> class encapsulates the width and the height
 * of a component (in Long precision) in a single object.
 * <br>Use of Dimension2d:
 * @code
 * Dimension2d d1(20,10);
 * Dimension2d * d2 = new Dimension2d(20,10);
 * Dimension2d d3; d3.h=20;d3.w=10;
 * Dimension2d d4 = d3 * 2;
 * if (d3==d4) { ... }
 * @endcode
 * <br>For the use of Dimension2d see @ref dimension_page.
 */
class Dimension2d: public Dimension {
public:
   /** The width dimension; negative values can be used. */
   Long w;
   /** The height dimension; negative values can be used. */
   Long h;

   /**
    * Returns the magic number of the object
    * (for instance Po_Dimension2d).
    * @return	the magic number. 
    */
   Typobj Type() const { return(Po_Dimension2d); } 
   
   /**
    * Returns the type name (for instance "Dimension2d").
    * @return	the name in a string.
    */
   std::string Name() const { return TypeName< Dimension2d >::Name();}

   /**
    * Creates a 2D dimension with a width of zero and a height of zero.
    */
   Dimension2d(): Dimension(), w(0),h(0) {}

   /**
    * Creates a 2D dimension with the specified width and height values.
    * @param height	the specified width.
    * @param width	the specified height.
    */
   Dimension2d( Long height, Long width ): Dimension(), w(width), h(height) {}

   /**
    * Creates a 2D dimension with the specified dimension.
    * @param d	the specified dimension for the width and the height values.
    */
   Dimension2d( const Dimension2d& d ): Dimension(), w(d.w), h(d.h) {}

   /**
    * Sets the new dimension values with the specified dimension values.
    * @param d	the specified dimension.
    * @return the specified dimension.
    */
   const Dimension2d& operator=(const Dimension2d& d){ w=d.w; h=d.h; return *this; }
   
   /**
    * Checks if the dimension is equal to a reference dimension.
    * @param d	the reference dimension.
    * @return true if dimensions are equal.
    */
   bool operator==( const Dimension2d& d ) const { return  d.w == w && d.h == h; }

   /**
    * Checks if the dimension is different from a reference dimension.
    * @param d	the reference dimension.
    * @return true if dimensions are different.
    */
   bool operator!=( const Dimension2d& d ) const { return !(d==*this); }
   
   /**
    * Creates a new 2D dimension from the addition
    * of each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension2d operator+( int x ) const { return Dimension2d(h+x,w+x);}
   
   /**
    * Creates a new 2D dimension from the subtraction
    * of the each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension2d operator-( int x ) const { return Dimension2d(h-x,w-x);}

   /**
    * Creates a new 2D dimension from the multiplication
    * of each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension2d operator*( int x ) const { return Dimension2d(h*x,w*x);}
   
   /**
    * Creates a new 2D dimension from the division
    * of the each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension2d operator/( int x ) const { return Dimension2d(h/x,w/x);}

   /**
    * Creates and returns a distinct copy of this object.
    */
   Pobject* Clone() const { return new Dimension2d(h,w); }   

   /**
    * Loads data from the given file.
    * @param df	the file where to read data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc LoadData( FILE *df ) {
      if (Fdecode(&h,sizeof(h),1,df)<1) return FAILURE;
      if (Fdecode(&w,sizeof(w),1,df)<1) return FAILURE;
      return SUCCESS;
   }

   /**
    * Saves data in the given file.
    * @param df	the file where to save data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveData( FILE *df ) const {
      if (this->Fencode(&h,sizeof(h),1,df)<1) return FAILURE;
      if (this->Fencode(&w,sizeof(w),1,df)<1) return FAILURE;
      return SUCCESS;
   }
};

/**
 * Creates a new 2D dimension that results from the multiplication
 * of the specified dimension by x.
 * @param d	the dimension.
 * @param x	the multiplier.
 * @return	a new dimension.
 */
inline const Dimension2d operator*( int x, const Dimension2d &d ){ return Dimension2d(d.h*x,d.w*x);}

/** @brief A 3D dimension.
 *
 * The <code>Dimension3d</code> class encapsulates the width, the height and the depth
 * of a component (in Long precision) in a single object.
 * <br>Use of Dimension3d:
 * @code
 * Dimension3d d1(30,20,10);
 * Dimension3d * d2 = new Dimension3d(30,20,10);
 * Dimension3d d3; d3.d=30; d3.h=20; d3.w=10;
 * Dimension3d d4 = d3 * 2;
 * if (d3==d4) { ... }
 * @endcode
 * <br>For the use of Dimension3d see @ref dimension_page.
 */
class Dimension3d: public Dimension {
public:
   /** The depth dimension; negative values can be used. */
   Long d;
   /** The height dimension; negative values can be used. */
   Long h;
   /** The width dimension; negative values can be used. */
   Long w;

   /**
    * Returns the magic number of the object
    * (for instance Po_Dimension3d).
    * @return	the magic number. 
    */
   Typobj Type() const { return(Po_Dimension3d); } 
   
   /**
    * Returns the type name (for instance "Dimension3d").
    * @return	the name in a string.
    */
   std::string Name() const { return TypeName< Dimension3d >::Name();}

   /**
    * Creates a 3D dimension with a width of zero,
    * a height of zero and a depth of zero.
    */
   Dimension3d(): Dimension(), d(0), h(0), w(0) {}

   /**
    * Creates a 3D dimension with the specified width, height and depth values.
    * @param depth	the specified depth.
    * @param height	the specified height.
    * @param width	the specified width.
    */
   Dimension3d( Long depth, Long height, Long width ): Dimension(), d(depth), h(height), w(width){}

   /**
    * Creates a 3D dimension with the specified dimension.
    * @param d	the specified dimension for the width, height and depth values.
    */
   Dimension3d( const Dimension3d &d ): Dimension(), d(d.d), h(d.h), w(d.w) {}

   /**
    * Sets the new dimension values with the specified dimension values.
    * @param x	the specified dimension.
    * @return the specified dimension.
    */
   Dimension3d operator=( const Dimension3d &x ) { w=x.w; h=x.h; d=x.d; return *this; }
   
   /**
    * Checks if the dimension is equal to a reference dimension.
    * @param x	the reference dimension.
    * @return true if dimensions are equal.
    */
   bool operator==( const Dimension3d &x ) const{ return x.w == w && x.h == h && x.d == d; }
   
   /**
    * Checks if the dimension is different from a reference dimension.
    * @param x	the reference dimension.
    * @return true if dimensions are different.
    */
   bool operator!=( const Dimension3d &x ) const { return !(x==*this); }
   
   /**
    * Creates a new 3D dimension from the addition
    * of the each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension3d operator+( int x ) const { return Dimension3d(d+x,h+x,w+x); }
   
   /**
    * Creates a new 3D dimension from the subtraction
    * of the each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */ 
   Dimension3d operator-( int x ) const { return Dimension3d(d-x,h-x,w-x); }

   /**
    * Creates a new 3D dimension from the multiplication
    * of the each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */
   Dimension3d operator*( int x ) const { return Dimension3d(d*x,h*x,w*x); }
   
   /**
    * Creates a new 3D dimension from the division
    * of the each dimension values by the specified value.
    * @param x	the specified value.
    * @return	a new dimension.
    */ 
   Dimension3d operator/( int x ) const { return Dimension3d(d/x,h/x,w/x); }

   /**
    * Creates and returns a distinct copy of this object.
    */
   Pobject* Clone() const { return new Dimension3d(d,h,w); }   

   /**
    * Loads data from the given file.
    * @param df	the file where to read data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc LoadData( FILE *df ) {
      if (this->Fdecode(&d,sizeof(d),1,df)<1) return FAILURE;
      if (this->Fdecode(&h,sizeof(h),1,df)<1) return FAILURE;
      if (this->Fdecode(&w,sizeof(w),1,df)<1) return FAILURE;
      return SUCCESS;
   }

   /**
    * Saves data in the given file.
    * @param df	the file where to save data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveData( FILE *df ) const {
      if (this->Fencode(&d,sizeof(d),1,df)<1) return FAILURE;
      if (this->Fencode(&h,sizeof(h),1,df)<1) return FAILURE;
      if (this->Fencode(&w,sizeof(w),1,df)<1) return FAILURE;
      return SUCCESS;
   }
};

/**
 * Creates a new 3D dimension from the multiplication
 * of the specified dimension by the specified value.
 * @param d	the dimension.
 * @param x	the multiplier.
 * @return	a new dimension.
 */
inline const Dimension3d operator*( int x, const Dimension3d &d ){ return Dimension3d(d.d*x,d.h*x,d.w*x);}

} //End of pandore:: namespace

#endif // __PDIMENSIONH__
