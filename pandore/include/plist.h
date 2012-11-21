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
 * @author Alexandre Duret-Lutz. 1999-10-08
 * @author Régis Clouard - 2001-04-10 (version 3.00)
 * @author Régis Clouard - 2002-12-12 (add Reset())
 * @author Régis Clouard - 2003-06-20 (fix bug on Heap::Push())
 * @author Régis Clouard - 2006-04-18 (add namespace)
 * @author Régis Clouard - 2007-03-07 (change Heap structre)
 */

/**
 * @file plist.h
 * @brief The definition of the complex data stuctures : fifo lifo heap.
 */

#ifndef __PPLISTH__
#define __PPLISTH__

namespace pandore {

/** @brief A link for complex lists.
 *
 * This class must be overload with an effective element.
 */
struct Link {
public:
   /** The next element in the list. */
   Link *next;
   
   /**
    * Creates a new Link.
    */
   Link() : next(0) { }
};


/** @brief The base class of all complex lists.
 * 
 * This class defines all funtions that manage a complex list.
 */
struct Blist {
protected:

   /** The head of the list. */
   Link *head;

   /** The queue of the list. */
   Link *queue;

   /**
    * Creates a new list with an empty queue and an empty head.
    */
   Blist(): head(0), queue(0) {}

   /**
    * Deletes the list.
    */
   ~Blist(){}

   /**
    * Inserts the given element at the ned of the list.
    * @param a	the element to insert.
    */
   bool	Insert_queue( Link* a ) {
      if (head){
	 queue->next=a;
	 queue=a;
      }else{
	 head=queue=a;
      }
      return true;
   }

   /**
    * Inserts the given element in front of the list.
    * @param a	the element to insert.
    */
   bool	Insert_head( Link* a ) {
      if (head) {
	 a->next=head;
	 head=a;
      }else
	 head=queue=a;
      return true;
   }
   
   /**
    * @return the head of the list.
    */
   Link *Head() { return head; }

   /**
    * @return the head of the list.
    */
   Link *Next() { return head; }
   
   /**
    * Deletes and returns the fisrt element in the list. 
    * @return the element or NULL.
    */
   Link *Get_head() {
      if (head){
	 Link *a;
	 a = head;
	 head = head->next;
	 if (head==NULL) queue=NULL;
	 return a;
      }
      return NULL;
   }

public:   
   /**
    * @return true if the list of empty.
    */
   bool Empty() { return head==NULL; }

   /**
    * @returns true if the list of full.
    */
   bool Full(){ return false; }
};

/** @brief A general element of a complex list.
 * 
 * A list element is a value of type T and
 * a link to the next element in the list.
 */
template <class T>
struct ListElement : public Link {
protected:

   /** The value of the element. */
   T element;

public:
   /**
    * Creates a new list element with the specified value.
    * @ param a	the element value.
    */
   ListElement( const T &a ) : element(a) {}

   /**
    * @return the next element in the list.
    */
   ListElement<T>* Next() { return (ListElement<T>*)next; }

   /**
    * @return true if the element is not the last one.
    */
   bool HasNext() { return next != NULL; }

   /**
    * @return the value of the element.
    */
   T Item() { return element;}
};

/** @brief A First In First Out list of elements.
 *
 * The class <code>Fifo</code> defines a list of 
 * any primitive types (Uchar, Char, Slong, Float, ..)
 * that is a first in first out list.
 * Element is inserted by <code>push()</code> and
 * removed by <code>pop()</code>.
 */
template <class T>
class Fifo : public Blist {
public:

   /**
    * Gets without removing the next to be returned.
    * @return the next element to be poped.
    */
   ListElement<T> *Head(){ return (ListElement<T>*)Blist::Head(); }

   /**
    * Inserts the specified element in the Fifo.
    * Is is not a distinct copy of the element but a reference on it.
    * @param element	the element to be pushed.
    */
   void Push( const T &element ) {
      Blist::Insert_queue(new ListElement<T>(element));
   }

   /**
    * Gets and removes the nxt element in the Fifo (the first in).
    * @return the first element.
    */
   T Pop(){
      ListElement<T>* l=(ListElement<T>*)Blist::Get_head();
      T a= l->Item();
      delete l;
      return a;
   }

   /**
    * Resets the content of the fifo.
    */
   void Reset() { while (!Empty()) (void)Pop(); } 
};

/** @brief A Last In First Out list of elements.
 *
 * The class <code>Fifo</code> defines a list of 
 * any primitive types (Uchar, Char, Slong, Float, ..)
 * that is a last in first out list.
 * Element is inserted by <code>push()</code> and
 * removed by <code>pop()</code>.
 */
template <class T>
class Lifo :public Blist {
public :

