//---------------------------------------------------------------------------
// NAME: Dominic MacIsaac
// CLASS: CPSC 223
// DATE: Fall 2021
// DESC: Hashmap implementation: uses a hash function, arrays, and linked list to 
// implement hashmap
//---------------------------------------------------------------------------

#ifndef HASHMAP_H
#define HASHMAP_H

#include <functional>
#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class HashMap : public Map<K,V>
{
public:

  // default constructor
  HashMap();

  // copy constructor
  HashMap(const HashMap& rhs);

  // move constructor
  HashMap(HashMap&& rhs);

  // copy assignment
  HashMap& operator=(const HashMap& rhs);

  // move assignment
  HashMap& operator=(HashMap&& rhs);  

  // destructor
  ~HashMap();
  
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

  // Returns true if the key is in the collection, and false otherwise.
  bool contains(const K& key) const;

  // Returns the keys k in the collection such that k1 <= k <= k2
  ArraySeq<K> find_keys(const K& k1, const K& k2) const;

  // Returns the keys in the collection in ascending sorted order
  ArraySeq<K> sorted_keys() const;  

  // statistics functions for the hash table implementation
  int min_chain_length() const;
  int max_chain_length() const;
  double avg_chain_length() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* next;
  };

  // number of key-value pairs in map
  int count = 0;

  // max size of the (array) table
  int capacity = 16;

  // threshold for resize and rehash
  const double load_factor_threshold = 0.60;
  
  // array of linked lists
  Node** table = new Node*[capacity];

  // the hash function
  int hash(const K& key) const{
    std::hash<K> hash_fun;
    size_t value = hash_fun(key);
    size_t index = value % capacity;
    return index;
  }

  // resize and rehash the table
  void resize_and_rehash(){
    int oldCap = capacity;
    capacity *= 2;
    Node** oldTable = table;
    Node** newTable = new Node*[capacity];
    table = newTable;
    init_table();
    count = 0;

    Node* temp = nullptr;

    for(int i = 0; i<oldCap; i++){
      temp = oldTable[i];
      while(oldTable[i] != nullptr){
        temp = oldTable[i];
        this->insert(temp->key, temp->value);
        oldTable[i] = temp->next;
        delete temp;
      }
    }
    delete[] oldTable;
  }

  // initialize the table to all nullptr
  void init_table(){
    for(int i = 0; i < capacity; i++){
      table[i] = nullptr;
    }
    return;
  }
  
  // clean up the table and reset member variables
  void make_empty(){
    Node* temp = nullptr;
    for(int i = 0; i < capacity; i++){
      temp = table[i];
      while(table[i] != nullptr){
        temp = table[i];
        table[i] = temp->next;
        delete temp;
      }
    }

    count = 0;
    capacity = 16;
    return;
  }
};


