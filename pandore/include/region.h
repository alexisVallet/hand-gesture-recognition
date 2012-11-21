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
 * @author Régis Clouard - 2001-04-10 (version 3.0)
 * @author Régis Clouard - 2002-11-29 (version 3.5)
 * @author Régis Clouard - 2002-12-09 (version 4.0)
 * @author Régis Clouard - 2004-07-22 (version 5.0)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2011-01-27 (new pixel array representation-Band3D, 2D & 1D)
 */

/**
 * @file region.h
 * @brief The definition of the classes region maps.
 */

#ifndef __PREGIONH__
#define __PREGIONH__

namespace pandore {
   
   // Definitions of region maps types.
   class Reg1d;
   class Reg2d;
   class Reg3d;
   
   /* @brief Trait that returns the name of the Pandore type TYPE.
    *
    * TypeName is a trait that retunrs the name
    * of the Pandore type T.
    */
   template<>
   struct TypeName< Reg1d > {
	 /**
	  * Returns the name of the type (for instance Reg1d).
	  * @return	the string with the name.
	  */
	 static std::string Name(){ return "Reg1d"; }
   };
   
   /* @brief Trait that returns the name of the Pandore type TYPE.
    *
    * TypeName is a trait that retunrs the name
    * of the Pandore type T.
    */
   template<>
   struct TypeName< Reg2d > {
	 /**
	  * Returns the name of the type.
	  * @return	the string with the name.
	  */
	 static std::string Name(){ return "Reg2d"; }
   };
   
   
   /* @brief Trait that returns the name of the Pandore type TYPE.
    *
    * TypeName is a trait that retunrs the name
    * of the Pandore type T.
    */
   template<>
   struct TypeName< Reg3d > {
	 /**
	  * Returns the name of the type.
	  * @return	the string with the name.
	  */
	 static std::string Name(){ return "Reg3d"; }
   };
   
   /** @brief A 1D region map.
    *
    * A region is defined as a set of connected pixels.@n
    * All the pixels of a same region have the same value
    * (called the label, a value in [0,+4294967295])@n
    * By convention, the region with the label=0 is considered
    * as a non region (the background).@n
    * A <code>Reg1d</code> region map is implemented as a
    * 1D Ulong image where each pixel is a label (in a Ulong precision).@n
    * To create a region:
    * @code
    * Reg1d rgs1(256);
    * Reg1d *rgs2 = new(rgs1.Props());
    * rgs1[21]=10;
    * @endcode
    * <br>For the use of Reg1d images see @ref region_page.
    */
   class Reg1d: public Img1d<Long> {
      protected:
	 /** The maximum label value : could be different from the number of labels if some labels are unused. */
	 Long nlabels;

      public:
	 /** The type of the labels (for instance Ulong). */
	 typedef Ulong ValueType;

	 /**
	  * Returns the region map identifier.
	  * @return	the identifier.
	  */
	 Typobj Type() const { return Po_Reg1d; }

	 /**
	  * Returns the name of the region type (for instance Reg1d).
	  * @return	the string with the name.
	  */
	 std::string Name() const { return TypeName< Reg1d >::Name(); }

	 /**
	  * Returns the current higher label value.
	  * @return	the total label.
	  */
	 Ulong Labels() const { return nlabels; }

	 /**
	  * Sets the new higher label value.
	  * @param n	the new higher label value.
	  * @return	the new higher label value.
	  */
	 Ulong Labels( Ulong n ) { return nlabels=n; }

	 /**
	  * Returns the related vector of properties.
	  * @return	the vector of properties.
	  */
      PobjectProps Props() const { return PobjectProps(nbands,ncol,0,0, (PColorSpace)0, nlabels, nlabels+1); }
   
	 /**
	  * Creates a new region map with no size and no data.
	  */
	 Reg1d(): Img1d<Long>(), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified width. 
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param w	the width of the map.
	  */
	 Reg1d( Long w ): Img1d<Long>(w), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified dimension. 
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param d	the dimension of the map.
	  */
	 Reg1d( const Dimension1d& d ): Img1d<Long>(d), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified properties.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param p	the properties.
	  */
	 Reg1d( const PobjectProps& p ): Img1d<Long>(p.ncol), nlabels(p.nlabels) {}
   
	 /**
	  * Allocates the region map data from the specified width.
	  * @warning the label values are not initialized with 0.
	  * @param w	the width of the map.
	  */
	 void New( Long w ){ Img1d<Long>::New(w); nlabels=0L; }

