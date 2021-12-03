//---------------------------------------------------------------------------
// NAME:Dominic MacIsaac
// DATE: Fall 2021
// DESC: Map with array sequence to store key value pairs
//---------------------------------------------------------------------------

#ifndef ARRAYMAP_H
#define ARRAYMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class ArrayMap : public Map<K,V>
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

  // implemented as a resizable array of (key-value) pairs
  ArraySeq<std::pair<K,V>> seq;

};

template<typename K, typename V>
int ArrayMap<K,V>::size() const{
  return seq.size();
}

  // Tests if the map is empty
  template<typename K, typename V>
  bool ArrayMap<K,V>::empty() const{
    if(seq.size()==0){ 
      return true;
    }
    return false;
  }

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  template<typename K, typename V>
  V& ArrayMap<K,V>::operator[](const K& key){
    int i = 0;
    while(i < seq.size()){
      if(seq[i].first == key){
        return seq[i].second;
      }
      ++i;
    }
    throw std:: out_of_range("ArrayMap<K,V>::operator[](const K& key");
  }

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  template<typename K, typename V>
  const V& ArrayMap<K,V>::operator[](const K& key) const{
    int i = 0;
    while(i < seq.size()){
      if(seq[i].first == key){
        return seq[i].second;
      }
      ++i;
    }
    throw std:: out_of_range("ArrayMap<K,V>::operator[](const K& key");
    
  }

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  template<typename K, typename V>
  void ArrayMap<K,V>::insert(const K& key, const V& value){
    seq.insert(std::pair(key,value), seq.size());
    return;
  }

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  template<typename K, typename V>
  void ArrayMap<K,V>::erase(const K& key){
    int i = 0;
    while(i < seq.size()){
      if(seq[i].first == key){
        seq.erase(i);
        return;
      }
      ++i;
    }
    throw std:: out_of_range("ArrayMap<K,V>::operator[](const K& key");
  }

  // Returns true if the key is in the collection, and false
  // otherwise.
  template<typename K, typename V>
  bool ArrayMap<K,V>:: contains(const K& key) const{
    int i = 0;
    while(i < seq.size()){
      if(seq[i].first == key){
        return true;
      }
      ++i;
    }
    return false;
  }

  // Returns the keys k in the collection such that k1 <= k <= k2
  template<typename K, typename V>
  ArraySeq<K> ArrayMap<K,V>::find_keys(const K& k1, const K& k2) const{
    ArraySeq<K> keyList;

    int i = 0;
    while(i < seq.size()){
      if(seq[i].first >= k1 && seq[i].first <= k2){
        keyList.insert(seq[i].first, keyList.size());
      }
      ++i;
    }

    return keyList;
  }

  // Returns the keys in the collection in ascending sorted order.
  template<typename K, typename V>
  ArraySeq<K> ArrayMap<K,V>::sorted_keys() const{
    ArraySeq<K> keyList;
   
    int i = 0;
    while(i < seq.size()){
      keyList.insert(seq[i].first, keyList.size());
      ++i;
    }

    keyList.merge_sort();
    return keyList;
  }

#endif
