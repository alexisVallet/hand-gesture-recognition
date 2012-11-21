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
 * @author Regis Clouard - 1997-10-27
 * @author François Angot - 1999-10-11
 * @author Alexandre Duret-Lutz - 1999-10-11
 * @author Régis Clouard - 2001-04-11 (version 3.00)
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2008-01-10 (change weights from float to double)
 * @author Régis Clouard - 2008-02-13 (add directed and undirected property)
 * @author François-Xavier Dupé - 2009-01-15 (extend graph representation)
 */

/**
 * @file graph.h
 * @brief This file contains the definition of the graphs.
 */

#include <vector>

#ifndef __PGRAPHH__
#define __PGRAPHH__

namespace pandore {

   class Graph2d;
   class Graph3d;


   /* @brief Trait that returns the name of the Pandore type.
    *
    * TypeName is a trait that returns the name
    * of the Pandore type T.
    */
   template<>
   struct TypeName< Graph2d > {
      /**
       * Returns the name of the type.
       * @return	the string with the name.
       */
      static std::string Name() {return "Graph2d";}
   };


   /* @brief Trait that returns the name of the Pandore type.
    *
    * TypeName is a trait that returns the name
    * of the Pandore type T.
    */
   template<> struct TypeName< Graph3d >{
      /**
       * Returns the name of the type.
       * @return	the string with the name.
       */
      static std::string Name() { return "Graph3d"; }
   };

   /** @brief An edge between two graph nodes.
    *
    * The class <code>GEdge</code> defines a undirected edge
    * between two nodes.
    * An edge is characterized by a weight
    * and the index of the connected node.
    */
   class GEdge{
   private:

      /** The next neighbourhood node. */
      GEdge *next; 

      /** The rank of the target node in the graph array. */
      Long node;

      /** The number which identifies the edge. */
      Long item;

   public:
      /** The valuation of the edge. */
      Double weight;
   
      /**
       * Creates a new edge to the specified node, with
       * the specified weight and the specified next edge.
       * @param n	the connected node.
       * @param adj	the next edge.
       * @param w	the weight.
       */
      GEdge( Long n, GEdge *adj, Double w=1 ): next(adj), node(n), item(-1), weight(w) {}

      /**
       * Creates a new edge to the specified node, with
       * the specified weight and the specified next edge.
       * @param n	the connected node.
       * @param adj	the next edge.
       * @param i       the identifier of the edge
       * @param w	the weight.
       */
      GEdge( Long n, GEdge *adj, Long i, Double w=1 ): next(adj), node(n), item(i), weight(w) {}

      /**
       * Deletes the node.
       */
      ~GEdge(){}

      /**
       * Returns the number of the adjacent node.
       * @return	the number of the connected node.
       */
      Long Node() const { return node; };

      /**
       * Returns the next neighbourhood node.
       * @return	the next edge.
       */
      GEdge* Next() const { return next; };

      /**
       * Sets a new neighbourhood node.
       * @param n	the  neighbourhood edge.
       * @return	the neighbourhood edge.
       */
      GEdge* Next( GEdge* n ) { return next=n; };

      /**
       * Returns the index of the referenced object.
       * @return	the index.
       */
      Long Item() const { return item; }

      /**
       * Sets the new index of the referenced object.
       * @param i	the new index.
       * @return	the new index of the object.
       */
      Long Item( Long i ) { return item=i; }

   };

   /** @brief A node of a graph.
    *
    * The class <code>GNode</code> defines a node.
    * A node indexes an object in a separate array of objects
    * at specified coordinates in the related image.
    * It is characterized by a value and a list
    * of connected nodes.
    */
   template< class Point >
   class GNode{
   private:
      /** The list of the adjacent nodes. */
      GEdge *adjacents;
      /** The number which identifies the object. */
      Long item;
      /** Trash for removed edges */
      std::vector<GEdge *> etrash;

   public :
      /** The valuation of the node. */
      Double value;	
      /** The coordinates of the node seeds. */
      Point seed;

