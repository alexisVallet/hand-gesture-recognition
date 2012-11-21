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
 * @author Régis Clouard - 2001-04-03 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 */

/**
 * @file pandore.h
 * @brief The main include file.
 */

#ifndef __PPANDOREH__
#define __PPANDOREH__

#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdlib.h>
#include <fcntl.h>

#include <string>

namespace pandore {
/*
 * The general constants.
 */
#ifndef NULL
#define	NULL	(0L)
#endif
#ifndef TRUE
#define TRUE	true
#endif
#ifndef FALSE
#define FALSE	false
#endif
#ifndef STATUS_FILE
#define STATUS_FILE  "pandore"
#endif

} //End of pandore:: namespace

#include "ptypes.h"

// Needed for cerr...
#include <iostream>
#include "errc.h"
#include "panfile.h"
#include "pobject.h"
#include "dimension.h"
#include "point.h"
#include "neighbours.h"
#include "image.h"
#include "region.h"
#include "graph.h"
#include "plist.h"
#include "promotions.h"
#include "plimits.h"
#include "collection.h"
#include "main.h"

namespace pandore {
 /*
  *  Some macro functions
  */
#ifndef MIN
#define	MIN(x,y) (((x)<(y))? (x) : (y))
#endif
#ifndef MAX
#define	MAX(x,y) (((x)>(y))? (x) : (y))
#endif
#ifndef SQR
#define	SQR(x) ((x)*(x))
#endif
#ifndef CUB
#define	CUB(x) ((x)*(x)*(x))
#endif
#ifndef ABS
#define	ABS(x) (((x)>0)? (x) : (-1*(x)))
#endif

#define	WHITE 255
#define	BLACK 0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

} //End of pandore:: namespace

#endif // __PPANDOREH__
