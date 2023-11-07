#include "slist.h"

/*
Class Library File
*/

// Constructor
Airport::Airport() {
  
}
// Destructor
    void Airport::destruct() {
      delete this;
    }
// add(value)				//Adds a new value to the end of this list.
    void Airport::add(Airport* value) {
      Airport* ptr = this;
      while (ptr->next) {
        ptr = ptr->next;
      }
      ptr->next = value;
    }
// clear()					//Removes all elements from this list.
    void Airport::clear() {
      Airport* ptr = this->next;
      while (ptr) {
        Airport* temp = ptr;
        ptr = ptr->next;
        temp->destruct();
      }
    }
// equals(list)				//Returns true if the two lists contain the same elements in the same order.
    bool Airport::equals(Airport* list) {
      Airport* ptr = this;
      Airport* ptr2 = list;
      while (ptr && list) {
        if (ptr->longitude != ptr2->longitude || ptr->latitude != ptr2->latitude)
          return false;
      }
      if (ptr || list)
        return false;
      return true;
    }
//get(index)				//Returns the element at the specified index in this list.
    Airport* Airport::get(int index) {
      Airport* ptr = this;
      for (int i = 0; i <= index && ptr; i++) {
        ptr = ptr->next;
      }
      return ptr;
    }
//insert(index, value)		//Inserts the element into this list before the specified index.
    void Airport::insert(int index, Airport* value) {
      Airport* ptr = this;
      for (int i = 0; i < index && ptr; i++) {
        ptr = ptr->next;
      }
      if (ptr) {
        ptr->next = value;
      }
    }
//exchg(index1, index2)		//Switches the payload data of specified indexex.
    void Airport::exchg(int index1, int index2) {
      Airport* temp = new Airport();
      Airport* ptr1 = this;
      for (int i = 0; i <= index1 && ptr1; i++) {
        ptr1 = ptr1->next;
      }
      Airport* ptr2 = this;
      for (int i = 0; i <= index2 && ptr2; i++) {
        ptr2 = ptr2->next;
      }
      if (ptr1 && ptr2) {
        temp->longitude = ptr1->longitude;
        temp->latitude = ptr1->latitude;
        for (int i = 0; i < 5; i++) {
          temp->code[i] = ptr1->code[i];
        }
        temp->dist = ptr1->dist;
        ptr1->longitude = ptr2->longitude;
        ptr1->latitude = ptr2->latitude;
        for (int i = 0; i < 5; i++) {
          ptr1->code[i] = ptr2->code[i];
        }
        ptr1->dist = ptr2->dist;
        ptr2->longitude = temp->longitude;
        ptr2->latitude = temp->latitude;
        for (int i = 0; i < 5; i++) {
          ptr2->code[i] = temp->code[i];
        }
        ptr2->dist = temp->dist;
      }
    }
//swap(index1,index2)		//Swaps node located at index1 with node at index2
    void Airport::swap(int index1, int index2) {
      Airport* p1 = this;
      Airport* p2 = this;
      for (int i = 0; i < index1 && p1; i++) {
        p1 = p1->next;
      }
      for (int i = 0; i < index2 && p2; i++) {
        p2 = p2->next;
      }
      Airport* temp = p2->next;
      p2->next = p2->next->next;
      temp->next = p2->next->next;
      p2->next->next = temp;
    }
// isEmpty()				//Returns true if this list contains no elements.
    bool Airport::isEmpty() {
      if (this->next)
        return false;
      return true;
    }
// remove(index)			//Removes the element at the specified index from this list.
    void Airport::remove(int index) {
      Airport* p1 = this;
      for (int i = 0; i < index && p1; i++) {
        p1 = p1->next;
      }
      Airport* temp = p1->next;
      p1->next = p1->next->next;
      temp->destruct();
    }
// set(index, value)		//Replaces the element at the specified index in this list with a new value.
    void Airport::set(int index, Airport* value) {
      Airport* p1 = this;
      for (int i = 0; i < index && p1; i++) {
        p1 = p1->next;
      }
      Airport* temp = p1->next;
      p1->next = value;
      value->next = temp->next;
      temp->destruct();
    }
// size()					//Returns the number of elements in this list.
    int Airport::size() {
      int c = 0;
      Airport* ptr = this;
      while (ptr) {
        c++;
        ptr = ptr->next;
      }
      return c;
    }
// DO NOT IMPLEMENT >>> subList(start, length)	//Returns a new list containing elements from a sub-range of this list.

// DO NOT IMPLEMENT >>> toString()				//Converts the list to a printable string representation.
