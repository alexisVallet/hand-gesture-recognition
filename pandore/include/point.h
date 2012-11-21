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
 * @author Alexandre Duret-Lutz. 1999-10-08
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 * @author Régis Clouard - 2004-06-30 (add operators *=, /=...)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file point.h
 * @brief This file contains the definition of the classes points.
 */

#ifndef __PPOINTH__
#define __PPOINTH__

namespace pandore {

class Dimension1d;
class Dimension2d;
class Dimension3d;
class Point1d;
class Point2d;
class Point3d;

/* @brief A trait that returns the name of the object Point1d.
 *
 * TypeName is a trait that returns the name
 * of the object Point1d.
 */
template<>
struct TypeName< Point1d >{
   /*
    * Returns the name of the type.
    * @return	the string with the name.
    */
   static std::string Name() { return "Point1d"; }
};

/* @brief A trait that returns the name of the object Point2d.
 *
 * TypeName is a trait that returns the name
 * of the object Point2d.
 */
template<>
struct TypeName< Point2d >{
   /**
    * Returns the name of the type.
    * @return	the string with the name.
    */
   static std::string Name() { return "Point2d"; }
};

/* @brief A trait that returns the name of the object Point3d.
 *
 * TypeName is a trait that returns the name
 * of the object Point3d.
 */
template<>
struct TypeName< Point3d >{
   /**
    * Returns the name of the type.
    * @return	the string with the name.
    */
   static std::string Name() { return "Point3d"; }
};

/** @brief The base abstract class of all nD-points.
 *
 * This is the abstract class of all the point classes.
 * Concrete classes are:
 * - Point1d
 * - Point2d
 * - Point3d
 *
 * A point represents a location in a given coordinate space,
 * specified in Long precision.
 * A Point is a Pobject, and thus can be saved in a file.
 * <br>For the use of Point see @ref point_page.
 */
class Point: public Pobject {
protected:
   Point(){}
   
public:
   ~Point(){}

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
   Pobject* UnMask( const Pobject * /*mask*/,const Pobject * /*reference*/ ) { return this; } 

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

/** @brief A 1D point.
 *
 * A point1d represents a 1D location in (x) coordinate space,
 * specified in Long precision.
 * A Point1d is a Pobject, and thus can be saved in and loaded
 * from a file.<br>
 * Use of Point1d:
 * @code
 * Point1d p1(10);
 * Point1d * p2 = new Point1d(10);
 * Point1d p3; p3.x=10;
 * Point1d p4 = p3 * 2;
 * @endcode
 * <br>For the use of Point1d see @ref point_page.
 */
class Point1d: public Point {
public:
   /** The x coordinate -abscissa. */
   Long x;
   
   /**
    * Returns the magic number of the object
    * (for instance Po_Point1d).
    * @return	the magic number. 
    */
   Typobj Type() const { return(Po_Point1d); } 
   
   /**
    * Returns the type name (for instance "Point1d").
    * @return	the name in a string.
    */
   std::string Name() const { return TypeName< Point1d >::Name();}
  
   /**
    * Constructs and initializes a point at the origin (0)
    * of the coordinate space.
    */
   Point1d(): Point(), x(0) {}

   /**
    * Constructs and initializes a point at the specified (x)
    * location in the coordinate space.
    * @param x	the x coordinate.
    */
   Point1d( Long x ): Point(), x(x) {}

   /**
    * Constructs and initializes a point with the same location
    * as the reference point.
    * @param p	a point
    */
   Point1d( const Point1d& p ): Point(), x(p.x) {}

   /**
    * Constructs and initializes a point with a specified dimension.
    * @param d	a dimension.
    */
   Point1d( const Dimension1d& d ): Point(), x(d.w) {}

   /**
    * Sets the coordinates with the coordinates of specified point.
    * @param pt	a point.
    * @return	the point itself.
    */
   const Point1d& operator=( const Point1d& pt ){ x=pt.x; return *this; }

   /**
    * Checks if the coordinates are equal to the coordinates of the
    * specified point.
    * @param pt	a point.
    * @return	true if coordinates are equal.
    */
   bool operator==( const Point1d& pt ) const { return  pt.x == x; }

