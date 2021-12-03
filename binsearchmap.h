//---------------------------------------------------------------------------
// NAME:Dominic MacIsaac
// DATE:Fall 2021
// DESC: Binary Search map that uses an array map and binary search function to story key value pairs in order
//---------------------------------------------------------------------------

#ifndef BINSEARCHMAP_H
#define BINSEARCHMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BinSearchMap : public Map<K,V>
{
public:

  // Returns the number of key-value pairs in the map
  int size() const;

  // Tests if the map is empty
  bool empty() const;

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  V& operator[](const K& key);

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  const V& operator[](const K& key) const;

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  void insert(const K& key, const V& value);

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  void erase(const K& key);

  // Returns true if the key is in the collection, and false
  // otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order.
  ArraySeq<K> sorted_keys() const;  

private:

  // If the key is in the collection, bin_search returns true and
  // provides the key's index within the array sequence (via the index
  // output parameter). If the key is not in the collection,
  // bin_search returns false and provides the last index checked by
  // the binary search algorithm. 
  bool bin_search(const K& key, int& index) const{
    if(seq.size() == 0){index = 0; return false;}
    int start = 0;
    int mid = 0;
    int end = seq.size()-1;

    while(start <= end){

      mid = (end-start)/2 + start;

      if(key == seq[mid].first){
        index = mid;
        return true;
      }

      if(key < seq[mid].first){
        end = mid - 1;
      }

      if(key > seq[mid].first){
        start = mid + 1;
      }

    }
    index = mid;
    return false;
  }
  
  // implemented as a resizable array of (key-value) pairs
  ArraySeq<std::pair<K,V>> seq;

};

template<typename K, typename V>
int BinSearchMap<K,V>::size() const{
   return seq.size();
}

  // Tests if the map is empty
  template<typename K, typename V>
  bool BinSearchMap<K,V>::empty() const{
     if(seq.size()==0){ 
      return true;
    }
    return false;
  }

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  template<typename K, typename V>
  V& BinSearchMap<K,V>::operator[](const K& key){
    int i = 0;
    if(bin_search(key,i)){return seq[i].second;}
    throw std:: out_of_range("ArrayMap<K,V>::operator[](const K& key");

  }

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  template<typename K, typename V>
  const V& BinSearchMap<K,V>::operator[](const K& key) const{
    int i = 0;
    if(bin_search(key,i)){return seq[i].second;}
    throw std:: out_of_range("ArrayMap<K,V>::operator[](const K& key");

  }

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  template<typename K, typename V>
  void BinSearchMap<K,V>::insert(const K& key, const V& value){
    if(this->empty()){
      seq.insert(std::pair(key,value),0);
      return;
    }
    int i = 0;
    this->bin_search(key, i);
    if(seq[i].first > key){
      seq.insert(std::pair(key,value),i);
      return;
    }
    seq.insert(std::pair(key,value),i+1);

    return;
  }

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  template<typename K, typename V>
  void BinSearchMap<K,V>::erase(const K& key){
    int i = 0;
    if(bin_search(key,i)){
      seq.erase(i);
      return;
    }
    throw std:: out_of_range("ArrayMap<K,V>::operator[](const K& key");
  }

  // Returns true if the key is in the collection, and false
  // otherwise.
  template<typename K, typename V>
  bool BinSearchMap<K,V>::contains(const K& key) const{
    int i = 0;
    return bin_search(key,i);
  }

  // Returns the keys k in the collection such that k1 <= k <= k2
  template<typename K, typename V>
  ArraySeq<K> BinSearchMap<K,V>::find_keys(const K& k1, const K& k2) const{
    ArraySeq<K> keyList;
    int start = 0, end = 0, i = 0;
    if(seq.empty()){return keyList;}
    bin_search(k1,start);
    bin_search(k2,end);
    for(start; start <= end; start++){
      keyList.insert(seq[start].first, i);
      ++i;
    }
    return keyList;
    
  }

  // Returns the keys in the collection in ascending sorted order.
  template<typename K, typename V>
  ArraySeq<K> BinSearchMap<K,V>::sorted_keys() const{
    ArraySeq<K> keyList;
    for(int i = 0; i < seq.size(); i++){
      keyList.insert(seq[i].first, i);
    }
    return keyList;
  }

#endif