      /**
       * Creates a new node with the specified index,
       * and the specified coordinates.
       * @param i	the index of the referenced object.
       * @param p	the specified coordinates.
       */
      GNode( Long i, const Point p ): adjacents(0), value(255.0) { item=i; seed=p; }

      /**
       * Deletes the node.
       */
      ~GNode();

      /**
       * Returns the list of all the connected nodes.
       * @return	the list of connected nodes.
       */
      GEdge* Neighbours() const { return adjacents; }

      /**
       * Returns the edge from the specified node.
       * @param n	the node to be searched.
       * @return	the edge with the specified node or NULL.
       */
      GEdge* Search( Long n ) const ;

      /**
       * Returns the edge from the specified node.
       * @param n	the node to be searched.
       * @param i       the identifier of the edge
       * @return	the edge with the specified node or NULL.
       */
      GEdge* Search( Long n, Long i ) const ;

      /**
       * Adds the specified node with the specified weight.
       * in front of the list of connected nodes
       * @param n	the specified node.
       * @param w	the weight of the edge.
       * @return the new of list of connected nodes.
       */
      GEdge* Add( Long n, Double w );

      /**
       * Adds the specified node with the specified weight and
       * the specified identifier.
       * in front of the list of connected nodes
       * @param n	the specified node.
       * @param w	the weight of the edge.
       * @param i       the identifier of the edge
       * @return the new of list of connected nodes.
       */
      GEdge* Add( Long n, Long i, Double w );

      /**
       * Deletes the specified node from the list of connected nodes.
       * @param n	the specified node.
       * @return the new list of edges.
       */
      GEdge* Del( Long n );

      /**
       * Deletes specific edge linking to the specified node
       * from the list of connected nodes.
       * @param i       the identifier of the edge
       * @param n	the specified node.
       * @return the new list of edges.
       */
      GEdge* Del( Long n, Long i );

      /**
       * Returns the index of the referenced object.
       * @return	the index.
       */
      Long Item() const { return item; }

      /**
       * Sets the new index of the referenced object.
       * @param i	the new index.
       * @return	the new index of the object.
       */
      Long Item( Long i ) { return item=i; }
   };

   /*
    * No GRAPH1D: it is not useful... It's my opinion.
    */

   /** @brief A 2D graph.
    *
    * A graph is a set of nodes connected to some other nodes.
    * The two types of graph are supported: directed and undirected;
    * the type must be specified with the constructor.
    * A node is characterized by a value which determines if the
    * node is active in the representation of the graph or not.
    * A node can reference any of the Pandore object. It indexes an 
    * item in a separate array of items by a long value.
    * It is equivalent to a pointer to an objet in an array
    * except that not type is needed. 
    * <br>see @ref graph_page.
    */
   class Graph2d: public Pobject {
   private :
      GNode< Point2d > **tnode;
      Long size;
      Long ncol;
      Long nrow;
      bool _directed;
   
      friend class GEdge;
   
   public :

      /** The type of the data (for instance Double). */
      typedef Double ValueType;
   
      /**
       * Returns the graph identifier.
       * @return	the identifier.
       */
      Typobj Type() const { return(Po_Graph2d); }

      /**
       * Returns the name of the graph type.
       * @return	the string with the name.
       */
      std::string Name() const { return TypeName< Graph2d >::Name(); }

      /**
       * @return true if the graph is directed.
       */
      bool isDirected() const { return _directed; }
   
      /**
       * Returns the number of columns of the related image.
       * @return	the width.
       */
      Long Width() const { return ncol; }

      /**
       * Returns the number of rows of the related image.
       * @return	the height.
       */
      Long Height() const { return nrow; }

      /**
       * Returns the number of nodes.
       * @return	the size.
       */
      Long Size() const { return size; }

      /**
       * Returns the dimension of the related image.
       * @return	the dimension.
       */
      Dimension2d ImageSize() const { return Dimension2d(nrow,ncol); }

      /**
       * Returns the related vector of properties.
       * @return	the vector of properties.
       */
      PobjectProps Props() const { return PobjectProps(0,ncol,nrow,0,(PColorSpace)0,0,size,_directed); };