	 /**
	  * Allocates the region map data from the specified dimension.
	  * @warning the label values are not initialized with 0.
	  * @param d	the dimension of the map.
	  */
	 void New( const Dimension1d& d ){ New(d.w); }

	 /**
	  * Allocates the region map data from the specified properties.
	  * @warning the label values are not initialized with 0.
	  * @param p	the properties of the map.
	  */
	 void New( const PobjectProps& p ) { New(p.ncol); nlabels=p.nlabels; }

	 /**
	  * Deletes the region map data without deleting the object itself.
	  */
	 void Delete (){ Img1d<Long>::Delete(); nlabels = 0L;}

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return	a new region map.
	  */
	 Pobject* Clone( ) const {
	    Reg1d *tmp = new Reg1d(ncol);
	    *tmp = *this;
	    return tmp;
	 }

	 /**
	  * Returns the region data as a vector.
	  * @return	the vector of all data.
	  */
	 ValueType* Vector() const { return (ValueType*)Img1d<Long>::Vector(); }

	 /**
	  * Returns the specified label at the specified column.
	  * @param col	the column number.
	  * @return	the label at the specified coordinate.
	  */
	 ValueType& operator[]( Long col ) { return (ValueType&)Imx1d<Long>::operator[](0)[col]; }

	 /**
	  * Returns the specified label at the specified column.
	  * @param col	the column number.
	  * @return	the label at the specified coordinate.
	  */
	 const ValueType& operator[]( Long col ) const { return (ValueType&)Imx1d<Long>::operator[](0)[col]; }
   
	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param col	the column number.
	  * @return	the label at the specified coordinate.
	  */
	 ValueType& operator()( Long col ) { return (ValueType&)Imx1d<Long>::operator()(0,col); }
   
	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param col	the column number.
	  * @return	the label at the specified coordinate.
	  */
	 const ValueType& operator()( Long col ) const { return (ValueType&)Imx1d<Long>::operator()(0,col); }

	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param p	the coordinates.
	  * @return	the label at the specified coordinate.
	  */
	 ValueType& operator[]( const Point1d& p ) { return (ValueType&)Imx1d<Long>::operator[](0)[p.x]; }
   
	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param p	the coordinates.
	  * @return	the label at the specified coordinate.
	  */
	 const ValueType& operator[]( const Point1d& p ) const { return (ValueType&)Imx1d<Long>::operator[](0)[p.x]; }
   
	 /**
	  * Sets the labels with the given value.
	  * This also sets the higher label value with the given value.
	  * @param val	the value.
	  * @return	the region map itself.
	  */
	 Reg1d& operator=(const Reg1d::ValueType val) {
	    Img1d<Long>::operator=(val);
	    nlabels=(val>0)? val:0;
	    return *this;
	 }

	 /**
	  * Sets the region map labels with the specified region map labels.
	  * @param rgs	a region map.
	  * @return	the region map itself.
	  */
	 Reg1d& operator=(const Reg1d &rgs) {
	    nlabels = rgs.nlabels;
	    memcpy(Vector(),rgs.Vector(),ncol*sizeof(Reg1d::ValueType));
	    return *this;
	 }
   
	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @param file	the file where to read attributes values. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE *file );

	 /**
	  * Saves the current attribute values.
	  * @param file	the file.
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE *file ) const ;
   
	 /**
	  * Loads data from the given file.
	  * @param file	the file where to read data. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadData( FILE *file );
   
	 /**
	  * Saves data in the given file.
	  * @param file	the file where to save data. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveData( FILE *file ) const;
   
	 /**
	  * Creates a new Pobject of the same type but
	  * where the data are masked by the given mask.
	  * It means that value are set to 0 when the related
	  * label in the mask is 0.
	  * @param mask the region map that is used as a mask. 
	  * @return	a new region map.
	  */
	 Pobject *Mask( const Pobject *mask );
   
	 /**
	  * Creates a new region map where the data
	  * are ummasked by the given mask and the given reference image.
	  * It means that values are set to the value of the
	  * reference object when the related label in the mask is 0.
	  * @param mask the region map that is used as a mask. 
	  * @param reference	the object that is used as a reference. 
	  * @return	a new region map.
	  */
	 Pobject *UnMask( const Pobject *mask,const Pobject *reference );
   