   /**
    * Gets without removing the next to be returned.
    * @return the next element to be poped.
    */
   ListElement<T> *Head(){ return (ListElement<T>*)Blist::Head(); }

   /**
    * Inserts the specified element in the Lifo.
    * Is is not a distinct copy of the element but a reference on it.
    * @param element	the element to be pushed.
    */
   void Push( const T &element ) {
      Blist::Insert_head(new ListElement<T>(element));
   }

   /**
    * Gets and removes the next element in the Lifo (the first in).
    * @return the last element.
    */
   T Pop() {
      ListElement<T>* l=(ListElement<T>*)Blist::Get_head();
      T a= l->Item();
      delete l;
      return a;
   }

   /**
    * Resets the content of the lifo.
    */
   void Reset() { while (!Empty()) (void)Pop(); } 
};

/** @brief A sort list of elements (min first).
 *
 * The class <code>Heap</code> defines a heap of 
 * any primitive types (Uchar, Char, Slong, Float, ..).
 * In a heap, each element is indexed by a key value. The next element
 * to be popped is the element with the min key.
 * Element is inserted by <code>push()</code> and
 * removed by <code>pop()</code>.
 * To create the new Heap named "foo" with a maximum of 100 floats
 * use: <code>Heap<Float> foo(100)</code>.
 */
template <class T, typename U, typename V>
class Heap{
private:
   /**
    * The tree of elements.
    */
   class Theap {
   public :
      U pkey;
      V skey;
      T element;
      
      Theap() {}
      ~Theap() {}
   };
   
   int _size;
   int _nitem;
   Theap *_data;

public:

   /**
    * Creates a new <code>Heap</code> with the specified size.
    * @param n	the maximum size of the heap.
    */
   Heap( int n ): _size(n), _nitem(0), _data(0) {
      if (n>0) _data=new Theap[n];
      else std::cerr<<"Error: null or negative heap size...not allocated"<<std::endl;
   }

   ~Heap(){ delete[] _data; }

   /**
    * Checks whether the heap is empty.
    * @return true if the heap is empty.
    */
   bool Empty() { return _nitem==0; }

   /**
    * Checks whether the heap is full.
    * @return true if the heap full.
    */
   bool Full() { return _nitem==_size-1; }

   /**
    * Returns the current number of elements of the heap.
    * @return the current size of the heap
    */
   int Nrank() { return _nitem; }

   /**
    * Resets the heap (-> Nrank() = 0).
    */
   void Reset() { _nitem=0; } 

   /**
    * Inserts a new element in the heap with the specified key.
    * @param item the element to be inserted.
    * @param pkey the primary key that identify the element in the heap.
    * @param skey the secondary key that identify the element in the heap in case of equals primary key.
    * @return true if the insertion is ok, false if the heap is full.
    */
   bool Push( const T &item, U pkey, V skey=0) {
      if (Full()) {
	 std::cerr<<"Warning: heap full..." << std::endl;
	 return false;
      }
      int child=_nitem++;
      int parent=(child-1)/2;

      while (child>0 && (pkey<_data[parent].pkey || (pkey==_data[parent].pkey && skey<_data[parent].skey))) {
	 _data[child]=_data[parent];
	 child=parent;
	 parent=(parent-1)/2;
      }
      _data[child].pkey=pkey;
      _data[child].skey=skey;
      _data[child].element=item;

      return true;
   } 

   /**
    * Removes and returns the next element with the minimum key value.
    * @param pkey used to return the value of the primary key of the next element.
    * @param skey used to return the value of the secondary key of the next element.
    * @return	the element.
    */
   T Pop( U *pkey=NULL, V *skey=NULL ) {
      if (Empty()) {
	 std::cerr<<"Warning: heap empty..." << std::endl;
	 return _data[0].element;
      }

      // Get top of the heap.
      T item=_data[0].element;
      if (pkey) *pkey=_data[0].pkey;
      if (skey) *skey=_data[0].skey;

      --_nitem;
      int parent=0;
      int child=1;

      // Move up the lower branch of the heap.
      while (child<_nitem) {

	 if (child+1<_nitem
	     && (_data[child+1].pkey<_data[child].pkey 
		 || (_data[child+1].pkey==_data[child].pkey
		     && _data[child+1].skey<_data[child].skey))) {
	    child++;
	 }
	 if (_data[_nitem].pkey<_data[child].pkey
	     || (_data[_nitem].pkey==_data[child].pkey
		 && _data[_nitem].skey<_data[child].skey)) {
	    break;
	 }
	 // Move up child as parent.
	 _data[parent]=_data[child];
	 parent=child;
	 child=child*2+1;
      }
      _data[parent]=_data[_nitem];
      return item;
   }