      /**
       * Creates a new graph with no data.
       * @param directed true for creating a directed graph.
       */
      Graph2d( bool directed =false): tnode(0), size(0), ncol(0), nrow(0), _directed(directed) { }
   
      /**
       * Creates a new graph with the specified number of nodes
       * and the specified dimension of the related image.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param directed true for creating a directed graph.
       */
      Graph2d( Long s, bool directed =false ): tnode(0), _directed(directed) { New(s,0,0); }

      /**
       * Creates a new graph with the specified number of nodes
       * and the specified dimension of the related image.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param h	the height of the related image.
       * @param w	the width of the related image.
       * @param directed true for creating a directed graph.
       */
      Graph2d( Long s, Long h, Long w, bool directed =false ): tnode(0), _directed(directed) { New(s,h,w); }
   
      /**
       * Creates a new graph with the specified number of nodes
       * and the specified dimension of the related image.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param d	the dimension of the image.
       * @param directed true for creating a directed graph.
       */
      Graph2d( Long s, const Dimension2d &d, bool directed =false): tnode(0), _directed(directed) { New(s,d.h,d.w); }
   
      /**
       * Creates a new graph with the specified properties.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param p	the properties.
       */
      Graph2d( const PobjectProps &p ): tnode(0){ _directed = p.directed; New(p.size,p.nrow,p.ncol); }
   
      /**
       * Deletes the graph.
       */
      ~Graph2d() { Delete(); }
   
      /**
       * Allocates the data from the specified number of nodes,
       * and the specified dimension of the related image.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param h	the height of the related image.
       * @param w	the width of the related image.
       */
      void New( Long s, Long h, Long w );

      /**
       * Allocates the image data from the specified vector of properties.
       * @warning the node value is not initialized with 0.
       * @param p	the vector of properties.
       */
      void New( const PobjectProps &p ) { New(p.size,p.nrow,p.ncol); }

      /**
       * Deletes the graph data.
       */
      void Delete();

      /**
       * Sets the values of the graph from the
       * specified graph values.
       * If needed, deletes the previous data
       * and reallocs new data.
       * @param src	the reference graph.
       */
      Graph2d& operator=( const Graph2d &src );

      /**
       * Initializes the graph with the given region map. Each region
       * is represented as a node, and connected regions are represented
       * as a link between the related nodes.
       * The seed map is used to set the coordinates of each node.
       * @param rgs	the region map.
       * @param seeds	the region map that holds the seeds.
       * @return	SUCCESS or FAILURE.
       */
      Errc Init( const Reg2d& rgs, const Reg2d& seeds );

      /**
       * Initializes the graph with the given region map. Each region
       * is represented as a node, and connected regions are represented
       * as a link between the related nodes.
       * @param rgs	the region map.
       * @return	SUCCESS or FAILURE.
       */
      Errc Init( const Reg2d &rgs );

      /**
       * Creates and returns a distinct copy of this object.
       * @return	a new graph.
       */
      Pobject *Clone() const;

      /**
       * Returns the node at the specified coordinates.
       * @param pos	the coordinates.
       * @return	the node at the specified coordinates.
       */
      GNode<Point2d> *operator[]( Long pos ){ return(tnode[pos]); }

      /**
       * Returns the node at the specified coordinates.
       * @param pos	the coordinates.
       * @return	the node at the specified coordinates.
       */
      const GNode<Point2d> *operator[]( Long pos ) const { return(tnode[pos]); }
   
      /**
       * Adds the specified node that references the specified item. 
       * @param node	the index of the node.
       * @param item	the index of the related item.
       * @param pt	the coordinate of the node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Add( Long node, Long item, const Point2d &pt );

      /**
       * Adds the specified node that references the specified item.
       * The coordinate of the node is set to (0,0).
       * @param node	the index of the node.
       * @param item	the index of the related item.
       * @return	SUCCESS or FAILURE.
       */
      Errc Add( Long node, Long item ) {
	 return Add(node,item,Point2d(0,0));
      }