	 /**
	  * Creates the region content by copy. Allocates the related
	  * data and sets the values with the rgs values. If needed
	  * casts the values by using the C casting.
	  * @param rgs the specified region.
	  */
	 Reg1d( const Reg1d &rgs ): Img1d<Long>() { New(rgs.Props()); *this=rgs; } 
   };

/** @brief A 2D region map.
 *
 * A region is defined as a set of connected pixels.@n
 * All the pixels of a same region have the same value
 * (called the label, a value in [0,+4294967295])@n
 * By convention, the region with the label=0 is considered
 * as a non region (the background).@n
 * A <code>Reg2d</code> region map is implemented as a
 * 2D Ulong image where each pixel is a label (in a Ulong precision).@n
 * To create a region:
 * @code
 * Reg2d rgs1(256,256);
 * Reg2d *rgs2 = new(rgs1.Props());
 * rgs1[10][21]=10;
 * @endcode
 * <br>For the use of Reg2d images see @ref region_page.
 */
   class Reg2d: public Img2d<Long> {
      public:
	 /** @brief The 1D image data.
	  *
	  * A Band1D addresses region data as data vector.
	  */
	 class Band1dr {
	    public:
	       // 1D data accessors.
	       /**
		* Stores the offset in the array of data
		* that corresponds to the beginning of the
		* vector of specified band.
		* @param offset the offset into the array.
		*/
	       explicit Band1dr( const Imx3d<Long> * const region, Long *offset ) : _region(region), _offset(offset) {}
	       Ulong &operator[]( Long x ){ return (Ulong&)_offset[x]; }
	       const Ulong &operator[]( Long x ) const { return (Ulong&)_offset[x]; }
	    private:
	       const Imx3d<Long> *_region;
	       Long *_offset;
	 };
	 

	 /** The maximum label value: could be different from the number of labels if some labels are unused. */
	 Ulong nlabels;

      public:
	 /** The type of the labels (for instance Ulong). */
	 typedef Ulong ValueType;

	 /**
	  * Returns the region map identifier.
	  * @return	the identifier.
	  */
	 Typobj Type() const { return Po_Reg2d; }

	 /**
	  * Returns the name of the region type (for instance Reg2d).
	  * @return	the string with the name.
	  */
	 std::string Name() const { return TypeName< Reg2d >::Name(); }

	 /**
	  * Returns the higher label value.
	  * @return	the higher label value.
	  */
	 Ulong Labels() const { return nlabels; }

	 /**
	  * Sets the new higher label value.
	  * @param n	the new higher label value.
	  * @return	the new higher label value.
	  */
	 Ulong Labels( Ulong n ) { return nlabels=n; }

	 /**
	  * Returns the related vector of properties.
	  * @return	the vector of properties.
	  */
      PobjectProps Props() const { return PobjectProps(nbands, ncol, nrow,0, (PColorSpace)0, nlabels, nlabels+1); }
   
	 /**
	  * Creates a new region map with no size and no data.
	  */
	 Reg2d(): Img2d<Long>(), nlabels(0){}

	 /**
	  * Creates a new region map with the specified width and height.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param h	the height of the map.
	  * @param w	the width of the map.
	  */
	 Reg2d(Long h,Long w): Img2d<Long>(h,w), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified dimension.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param d	the dimension of the map.
	  */
	 Reg2d(const Dimension2d& d): Img2d<Long>(d), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified properties.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param p	the properties.
	  */
      Reg2d(const PobjectProps& p): Img2d<Long>(p.nrow,p.ncol),nlabels(p.nlabels) { }

	 /**
	  * Allocates the region map data from the specified height and width.
	  * @warning the label values are not initialized with 0.
	  * @param h	the heigth of the map.
	  * @param w	the width of the map.
	  */
	 void New( Long h, Long w ) { Img2d<Long>::New(h,w); nlabels=0L; }

	 /**
	  * Allocates the region map data from the specified dimension.
	  * @warning the label values are not initialized with 0.
	  * @param d	the dimension of the map.
	  */
	 void New( const Dimension2d &d ) { New(d.h,d.w); }

	 /**
	  * Allocates the region map data from the specified properties.
	  * @warning the label values are not initialized with 0.
	  * @param p	the properties of the map.
	  */
	 void New( const PobjectProps &p, Long * data=0 ) {
	    (void)data;
	    New(p.nrow, p.ncol );
	    nlabels=p.nlabels;
	 }

	 /**
	  * Deletes the region map data without deleting the object itself.
	  */
	 void Delete() { Img2d<Long>::Delete(); nlabels = 0L; }

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return	a new region map.
	  */
	 Pobject* Clone( ) const {
	    Reg2d *tmp = new Reg2d(nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }

	 /**
	  * Returns the region data as a vector.
	  * @return	the vector of all data. 
	  */
	 ValueType* Vector() const { return (ValueType*)Img2d<Long>::Vector(); }
      
	 /**
	  * Returns the line at the specified row.
	  * @param row	the row.
	  * @return	the vector at the specified row.
	  */
	 Band1dr operator[]( Long row ) { return Band1dr(this,&_data[ncol*row]); }

	 /**
	  * Returns the line at the specified row.
	  * @param row	the row.
	  * @return	the vector at the specified row.
	  */
	 const Band1dr operator[]( Long row ) const { return Band1dr(this,&_data[ncol*row]); }

	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param y	the y-coordinate.
	  * @param x	the x-coordinate.
	  * @return	the label at the specified coordinates.
	  */
	 ValueType& operator()( Long y, Long x ) { return (ValueType&) Imx2d<Long>::operator()(0,y,x); }
   
	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param y	the y-coordinate.
	  * @param x	the x-coordinate.
	  * @return	the label at the specified coordinates.
	  */
	 const ValueType& operator()( Long y, Long x ) const { return (ValueType&)Imx2d<Long>::operator()(0,y,x); }
	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param p	the coordinates.
	  * @return	the label at the specified coordinates.
	  */
	 ValueType& operator[]( const Point2d& p ) { return (ValueType&) Imx2d<Long>::operator()(0,p.y,p.x); }
   
	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param p	the coordinates.
	  * @return	the label at the specified coordinates.
	  */
	 const ValueType& operator[]( const Point2d& p ) const { return (ValueType&)Imx2d<Long>::operator()(0,p.y,p.x); }
   
	 /**
	  * Sets the labels with the given value.
	  * This also sets the higher label value with the given value.
	  * @param val	the value.
	  * @return	the region map itself.
	  */
	 Reg2d& operator=( const Reg2d::ValueType val ) {
	    Img2d<Long>::operator=(val);
	    nlabels=(val>0)? val:0;
	    return *this;
	 }

	 /**
	  * Sets the region map labels with the specified region map labels.
	  * @param reg	a region map.
	  * @return	the region map itself.
	  */
	 Reg2d& operator=( const Reg2d &rgs ) {
	    nlabels = rgs.nlabels;
	    memcpy(Vector(),rgs.Vector(),nrow*ncol*sizeof(Reg2d::ValueType));
	    return *this;
	 }
   
	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @param file	the file where to read attributes values. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE *file );

	 /**
	  * Saves the current attribute values.
	  * @param file	the file.
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE *file ) const;
	 /**
	  * Loads data from the given file.
	  * @param file	the file where to read data. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadData( FILE *file );

	 /**
	  * Saves data in the given file.
	  * Allocates therefrom the related data.
	  * @param file	the file where to save data. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveData( FILE *file ) const;

	 /**
	  * Creates a new Pobject of the same type but
	  * where the data are masked by the given mask.
	  * It means that value are set to 0 when the related
	  * label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @return	a new region map.
	  */
	 Pobject* Mask( const Pobject *mask ) ;

	 /**
	  * Creates a new region map where the data
	  * are ummasked by the given mask and the given reference image.
	  * It means that values are set to the value of the
	  * reference object when the related label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @param reference	the object that is used as a reference. 
	  * @return	a new region map.
	  */
	 Pobject* UnMask( const Pobject *mask,const Pobject *reference ) ;

	 /**
	  * Creates the region content by copy. Allocates the related
	  * data and sets the values with the rgs values. If needed
	  * casts the values by using the C casting.
	  * @param rgs	the specified image.
	  */
	 Reg2d( const Reg2d &rgs ): Img2d<Long>() { New(rgs.Props()); *this=rgs; }
   };