   /**
    * Checks if the coordinates are different from the specified coordinates.
    * @param pt	a point.
    * @return	true if coordinates are different.
    */
   bool operator!=( const Point1d& pt ) const { return !(pt==*this); }

   /**
    * Adds the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point1d& operator+=( const Point1d& pt ) {x += pt.x; return *this; }

   /**
    * Subtracts the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point1d& operator-=( const Point1d& pt ) {x -= pt.x; return *this;}

   /**
    * Multiplies the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point1d& operator*=( const Point1d& pt ) {x *= pt.x; return *this;}

   /**
    * Divides the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point1d& operator/=( const Point1d& pt ) {x /= pt.x; return *this;}
   
   /**
    * Returns a new point from the addition
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point1d operator+( const Point1d& pt ) const { return Point1d(x+pt.x); }

   /**
    * Returns a new point from the subtraction
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point1d operator-( const Point1d& pt ) const { return Point1d(x-pt.x); }

   /**
    * Returns a new point from the multiplication
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point1d operator*( const Point1d& pt ) const { return Point1d(x*pt.x); }

   /**
    * Returns a new point from the division
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point1d operator/( const Point1d& pt ) const {return Point1d(x/pt.x);}
   
   /**
    * Creates and returns a distinct copy of this object.
    */
   Pobject* Clone() const { return new Point1d(x); }
   
   /**
    * Loads data from the given file.
    * @param df	the file where to read data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc LoadData( FILE *df ) {
      if (this->Fdecode(&x,sizeof(x),1,df)<1)
	 return FAILURE;
      return SUCCESS;
   }
  
   /**
    * Saves data in the given file.
    * @param df	the file where to save data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveData( FILE *df ) const {
      if (this->Fencode(&x,sizeof(x),1,df)<1)
	 return FAILURE;
      return SUCCESS;
   }
};

/** @brief A 2D point.
 *
 * A point2d represents a 2D location in (x, y) coordinate space,
 * specified in Long precision.
 * A Point2d is a Pobject, and thus can be saved in and 
 * loaded from a file.<br>
 * Use of a Point2d:
 * @code
 * Point2d p1(10,15);
 * Point2d * p2 = new Point2d(10,15);
 * Point2d p3; p.y=10;p3.x=15;
 * Point2d p4 = p3 * 2;
 * @endcode
 * <br>For the use of Point2d see @ref point_page.
 */
class Point2d: public Point {
public:
   /**   The x coordinate -abscissa. */
   Long x;
   /**   The y coordinate -ordinate. */
   Long y;

   /**
    * Returns the magic number of the object
    * (for instance Po_Point2d).
    * @return	the magic number. 
    */
   Typobj Type() const { return(Po_Point2d); } 
   
   /**
    * Returns the type name (for instance "Point2d").
    * @return	the name in a string.
    */
   std::string Name() const { return TypeName< Point2d >::Name();}
   
   /**
    * Constructs and initializes a point at the origin (0,0)
    * of the coordinate space.
    */
   Point2d(): Point(), x(0),y(0) {}

   /**
    * Constructs and initializes a point at the specified (i,i)
    * location in the coordinate space.
    * @param i	the value for x and y coordinates.
    */
   Point2d( Long i ): Point(), x(i), y(i) {}

   /**
    * Constructs and initializes a point at the specified (y,x)
    * location in the coordinate space.
    * @param y	the y coordinate.
    * @param x	the x coordinate.
    */
   Point2d( Long y, Long x ): Point(), x(x), y(y) {}

   /**
    * Constructs and initializes a point with the same location
    * as the reference point.
    * @param p	a point.
    */
   Point2d( const Point2d& p): Point(), x(p.x), y(p.y) {}

   /**
    * Constructs and initializes a point with a specified dimension.
    * @param p	a dimension.
    */
   Point2d( const Dimension2d& p): Point(), x(p.w), y(p.h) {}

   /**
    * Sets the coordinates with the coordinates of specified point.
    * @param pt	a point.
    * @return	the point itself.
    */
   const Point2d& operator=( const Point2d& pt ){ x=pt.x; y=pt.y; return *this; }