      /**
       * Adds the specified node that references the specified item.
       * The coordinates of the node is set to the specificied cordinates.
       * @param node	the index of the node.
       * @param item	the index of the related item.
       * @param y		the row coordinate.
       * @param x		the column coordinate.
       * @return	SUCCESS or FAILURE.
       */
      Errc Add( Long node, Long item, Long y, Long x ) {
	 return Add(node,item,Point2d(y,x));
      }

      /**
       * Deletes the specified node from the graph. Unlinks it
       * from connected nodes.
       * @param s	the node to be deleted.
       * @return	SUCCESS or FAILURE.
       */
      Errc Del( Long s );

      /**
       * Links the two specified nodes s1 and s2 by adding two edges
       * one from s1 to s2 and one from s2 to s1 and sets the specified value
       * for each edge weight, either by adding it to the current weight
       * if add = true or by setting it.
       * @param s1	the first node.
       * @param s2	the second node.
       * @param weight	the weight for the link.
       * @param add	if true adds the weight to the current weight,
       *                otherwise sets the new value.
       * @return	SUCCESS or FAILURE.
       */
      Errc Link( Long s1, Long s2, Double weight=1.0F, bool add=false );

      /**
       * Links the two specified nodes s1 and s2 by adding two identified edges
       * one from s1 to s2 and one from s2 to s1 and sets the specified value
       * for the link weight, either by adding it to the current weight
       * if add = true or by setting it.
       * @param s1	the first node.
       * @param s2	the second node.
       * @param i       the identifier of the edge
       * @param weight	the weight for the link.
       * @param add	if true adds the weight to the current weight,
       *                otherwise sets the new value.
       * @return	SUCCESS or FAILURE.
       */
      Errc Link( Long s1, Long s2, Long i, Double weight=1.0F, bool add=false );

      /**
       * Unlinks the two specified nodes.
       * s1 will no longer be a neighbour of s2 (and vice versa).
       * @param s1	the first node.
       * @param s2	the second node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Unlink( Long s1, Long s2 );

      /**
       * Removes the link i between the two specified nodes s1 and s2.
       * Other link between the two nodes s1 and s2 are not
       * removed, therefore s1 can remain a neighbor of s2.
       *
       * @param s1	the first node.
       * @param s2	the second node.
       * @param i       the identifier of the edge.
       * @return	SUCCESS or FAILURE.
       */
      Errc Unlink( Long s1, Long s2, Long i );

      /**
       * Merges the two specified nodes.This means keeps
       * only the first node and merges all neighbours of the
       * second node. The result weight is the sum of the weight, 
       * but the seed is still the seed of the first node.
       * @param s1	the first node.
       * @param s2	the second node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Merge( Long s1, Long s2 );

      /**
       * Splits the first node to create the second node.
       * The list of neighbours, the weight and the seeds
       * are duplicated.
       * @param s1	the first node.
       * @param s2	the second node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Split( Long s1, Long s2 );
   
      /**
       * Loads attribute values from the specified file.
       * Allocates therefrom the related data.
       * @param file	the file where to read attributes values. 
       * @return	SUCCESS or FAILURE in case of IO errors..
       */
      Errc LoadAttributes( FILE *file );

      /**
       * Saves the current attribute values.
       * @param file	the file.
       * @return	SUCCESS or FAILURE in case of IO errors..
       */
      Errc SaveAttributes( FILE *file ) const;

      /**
       * Loads data from the specified file.
       * @param file	the file where to read data. 
       * @return	SUCCESS or FAILURE in case of IO errors..
       */
      Errc LoadData( FILE *file );

      /**
       * Saves data in the specified file.
       * @param file	the file where to save data. 
       * @return	SUCCESS or FAILURE in case of IO errors..
       */
      Errc SaveData( FILE *file ) const;

      /**
       * Creates a new Graph of the same type but
       * where the data are masked by the given mask.
       * It means that value are set to 0 when the related
       * label in the mask is 0.
       * @param mask	the region map that is used as a mask. 
       * @return	the new Graph.
       */
      Pobject *Mask( const Pobject *mask ) ;