/** @brief A 3D region map.
 *
 * A region is defined as a set of connected pixels.@n
 * All the pixels of a same region have the same value
 * (called the label, a value in [0,+4294967295])@n
 * By convention, the region with the label=0 is considered
 * as a non region (the background).@n
 * A <code>Reg3d</code> region map is implemented as a
 * 3D Ulong image where each pixel is a label (in a Ulong precision).@n
 * To create a region:
 * @code
 * Reg3d rgs1(100,256,256);
 * Reg3d *rgs2 = new(rgs1.Props());
 * rgs1[5][10][21]=10;
 * @endcode
 * <br>For the use of Reg3d images see @ref region_page.
 */
   class Reg3d: public Img3d<Long> {
	 /** @brief The 2D region data.
	  *
	  * A Band2D addresses region data as 2D matrix. It allows to index
	  * a vector as matrix.
	  */
	 class Band2dr {
	    public:
	       // 2D data accessors.
	       /**
		* Stores the offset in the array of data
		* that corresponds to the beginning of the
		* matrix of specified band.
		* @param offset the offset into the array.
		*/
	       explicit Band2dr( const Imx3d<Long> *region, Long *offset ) : _region(region), _offset(offset) {}
	       explicit Band2dr(): _region(0), _offset(0) {};
	       Reg2d::Band1dr operator[]( Long y ){ return Reg2d::Band1dr(_region, &_offset[_region->Width()*y]); }
	       const Reg2d::Band1dr operator[]( Long y ) const { return Reg2d::Band1dr(_region, &_offset[_region->Width()*y]); }
	    private:
	       const Imx3d<Long> *_region;
	       Long *_offset;
	 };
      protected:
	 /** The maximum label value: could be different from the number of labels if some labels are unused. */
	 Ulong nlabels;

      public:
	 /** The type of the labels (for instance Ulong). */
	 typedef Ulong ValueType;

	 /**
	  * Returns the region map identifier.
	  * @return	the identifier.
	  */
	 Typobj Type() const { return Po_Reg3d; }

	 /**
	  * Returns the name of the region type (for instance Reg3d).
	  * @return	the string with the name.
	  */
	 std::string Name() const { return TypeName< Reg3d >::Name(); }

	 /**
	  * Returns the current higher label value.
	  * @return	the higher label value.
	  */
	 Ulong Labels() const { return nlabels; }

	 /**
	  * Sets the new higher label value.
	  * @param n	the new higher label value.
	  * @return	the new higher label value.
	  */
	 Ulong Labels( Ulong n ) { return nlabels=n; }

	 /**
	  * Returns the related vector of properties.
	  * @return	the vector of properties.
	  */
	 PobjectProps Props() const {return PobjectProps(nbands,ncol,nrow,ndep,(PColorSpace)0,nlabels,nlabels+1);};

	 /**
	  * Creates a new region map with no size and no data.
	  */
	 Reg3d(): Img3d<Long>(), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified width, height and depth.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param d	the depth of the map.
	  * @param h	the height of the map.
	  * @param w	the width of the map.
	  */
	 Reg3d( Long d, Long h, Long w ): Img3d<Long>(d,h,w), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified dimension.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param d	the dimension of the map.
	  */
	 Reg3d( const Dimension3d& d ): Img3d<Long>(d), nlabels(0) {}

	 /**
	  * Creates a new region map with the specified properties.
	  * Allocates therefrom the related data.
	  * @warning the label values are not initialized with 0.
	  * @param p	the properties.
	  */
	 Reg3d(const PobjectProps& p): Img3d<Long>(p.ndep,p.nrow,p.ncol),nlabels(p.nlabels) {}

	 /**
	  * Allocates the region map data from the specified depth, height and width.
	  * @warning the label values are not initialized with 0.
	  * @param d	the depth of the map.
	  * @param h	the heigth of the map.
	  * @param w	the width of the map.
	  */
	 void New( Long d, Long h, Long w ) { Img3d<Long>::New(d,h,w); nlabels=0L; }

	 /**
	  * Allocates the region map data from the specified dimension.
	  * @warning the label values are not initialized with 0.
	  * @param d	the dimension of the map.
	  */
	 void New( const Dimension3d& d ){ New(d.d,d.h,d.w); }

	 /**
	  * Allocates the region map data from the specified properties.
	  * @warning the label values are not initialized with 0.
	  * @param p	the properties of the map.
	  */
      void New( const PobjectProps& p, Long *data=0 ) { (void)data; New(p.ndep,p.nrow,p.ncol);nlabels=p.nlabels; 
      }
	 /**
	  * Deletes the region map data without deleting the object itself.
	  */
	 void Delete (){ Img3d<Long>::Delete(); nlabels = 0L;}

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return	a new region map.
	  */
	 Pobject* Clone( ) const {
	    Reg3d *tmp = new Reg3d(ndep,nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }

	 /**
	  * Returns the region data as a vector.
	  * @return	the vector of all data.
	  */
	 ValueType* Vector() const { return (ValueType*)Img3d<Long>::Vector(); }
   
	 /**
	  * Sets the labels with the given value.
	  * This also sets the higher label value with the given value.
	  * @param val	the value.
	  * @return	the region map itself.
	  */
	 Reg3d& operator=( const Reg3d::ValueType val ) {
	    Img3d<Long>::operator=(val);
	    nlabels=(val>0)? val:0;
	    return *this;
	 }

	 /**
	  * Sets the region map labels with the specified region map labels.
	  * @param reg	a region map.
	  * @return	the region map itself.
	  */
	 Reg3d& operator=( const Reg3d &rgs ) {
	    nlabels = rgs.nlabels;
	    memcpy(Vector(),rgs.Vector(),ndep*nrow*ncol*sizeof(Reg3d::ValueType));
	    return *this;
	 }

	 /**
	  * Returns the plane at the specified depth.
	  * @param dep	the depth.
	  * @return	the plane at the specified depth.
	  */
	 Band2dr operator[]( Long dep ) { return Band2dr(this,&_data[matrixSize*dep]); }

	 /**
	  * Returns the plane at the specified depth.
	  * @param dep	the depth.
	  * @return	the plane at the specified depth.
	  */
	 const Band2dr operator[]( Long dep ) const { return Band2dr(this,&_data[matrixSize*dep]); }

	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param z	the z-coordinate.
	  * @param y	the y-coordinate.
	  * @param x	the x-coordinate.
	  * @return	the label at the specified coordinates.
	  */
	 ValueType& operator()( Long z, Long y, Long x ) { return (ValueType&) Imx3d<Long>::operator()(0,z,y,x); }

	 /**
	  * Returns the specified label at the specified coordinates.
	  * Returns the specified label at the specified coordinates.
	  * @param z	the z-coordinate.
	  * @param y	the y-coordinate.
	  * @param x	the x-coordinate.
	  * @return	the label at the specified coordinates.
	  */
	 const ValueType& operator()( Long z, Long y, Long x ) const { return (ValueType&)Imx3d<Long>::operator()(0,z,y,x); }

	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param p	the coordinates.
	  * @return	the label at the specified coordinates.
	  */
	 ValueType& operator[]( const Point3d& p ) { return (ValueType&) Imx3d<Long>::operator()(0,p.z,p.y,p.x); }

	 /**
	  * Returns the specified label at the specified coordinates.
	  * @param p	the coordinates.
	  * @return	the label at the specified coordinates.
	  */
	 const ValueType& operator[]( const Point3d& p ) const { return (ValueType&)Imx3d<Long>::operator()(0,p.z,p.y,p.x); }

	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @param file	²the file where to read attributes values. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE *file );

	 /**
	  * Saves the current attribute values.
	  * @param file	the file.
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE *file ) const;

	 /**
	  * Loads data from the given file.
	  * @param file	the file where to read data. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadData( FILE *file );

	 /**
	  * Saves data in the given file.
	  * Allocates therefrom the related data.
	  * @param file	the file where to save data. 
	  * @return	SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveData( FILE *file ) const;

	 /**
	  * Creates a new Reg3d where the data are masked by the given mask.
	  * It means that value are set to 0 when the related
	  * label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @return	a new region map.
	  */
	 Pobject* Mask( const Pobject *mask ) ;

	 /**
	  * Creates a new region map where the data
	  * are ummasked by the given mask and the given reference image.
	  * It means that values are set to the value of the
	  * reference object when the related label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @param reference	the object that is used as a reference. 
	  * @return	a new region map.
	  */
	 Pobject* UnMask( const Pobject *mask,const Pobject *reference ) ;

	 /**
	  * Creates the region content by copy. Allocates the related
	  * data and sets the values with the rgs values. If needed
	  * casts the values by using the C casting.
	  * @param rgs	the specified image.
	  */
	 Reg3d( const Reg3d &rgs ): Img3d<Long>() { New(rgs.Props()); *this=rgs; }
   };

} //End of pandore:: namespace


#endif // __PREGIONH__
