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
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 * @author Régis Clouard - 2002-05-23 (version 4.00)
 * @author Régis Clouard - 2004-08-11 (new 26-connexity)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file neighbours.h
 * @brief The definition of the arrays for neighbour accesses.
 */

#ifndef __PNEIGHBOURSH__
#define __PNEIGHBOURSH__

namespace pandore {

const Long v2x []={-1,1,-1};

/** The predefined array for y-shift for 4-connexity neighbours. */
const Long v4y []={0 ,-1, 0, 1, 0};
/** The predefined array for x-shift for 4-connexity neighbours. */
const Long v4x []={-1, 0, 1, 0, -1};

/** The predefined array for y-shift for 8-connexity neighbours. */
const Long v8y []={0 ,-1,-1,-1, 0, 1, 1, 1, 0};
/** The predefined array for x-shift for 8-connexity neighbours. */
const Long v8x []={-1,-1, 0, 1, 1, 1, 0,-1,-1};

/** The predefined array for z-shift for 6-connexity neighbours. */
const Long v6z[]={-1, 0, 0, 1, 0, 0,-1};
/** The predefined array for y-shift for 6-connexity neighbours. */
const Long v6y[]={ 0, 0,-1, 0, 0, 1, 0};
/** The predefined array for x-shift for 6-connexity neighbours. */
const Long v6x[]={ 0,-1, 0, 0, 1, 0, 0};

/** The predefined array for z-shift for 26-connexity neighbours. */
const Long v26z[]={ -1,-1,-1,-1,-1,-1,-1,-1,-1,  0, 0, 0, 0,  +1,+1,+1,+1,+1,+1,+1,+1,+1,   0, 0, 0, 0,  -1};

/** The predefined array for y-shift for 26-connexity neighbours. */
const Long v26y[]={  0, 0,-1,-1,-1, 0, 1, 1, 1,  0,-1,-1,-1,   0, 0, 1, 1, 1, 0,-1,-1,-1,   0, 1, 1, 1,   0};

/** The predefined array for x-shift for 26-connexity neighbours. */
const Long v26x[]={  0,-1,-1, 0, 1, 1, 1, 0,-1, -1,-1, 0, 1,   0, 1, 1, 0,-1,-1,-1, 0, 1,   1, 1, 0,-1,   0};

/** The predefined array for point shift for 2-connexity neighbours. */
const Point1d v2[]= { Point1d(-1),
			     Point1d(1),
			     Point1d(-1)};

/** The predefined array for point shift for 4-connexity neighbours. */
const Point2d v4[]= { Point2d(0,-1), 
			     Point2d(-1,0), 
			     Point2d(0,1), 
			     Point2d(1,0),
			     Point2d(0,-1)};

/** The predefined array for point shift for 8-connexity neighbours. */
const Point2d v8[]= { Point2d(0,-1),
			     Point2d(-1,-1),
			     Point2d(-1,0),
			     Point2d(-1,1),
			     Point2d(0,1),
			     Point2d(1,1),
			     Point2d(1,0),
			     Point2d(1,-1),
			     Point2d(0,-1)};

/** The predefined array for point shift for 6-connexity neighbours. */
const Point3d v6[]= { Point3d(-1,0,0),
			     Point3d(0,0,-1),
			     Point3d(0,-1,0),
			     Point3d(1,0,0),
			     Point3d(0,0,1),
			     Point3d(0,1,0),
			     Point3d(-1,0,0) };

/** The predefined array for point shift for 26-connexity neighbours. */
const Point3d v26[]={ Point3d(-1, 0, 0),
			     Point3d(-1, 0,-1),
			     Point3d(-1,-1,-1),
			     Point3d(-1,-1, 0),
			     Point3d(-1,-1, 1),
			     Point3d(-1, 0, 1),
			     Point3d(-1, 1, 1),
			     Point3d(-1, 1, 0),
			     Point3d(-1, 1,-1),

			     Point3d( 0, 0,-1),
			     Point3d( 0,-1,-1),
			     Point3d( 0,-1, 0),
			     Point3d( 0,-1, 1),

			     Point3d(+1, 0, 0),
			     Point3d(+1, 0, 1),
			     Point3d(+1, 1, 1),
			     Point3d(+1, 1, 0),
			     Point3d(+1, 1,-1),
			     Point3d(+1, 0,-1),
			     Point3d(+1,-1,-1),
			     Point3d(+1,-1, 0),
			     Point3d(+1,-1, 1),

			     Point3d( 0, 0, 1),
			     Point3d( 0, 1, 1),
			     Point3d( 0, 1, 0),
			     Point3d( 0, 1,-1),

			     Point3d(-1,0, 0)};

/**
 * The predefined array for x-shift for a given connexity neighbours.
 * Indirection with connexity. vc[connexity][neighbour]
 */
const Long* const vcx[]={0,0,v2x,0,v4x,0,v6x,0,v8x,
			   0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,v26x};
/**
 * The predefined array for y-shift for a given connexity neighbours.
 * Indirection with connexity. vc[connexity][neighbour]
 */
const Long* const vcy[]={0,0,0,0,v4y,0,v6y,0,v8y,
			   0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,v26y};
/**
 * The predefined array for z-shift for a given connexity neighbours.
 * Indirection with connexity. vc[connexity][neighbour]
 */
const Long* const vcz[]={0,0,0,0,0,0,v6z,0,0,
			   0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,v26z};

/**
 * The predefined array for point shift for a given connexity neighbours.
 * Indirection with connexity. vc[connexity][neighbour]
 */
const Point* const vc[]={0,0,v2,0,v4,0,v6,0,v8,
			   0,0,0,0,0,0,0,0,0,0,0,0,
			   0,0,0,0,0,v26};

} //End of pandore:: namespace

#endif // __PNEIGHBOURSH__