      /**
       * Creates a new graph where the data
       * are ummasked by the given mask and the given reference image.
       * It means that values are set to the value of the
       * reference object when the related label in the mask is 0.
       * @param mask	the region map that is used as a mask. 
       * @param reference	the object that is used as a reference. 
       * @return	a new Graph.
       */
      Pobject *UnMask( const Pobject *mask, const Pobject *reference ) ;

      /**
       * Creates a new graph by copy. Allocates the related
       * data and sets the values with the grs values. If needed
       * casts the values by using the C casting.
       * @param grs	the specified graph.
       */
      Graph2d( const Graph2d &grs ): Pobject() { *this = grs; _directed = grs._directed; };
   };

   /** @brief A 3D graph.
    *
    * A graph is a set of nodes connected to some other nodes.
    * The two types of graph are supported: directed and undirected;
    * the type must be specified with the constructor.
    * A node is characterized by a value which determines if the
    * node is active in the representation of the graph or not.
    * A node can reference any of the Pandore object. It indexes an 
    * item in a separate array of items by a long value.
    * It is equivalent to a pointer to an objet in an array
    * except that not type is needed. 
    * <br>see @ref graph_page.
    */
   class Graph3d: public Pobject {
   private :
      GNode<Point3d> **tnode;
      Long size;
      Long ncol;
      Long nrow;
      Long ndep;
      bool _directed;
   
      friend class GEdge;

   public :

      /** The type of the data (for instance Double). */
      typedef Double ValueType;
   
      /**
       * Returns the graph identifier.
       * @return	the identifier.
       */
      Typobj Type() const {return(Po_Graph3d);}

      /**
       * Returns the name of the graph type.
       * @return	the string with the name.
       */
      std::string Name() const { return TypeName< Graph3d >::Name(); }

      /**
       * @return true if the graph is directed.
       */
      bool isDirected() const { return _directed; }

      /**
       * Returns the number of columns of the related image.
       * @return	the width.
       */
      Long Width() const { return ncol; }
   
      /**
       * Returns the number of rows of the related image.
       * @return	the width.
       */
      Long Height() const { return nrow; }

      /**
       * Returns the number of planes of the related image.
       * @return	the depth.
       */
      Long Depth() const { return ndep; }
   
      /**
       * Returns the number of nodes.
       */
      Long Size() const { return size; }
   
      /**
       * Returns the dimension of the related image.
       * @return	the dimension.
       */
      Dimension3d ImageSize() const {return Dimension3d(ndep,nrow,ncol);}
   
      /**
       * Returns the related vector of properties.
       * @return	the vector of properties.
       */
      PobjectProps Props() const { return PobjectProps(0,ncol,nrow,ndep,(PColorSpace)0,0,size,_directed); }
   
      /**
       * Creates a new graph with no data.
       * @param directed true for creating a directed graph.
       */
      Graph3d( bool directed =false ): tnode(0), size(0), ncol(0), nrow(0), ndep(0), _directed(directed) { }

      /**
       * Creates a new graph with the specified number of nodes
       * and the specified dimension of the related image.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param directed true for creating a directed graph.
       */
      Graph3d( Long s, bool directed =false ): tnode(0),_directed(directed)  { New(s,0,0,0); }

      /**
       * Creates a new graph with the specified number of nodes
       * and the specified dimension of the related image.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param d	the number of bands of the related image.
       * @param h	the height of the related image.
       * @param w	the width of the related image.
       * @param directed true for creating a directed graph.
       */
      Graph3d( Long s, Long d, Long h, Long w, bool directed =false ): tnode(0),_directed(directed)  { New(s,d,h,w); }
   
      /**
       * Creates a new graph with the specified number of nodes
       * and the specified dimension of the related image.
       * @warning the node value is not initialized with 0.
       * Allocates therefrom the related data.
       * @param s	the number of nodes.
       * @param d	the dimension of the i`mage.
       * @param directed true for creating a directed graph.
       */
      Graph3d( Long s, const Dimension3d &d, bool directed =false ): tnode(0), _directed(directed) { New(s,d.d,d.h,d.w); }

