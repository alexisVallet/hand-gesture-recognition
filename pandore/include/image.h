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
 * @author Régis Clouard - 1995-10-08
 * @author Francois Angot - 1998-10-01
 * @author Olivier Lezoray - 1999-10-11
 * @author Alexandre Duret-Lutz - 1999-10-11
 * @author Régis Clouard - 2001-04-03 (version 3.00)
 * @author Régis Clouard - 2002-11-28 (version 3.5)
 * @author Régis Clouard - 2002-12-22 (version 4.0: new image types)
 * @author Régis Clouard - 2004-07-21 (version 5.0)
 * @author Régis Clouard - 2004-10-13 (adaptation a gcc 3.4)
 * @author Régis Clouard - 2005-03-25 (fix bug on allocation with predefined data)
 * @author Régis Clouard - 2005-11-07 (free copy constructors: (Image(Image&)).
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2006-05-09 (allocate only one vector for all bands)
 * @author Régis Clouard - 2006-05-22 (extends allocation with predefined data)
 * @author Régis Clouard - 2011-01-27 (new pixel array representation-Band3D & 2D)
 * @author Régis Clouard - Jan 19, 2012 (add 3dimage[0] = 2D image)
 */

/**
 * @file image.h
 *
 * @brief The definition of the various image classes.
 */

#ifndef __PIMAGEH__
#define __PIMAGEH__

namespace pandore {
   
////////// 
////////// Imx3d
//////////

template< typename T > 
class Imx2d;
   
/** @brief The 3D multispectral image.
 *
 * A <code>Imx3d</code> is a multispectral 3D image.
 * It is implemented as n 3D arrays of pixels,
 * where a pixel is of T type and n is the band number.
 * This class is the base class of all other image classes,
 * it means that other image classes are only rewriting
 * of this class. For example, a Img2duc is an image with one
 * band and one plane for the depth dimension.
 * <br>For the use of Imx3d images see @ref image_page.
 */
   template< typename T > 
   class Imx3d: public Pobject {
      protected:
	 /** @brief The 1D image data.
	  *
	  * A Band1D addresses image data as data vector.
	  */
	 class Band1d {
	    public:
	       // 1D data accessors.
	       /**
		* Stores the offset in the array of data
		* that corresponds to the beginning of the
		* vector of specified band.
		* @param image the related image.
		* @param offset the offset into the array.
		*/
	       explicit Band1d( const Imx3d<T> * const image, T *offset ) : _image(image), _offset(offset) {}
	       T &operator[]( Long x ){ return _offset[x]; }
	       const T &operator[]( Long x ) const { return _offset[x]; }
	       T &operator[]( const Point1d &p ){ return _offset[p.x]; }
	       const T & operator[]( const Point1d &p ) const { return _offset[p.x]; }
	    private:
	       const Imx3d<T> *_image;
	       T *_offset;
	 };
	 
	 /** @brief The 2D image data.
	  *
	  * A Band2D addresses image data as 2D matrix. It allows to index
	  * a vector as matrix.
	  */
	 class Band2d {
	    public:
	       // 2D data accessors.
	       /**
		* Stores the offset in the array of data
		* that corresponds to the beginning of the
		* matrix of specified band.
		* @param image the related image.
		* @param offset the offset into the array.
		*/
	       explicit Band2d( const Imx3d<T> * const image, T *offset ) : _image(image), _offset(offset) {}
	       explicit Band2d(): _image(0), _offset(0) {};
	       void New( const Imx3d<T> * const image, T *offset ) { _image=image; _offset=offset; }
	       
	       Band1d operator[]( Long y ){ return Band1d(_image, &_offset[_image->ncol*y]); }
	       const Band1d operator[]( Long y ) const { return Band1d(_image, &_offset[_image->ncol*y]); }
	       T &operator[]( const Point2d &p ){ return _offset[_image->ncol*p.y + p.x]; }
	       const T & operator[]( const Point2d &p ) const { return _offset[_image->ncol*p.y + p.x]; }
//	       T * &operator( )( ) { return &_data[_offset]; } 
	       Band2d& operator=( const Imx2d<T> &ims ) {
		  if (_image->Bands() != ims.Bands( )
		      || _image->Depth() != ims.Depth() 
		      || _image->Height() != ims.Height()
		      || Width() != ims.Width()) {
		    std::cerr << "Error: incomptabiles images for operator: 2D image = 3D image[i]" << std::endl;
		  } else {
		     T *ps = ims.Vector();
		     T *pe = ps+ims.Bands()*ims.nrow*ims.ncol;
		     T *pd = _offset;
		     for (; ps<pe; ) {
			*(pd++) = (T)*(ps++);
		     }
		  }
		  return *this;
	       }
	       Band2d& operator=( const T val ) {
		  T *pd = _offset;
		  T *pe = pd+_image->nbands*_image->nrow*_image->ncol;
		  for (; pd<pe; ) {
		     *(pd++) = val;
		  }
		  return *this;
	       }
	    private:
	       const Imx3d<T> *_image;
	       T *_offset;
	 };

	 /** @brief The 3D image data.
	  *
	  * A Band3d addresses the image data as a 3D volume.It allows to index
	  * a vector as volume.
	  */
	 class Band3d {
	    public:
	       /**
		* Stores the offset in the array of data
		* that corresponds to the beginning of the
		* volume of specified band.
		* @param image the related image.
		* @param offset the offset into the array.
		*/
	       explicit Band3d( const Imx3d<T> * const image, T *offset ) : _image(image), _offset(offset) {}
	       // 3D data accessors.
	       Band2d operator[]( Long z ) { return Band2d(_image,&_offset[_image->matrixSize*z]); }
	       explicit Band3d(): _image(0), _offset(0) {};
	       void New( const Imx3d<T> * const image, T *offset ) { _image=image; _offset=offset; }

	       const Band2d operator[]( Long z ) const { return Band2d(_image, &_offset[_image->matrixSize*z]); }
	       T &operator[]( const Point3d &p ){ return _offset[_image->matrixSize*p.z + _image->ncol*p.y + p.x]; }
	       const T & operator[]( const Point3d &p ) const { return _offset[_image->matrixSize*p.z + _image->ncol*p.y + p.x]; }
	       T &operator()( const Point3d &p ){ return _offset[_image->matrixSize*p.z + _image->ncol*p.y + p.x]; }
	       const T & operator()( const Point3d &p ) const { return _offset[_image->matrixSize*p.z + _image->ncol*p.y + p.x]; }
//	       T * &operator( )( ) { return &_data[_offset]; }
	    private:
	       const Imx3d<T> *_image;
	       T *_offset;
	 };

      protected:
	 /** The memory block for data. */
	 T *_data; 
	 /** Specifies if the data has been created by the image. */
	 bool _isDataOwner;

	 /** The number of bands.*/
	 Long nbands; 
	 /** The number of columns. */
	 Long ncol;
	 /** The number of rows. */
	 Long nrow;
	 /** The number of planes. */
	 Long ndep;
         /** The matrix size */
	 Long matrixSize;         /** The voloume size */
	 Long volumeSize;

      private:
	 /** The color space. @see PColorSpace */
	 PColorSpace colorspace;

      public:
	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Imx3d< T > >::type; }

	 /**
	  * Returns the type name (for instance Imx3duc or Imx3dsl or Imx3dsf).
	  */
	 std::string Name( ) const { return TypeName< Imx3d < T > >::Name( ); }

	 /**
	  * Returns the number of columns.
	  */
	 Long Width( ) const { return ncol; }

	 /**
	  * Returns the number of rows.
	  */
	 Long Height( ) const { return nrow; }

	 /**
	  * Returns the number of planes.
	  */
	 Long Depth( ) const { return ndep; }

	 /**
	  * Returns the number of bands.
	  */
	 Long Bands( ) const { return nbands; }

	 /**
	  * Returns the dimension of the image.
	  */
	 Dimension3d Size( ) const { return Dimension3d(ndep,nrow,ncol); }

	 /**
	  * Returns the number of pixels in the image.
	  */
	 Ulong VectorSize( ) const { return (Ulong)volumeSize; }

	 /**
	  * Returns the related vector of properties.
	  * @return the vector of properties.
	  */
	 PobjectProps Props( ) const { return PobjectProps( nbands, ncol, nrow, ndep, colorspace, 0, ndep*ncol*nrow );}

	 /**
	  * Creates a new image with no size and no data.
	  */
	 Imx3d( ): Pobject( ), _data(0), _isDataOwner(false), nbands(0), ncol(0), nrow(0), ndep(0), matrixSize(0), volumeSize(0), colorspace(RGB) {}

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param d		the depth of the image.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imx3d( Long b, Long d, Long h, Long w, T *data=0 ): Pobject (), _data(0), _isDataOwner(false), nbands(0), ncol(0), nrow(0), ndep(0), matrixSize(0), volumeSize(0), colorspace( RGB ) { New( b,d,h,w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Imx3d( Long b, const Dimension3d &d, T *data=0 ): Pobject ( ), _data(0), _isDataOwner(false), nbands(0), ncol(0), nrow(0), ndep(0), matrixSize(0), volumeSize(0), colorspace(RGB) { New( b,d.d,d.h,d.w,data ); }
	 
	 /**
	  * Creates a new image with the specified properties.
	  * Allocates therefrom the related data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * @param p	the properties.
	  * @param data	the vector of data.
	  */
	 Imx3d( const PobjectProps &p, T *data=0 ): Pobject ( ), _data(0), _isDataOwner(false), nbands(0), ncol(0), nrow(0), ndep(0), matrixSize(0), volumeSize(0) { New( p,data ); }

	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Imx3d( const Imx3d  &ims ): Pobject() { New(ims.Props()); *this=ims; }

	 ~Imx3d( ) { Delete( ); }

	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the depth of the image.
	  * @param h	the heigth of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data (if any).
	  */
	 void New( Long b, Long d, Long h, Long w, T *data=0) {
	    if (data!=0 || (nbands*ncol*nrow*ndep != b*w*h*d)) {
	       Delete();
	       
	       if ((_isDataOwner=(data==0))) {
		  _data=new T[b*w*h*d];
	       } else {
		  _data = data;
	       }
	    }
	    ndep=d;
	    nrow=h;
	    ncol=w;
	    nbands=b;
	    matrixSize = ncol*nrow;
	    
	    volumeSize = matrixSize*ndep;
	 }

	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the dimension of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long b, const Dimension3d &d, T *data=0) { New( b,d.d,d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	the vector of data.
	  */
	 virtual void New( const PobjectProps &p, T *data=0 ) { New( p.nbands,p.ndep,p.nrow,p.ncol,data ); colorspace=p.colorspace; }

	 /**
	  * Deletes the image data without deleting the image itself.
	  */
	 void Delete( ) {
	    if (_isDataOwner) { delete[] _data;}
	    _data=0; nbands=0L; ndep=nrow=ncol=matrixSize=volumeSize=0L;
	 }
   
	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 virtual Pobject* Clone( ) const {
	    Imx3d< T > *tmp = new Imx3d< T > (nbands,ndep,nrow,ncol);
	    *tmp = *this;
      
	    return tmp;
	 }
   
	 /**
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Imx3d< T > &operator=( const T val ) {
	    T *bp=Vector();
	    T *ep=bp+(nbands*ndep*nrow*ncol);
      
	    for (;bp<ep;*(bp++)=val) ;
      
	    return *this;
	 }
   
	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that the two images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Imx3d< T > &operator=( const Imx3d< U > &src ) {
	    if (Bands() != src.Bands( ) || Depth() != src.Depth()  ||
		Height() != src.Height() || Width() != src.Width()) {
	       Delete();
	       New(src.Bands(),src.Depth(),src.Height(), src.Width());
	    }
	    T *pd=Vector();
	    U *ps=src.Vector();
	    U *pe=ps+nbands*ndep*nrow*ncol;
	    
	    for (; ps<pe; ) {
	       *(pd++) = (T)*(ps++);
	    }
	    return *this;
	 }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Imx3d< T > &operator=( const Imx3d< T > &src ) {
	    if (Bands() != src.Bands( )|| Depth() != src.Depth() 
		|| Height() != src.Height() || Width() != src.Width()) {
	       Delete();
	       New(src.Bands(),src.Depth(),src.Height(), src.Width());
	    }
	    memcpy(Vector(),src.Vector(),nbands*ndep*nrow*ncol*sizeof(T));
	    return *this;
	 }
   
	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 T* Vector( Long band=0 ) const { return &_data[volumeSize*band]; }

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 Band3d operator[]( Long band ) { return Band3d(this, &_data[volumeSize*band]); }

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 const Band3d operator[]( Long band ) const { return Band3d(this, &_data[volumeSize*band]); }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param z the z-coordinate.
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 T &operator()( Long b, Long z, Long y, Long x ) { return _data[volumeSize*b + matrixSize*z + ncol*y + x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param z the z-coordinate.
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 const T &operator()( Long b, Long z, Long y, Long x ) const { return _data[volumeSize*b + matrixSize*z + ncol*y + x]; }
	 
	 
	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param p point3d.
	  */
	 T &operator()( Long b, Point3d &p ) { return _data[volumeSize*b + matrixSize*p.z + ncol*p.y + p.x]; }
	 
	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param p point3d.
	  */
	 const T &operator()( Long b, Point3d &p ) const { return _data[volumeSize*b + matrixSize*p.z + ncol*p.y + p.x]; }
	 
	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * @param file	the file where to read attributes values. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 virtual Errc LoadAttributes( FILE *file ) {
	    Long attr[4];
      
	    if (this->Fdecode((void*)attr,sizeof(*attr),4,file) < 4)
	       return FAILURE;
	    New(attr[0],attr[1],attr[2],attr[3]);
	    return SUCCESS;
	 }
   
	 /**
	  * Saves the current attribute values in the specified file.
	  * @param file	the file.
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 virtual Errc SaveAttributes( FILE *file ) const {
	    Long attr[4];

	    attr[0]=nbands;attr[1]=ndep; attr[2]=nrow;attr[3]=ncol;
	    if (this->Fencode((void*)attr,sizeof(*attr),4,file) < 4){
	       return FAILURE;
	    }
	    return SUCCESS;
	 }

	 /**
	  * Loads data from the given file.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * @param file	the file where to read data. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 virtual Errc LoadData( FILE *file ) {
	    size_t x = volumeSize;
	    // Problem : Visual C++ 2005 cannot call the fread function to read from a buffer
	    // that is larger than 64 MB in.
	    // See http://support.microsoft.com/default.aspx?scid=kb;en-us;899149

#ifdef _WIN32
	    if (x*sizeof(T) < (size_t)67076095) {
#endif
	       size_t a;
	       for (int b=0; b<nbands; b++) {
		  if ((a=this->Fdecode((void*)Vector(b),sizeof(T),x,file)) < x) {
		     return FAILURE;
		  }
	       }
#ifdef _WIN32
	    } else {
	       x = matrixSize;
	       for (int b=0; b<nbands; b++) {
		  T *data = Vector(b);
		  for (int z=0; z<ndep; z++) {
		     if (this->Fdecode((void*)data,sizeof(T),x,file)<x) {
			return FAILURE;
		     }
		     data += x;
		  }
	       }
	    }
#endif      
	    return SUCCESS;
	 }

	 /**
	  * Saves data in the given file.
	  * @param file	the file where to save data. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 virtual Errc SaveData( FILE *file ) const {
	    size_t x = volumeSize;
	    // Problem : Visual C++ 2005 cannot call the fwrite function to
            // write to a buffer that is larger than 64 MB in. 
	    // See: http://support.microsoft.com/default.aspx?scid=kb;en-us;899149
#ifdef _WIN32
	    if (x*sizeof(T) < (size_t)67076095) {
#endif
	       for (int b=0; b<nbands; b++) {
		  if (this->Fencode((void*)Vector(b),sizeof(T),x,file)<x) {
		     return FAILURE;
		  }
	       }
#ifdef _WIN32
	    } else {
	       x = matrixSize;
	       for (int b=0; b<nbands; b++) {
		  T *data = Vector(b);
		  for (int z=0; z<ndep; z++) {
		     if (this->Fencode((void*)data,sizeof(T),x,file)<x) {
			return FAILURE;
		     }
		     data += x;
		  }
	       }
	    }
#endif
	    return SUCCESS;
	 }
   
	 /**
	  * Masks the data from the given mask.
	  * It means that pixels are set to 0 when the related
	  * label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @return a new image.
	  */
	 virtual Pobject* Mask( const Pobject* mask ) {
	    if ((!mask)||
		(mask->Type()!=Po_Reg3d)||
		(((Imx3d<Long>*)mask)->Size()!=Size())) {
	       std::cerr << "Warning: bad mask format... ignored" << std::endl;
	       return this;
	    }
      
	    Imx3d< T > *objd = (Imx3d< T >*)Clone();
	    Imx3d<Long> *m=(Imx3d<Long>*)mask;
	    for (int b=0; b<nbands;b++) {
	       Ulong *pm=(Ulong*)m->Vector(0);
	       T *pp=objd->Vector(b);
	       T *pq=Vector(b);
	       for (int i=0; i< volumeSize;i++, pq++, pm++, pp++)
		  *pp= (*pm==0)? 0 : *pq;
	    }
	    return objd;
	 }
   
	 /**
	  * Unmasks the data from the given mask.
	  * It means that pixels are set to the pixel value of the
	  * reference image when the related label in the mask is 0.
	  * @param mask		the region map that is used as a mask. 
	  * @param reference	the image that is used as a reference. 
	  * @return a new image.
	  */
	 virtual Pobject* UnMask( const Pobject* mask, const Pobject* reference ) {
	    if ((!mask)||
		(mask->Type()!=Po_Reg3d)||
		(((Imx3d<Long>*)mask)->Size()!=Size())||
		(reference->Type() != Type())||
		(((Imx3d<T>*)reference)->Size()!=Size())) {
	       std::cerr << "Warning: bad unmask format... ignored" << std::endl;
	       return this;
	    }
      
	    Imx3d< T > *objs = (Imx3d< T > *)reference;
	    Imx3d< T > *objd = (Imx3d< T >*)Clone();
	    Imx3d<Long> *m=(Imx3d<Long>*)mask;
	    for (int b=0; b<nbands; b++) {
	       Ulong *pm=(Ulong*)m->Vector(0);
	       T *pp=objd->Vector(b);
	       T *pq=Vector(b);
	       T *ps=objs->Vector(b);
	 
	       for (int i=0; i<volumeSize; i++, pp++,pq++,pm++,ps++)
		  *pp=(*pm==0)? *ps : *pq;
	    }
	    return objd;
	 }
   
	 /**
	  * Returns the current colorspace of the color image.
	  */
	 PColorSpace ColorSpace( ) const { return colorspace; }

	 /**
	  * Sets the current colorspace of the color image
	  * with the specified value.
	  * @param e the new colorspace.
	  */
	 PColorSpace ColorSpace( PColorSpace e ) { return colorspace=e; }

	 /**
	  * Checks if the image contains the point
	  * at the specified location (x, y).
	  * @param x the column coordinate.
	  * @param y the row coordinate.
	  * @param z the plane coordinate.
	  * @return true if the coordinate are in the image boundary.
	  */
	 bool Hold( Long z, Long y, Long x ) const { return( ( z>=0 ) && ( z<ndep ) && ( y>=0 ) && ( y<nrow ) && ( x>=0 ) && ( x<ncol ) );}

	 /**
	  * Checks if the image contains the point.
	  * @param pt the point.
	  * @return true if the point is in the image boundary.
	  */
	 bool Hold( const Point3d &pt ) const { return( ( pt.z>=0 ) && ( pt.z<ndep ) && ( pt.y>=0 ) && ( pt.y<nrow ) && ( pt.x>=0 ) && ( pt.x<ncol ) );}
   
	 /**
	  * Fills the specified border of the image with the specified value.
	  * @param val	the value.
	  * @param d the depth of the border.
	  * @param h the height of the border.
	  * @param l the width of the border.
	  */
	 Errc Frame( ValueType val, Long d, Long h, Long l ) {
	    if ((d<0) || (h<0) || (l<0))
	       return FAILURE;
	    for (int b=0; b<nbands; b++){
	       register int x,y,z;
	       for (z=0;z<ndep;z++)
		  for (y=0;y<nrow;y++)
		     for (x=0;x<l;x++) {
			operator()(b,z,y,x) = (T)val;
			operator()(b,z,y,ncol-1-x) = (T)val;
		     }
	       for (z=0;z<ndep;z++)
		  for (y=0;y<h;y++)
		     for (x=l;x<ncol-l;x++) {
			operator()(b,z,y,x) = (T)val;
		        operator()(b,z,nrow-1-y,x) = (T)val;
		     }
	       for (z=0;z<d;z++)
		  for (y=h;y<nrow-h;y++)
		     for (x=l;x<ncol-l;x++) {
			operator()(b,z,y,x) = (T)val;
			operator()(b,ndep-1-z,y,x) = (T)val;
		     }
	    }
	    return SUCCESS;
	 }

	 /**
	  * Fills the specified border of the image with the specified value.
	  * @param v	the value.
	  * @param d		the height, width and depth of the border.
	  */
	 Errc Frame( ValueType v, Long d ) { return Frame( v,d,d,d ); }

	 /**
	  * Fills the specified border of the image with the related values
	  * of the specified image.
	  * @param ims the reference image.
	  * @param d the depth, height and width of the border.
	  */
	 template < typename U>
	 Errc Frame( const Imx3d<U> &ims, Long d ) { return Frame( ims,d,d,d ); }

	 /**
	  * Fills the specified border of the image with the related values
	  * of the specified image.
	  * @param ims the reference image.
	  * @param d the depth of the border.
	  * @param h the height of the border.
	  * @param l the width of the border.
	  */
	 template < typename U >
	 Errc Frame( const Imx3d< U > &ims, Long d, Long h, Long l ) {
	    if ( l==-1 ){ l=h=d;}
	    if ( ( d<0 ) || ( h<0 ) || ( l<0 ) )
	       return FAILURE;
	    for ( int b=0; b<nbands; b++ ) {
	       register int i,j,k;
	       for ( i=0;i<ndep;i++ )
		  for ( j=0;j<nrow;j++ )
		     for ( k=0;k<l;k++ ) {
			operator()(b,i,j,k) = ( T )ims(b,i,j,k);
			operator()(b,i,j,ncol-1-k) = ( T )ims(b,i,j,ncol-1-k);
		     }
	       for ( i=0;i<ndep;i++ )
		  for ( j=0;j<h;j++ )
		     for ( k=l;k<ncol-l;k++ ) {
			operator()(b,i,j,k) = ( T )ims(b,i,j,k);
			operator()(b,i,nrow-1-j,k) = ( T )ims(b,i,nrow-1-j,k);
		     }
	       for ( i=0;i<d;i++ )
		  for ( j=h;j<nrow-h;j++ )
		     for ( k=l;k<ncol-l;k++ ) {
			operator()(b,i,j,k) = ( T )ims(b,i,j,k);
			operator()(b,ndep-1-i,j,k) = ( T )ims(b,ndep-1-i,j,k);
		     }
	    }
	    return SUCCESS;
	 }
   
   };

//////////
////////// Imx2d
//////////

/** @brief The 2D multispectral image.
 *
 * A <code>Imx2d</code> is a multispectral 2D image.
 * A 2D multispectral image is implemented as n 2D arrays of pixels,
 * where a pixel is of T type and n is the number of bands.
 * <br>For the use of Imx2d images see @ref image_page.
 */
   template< typename T > 
   class Imx2d: public Imx3d< T > {
      protected:
	 using Imx3d<T>::_data;
	 using Imx3d<T>::ncol;
	 using Imx3d<T>::nrow;
	 using Imx3d<T>::nbands;
	 using Imx3d<T>::matrixSize;
	 using Imx3d<T>::ColorSpace;

      public:
	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Imx2d< T > >::type; }

	 /**
	  * Returns the type name (for instance Imx2duc or Imx2dsl or Imx2dsf).
	  */
	 std::string Name( ) const { return TypeName< Imx2d < T > >::Name( ); }

	 /**
	  * Returns the dimension of the image.
	  */
	 Dimension2d Size( ) const{ return Dimension2d( nrow,ncol ); }

	 /**
	  * Creates a new image with no size and no data.
	  */
	 Imx2d( ): Imx3d<T>( ){ }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imx2d( Long b, Long h, Long w, T *data=0 ): Imx3d<T>( ) { New( b,h,w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Imx2d( Long b, const Dimension2d &d, T *data=0 ): Imx3d<T>( ) { New( b,d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	the vector of data.
	  */
	 Imx2d( const PobjectProps &p, T *data=0 ): Imx3d<T>( ) { New( p,data ); }

	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param h	the heigth of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long b, Long h, Long w, T *data=0 ) { Imx3d<T>::New( b,1,h,w,data); }

	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the dimension of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long b, const Dimension2d &d, T *data=0 ) { New( b,d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	the vector of data.
	  */
	 void New( const PobjectProps &p, T *data=0 ) { New( p.nbands,p.nrow,p.ncol,data ); ColorSpace(p.colorspace); }

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Imx2d< T > *tmp = new Imx2d< T >(nbands,nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }

	 /*   
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Imx2d< T > &operator=( const T val ) { Imx3d<T>::operator=( val ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Imx2d< T > &operator=( const Imx2d< U > &src ) { Imx3d<T>::operator=( src ); return *this; }
 
	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Imx2d< T > &operator=( const Imx2d< T > &src ) { Imx3d<T>::operator=( src ); return *this; }

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 T* Vector( Long band=0 ) const { return &_data[matrixSize*band]; }

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 typename Imx3d<T>::Band2d operator[]( Long band ) { return typename Imx3d<T>::Band2d(this, &_data[matrixSize*band]); } 

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 const typename Imx3d<T>::Band2d operator[]( Long band ) const { return typename Imx3d<T>::Band2d(this, &_data[matrixSize*band]); } 

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 T &operator()( Long b, Long y, Long x ) { return _data[matrixSize*b + ncol*y + x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 const T &operator()( Long b, Long y, Long x ) const { return _data[matrixSize*b + ncol*y + x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param p point2d.
	  */
	 const T &operator()( Long b, Point2d &p ) const { return _data[matrixSize*b + ncol*p.y + p.x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param p point2d.
	  */
	 T &operator()( Long b, Point2d &p ) { return _data[matrixSize*b + ncol*p.y + p.x]; }

	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * @param file	the file where to read attributes values. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE *file ) {
	    Long attr[3];
      
	    if (this->Fdecode((void*)attr,sizeof(*attr),3,file) < 3)
	       return FAILURE;
	    New(attr[0],attr[1],attr[2]);
	    return SUCCESS;
	 }
   
	 /**
	  * Saves the current attribute values in the specified file.
	  * @param file	the file.
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE *file ) const {
	    Long attr[3];

	    attr[0]=nbands;attr[1]=nrow;attr[2]=ncol;
	    if (this->Fencode((void*)attr,sizeof(*attr),3,file) < 3){
	       return FAILURE;
	    }
	    return SUCCESS;
	 }
   
	 /**
	  * Masks the data from the given mask.
	  * It means that pixels are set to 0 when the related
	  * label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @return a new image.
	  */
	 Pobject* Mask( const Pobject* mask ) {
	    if ((!mask)||(mask->Type()!=Po_Reg2d)||(((Imx2d<Long>*)mask)->Size()!=Size())){
	       std::cerr << "Warning: bad mask format... ignored" << std::endl;
	       return this;
	    }
      
	    Imx2d< T > *objd = (Imx2d< T> *)Clone();
	    Imx2d<Long> *m=(Imx2d<Long>*)mask;
	    for (int b=0; b<nbands;b++) {
	       Ulong *pm=(Ulong*)m->Vector(0);
	       T *pp=objd->Vector(b);
	       T *pq=Vector(b);
	 
	       for (int i=0; i<matrixSize; i++, pp++,pq++,pm++)
		  *pp=(*pm==0)? 0 : *pq;
	    }
	    return objd;
	 }
   
   
	 /**
	  * Unmasks the data from the given mask.
	  * It means that pixels are set to the pixel value of the
	  * reference image when the related label in the mask is 0.
	  * @param mask		the region map that is used as a mask. 
	  * @param reference	the image that is used as a reference. 
	  * @return a new image.
	  */
	 Pobject* UnMask( const Pobject* mask, const Pobject* reference ){
	    if ((!mask)||
		(mask->Type()!=Po_Reg2d)||
		(((Imx2d<Long>*)mask)->Size()!=Size())||
		(reference->Type() != Type())||
		(((Imx2d<T>*)reference)->Size()!=Size())) {
	       std::cerr << "Warning: bad unmask format... ignored" << std::endl;
	       return this;
	    }
      
	    Imx2d< T > *objs = (Imx2d< T > *)reference;
	    Imx2d< T > *objd = (Imx2d< T> *)Clone();
	    Imx2d<Long> *m=(Imx2d<Long>*)mask;
	    for (int b=0; b<nbands;b++){
	       Ulong *pm=(Ulong*)m->Vector(0);
	       T *pp=objd->Vector(b);
	       T *pq=Vector(b);
	       T *ps=objs->Vector(b);
	 
	       for (int i=0; i<matrixSize; i++, pp++,pq++,pm++,ps++)
		  *pp=(*pm==0)? *ps : *pq;
	    }
	    return objd;
	 }
   
	 /**
	  * Checks if the image contains the point
	  * at the specified location (x, y).
	  * @param x	the column coordinate.
	  * @param y	the row coordinate.
	  * @return true if the coordinate are in the image boundary.
	  */
	 bool Hold( Long y, Long x ) const { return Hold( Point2d( y,x ) ); }

	 /**
	  * Checks if the image contains the point.
	  * @param pt	the point.
	  * @return true if the point is in the image boundary.
	  */
	 bool Hold( const Point2d &pt ) const { return ( pt.y>=0 ) &&( pt.y<nrow ) &&( pt.x>=0 ) &&( pt.x<ncol ); }

	 /**
	  * Fills the specified border of the image with the specified value.
	  * @param val	the value.
	  * @param h		the height and width of the border.
	  */
	 Errc Frame( ValueType val, Long h ){ return Imx3d<T>::Frame( val,0,h,h ); }

	 /**
	  * Fills the specified border of the image with the specified value.
	  * @param val	the value.
	  * @param h		the height of the border.
	  * @param l		the width of the border.
	  */
	 Errc Frame( ValueType val, Long h, Long l ){ return Imx3d<T>::Frame( val,0,h,l ); }

	 /**
	  * Fills the specified border of the image with the related value
	  * of the specified image.
	  * @param ims	the reference image.
	  * @param h		the height and width of the border.
	  */
	 template < typename U >
	 Errc Frame( const Imx2d< U > &ims, Long h ) { return Imx3d<T>::Frame( ims,0,h,h ); }

	 /**
	  * Fills the specified border of the image with the related value
	  * of the specified image.
	  * @param ims	the reference image.
	  * @param h		the height of the border.
	  * @param l		the width of the border.
	  */
	 template < typename U >
	 Errc Frame( const Imx2d< U > &ims, Long h, Long l ) { return Imx3d<T>::Frame( ims,0,h,l ); }
   
	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Imx2d( const Imx2d  &ims ): Imx3d<T>( ) { New(ims.Props()); *this=ims; }
   };

//////////
////////// Imx1d
//////////

/** @brief The 1D multispectral image.
 *
 * A <code>Imx1d</code> is a multispectral 1D image.
 * A 1D multispectral image is implemented as n 1D arrays of pixels,
 * where a pixel is of T type and n is the number of bands.
 * <br>For the use of Imx1d images see @ref image_page.
 */
   template <class T>
   class Imx1d: public Imx3d< T > {
      protected:
	 using Imx3d<T>::_data;
	 using Imx3d<T>::ncol;
	 using Imx3d<T>::nbands; 
	 using Imx3d<T>::ColorSpace;
	 
      public:
	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Imx1d< T > >::type; }

	 /**
	  * Returns the type name (for instance Imx1duc or Imx1dsl or Imx1dsf).
	  */
	 std::string Name( ) const { return TypeName< Imx1d < T > >::Name( ); }

	 /**
	  * Returns the dimension of the image.
	  */
	 Dimension1d Size( ) const{ return Dimension1d( ncol ); }
   
	 /**
	  * Creates a new image with no size and no data.
	  */
	 Imx1d( ): Imx3d<T>( ){ }
   
	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imx1d( Long b, Long w, T *data=0 ): Imx3d<T>( ) { New( b,w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Imx1d( Long b, const Dimension1d &d, T *data=0 ): Imx3d<T>( ) { New( b,d.w,data ); }

	 /**
	  * Creates a new image with the specified properties.
	  * Allocates therefrom the related data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * @param p	the properties.
	  * @param data	the vector of data.
	  */
	 Imx1d( const PobjectProps &p, T *data=0 ): Imx3d<T>( ) { New( p,data ); }

	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long b, Long w, T *data=0 ) { Imx3d<T>::New(b,1,1,w,data); }

	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the dimension of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long b, const Dimension1d &d, T *data=0 ) { New( b,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	the vector of data.
	  */
	 void New( const PobjectProps &p, T *data=0 ){ New( p.nbands,p.ncol,data ); ColorSpace(p.colorspace); }

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Imx1d< T > *tmp=new Imx1d< T >(nbands,ncol);
	    *tmp=*this;
      
	    return tmp;
	 }
   
	 /*   
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Imx1d< T > &operator=( const T val ) { Imx3d<T>::operator=( val ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Imx1d< T > &operator=( const Imx1d< U > &src ) { Imx3d<T>::operator=( src ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Imx1d< T > &operator=( const Imx1d< T > &src ) { Imx3d<T>::operator=( src ); return *this; }

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 T* Vector( Long band=0 ) const { return &_data[ncol*band]; }

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 typename Imx3d<T>::Band1d operator[]( Long band ) { return typename Imx3d<T>::Band1d(this,&_data[ncol*band]); } 

	 /**
	  * Returns the specified band of the image data as a unique vector.
	  * @param band	the band number.
	  */
	 const typename Imx3d<T>::Band1d operator[]( Long band ) const { return typename Imx3d<T>::Band1d(this, &_data[ncol*band]); } 

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param x the x-coordinate.
	  */
	 T &operator()( Long b, Long x ) { return _data[ncol*b + x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param x the x-coordinate.
	  */
	 const T &operator()( Long b, Long x ) const { return _data[ncol*b + x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param p point1d.
	  */
	 T &operator()( Long b, Point1d &p ) { return _data[ncol*b + p.x]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param b the band.
	  * @param p point1d.
	  */
	 const T &operator()( Long b, Point1d &p ) const { return _data[ncol*b + p.x]; }

	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * @param file	the file where to read attributes values. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE* file ) {
	    Long attr[2];
      
	    if (this->Fdecode((void*)attr,sizeof(*attr),2,file)< 2)
	       return FAILURE;
	    New(attr[0],attr[1]);
	    return SUCCESS;
	 }
   
	 /**
	  * Saves the current attribute values in the specified file.
	  * @param file	the file.
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE* file ) const {
	    Long attr[2];
      
	    attr[0]=nbands; attr[1]=ncol; 
	    if (this->Fencode((void*)attr,sizeof(*attr),2,file)< 2)
	       return FAILURE;
	    return SUCCESS;
	 }
   
	 /**
	  * Masks the data from the given mask.
	  * It means that pixels are set to 0 when the related
	  * label in the mask is 0.
	  * @param mask	the region map that is used as a mask. 
	  * @return a new image.
	  */
	 Pobject* Mask( const Pobject* mask ) {
	    if ((!mask)||
		(mask->Type()!=Po_Reg1d)||
		(((Imx1d<Long>*)mask)->Size()!=Size())) {
	       std::cerr << "Warning: bad mask format... ignored" << std::endl;
	       return this;
	    }
      
	    Imx1d< T > *objd = (Imx1d< T >*)Clone();
	    Imx1d<Long> *m=(Imx1d<Long>*)mask;
	    for (int b=0; b<nbands;b++){
	       Ulong *pm=(Ulong*)m->Vector(0);
	       T *pp=objd->Vector(b);
	       T *pq=Vector(b);
	 
	       for (int i=0; i<ncol; i++, pp++,pq++,pm++)
		  *pp=(*pm==0)? 0 : *pq;
	 
	    }  
	    return objd;
	 }

	 /**
	  * Unmasks the data from the given mask.
	  * It means that pixels are set to the pixel value of the
	  * reference image when the related label in the mask is 0.
	  * @param mask		the region map that is used as a mask. 
	  * @param reference	the image that is used as a reference. 
	  * @return a new image.
	  */
	 Pobject* UnMask( const Pobject* mask, const Pobject* reference ) {
	    if ((!mask)||
		(mask->Type()!=Po_Reg1d)||
		(((Imx1d<Long>*)mask)->Size()!=Size())||
		(reference->Type() != Type())||
		(((Imx1d<T>*)reference)->Size()!=Size())){
	       std::cerr << "Warning: bad unmask format... ignored" << std::endl;
	       return this;
	    }
	    if ((mask == NULL) || (mask->Type() != Po_Reg1d) || (reference->Type() != Type())){
	       return this;
	    }
	    Imx1d< T > *objs = (Imx1d< T > *)reference;
	    Imx1d< T > *objd = (Imx1d< T >*)Clone();
	    Imx1d<Long> *m=(Imx1d<Long>*)mask;
	    for (int b=0; b<nbands;b++){
	       Ulong *pm=(Ulong*)m->Vector(0);
	       T *pp=objd->Vector(b);
	       T *pq=Vector(b);
	       T *ps=objs->Vector(b);
	 
	       for (int i=0; i<ncol; i++, pp++,pq++,pm++,ps++)
		  *pp=(*pm==0)? *ps : *pq;
	    }
	    return objd;
	 }
   
	 /**
	  * Checks if the image contains the point
	  * at the specified location (x).
	  * @param x	the column coordinate.
	  * @return true if the coordinate are in the image boundary.
	  */
	 bool Hold( Long x ) const { return Hold( Point1d( x ) ); }

	 /**
	  * Checks if the image contains the point.
	  * @param pt	the point.
	  * @return true if the point is in the image boundary.
	  */
	 bool Hold( const Point1d &pt ) const{ return ( pt.x>=0 ) &&( pt.x<ncol ); }

	 /**
	  * Fills the specified border of the image with the specified value.
	  * @param val	the value.
	  * @param l		the width of the border.
	  */
	 Errc Frame( ValueType val, Long l ){ return Imx3d<T>::Frame( val,1,1,l ); }

	 /**
	  * Fills the specified border of the image with the related value
	  * of the specified image.
	  * @param ims	the reference image.
	  * @param l		the width of the border.
	  */
	 template < typename U >
	 Errc Frame( const Imx1d< U > &ims, Long l ) { return Imx3d<T>::Frame( ims,1,1,l ); }

	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Imx1d( const Imx1d  &ims ): Imx3d<T>()  { New(ims.Props()); *this=ims; }
   };

//////////
////////// Img1d
//////////

/** @brief The 1D gray level image.
 *
 * A <code>Img1d</code> is a gray level 1D image.
 * A 1D gray level image is implemented as one 1D array of pixels,
 * where a pixel is of T type.
 * <br>For the use of Img1d images see @ref image_page.
 */
   template <class T>
   class Img1d: public Imx1d<T> {
      protected:
	 using Imx1d<T>::ncol;
	 using Imx1d<T>::nbands;
	 using Imx1d<T>::ColorSpace;

      public:
	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Img1d< T > >::type; }

	 /**
	  * Returns the type name (for instance Img1duc or Img1dsl or Img1dsf).
	  */
	 std::string Name( ) const { return TypeName< Img1d < T > >::Name( ); }
   
	 /**
	  * Creates a new image with no size and no data.
	  */
	 Img1d( ): Imx1d<T>( ) { }

	 /**
	  * Creates a new image with the specified width,
	  * and sets the specified vector as data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Img1d( Long w, T *data=0 ): Imx1d<T>( ) { New( w,data ); }

	 /**
	  * Creates a new image with the specified dimension,
	  * and sets the specified vector as data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Img1d( const Dimension1d &d, T *data=0 ): Imx1d<T>( ) { New( d.w,data ); }
   
	 /**
	  * Creates a new image with the specified properties.
	  * Allocates therefrom the related data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * @param p	the properties.
	  * @param data	the vector of data.
	  */
	 Img1d( const PobjectProps &p, T *data=0 ): Imx1d<T>( ) { New( p,data ); }
   
	 /**
	  * Sets the image data with the specified vector of data
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param data	the image data vector.
	  * @param w		the width of the vector.
	  */
	 void New( Long w, T *data=0 ) { Imx1d<T>::New( 1,w,data ); }

	 /**
	  * Sets the image data with the specified vector of data
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the vector.
	  * @param data	the image data vector.
	  */
	 void New( const Dimension1d &d, T *data=0 ){ New( d.w, data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	the image data vector.
	  */
	 void New( const PobjectProps &p, T *data=0 ){ New( p.ncol,data ); ColorSpace(p.colorspace); }

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Img1d< T > *tmp = new Img1d< T >(ncol);
	    *tmp = *this;
	    return tmp;
	 }
   
	 // No inheritance of operator= ! Overload.
	 /*   
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Img1d< T > &operator=( const T val ) { Imx1d<T>::operator=( val );return *this;}

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimension.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Img1d< T > &operator=( const Img1d< U > &src ) { Imx1d<T>::operator=( src ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimension.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Img1d< T > &operator=( const Img1d< T > &src ) { Imx1d<T>::operator=( src ); return *this; }

	 /**
	  * Returns the image data as a unique vector.
	  */
	 ValueType* Vector( ) const { return Imx1d<T>::Vector( 0 ); }

	 /**
	  * Returns the pixel at the specified column.
	  * @param col	the column number.
	  */
	 ValueType &operator[]( Long col ) { return Imx1d<T>::operator()(0,col); }

	 /**
	  * Returns the pixel at the specified column.
	  * @param col	the column number.
	  */
	 const ValueType &operator[]( Long col ) const { return Imx1d<T>::operator()(0,col); }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param x the x-coordinate.
	  */
	 ValueType &operator()( Long x ) { return Imx1d<T>::operator()(0,x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator[]( const Point1d &p ) { return Imx1d<T>::operator()(0,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator[]( const Point1d &p ) const { return Imx1d<T>::operator()(0,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator()( int, const Point1d &p ) { return Imx1d<T>::operator()(0,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator()( int, const Point1d &p ) const { return Imx1d<T>::operator()(0,p.x); }

	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Img1d( const Img1d  &ims ): Imx1d<T>()  { New(ims.Props()); *this=ims; }
   };

//////////
////////// Img2d
//////////

/** @brief The 2D gray level image.
 *
 * A <code>Img2d</code> is a gray level 2D image.
 * A 2D gray level image is implemented as one 2D array of pixels,
 * where a pixel is of T type.
 * <br>For the use of Img2d images see @ref image_page.
 */
   template< typename T > 
   class Img2d: public Imx2d<T> {
      protected:
	 using Imx2d<T>::nbands;
	 using Imx2d<T>::nrow;
	 using Imx2d<T>::ncol;
	 using Imx2d<T>::ColorSpace;

      public:
	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Img2d< T > >::type; }

	 /**
	  * Returns the type name (for instance Img2duc or Img2dsl or Img2dsf).
	  */
	 std::string Name( ) const { return TypeName< Img2d < T > >::Name( ); }

	 /**
	  * Creates a new image with no size and no data.
	  */
	 Img2d( ): Imx2d<T>( ){}

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Img2d( Long h, Long w, T *data=0 ): Imx2d<T>( ) { New( h,w,data ); }

	 /**
	  * Creates a new image with the specified dimension,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Img2d( const Dimension2d &d, T *data=0 ): Imx2d<T>( ) { New( d.h,d.w,data ); }
   
	 /**
	  * Creates a new image with the specified properties.
	  * Allocates therefrom the related data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * @param p	the properties.
	  * @param data	the vector of data.
	  */
	 Img2d( const PobjectProps &p, T *data=0 ): Imx2d<T>( ) { New( p,data ); }

	 /**
	  * Sets the image data with the specified vector of data
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param h		the height of the vector.
	  * @param w		the width of the vector.
	  * @param data	the image data vector. 
	  */
	 void New( Long h, Long w, T *data=0 ) { Imx2d<T>::New( 1,h,w,data ); }

	 /**
	  * Sets the image data with the specified vector of data
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the vector.
	  * @param data	the image data vector. 
	  */
	 void New( const Dimension2d &d, T *data=0 ){ New( d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	the image data vector. 
	  */
	 void New( const PobjectProps &p, T *data=0 ) {
	    New( p.nrow,p.ncol,data );
	    ColorSpace(p.colorspace);
	 }
 
	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Img2d< T > *tmp = new Img2d< T >(nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }
	 // No inheritance of operator= ! Overload.

	 /*   
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Img2d< T > &operator=( const T val ) { Imx2d<T>::operator=( val );return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Img2d< T > &operator=( const Img2d< U > &src ) { Imx2d<T>::operator=( src ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Img2d< T > &operator=( const Img2d< T > &src ) { Imx2d<T>::operator=( src ); return *this; }

	 /**
	  * Returns the image data as a unique vector.
	  */
	 ValueType* Vector( ) const { return Imx2d<T>::Vector( 0 ); }


	 /**
	  * Returns the line at the specified row.
	  * @param row	the row number.
	  */
	 typename Imx3d<T>::Band1d operator[]( Long row ) { return Imx2d<T>::operator[](0)[row]; }

	 /**
	  * Returns the line at the specified row.
	  * @param row	the row number.
	  */
	 const typename Imx3d<T>::Band1d operator[]( Long row ) const { return Imx2d<T>::operator[](0)[row]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 ValueType &operator()( Long y, Long x ) { return Imx2d<T>::operator()(0,y,x); }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 const ValueType &operator()( Long y, Long x ) const { return Imx2d<T>::operator()(0,y,x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator[]( const Point2d &p ) { return Imx2d<T>::operator()(0,p.y,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator[]( const Point2d &p ) const { return Imx2d<T>::operator()(0,p.y,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator()( int, const Point2d &p ) { return Imx2d<T>::operator()(0,p.y,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator()( int, const Point2d &p ) const { return Imx2d<T>::operator()(0,p.y,p.x); }

	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Img2d( const Img2d  &ims ): Imx2d<T>() { New(ims.Props()); *this=ims; }
   };

//////////
////////// Img3d
//////////

/** @brief The 3D gray level image.
 *
 * A <code>Img3d</code> is a gray level 3D image.
 * A 3D gray level image is implemented as one 3D array of pixels,
 * where a pixel is of T type.
 * <br>For the use of Img3d images see @ref image_page.
 */
   template <typename T>
   class Img3d: public Imx3d<T> {
      protected:
	 using Imx3d<T>::nbands;
	 using Imx3d<T>::ncol;
	 using Imx3d<T>::nrow;
	 using Imx3d<T>::ndep;
	 using Imx3d<T>::ColorSpace;

      public:
	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;


	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Img3d< T > >::type; }

	 /**
	  * Returns the type name (for instance Img3duc or Img3dsl or Img3dsf).
	  */
	 std::string Name( ) const { return TypeName< Img3d < T > >::Name( ); }

	 /**
	  * Creates a new image with no size and no data.
	  */
	 Img3d( ): Imx3d<T>( ) { }
   
	 /**
	  * Creates a new image with the specified depth, height and width values,
	  * and sets the specified vector as data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the depth of the image.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	a vector of data.
	  */
	 Img3d( Long d, Long h, Long w, T *data=0 ): Imx3d<T>( ) { New( d,h,w,data ); }
   
	 /**
	  * Creates a new image with the specified dimension,
	  * and sets the specified vector as data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the image.
	  * @param data	a vector of data.
	  */
	 Img3d( const Dimension3d &d, T *data=0 ): Imx3d<T>( ) { New( d.d,d.h,d.w,data ); }
   
	 /**
	  * Creates a new image with the specified properties.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties.
	  * @param data	a vector of data.
	  */
	 Img3d( const PobjectProps &p, T *data=0 ): Imx3d<T>( ) { New( p,data ); }
   
	 /**
	  * Sets the image data with the specified vector of data
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the depth of the vector.
	  * @param h		the height of the vector.
	  * @param w		the width of the vector.
	  * @param data	a vector of data.
	  */
	 void New( Long d, Long h, Long w, T *data=0 ) { Imx3d<T>::New( 1,d,h,w,data ); }

	 /**
	  * Sets the image data with the specified vector of data
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d	the dimension of the image.
	  * @param data	a vector of data.
	  */
	 void New( const Dimension3d &d, T *data=0 ) { New( d.d,d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param p	the properties of the image.
	  * @param data	a vector of data.
	  */
	 void New( const PobjectProps &p, T *data=0 ) { New( p.ndep,p.nrow,p.ncol,data ); ColorSpace(p.colorspace); }

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Img3d< T > *tmp = new Img3d< T >(ndep,nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }

	 // No inheritance of operator= ! Overload.

	 /*   
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Img3d< T > &operator=( const T val ) { Imx3d<T>::operator=( val );return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Img3d< T > &operator=( const Img3d< U > &src ) { Imx3d<T>::operator=( src ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Img3d< T > &operator=( const Img3d< T > &src ) { Imx3d<T>::operator=( src ); return *this; }

	 /**
	  * Returns the image data as a unique vector.
	  */
	 ValueType* Vector( ) const { return Imx3d<T>::Vector(0); }

	 /**
	  * Returns the plane at the specified depth.
	  * @param dep	the depth number.
	  */
	 typename Imx3d<T>::Band2d operator[]( Long dep ) { return Imx3d<T>::operator[](0)[dep]; }
	 
	 /**
	  * Returns the plane at the specified depth.
	  * @param dep	the depth number.
	  */
	 const typename Imx3d<T>::Band2d operator[]( Long dep ) const { return Imx3d<T>::operator[](0)[dep]; }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param z the z-coordinate.
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 ValueType &operator()( Long z, Long y, Long x ) { return Imx3d<T>::operator()(0,z,y,x); }

	 /**
	  * Returns the pixel value at the specified coordinates.
	  *
	  * @param z the z-coordinate.
	  * @param y the y-coordinate.
	  * @param x the x-coordinate.
	  */
	 const ValueType &operator()( Long z, Long y, Long x ) const { return Imx3d<T>::operator()(0,z,y,x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator[]( const Point3d &p ) {return operator()(p.z,p.y,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator[]( const Point3d &p ) const { return operator()(p.z,p.y,p.x);}

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator()( const Point3d &p ) {return operator()(p.z,p.y,p.x); }

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator()( const Point3d &p ) const { return operator()(p.z,p.y,p.x);}

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 const ValueType &operator()( int, const Point3d &p ) const { return operator()(p.z,p.y,p.x);}

	 /**
	  * Returns the pixel at the specified coordinates.
	  * @param p	the coordinate.
	  */
	 ValueType &operator()( int, const Point3d &p ) {return operator()(p.z,p.y,p.x); }

	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Img3d( const Img3d  &ims ): Imx3d<T>()  { New(ims.Props()); *this=ims; }
   };

//////////
////////// Imc2d
//////////

/** @brief The 2D color image.
 *
 * A <code>Imc2d</code> is a color 2D image.
 * A 2D color image is implemented with three 2D arrays of pixels,
 * where a pixel is of T type.@n
 * <br>For the use of Imc2d image see @ref image_page.
 */
   template< typename T > 
   class Imc2d: public Imx2d<T> {
      protected:
	 using Imx2d<T>::nbands;
	 using Imx2d<T>::ncol;
	 using Imx2d<T>::nrow;
	 
      public:
	 using Imx2d<T>::ColorSpace;

	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

 	 /** The X band ( eg. Red for RGB color image) of the color image. */
 	 typename Imx3d<T>::Band2d X;

 	 /** The Y band (eg. Green for RGB color image) of the color image. */
 	 typename Imx3d<T>::Band2d Y;

 	 /** The Z band (eg. Blue for RGB color image) of the color image. */
 	 typename Imx3d<T>::Band2d Z;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Imc2d< T > >::type; }

	 /**
	  * Returns the type name (for instance Imc2duc or Imc2dsl or Imc2dsf).
	  */
	 std::string Name( ) const { return TypeName< Imc2d < T > >::Name( ); }

	 /**
	  * Creates a new image with no size and no data.
	  */
	 Imc2d( ): Imx2d<T>( ) { }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imc2d( Long h, Long w, T *data=0 ): Imx2d<T> ( ) { New( h,w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Imc2d( const Dimension2d &d, T *data=0 ): Imx2d<T>( ) { New( d,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * <i>This constructor is defined to use a color image as
	  * a multispectral image.</i>
	  * @param b	the number of bands (ignored always 3).
	  * @param d	the dimension of the image.
	  * @param data	a vector of data.
	  */
	 Imc2d( Long b, const Dimension2d &d, T *data=0 ): Imx2d<T>( ) { New( b,d.h,d.w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imc2d( Long b, Long h, Long w, T *data=0 ): Imx2d<T>( ) { New( b, h,w,data ); }

	 /**
	  * Creates a new image with the specified properties.
	  * Allocates therefrom the related data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * @param p	the properties.
	  * @param data	the vector of data.
	  */
	 Imc2d( const PobjectProps &p, T *data=0 ): Imx2d<T>( ){ New( p,data); }

	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param h	the heigth of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long h, Long w, T *data=0 ) {
	    Imx2d<T>::New(3,h,w,data);
            // Kept for sake of compatibility.
	    X.New(this, Imx2d<T>::Vector(0));
	    Y.New(this, Imx2d<T>::Vector(1));
	    Z.New(this, Imx2d<T>::Vector(2));
	 }

	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param h	the heigth of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long /*b*/, Long h, Long w, T *data=0 ) { New( h,w,data ); }

	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d	the dimension of the image.
	  * @param data	the vector of data.
	  */
	 void New( const Dimension2d &d, T *data=0 ) { New( d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the dimension of the image.
	  * @param data	a vector of data.
	  */
	 void New( Long /*b*/, const Dimension2d &d, T *data=0 ) { New( d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * @param p	the properties of the image.
	  * @param data	a vector of data.
	  */
	 void New( const PobjectProps &p, T *data=0 ) { ColorSpace(p.colorspace); New( p.nrow,p.ncol,data ); }

	 /**
	  * Creates and returns a distinct copy of this object.@n
	  * Example:@n
	  * <tt>Imc2duc *imd = (Imc2duc*)ims->Clone();</tt>
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Imc2d< T > *tmp = new Imc2d< T >(nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }
   
	 // No inheritance of operator=( ) ! Overload.

	 /*   
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Imc2d< T > &operator=( const T val ){ Imx2d<T>::operator=( val ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Imc2d< T > &operator=( const Imc2d< U > &src ) { Imx2d<T>::operator=( src ); return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Imc2d< T > &operator=( const Imc2d< T > &src ) { Imx2d<T>::operator=( src ); return *this; }

	 /**
	  * Returns the X band of the image data as a unique vector
	  * (eg. Red for RGB color image).
	  */
	 ValueType* VectorX( ) const { return Imx2d<T>::Vector( 0 ); }

	 /**
	  * Returns the Y band of the image data as a unique vector
	  * (eg. Green for RGB color image).
	  */
	 ValueType* VectorY( ) const { return Imx2d<T>::Vector( 1 ); }

	 /**
	  * Returns the Z band of the image data as a unique vector
	  * (eg. Blue for RGB color image).
	  */
	 ValueType* VectorZ( ) const { return Imx2d<T>::Vector( 2 ); }

	 // Transfer
	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * @param file	the file where to read attributes values. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE *file ){
	    Long attr[3];

	    if (this->Fdecode((void*)attr,sizeof(*attr),3,file) < 3)
	       return FAILURE;
	    New(attr[1],attr[2]);
      
	    PColorSpace c;
	    if (this->Fdecode((void*)&c,sizeof(c),1,file) < 1) {
	       return FAILURE;
	    }
	    ColorSpace(c);
	    return SUCCESS;
	 }
   
	 /**
	  * Saves the current attribute values in the specified file.
	  * @param file	the file.
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE *file ) const {
	    if (Imx2d<T>::SaveAttributes(file) == FAILURE)
	       return FAILURE;
      
	    PColorSpace c=ColorSpace();
	    if (this->Fencode((void*)&c,sizeof(c),1,file) < 1)
	       return FAILURE;
	    return SUCCESS;
	 }
   
	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Imc2d( const Imc2d  &ims ): Imx2d<T>() { New(ims.Props()); *this=ims; }
   };

////////// 
////////// Imc3d
////////// 

/** @brief The 3D color image.
 *
 * A <code>Imc3d</code> is a color 3D image.
 * A 3D color image is implemented with three 3D arrays of pixels,
 * where a pixel is of T type.
 * <br>For the use of Imc3d images see @ref image_page.
 */
   template< typename T > 
   class Imc3d: public Imx3d<T> {
      protected:
	 using Imx3d<T>::nbands;
	 using Imx3d<T>::ncol;
	 using Imx3d<T>::nrow;
	 using Imx3d<T>::ndep;

      public:
	 using Imx3d<T>::ColorSpace;

	 /** The type of the data (Uchar, Long or Float). */
	 typedef T ValueType;

	 /** The X band (eg. Red for RGB color image) of the color image. */
	 typename Imx3d<T>::Band3d X;

	 /** The Y band (eg. Green for RGB color image) of the color image. */
	 typename Imx3d<T>::Band3d Y;

	 /** The Z band (eg. Blue for RGB color image) of the color image. */
	 typename Imx3d<T>::Band3d Z;

	 /**
	  * Returns the identifier of the object (ie. the magic number).
	  */
	 Typobj Type( ) const { return ( Typobj )Po_type< Imc3d< T > >::type; }

	 /**
	  * Returns the type name (for instance Imc3duc or Imc3dsl or Imc3dsf).
	  */
	 std::string Name( ) const { return TypeName< Imc3d <T> >::Name( ); }

	 /**
	  * Creates a new image with no size and no data.
	  */
	 Imc3d( ): Imx3d<T>( ) { }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param d		the depth of the image.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imc3d( Long b, Long d, Long h, Long w, T *data=0 ): Imx3d<T>( ) { New( b,d,h,w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b		the number of bands of the image.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Imc3d( Long b, const Dimension3d &d, T *data=0 ): Imx3d<T>( ) { New( b,d,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the depth of the image.
	  * @param h		the height of the image.
	  * @param w		the width of the image.
	  * @param data	the vector of data.
	  */
	 Imc3d( Long d, Long h, Long w, T *data=0 ): Imx3d<T>( ) { New( d,h,w,data ); }

	 /**
	  * Creates a new image with the specified dimensions,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d		the dimension of the image.
	  * @param data	the vector of data.
	  */
	 Imc3d( const Dimension3d &d, T *data=0 ): Imx3d<T>( ) { New( d,data ); }
 
	 /**
	  * Creates a new image with the specified properties,
	  * and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @warning the pixel values are not initialized with 0.
	  * @param p	the properties.
	  * @param data	the vector of data.
	  */
	 Imc3d( const PobjectProps &p, T *data=0 ): Imx3d<T>( ) { New( p, data); }
   
	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the depth of the image.
	  * @param h	the heigth of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long /*b*/, Long d, Long h, Long w, T *data=0 ) { New (d,h,w,data); } 

	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param b	the number of bands of the image.
	  * @param d	the dimension of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long /*b*/, const Dimension3d &d, T *data=0 ) { New( d.d,d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified band number, depth,
	  * height and width values and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d	the depth of the image.
	  * @param h	the heigth of the image.
	  * @param w	the width of the image.
	  * @param data	the vector of data.
	  */
	 void New( Long d, Long h, Long w, T *data=0 ) {
	    Imx3d<T>::New( 3,d,h,w,data );
            // Kept for sake of compatibility.
	    X.New(this, Imx3d<T>::Vector(0));
	    Y.New(this, Imx3d<T>::Vector(1));
	    Z.New(this, Imx3d<T>::Vector(2));
	 }
	 /**
	  * Allocates the image data from the specified band number
	  * and dimensions and the specified data.
	  * If data=0 then data are allocated and freed by the image 
	  * else data are allocated and freed externally.
	  * @param d	the dimension of the image.
	  * @param data	a vector of data.
	  */
	 void New( const Dimension3d &d, T *data=0 ) { New( d.d,d.h,d.w,data ); }

	 /**
	  * Allocates the image data from the specified properties.
	  * @param p	the properties of the image.
	  * @param data	a vector of data.
	  */
	 void New( const PobjectProps &p, T* data=0 ){ ColorSpace(p.colorspace), New( p.ndep,p.nrow,p.ncol,data); }

	 /**
	  * Creates and returns a distinct copy of this object.
	  * @return a new image.
	  */
	 Pobject* Clone( ) const {
	    Imc3d< T > *tmp = new Imc3d< T >(ndep,nrow,ncol);
	    *tmp = *this;
	    return tmp;
	 }
   
	 // No inheritance of operator= ! Overload.

	 /*
	  * Sets all pixels with the given value.
	  * @param val	the given value.
	  * @return the image itself.
	  */
	 Imc3d< T > &operator=( const T val ) { Imx3d<T>::operator=( val );return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 template< typename U >
	 Imc3d< T > &operator=( const Imc3d< U > &src ) { Imx3d<T>::operator=( src );return *this; }

	 /**
	  * Sets the pixel values with the pixel values of the given image.
	  * This supposes that images have the same dimensions.
	  * @param src	the given image.
	  * @return the image itself.
	  */
	 Imc3d< T > &operator=( const Imc3d< T > &src ) { Imx3d<T>::operator=( src );return *this; }

	 /**
	  * Returns the X band of the image data as a unique vector
	  * (eg. Red for RGB color image).
	  */
	 ValueType* VectorX( ) const { return Imx3d<T>::Vector( 0 ); }

	 /**
	  * Returns the Y band of the image data as a unique vector
	  * (eg. Green for RGB color image).
	  */
	 ValueType* VectorY( ) const { return Imx3d<T>::Vector( 1 ); }
   
	 /**
	  * Returns the Z band of the image data as a unique vector
	  * (eg. Blue for RGB color image).
	  */
	 ValueType* VectorZ( ) const { return Imx3d<T>::Vector( 2 ); }

	 /**
	  * Loads attribute values from the given file.
	  * Allocates therefrom the related data.
	  * @warning the pixel values are not initialized with 0.
	  * @param file	the file where to read attributes values. 
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc LoadAttributes( FILE *file ) {
	    Long attr[4];
	    // Remarque ; attr[0] = nbands. Always =3.
	    if (this->Fdecode((void*)attr,sizeof(*attr),4,file) < 4)
	       return FAILURE;
	    New(attr[1],attr[2],attr[3]);
      
	    PColorSpace c;
	    if (this->Fdecode((void*)&c,sizeof(c),1,file) < 1) {
	       return FAILURE;
	    }
	    ColorSpace(c);
	    return SUCCESS;
	 }

	 /**
	  * Saves the current attribute values in the specified file.
	  * @param file	the file.
	  * @return SUCCESS or FAILURE in case of IO errors.
	  */
	 Errc SaveAttributes( FILE *file ) const {
	    if (Imx3d<T>::SaveAttributes(file) == FAILURE)
	       return FAILURE;
      
	    PColorSpace c=ColorSpace();
	    if (this->Fencode((void*)&c,sizeof(c),1,file) < 1)
	       return FAILURE;   
	    return SUCCESS;
	 }
   
	 /**
	  * Creates the image content by copy. Allocates the related
	  * data and sets the values with the ims values. If needed
	  * casts the values by using the C casting.
	  * @param ims	the specified image.
	  */
	 Imc3d( const Imc3d  &ims ): Imx3d<T>() { New(ims.Props()); *this=ims; }
   };

   typedef Imx1d<Uchar>  Imx1duc;
   typedef Imx1d<Long>   Imx1dsl;
   typedef Imx1d<Float>  Imx1dsf;

   typedef Imx2d<Uchar>  Imx2duc;
   typedef Imx2d<Long>   Imx2dsl;
   typedef Imx2d<Float>  Imx2dsf;

   typedef Imx3d<Uchar>  Imx3duc;
   typedef Imx3d<Long>   Imx3dsl;
   typedef Imx3d<Float>  Imx3dsf;

   typedef Img1d<Uchar>  Img1duc;
   typedef Img1d<Long>   Img1dsl;
   typedef Img1d<Float>  Img1dsf;

   typedef Img2d<Uchar>  Img2duc;
   typedef Img2d<Long>   Img2dsl;
   typedef Img2d<Float>  Img2dsf;

   typedef Img3d<Uchar>  Img3duc;
   typedef Img3d<Long>   Img3dsl;
   typedef Img3d<Float>  Img3dsf;

   typedef Imc2d<Uchar>  Imc2duc;
   typedef Imc2d<Long>   Imc2dsl;
   typedef Imc2d<Float>  Imc2dsf;

   typedef Imc3d<Uchar>  Imc3duc;
   typedef Imc3d<Long>   Imc3dsl;
   typedef Imc3d<Float>  Imc3dsf;

/* @brief The magic number for the type Img1duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img1duc.
 */
   template<> struct Po_type<Img1duc> {
	 enum {type = Po_Img1duc };
   };

/* @brief Trait that returns the name of the Pandore type Img1duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img1duc > {
	 static std::string Name( ){ return "Img1duc"; }
   };
/* @brief The magic number for the type Img1dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img1dsl.
 */
   template<> struct Po_type<Img1dsl> {
	 enum {type = Po_Img1dsl };
   };

/* @brief Trait that returns the name of the Pandore type Img1dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img1dsl > {
	 static std::string Name( ){ return "Img1dsl"; }
   };
/* @brief The magic number for the type Img1dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img1dsf.
 */
   template<> struct Po_type<Img1dsf> {
	 enum {type = Po_Img1dsf };
   };

/* @brief Trait that returns the name of the Pandore type Img1dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img1dsf > {
	 static std::string Name( ){ return "Img1dsf"; }
   };
/* @brief The magic number for the type Img2duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img2duc.
 */
   template<> struct Po_type<Img2duc> {
	 enum {type = Po_Img2duc };
   };

/* @brief Trait that returns the name of the Pandore type Img2duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img2duc > {
	 static std::string Name( ){ return "Img2duc"; }
   };
/* @brief The magic number for the type Img2dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img2dsl.
 */
   template<> struct Po_type<Img2dsl> {
	 enum {type = Po_Img2dsl };
   };

/* @brief Trait that returns the name of the Pandore type Img2dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img2dsl > {
	 static std::string Name( ){ return "Img2dsl"; }
   };
/* @brief The magic number for the type Img2dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img2dsf.
 */
   template<> struct Po_type<Img2dsf> {
	 enum {type = Po_Img2dsf };
   };

/* @brief Trait that returns the name of the Pandore type Img2dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img2dsf > {
	 static std::string Name( ){ return "Img2dsf"; }
   };
/* @brief The magic number for the type Img3duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img3duc.
 */
   template<> struct Po_type<Img3duc> {
	 enum {type = Po_Img3duc };
   };

/* @brief Trait that returns the name of the Pandore type Img3duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img3duc > {
	 static std::string Name( ){ return "Img3duc"; }
   };
/* @brief The magic number for the type Img3dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img3dsl.
 */
   template<> struct Po_type<Img3dsl> {
	 enum {type = Po_Img3dsl };
   };

/* @brief Trait that returns the name of the Pandore type Img3dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img3dsl > {
	 static std::string Name( ){ return "Img3dsl"; }
   };
/* @brief The magic number for the type Img3dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Img3dsf.
 */
   template<> struct Po_type<Img3dsf> {
	 enum {type = Po_Img3dsf };
   };

/* @brief Trait that returns the name of the Pandore type Img3dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Img3dsf > {
	 static std::string Name( ){ return "Img3dsf"; }
   };
/* @brief The magic number for the type Imc2duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imc2duc.
 */
   template<> struct Po_type<Imc2duc> {
	 enum {type = Po_Imc2duc };
   };

/* @brief Trait that returns the name of the Pandore type Imc2duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imc2duc > {
	 static std::string Name( ){ return "Imc2duc"; }
   };
/* @brief The magic number for the type Imc2dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imc2dsl.
 */
   template<> struct Po_type<Imc2dsl> {
	 enum {type = Po_Imc2dsl };
   };

/* @brief Trait that returns the name of the Pandore type Imc2dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imc2dsl > {
	 static std::string Name( ){ return "Imc2dsl"; }
   };
/* @brief The magic number for the type Imc2dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imc2dsf.
 */
   template<> struct Po_type<Imc2dsf> {
	 enum {type = Po_Imc2dsf };
   };

/* @brief Trait that returns the name of the Pandore type Imc2dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imc2dsf > {
	 static std::string Name( ){ return "Imc2dsf"; }
   };
/* @brief The magic number for the type Imc3duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imc3duc.
 */
   template<> struct Po_type<Imc3duc> {
	 enum {type = Po_Imc3duc };
   };

/* @brief Trait that returns the name of the Pandore type Imc3duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imc3duc > {
	 static std::string Name( ){ return "Imc3duc"; }
   };
/* @brief The magic number for the type Imc3dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imc3dsl.
 */
   template<> struct Po_type<Imc3dsl> {
	 enum {type = Po_Imc3dsl };
   };

/* @brief Trait that returns the name of the Pandore type Imc3dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imc3dsl > {
	 static std::string Name( ){ return "Imc3dsl"; }
   };
/* @brief The magic number for the type Imc3dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imc3dsf.
 */
   template<> struct Po_type<Imc3dsf> {
	 enum {type = Po_Imc3dsf };
   };

/* @brief Trait that returns the name of the Pandore type Imc3dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imc3dsf > {
	 static std::string Name( ){ return "Imc3dsf"; }
   };
/* @brief The magic number for the type Imx1duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx1duc.
 */
   template<> struct Po_type<Imx1duc> {
	 enum {type = Po_Imx1duc };
   };

/* @brief Trait that returns the name of the Pandore type Imx1duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx1duc > {
	 static std::string Name( ){ return "Imx1duc"; }
   };
/* @brief The magic number for the type Imx1dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx1dsl.
 */
   template<> struct Po_type<Imx1dsl> {
	 enum {type = Po_Imx1dsl };
   };

/* @brief Trait that returns the name of the Pandore type Imx1dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx1dsl > {
	 static std::string Name( ){ return "Imx1dsl"; }
   };
/* @brief The magic number for the type Imx1dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx1dsf.
 */
   template<> struct Po_type<Imx1dsf> {
	 enum {type = Po_Imx1dsf };
   };

/* @brief Trait that returns the name of the Pandore type Imx1dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx1dsf > {
	 static std::string Name( ){ return "Imx1dsf"; }
   };
/* @brief The magic number for the type Imx2duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx2duc.
 */
   template<> struct Po_type<Imx2duc> {
	 enum {type = Po_Imx2duc };
   };

/* @brief Trait that returns the name of the Pandore type Imx2duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx2duc > {
	 static std::string Name( ){ return "Imx2duc"; }
   };
/* @brief The magic number for the type Imx2dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx2dsl.
 */
   template<> struct Po_type<Imx2dsl> {
	 enum {type = Po_Imx2dsl };
   };

/* @brief Trait that returns the name of the Pandore type Imx2dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx2dsl > {
	 static std::string Name( ){ return "Imx2dsl"; }
   };
/* @brief The magic number for the type Imx2dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx2dsf.
 */
   template<> struct Po_type<Imx2dsf> {
	 enum {type = Po_Imx2dsf };
   };

/* @brief Trait that returns the name of the Pandore type Imx2dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx2dsf > {
	 static std::string Name( ){ return "Imx2dsf"; }
   };
/* @brief The magic number for the type Imx3duc.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx3duc.
 */
   template<> struct Po_type<Imx3duc> {
	 enum {type = Po_Imx3duc };
   };

/* @brief Trait that returns the name of the Pandore type Imx3duc.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx3duc > {
	 static std::string Name( ){ return "Imx3duc"; }
   };
/* @brief The magic number for the type Imx3dsl.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx3dsl.
 */
   template<> struct Po_type<Imx3dsl> {
	 enum {type = Po_Imx3dsl };
   };

/* @brief Trait that returns the name of the Pandore type Imx3dsl.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx3dsl > {
	 static std::string Name( ){ return "Imx3dsl"; }
   };
/* @brief The magic number for the type Imx3dsf.
 *
 * Po_Type is an helper class that defines the
 * magic number for the type Imx3dsf.
 */
   template<> struct Po_type<Imx3dsf> {
	 enum {type = Po_Imx3dsf };
   };

/* @brief Trait that returns the name of the Pandore type Imx3dsf.
 *
 * TypeName is a trait that returns the name
 * of the Pandore type T.
 */
   template<> struct TypeName< Imx3dsf > {
	 static std::string Name( ){ return "Imx3dsf"; }
   };

} //End of pandore:: namespace

#endif // __PIMAGEH__