   /**
    * Removes from the heap the first occurence of the element
    * specified by its value.
    * @param item	the element to be removed.
    * @return	SUCCCESS or FAILURE
    */
   Errc Remove( T &item ) {
      bool result=false;
      int i=0;

      for (; i<_nitem && !(_data[i].element==item); i++) ;
      if (i>= _nitem) return false;
      
      --_nitem;
      int parent=i;
      int child=i*2+1;

      // Move up the lower branch of the heap.
      while (child<_nitem) {
	 if (child+1<_nitem
	     && (_data[child+1].pkey<_data[child].pkey
		 || (_data[child+1].pkey==_data[child].pkey
		     && _data[child+1].skey<_data[child].skey))) {
	    child++;
	 }

	 if (_data[_nitem].pkey<_data[child].pkey
	     || (_data[_nitem].pkey==_data[child].pkey
		 && _data[_nitem].skey<_data[child].skey)) {
	    break;
	 }
	 
	 // Move up child as parent.
	 _data[parent]=_data[child];
	 parent=child;
	 child=child*2+1;
      }
      _data[parent]=_data[_nitem];

      return true;
   }
};

/** @brief An ordered list of First In First Out list elements.
 *
 * The class <code>OrderedFifo</code> defines a ordered
 * list of element, which is implemented as an array of fifo.
 * Each element is indexed by a key value (a Long value).
 * Elements with the same key value are ordered in a fifo.
 * To create the new Heap named "foo" with a maximum of 100 floats
 * use: <code>Heap<Float> foo(100)</code>.
 */
template< typename T >
class OrderedFifo {
private:
   Long nfifo;
   Long nitem;
   Long min;
   Long max;

   Fifo< T > *tfifo;

public:
   
   /**
    * Creates a new ordered list with the specified maximum size
    * that corresponds to the maximum key value for elements.
    * @param size	the number of fifo.
    */
   OrderedFifo( Long size ): nfifo(size), nitem(0), min(0),max(0) {
      if (size) {
	 tfifo=(Fifo< T >*)calloc(size,sizeof(Fifo< T >));
	 if (tfifo==NULL) {
	    std::cerr << "Warning: memory full: OrderedFifo<T>." << std::endl;
	 }
      }else
	 tfifo=NULL;
   }

   ~OrderedFifo() {
      for (Long i=0;i<nfifo;i++)
	 while (!(tfifo[i].Empty()))
	    tfifo[i].Pop();
      free(tfifo);
   }

   /**
    * Returns the current number of elements if the heap.
    * @return the current size of the heap
    */
   int Nrank(){ return nitem; }

   /**
    * Returns the i th fifo in the list. 
    * @param i	the index of the fifo.
    * @return	the related fifo or NULL.
    */
   Fifo< T > operator[]( Long i ) { return tfifo[i]; }

   /**
    * Returns the index of the first not empty fifo.
    * @return the index in the list.  
    */
   Long First() {
      Long i;
      for (i=0;(i<nfifo) && (tfifo[i].Empty());i++) ;
      return i;
   }
   
   /**
    * Returns the index of the last not empty fifo.
    * @return the index in the list.  
    */
   Long Last() {
      Long i;

      if (!nfifo) return 0;
      for (i=nfifo-1;(i>=0) && (tfifo[i].Empty());i--) ;
      return i;
   }

   /**
    * Inserts a new element in the heap with the specified key.
    * @param item	the element to be inserted.
    * @param kitem	the key that identify the element in the ordered list.
    * @return true if the insertion is ok, false if the heap is full.
    */
   bool Push( const T &item, Long kitem ) {
      if (kitem>=nfifo)
	 return false;
      tfifo[kitem].Push(item);
      if (((min==max) && (min==0)) || (min>kitem)) min=kitem;
      if (max<kitem) max=kitem;
      nitem++;
      return true;
   }
   
   /**
    * Removes and returns the next element with the minimum key value.
    * @param kitem	use to return the value of the key of the next element.
    * @return	the related element.
    */
   T Pop( long *kitem=NULL ) {
      T pt;
      if (Empty()) {
	 std::cerr << "Warning: fifo empty..." << std::endl;
	 return T();
      }
      pt=tfifo[min].Pop();
      if (kitem)
	 *kitem=min;
      if (tfifo[min].Empty()) {
	 if (max==min) min=max=0;
	 else min=First();
      }
      nitem--;
      return pt;
   }
   
   /**
    * Checks whether the OrderedFifo is empty.
    * @return true if the OrderedFifo is empty, false otherwise.
    */
   bool Empty() { return (min==max) && (min==0); }
};

} //End of pandore:: namespace

#endif // __PPLISTH__