   /**
    * Checks if the coordinates are equal to the coordinates of the
    * specified point.
    * @param pt	a point.
    * @return	true if coordinates are equal.
    */
   bool operator==( const Point2d& pt ) const { return  pt.x == x && pt.y == y; }

   /**
    * Checks if the coordinates are different from the specified coordinates.
    * @param pt	a point.
    * @return	true if coordinates are different.
    */
   bool operator!=( const Point2d& pt ) const { return !(pt==*this); }
   
   /**
    * Adds the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point2d& operator+=( const Point2d& pt ) { x += pt.x; y += pt.y; return *this; }

   /**
    * Subtracts the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point2d& operator-=( const Point2d& pt ) { x -= pt.x; y -= pt.y; return *this; }

   /**
    * Divides the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point2d& operator/=( const Point2d& pt ) { x /= pt.x; y /= pt.y; return *this; }

   /**
    * Multiplies the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point2d& operator*=( const Point2d& pt ) { x *= pt.x; y *= pt.y; return *this; }

   /**
    * Returns a new point from the addition
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point2d operator+( const Point2d& pt ) const { return Point2d(y+pt.y,x+pt.x); }
   
   /**
    * Returns a new point from the subtraction
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point2d operator-( const Point2d& pt ) const { return Point2d(y-pt.y,x-pt.x); }
   
   /**
    * Returns a new point from the multiplication
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point2d operator*( const Point2d& pt ) const { return Point2d(y*pt.y,x*pt.x); }

   /**
    * Returns a new point from the division
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point2d operator/( const Point2d& pt ) const { return Point2d(y/pt.y,x/pt.x); }

   /**
    * Creates and returns a distinct copy of this object.
    */
   Pobject* Clone() const { return new Point2d(y,x); }

   /**
    * Loads data from the given file.
    * @param df	the file where to read data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc LoadData( FILE *df ) {
      if (Fdecode(&y,sizeof(y),1,df)<1) return FAILURE;
      if (Fdecode(&x,sizeof(x),1,df)<1) return FAILURE;
      return SUCCESS;
   }

   /**
    * Saves data in the given file.
    * @param df	the file where to save data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveData( FILE *df ) const {
      if (this->Fencode(&y,sizeof(y),1,df)<1) return FAILURE;
      if (this->Fencode(&x,sizeof(x),1,df)<1) return FAILURE;
      return SUCCESS;
   }
};

/** @brief A 3D point.
 *
 * A point3d represents a 3D location in (x, y, z) coordinate space,
 * specified in Long precision.
 * A Point3d is a Pobject, and thus can be saved in and loaded
 * from a file.<br>
 * Use of Point3d:
 * @code
 * Point3d p1(10,15,20);
 * Point3d * p2 = new Point3d(10,15,20);
 * Point3d p3; p3.z=10;p3.y=15;p3.x=20;
 * Point3d p4 = p3 * 2;
 * @endcode
 * <br>For the use of Point3d see @ref point_page.
 */
class Point3d: public Point {
public:
   /**   The z coordinate -abscissa. */
   Long z;
   /**   The y coordinate -ordinate. */
   Long y;
   /**   The x coordinate -depth. */
   Long x;

   /**
    * Returns the magic number of the object
    * (for instance Po_Point3d).
    * @return	the magic number. 
    */
   Typobj Type() const { return(Po_Point3d); } 
   
   /**
    * Returns the type name (for instance "Point3d").
    * @return	the name in a string.
    */
   std::string Name() const { return TypeName< Point3d >::Name();}
  
   /**
    * Constructs and initializes a point at the origin (0,0,0)
    * of the coordinate space.
    */
   Point3d(): Point(), z(0),y(0),x(0){}

   /**
    * Constructs and initializes a point at the specified (i,i,i)
    * location in the coordinate space.
    * @param i	the value for x, y and z coordinates.
    */
   Point3d( Long i ): Point(), z(i), y(i), x(i){}

