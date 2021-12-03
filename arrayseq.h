
//---------------------------------------------------------------------------
// NAME:Dominic MacIsaac
// FILE: arrayseq.h
// DATE: Fall 2021
// DESC: Array Sequence class that includes the merge_sort and quick_sort function
//----------------------------------------------------------------------


#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>
#include <ostream>
#include "sequence.h"


template<typename T>
class ArraySeq : public Sequence<T>
{
public:

  // Default constructor
  ArraySeq();

  // Copy constructor
  ArraySeq(const ArraySeq& rhs);

  // Move constructor
  ArraySeq(ArraySeq&& rhs);

  // Copy assignment operator
  ArraySeq& operator=(const ArraySeq& rhs);

  // Move assignment operator
  ArraySeq& operator=(ArraySeq&& rhs);

 friend std::ostream & operator << (std::ostream &out, const ArraySeq& rhs){
   if(rhs.empty()){return out;}
   out << rhs.array[0];
   for(int i = 1; i < rhs.count; i ++){
     out << ", " << rhs.array[i];
   }
   return out;
   }

 friend std::istream & operator >> (std::istream &in, const ArraySeq& rhs){
   return in;
   }
  
  // Destructor
  ~ArraySeq();
  
  // Returns the number of elements in the sequence
  virtual int size() const;

  // Tests if the sequence is empty
  virtual bool empty() const;

  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual T& operator[](int index);

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual const T& operator[](int index) const;

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  virtual void insert(const T& elem, int index);

  // Shrinks the sequence by removing the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  virtual void erase(int index);

  // Returns true if the element is in the sequence, and false
  // otherwise.
  virtual bool contains(const T& elem) const;

  // Sorts the elements in the sequence using less than equal (<=)
  // operator. (Not implemented in HW-3)
  virtual void sort(); 
  virtual void merge_sort();
  virtual void quick_sort();
  
private:

  // resizable array
  T* array = nullptr;

  // size of list
  int count = 0;

  // max capacity of the array
  int capacity = 0;

  // helper to double the capacity of the array
  void resize(){
    if(capacity == 0)
    {
    array = new T[1];
    ++capacity;
    }
    else {
      capacity=capacity*2;
      T* temp = new T[capacity];
       for(int i = 0; i < count; i++){
         temp[i] = array[i];
       }
    delete [] array;
    array = temp;
    }
  }
  
  // helper to delete the array list (called by destructor and copy
  // constructor)
  void make_empty(){
    delete[] array;
    count = 0;
    capacity = 0;
  }

  void merge_sort(int start, int end){
    if (start < end){
      int mid = (start + end)/2;
      this->merge_sort(start, mid);
      this->merge_sort(mid+1, end);
      T temp[(end-start)+1];
      int first1 = start;
      int first2 = mid +1;
      int i = 0;
      while(first1 <= mid and first2 <= end){
        if (array[first1] < array[first2]){
          temp[i++] = array[first1++];
        }
        else{
          temp[i++] = array[first2++];
        }
      }
      while (first1 <= mid){
        temp[i++] = array[first1++];
      }
      while(first2 <= end){
        temp[i++] = array[first2++];
      }
      for(i = 0; i <= (end-start); i++){
        array[start+i] = temp[i];
      }
    }
  }

  void quick_sort(int start, int end){
    if(start < end){
      T temp;

      T pivot_val = array[start];
      int end_p1 = start;
      for(int i = start+1; i <= end; i++){
        if(array[i] < pivot_val){
          end_p1 = end_p1 +1;
          temp = array[i];
          array[i] = array[end_p1];
          array[end_p1] = temp;
          
        }
      }
      
      temp = array[start];
      array[start] = array[end_p1];
      array[end_p1] = temp;
      this->quick_sort(start, (end_p1-1));
      this->quick_sort((end_p1+1), end);
    }
  }
};