      /**
       * Creates a new graph with the specified properties.
       * Allocates therefrom the related data.
       * @warning the node value is not initialized with 0.
       * @param p	the properties.
       */
      Graph3d( const PobjectProps& p ): tnode(0) { _directed=p.directed; New(p.size,p.ndep,p.nrow,p.ncol); }
   
      /**
       * Deletes the current graph.
       */
      ~Graph3d(){ Delete(); }

      /**
       * Allocates the data from the specified number of nodes,
       * and the specified dimension of the related image.
       * @warning the node value is not initialized with 0.
       * @param s	the number of nodes.
       * @param d	the depth of the related image.
       * @param h	the height of the related image.
       * @param w	the width of the related image.
       */
      void New( Long s, Long d, Long h, Long w );

      /**
       * Allocates the image data from the specified vector of properties.
       * @warning the node value is not initialized with 0.
       * @param p	the vector of properties.
       */
      void New( const PobjectProps &p ) { New(p.size,p.ndep,p.nrow,p.ncol); }

      /**
       * Deletes the graph data.
       */
      void Delete();

      /**
       * Initializes the graph with the given region map. Each region
       * is represented as a node, and connected regions are represented
       * as a link between the related nodes.
       * The seed map is used to set the coordinates of each node.
       * @param rgs	the region map.
       * @param seeds	the region map that holds the seeds.
       * @return	SUCCESS or FAILURE.
       */
      Errc Init( const Reg3d &rgs, const Reg3d &seeds );

      /**
       * Initializes the graph with the given region map. Each region
       * is represented as a node, and connected regions are represented
       * as a link between the related nodes.
       * @param rgs	the region map.
       * @return	SUCCESS or FAILURE.
       */
      Errc Init( const Reg3d &rgs );

      /**
       * Sets the values of the graph from the
       * specified graph values.
       * If needed, deletes the previous data
       * and reallocs new data.
       * @param src	the reference graph.
       */
      Graph3d& operator=( const Graph3d &src );

      /**
       * Creates and returns a distinct copy of this object.
       * @return	a new graph.
       */
      Pobject *Clone() const;

      /**
       * Returns the node at the specified coordinates.
       * @param pos	the coordinates.
       * @return	the node at the specified coordinates.
       */
      GNode<Point3d> *operator[]( Long pos ) { return(tnode[pos]); }

      /**
       * Returns the node at the specified coordinates.
       * @param pos	the coordinates.
       * @return	the node at the specified coordinates.
       */
      const GNode<Point3d> *operator[]( Long pos ) const { return(tnode[pos]); }

      /**
       * Adds the specified node that references the specified item. 
       * @param node	the index of the node.
       * @param item	the index of the related item.
       * @param pt		the coordinate of the node.
       */
      Errc Add( Long node, Long item, const Point3d& pt );

      /**
       * Adds the specified node that references the specified item.
       * The coordinates of the node is set to (0,0,0).
       * @param node	the index of the node.
       * @param item	the index of the related item.
       * @return	SUCCESS or FAILURE.
       */
      Errc Add( Long node, Long item ) { return Add(node,item,Point3d(0,0,0)); }

      /**
       * Adds the specified node that references the specified item.
       * The coordinates of the node is set to the specified cordinates.
       * @param node	the index of the node.
       * @param item	the index of the related item.
       * @param z		the plane coordinate.
       * @param y		the row coordinate.
       * @param x		the column coordinate.
       * @return	SUCCESS or FAILURE.
       */
      Errc Add( Long node, Long item, Long z, Long y, Long x ){ 
	 return Add(node,item,Point3d(z,y,x));
      }
   
      /**
       * Deletes the specified node from the graph. Unlinks it
       * from connected nodes.
       * @param s	the node to be deleted.
       * @return	SUCCESS or FAILURE.
       */
      Errc Del( Long s );