   /**
    * Constructs and initializes a point at the specified (z,y,x)
    * location in the coordinate space.
    * @param x	the x coordinate.
    * @param y	the y coordinate.
    * @param z	the z coordinate.
    */
   Point3d( Long z, Long y, Long x ): Point(), z(z), y(y), x(x){}

   /**
    * Constructs and initializes a point with a specified dimension.
    * @param p	a dimension.
    */
   Point3d( const Dimension3d& p): Point(), z(p.d), y(p.h), x(p.w) {}

   /**
    * Constructs and initializes a point with the same location
    * as the reference point.
    * @param p	a point.
    */
   Point3d( const Point3d& p): Point(), z(p.z), y(p.y), x(p.x) {}

   /**
    * Sets the coordinates with the coordinates of specified point.
    * @param pt	a point.
    * @return	the point itself.
    */
   Point3d operator=( Point3d pt ) { x=pt.x; y=pt.y; z=pt.z; return *this;}
   
   /**
    * Checks if the coordinates are equal to the coordinates of the
    * specified point.
    * @param pt	a point.
    * @return	true if coordinates are equal.
    */
   bool operator==( const Point3d& pt ) const { return pt.x == x && pt.y == y && pt.z == z; }

   /**
    * Checks if the coordinates are different from the specified coordinates.
    * @param pt	a point.
    * @return	true if coordinates are different.
    */
   bool operator!=( const Point3d& pt ) const { return !(pt==*this); }

   /**
    * Adds the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */ 
   Point3d& operator+=( const Point3d& pt ) { x += pt.x; y += pt.y; z += pt.z; return *this; }

   /**
    * Subtracts the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point3d& operator-=( const Point3d& pt ) { x -= pt.x; y -= pt.y; x -= pt.x; return *this; }

   /**
    * Multiplies the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point3d& operator*=( const Point3d& pt ) { x *= pt.x; y *= pt.y; x *= pt.x; return *this; }

   /**
    * Divides the coordinates with the coordinates of the specified point.
    * @param pt	a point.
    * @return	the objet itself.
    */
   Point3d& operator/=( const Point3d& pt ) { x /= pt.x; y /= pt.y; x /= pt.x; return *this; }

   /**
    * Returns a new point from the addition
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point3d operator+( const Point3d& pt ) const { return Point3d(z+pt.z,y+pt.y,x+pt.x); }
   
   /**
    * Returns a new point from the subtraction
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point3d operator-( const Point3d& pt ) const { return Point3d(z-pt.z,y-pt.y,x-pt.x); }
   
   /**
    * Returns a new point from the multiplication
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point3d operator*( const Point3d& pt ) const { return Point3d(z*pt.z,y*pt.y,x*pt.x); }
   
   /**
    * Returns a new point from the division
    * of the coordinates of the object with the coordinates of the specified 
    * point.
    * @param pt	the specified point.
    * @return	a new point.
    */
   Point3d operator/( const Point3d& pt ) const { return Point3d(z/pt.z,y/pt.y,x/pt.x); }

   /**
    * Creates and returns a distinct copy of this object.
    */
   Pobject* Clone() const { return new Point3d(z,y,x); }

   /**
    * Loads data from the given file.
    * @param df	the file where to read data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc LoadData( FILE *df ) {
      if (this->Fdecode(&z,sizeof(z),1,df)<1) return FAILURE;
      if (this->Fdecode(&y,sizeof(y),1,df)<1) return FAILURE;
      if (this->Fdecode(&x,sizeof(x),1,df)<1) return FAILURE;
      return SUCCESS;
   }

   /**
    * Saves data in the given file.
    * @param df	the file where to save data. 
    * @return	SUCCESS or FAILURE in case of IO errors.
    */
   Errc SaveData( FILE *df ) const {
      if (this->Fencode(&z,sizeof(z),1,df)<1) return FAILURE;
      if (this->Fencode(&y,sizeof(y),1,df)<1) return FAILURE;
      if (this->Fencode(&x,sizeof(x),1,df)<1) return FAILURE;
      return SUCCESS;
   }
};

} //End of pandore:: namespace

#endif // __PPOINTH__