template<typename T>
ArraySeq<T>::ArraySeq()
{
   return;
}

 // Copy constructor
 
 template<typename T>
  ArraySeq<T>::ArraySeq(const ArraySeq& rhs){
    *this = rhs;
    return;
  }

  // Move constructor
  template<typename T>
  ArraySeq<T>::ArraySeq(ArraySeq&& rhs){
    *this = std::move(rhs);
  }

  // Copy assignment operator
  template<typename T>
  ArraySeq<T>& ArraySeq<T>::operator=(const ArraySeq& rhs){
    if(this != &rhs){
      this->make_empty();
      this->capacity = rhs.capacity;
      this->count = rhs.count;
      T* temp = new T[this->capacity];
      this->array = temp;
      for(int i = 0; i<this->count; i++){
        this->array[i] = rhs.array[i];
      }
    }
    return *this;
  }

  // Move assignment operator
  template<typename T>
  ArraySeq<T>& ArraySeq<T>::operator=(ArraySeq&& rhs){
    if(this != &rhs){
      this->make_empty();
      this->capacity = rhs.capacity;
      this->count = rhs.count;
      this->array = rhs.array;
      rhs.array = nullptr;
      rhs.count = 0;
      rhs.capacity = 0;
    }

    return *this;
  }

  // Destructor
  template<typename T>
  ArraySeq<T>::~ArraySeq(){
    this->make_empty();
    return;
  }
  
  // Returns the number of elements in the sequence
  template<typename T>
  int ArraySeq<T>::size() const{
    return count;
  }

  // Tests if the sequence is empty
  template<typename T>
  bool ArraySeq<T>::empty() const{
    if(count == 0){
      return true;
    }
    return false;
  }

  // Returns a reference to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  template<typename T>
  T& ArraySeq<T>::operator[](int index){
    if (index < 0 || index >= count){
      throw std:: out_of_range("ArraySeq <T>:: operator[](int index)");
    }

    return array[index];
  }

  // Returns a constant address to the element at the index in the
  // sequence. Throws out_of_range if index is invalid.
  template<typename T>
  const T& ArraySeq<T>::operator[](int index) const{
    if (index < 0 || index >= count){
      throw std:: out_of_range("const T& ArraySeq <T>:: operator[](int index)");
    }

    return array[index];
  }

  // Extends the sequence by inserting the element at the given
  // index. Throws out_of_range if the index is invalid.
  template<typename T>
  void ArraySeq<T>::insert(const T& elem, int index){
   
    if(capacity == 0 and index == 0){
      this->resize();
    }

    if(count == capacity){
      this->resize();
    }

    if (index < 0 || index >= capacity){
      throw std:: out_of_range("ArraySeq <T>:: insert(const T& elem, int index)");
      return;
    }
    
    for(int i = count; i>index; i--){
      array[i] = array[i-1];
    }

    array[index] = elem;
    ++count;
    return;
  }

  
  template<typename T>
  void ArraySeq<T>::erase(int index){
    
    
    if (index < 0 || index >= count){
      throw std:: out_of_range("ArraySeq <T>:: erase(int index)");
    }
   
    T* temp = new T[1];
    
    
    if(capacity == 1){
      array[0] = temp[0];
      --count;
      delete [] temp;
      return;
    }

   
    for(int i = index; i < count; i++){
      array[i] = array[i+1];
    }

    --count;
    delete [] temp;
    return;
  }

  template<typename T>
  bool ArraySeq<T>::contains(const T& elem) const{
    for(int i = 0; i < count; i++){
      if(elem == array[i]){
        return true;
      }
    }
    return false;
  }



template<typename T>
void ArraySeq<T>::sort()
{
  // TODO: saved for future assignment
}


// TODO: Implement the above functions below using the approaches
//       discussed in class and specified in the homework assignment.


template<typename T>
void ArraySeq<T>::merge_sort(){
  this->merge_sort(0,this->size()-1);
}

template<typename T>
void ArraySeq<T>::quick_sort(){
  this->quick_sort(0,this->size()-1);
}


#endif