// default constructor
template<typename K, typename V>
  HashMap<K,V>::HashMap(){
    count = 0;
    capacity = 16;
    init_table();
    return;
  }

  // copy constructor
  template<typename K, typename V>
  HashMap<K,V>::HashMap(const HashMap& rhs){
    *this = rhs;
    return;
  }

  // move constructor
  template<typename K, typename V>
 HashMap<K,V>::HashMap(HashMap&& rhs){
    *this = std::move(rhs);
  }

  // copy assignment
  template<typename K, typename V>
  HashMap<K,V>& HashMap<K,V>::operator=(const HashMap& rhs){
    if(this != &rhs){
      if(count > 0){
        this->make_empty();
      }
      delete[] this->table;
      this->capacity = rhs.capacity;
      this->table = new Node*[capacity];
      this->init_table();
      this->count = rhs.count;
      if(rhs.empty()){
        return *this;
      }
      Node* tempR = nullptr;
      for(int i = 0; i < capacity; i++){
        tempR = rhs.table[i];
        while(tempR != nullptr){
          Node* newNode = new Node;
          newNode->key = tempR->key;
          newNode->value = tempR->value;
          newNode->next = this->table[i];
          this->table[i] = newNode;
          tempR = tempR->next;
        }
      }
    }
    return *this;
  }

  // move assignment
  template<typename K, typename V>
  HashMap<K,V>& HashMap<K,V>::operator=(HashMap&& rhs){
    if(this != &rhs){
      if(count>0){
        this->make_empty();
      }
      delete[] this->table;
      this->capacity = rhs.capacity;
      this->count = rhs.count;
      this->table = rhs.table;
      rhs.count = 0;
      rhs.capacity = 16;
      rhs.table = new Node*[capacity];
      rhs.init_table();
    }
    return *this;
  }

  // destructor
  template<typename K, typename V>
  HashMap<K,V>::~HashMap(){
    this->make_empty();
    delete[] this->table;
    return;
  }
  
  // Returns the number of key-value pairs in the map
  template<typename K, typename V>
  int HashMap<K,V>::size() const{
    return count;
  }

  // Tests if the map is empty
  template<typename K, typename V>
  bool HashMap<K,V>::empty() const{

    for(int i = 0;i<capacity; i++){
      if(table[i] != nullptr){
        return false;
      }
    }
    return true;
  }

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
  template<typename K, typename V>
  V& HashMap<K,V>::operator[](const K& key){
    int hash_index = hash(key);
    if(hash_index>= capacity or table[hash_index] == nullptr){
      throw std:: out_of_range("HashMap<K,V>::operator[](const K& key");
    }

    Node* temp = table[hash_index];
    while(temp != nullptr){
      if(temp->key == key){
        return temp->value;
      }
      temp = temp->next;
    }
    throw std:: out_of_range("HashMap<K,V>::operator[](const K& key");
  }

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
  template<typename K, typename V>
  const V& HashMap<K,V>::operator[](const K& key) const{
    int hash_index = hash(key);
    if(hash_index>= capacity or table[hash_index] == nullptr){
      throw std:: out_of_range("HashMap<K,V>::operator[](const K& key");
    }

    Node* temp = table[hash_index];
    while(temp != nullptr){
      if(temp->key == key){
        return temp->value;
      }
      temp = temp->next;
    }
    throw std:: out_of_range("HashMap<K,V>::operator[](const K& key");
  }

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
  template<typename K, typename V>
  void HashMap<K,V>::insert(const K& key, const V& value){
    double total = (count * 1.0) / capacity;
    if(total >= load_factor_threshold){
      resize_and_rehash();
    }

    int hash_index = hash(key);
    Node* newNode = new Node;
    newNode->value = value;
    newNode->key = key;
  
    if(table[hash_index] == nullptr){
      newNode->next = nullptr;
      table[hash_index] = newNode;
    }
    else{
      Node* temp = table[hash_index];
      table[hash_index] = newNode;
      newNode->next = temp;
    }
    count++;
    
    return;
  }

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
  template<typename K, typename V>
  void HashMap<K,V>::erase(const K& key){
    int hash_index = hash(key);

    Node* temp = table[hash_index];
    Node* before = nullptr;
    while(temp != nullptr){
      if(temp->key == key){
        if(temp == table[hash_index]){
          table[hash_index] = temp->next;
          delete temp;
          count--;
          return;
        }
        if(temp->next == nullptr){
          delete temp;
          count--;
          return;
        }
        before->next = temp->next;
        delete temp;
        count--;
        return;
      }
      before = temp;
      temp = temp->next;
    }

    throw std:: out_of_range("HashMap<K,V>::erase(const K& key");
  }

  // Returns true if the key is in the collection, and false otherwise.
  template<typename K, typename V>
  bool HashMap<K,V>::contains(const K& key) const{
    int hash_index = hash(key);
    if(hash_index>= capacity or table[hash_index] == nullptr){
     return false;
    }

    Node* temp = table[hash_index];
    while(temp != nullptr){
      if(temp->key == key){
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  // Returns the keys k in the collection such that k1 <= k <= k2
  template<typename K, typename V>
  ArraySeq<K> HashMap<K,V>::find_keys(const K& k1, const K& k2) const{
    ArraySeq<K> keyList;
    Node* temp = nullptr;
    for(int i = 0; i < capacity; i++){
      temp = table[i];
      while(temp != nullptr){
        if(temp->key >= k1 and temp->key <= k2){
          keyList.insert(temp->key,keyList.size());
        }
        temp = temp->next;
      }
    }
    return keyList;
  }

  // Returns the keys in the collection in ascending sorted order
  template<typename K, typename V>
  ArraySeq<K> HashMap<K,V>::sorted_keys() const{
    ArraySeq<K> keyList;
    Node* temp = nullptr;
    for(int i = 0; i < capacity; i++){
      temp = table[i];
      while(temp != nullptr){
        keyList.insert(temp->key,keyList.size());
        temp = temp->next;
      }
    }
    keyList.merge_sort();
    return keyList;
  }

  // statistics functions for the hash table implementation
  template<typename K, typename V>
  int HashMap<K,V>::min_chain_length() const{
    int minLeng = 0;
    int currCount = 0;

    Node* temp = nullptr;
    for(int i = 0; i <capacity; i++){
      temp = table[i];
      while(temp != nullptr){
        currCount++;
        temp = temp->next;
      }
      if(minLeng > currCount or (minLeng == 0 and currCount != 0)){
        minLeng = currCount;
      }
    }
    return minLeng;
  }

  template<typename K, typename V>
  int HashMap<K,V>::max_chain_length() const{
   int maxLeng = 0;
    int currCount = 0;

    Node* temp = nullptr;
    for(int i = 0; i <capacity; i++){
      temp = table[i];
      currCount = 0;
      while(temp != nullptr){
        currCount++;
        temp = temp->next;
      }
      if(maxLeng < currCount){
        maxLeng = currCount;
      }
    }
    return maxLeng;
  }

  template<typename K, typename V>
  double HashMap<K,V>::avg_chain_length() const{
    double withNodes = 0, total = 0, avg = 0;
    bool checked = false;

    Node* temp = nullptr;
    for(int i = 0; i <capacity; i++){
      temp = table[i];
      checked = false;
      while(temp != nullptr){
        if(checked == false){
          withNodes++;
          checked = true;
        }
        total++;
        temp = temp->next;
      }
    }

    if(withNodes == 0) {return 0;}
    return total/withNodes;
  }
  


#endif