      /**
       * Links the two specified nodes s1 and s2 by adding two edges
       * one from s1 to s2 and one from s2 to s1 and sets the specified value
       * for the link weight, either by adding it to the current weight
       * if add = true or by setting it.
       * @param s1	the first node.
       * @param s2	the second node.
       * @param weight	the weight for the link.
       * @param add	if true adds the weight to the current weight,
       *                otherwise sets the new value.
       * @return	SUCCESS or FAILURE.
       */
      Errc Link( Long s1, Long s2, Double weight=1.0F, bool add=false );

      /**
       * Links the two specified nodes s1 and s2 by adding two identified edges
       * one from s1 to s2 and one from s2 to s1 and sets the specified value
       * for the link weight, either by adding it to the current weight
       * if add = true or by setting it.
       * @param s1	the first node.
       * @param s2	the second node.
       * @param i       the identifier of the edge.
       * @param weight	the weight for the link.
       * @param add	if true adds the weight to the current weight,
       *                otherwise sets the new value.
       * @return	SUCCESS or FAILURE.
       */
      Errc Link( Long s1, Long s2, Long i, Double weight=1.0F, bool add=false );

      /**
       * Unlinks the two specified nodes.
       * s1 will no longer be a neighbour of s2 (and vice versa).
       * @param s1	the first node.
       * @param s2	the second node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Unlink( Long s1, Long s2 );

      /**
       * Unlinks the two specified nodes (linked be the identified edge).
       * s1 will no longer be a neighbour of s2 (and vice versa).
       * @param s1	the first node.
       * @param s2	the second node.
       * @param i       the identifier of the edge
       * @return	SUCCESS or FAILURE.
       */
      Errc Unlink( Long s1, Long s2, Long i );

      /**
       * Merges the two specified nodes.This means keeps
       * only the first node and merges all neighbours of the
       * second node. The result weight is the sum of the weight, 
       * but the seed is still the seed of the first node.
       * @param s1	the first node.
       * @param s2	the second node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Merge( Long s1, Long s2 );

      /**
       * Splits the first node to create the second node.
       * The list of neighbours, the weight and the seeds
       * are duplicated.
       * @param s1	the first node.
       * @param s2	the second node.
       * @return	SUCCESS or FAILURE.
       */
      Errc Split( Long s1, Long s2 );
   
      /**
       * Loads attribute values from the specified file.
       * Allocates therefrom the related data.
       * @param file	the file where to read attributes values. 
       * @return	SUCCESS or FAILURE in case of IO errors..
       */
      Errc LoadAttributes( FILE *file );
   
      /**
       * Saves the current attribute values.
       * @param file	the file.
       * @return	SUCCESS or FAILURE in case of IO errors.
       */
      Errc SaveAttributes( FILE *file ) const;

      /**
       * Loads data from the specified file.
       * @param file	the file where to read data. 
       * @return	SUCCESS or FAILURE in case of IO errors.
       */
      Errc LoadData( FILE *file );

      /**
       * Saves data in the specified file.
       * Allocates therefrom the related data.
       * @param file	the file where to save data. 
       * @return	SUCCESS or FAILURE in case of IO errors.
       */
      Errc SaveData( FILE *file ) const;
   
      /**
       * Creates a new graph where the data are masked by the given mask.
       * It means that value are set to 0 when the related
       * label in the mask is 0.
       * @param mask	the region map that is used as a mask. 
       * @return	a new Graph.
       */
      Pobject *Mask( const Pobject *mask ) ;

      /**
       * Creates a new Graph of the same type but where the data
       * are ummasked by the given mask and the given reference image.
       * It means that values are set to the value of the
       * reference object when the related label in the mask is 0.
       * @param mask	the region map that is used as a mask. 
       * @param reference	the object that is used as a reference. 
       * @return	the new Graph.
       */
      Pobject *UnMask( const Pobject *mask,const Pobject *reference ) ;
   
      /**
       * Creates a new graph by copy. Allocates the related
       * data and sets the values with the grs values. If needed
       * casts the values by using the C casting.
       * @param grs	the specified graph.
       */
      Graph3d( const Graph3d &grs ): Pobject() { _directed=grs._directed; *this=grs; };
   };

} //End of pandore:: namespace

#endif // __PGRAPHH__
