#ifndef SLIST_H
#define SLIST_H

class Airport {

  private:

  public: 
    char code[5];
    double longitude;
    double latitude;
    double dist;
    Airport *next;

// Constructor
    Airport();
// Destructor
    void destruct();
// add(value)				//Adds a new value to the end of this list.
    void add(Airport* value);
// clear()					//Removes all elements from this list.
    void clear();
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
    bool equals(Airport* list);
//get(index)				//Returns the element at the specified index in this list.
    Airport* get(int index);
//insert(index, value)		//Inserts the element into this list before the specified index.
    void insert(int index, Airport* value);
//exchg(index1, index2)		//Switches the payload data of specified indexex.
    void exchg(int index1, int index2);
//swap(index1,index2)		//Swaps node located at index1 with node at index2
    void swap(int index1, int index2);
// isEmpty()				//Returns true if this list contains no elements.
    bool isEmpty();
// remove(index)			//Removes the element at the specified index from this list.
    void remove(int index);
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
    void set(int index, Airport* value);
// size()					//Returns the number of elements in this list.
    int size();
// DO NOT IMPLEMENT >>> subList(start, length)	//Returns a new list containing elements from a sub-range of this list.

// DO NOT IMPLEMENT >>> toString()				//Converts the list to a printable string representation.

};

#endif