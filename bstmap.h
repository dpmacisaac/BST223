//---------------------------------------------------------------------------
// NAME: Dominic MacIsaac
// DATE: Fall 2021
// DESC: Implementation of Binary Search Tree
//---------------------------------------------------------------------------

#ifndef BSTMAP_H
#define BSTMAP_H

#include "map.h"
#include "arrayseq.h"


template<typename K, typename V>
class BSTMap : public Map<K,V>
{
public:

  // default constructor
  BSTMap();

  // copy constructor
  BSTMap(const BSTMap& rhs);

  // move constructor
  BSTMap(BSTMap&& rhs);

  // copy assignment
  BSTMap& operator=(const BSTMap& rhs);

  // move assignment
  BSTMap& operator=(BSTMap&& rhs);  

  // destructor
  ~BSTMap();
  
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

  // Returns the height of the binary search tree
  int height() const;
  
private:

  // node for linked-list separate chaining
  struct Node {
    K key;
    V value;
    Node* left;
    Node* right;
  };

  // number of key-value pairs in map
  int count = 0;

  // array of linked lists
  Node* root = nullptr;

  // clean up the tree and reset count to zero given subtree root
  void make_empty(Node* st_root);

  // copy assignment helper
  Node* copy(const Node* rhs_st_root) const;
  
  // erase helper
  Node* erase(const K& key, Node* st_root);

  // find_keys helper
  void find_keys(const K& k1, const K& k2, const Node* st_root,
                 ArraySeq<K>& keys) const;

  // sorted_keys helper
  void sorted_keys(const Node* st_root, ArraySeq<K>& keys) const;

  // height helper
  int height(const Node* st_root) const;
  
};

template<typename K, typename V>
BSTMap<K,V>::BSTMap(){
  return;
}

  // copy constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(const BSTMap& rhs){
  *this = rhs;
  return;
}

  // move constructor
template<typename K, typename V>
BSTMap<K,V>::BSTMap(BSTMap&& rhs){
  *this = std::move(rhs);
  return;
}

  // copy assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(const BSTMap& rhs){
  if(this != &rhs){
    make_empty(root);
    root = copy(rhs.root);
    count = rhs.count;
  }
  return *this;
}

  // move assignment
template<typename K, typename V>
BSTMap<K,V>& BSTMap<K,V>::operator=(BSTMap&& rhs){
  if(this != &rhs){
    make_empty(root);
    root = rhs.root;
    count = rhs.count;

    rhs.root = nullptr;
    rhs.count = 0;
  }
  return *this;
}

  // destructor
template<typename K, typename V>
BSTMap<K,V>::~BSTMap(){
  make_empty(root);
  return;
}
  
  // Returns the number of key-value pairs in the map
template<typename K, typename V>
int BSTMap<K,V>::size() const{
  return count;
}

  // Tests if the map is empty
template<typename K, typename V>
bool BSTMap<K,V>::empty() const{
  if(count == 0){
    return true;
  }
  return false;
}

  // Allows values associated with a key to be updated. Throws
  // out_of_range if the given key is not in the collection.
template<typename K, typename V>
V& BSTMap<K,V>::operator[](const K& key){
  if(empty()){
    throw std:: out_of_range("BSTMap<K,V>::operator[](const K& key");
  }
  Node* temp = root;
  while(temp!= nullptr){
    if(key == temp->key){
      return temp->value;
    }

    if(key > temp->key){
      temp = temp->right;
    }

    if(key < temp->key){
      temp = temp->left;
    }
  }
  throw std:: out_of_range("BSTMap<K,V>::operator[](const K& key");

}

  // Returns the value for a given key. Throws out_of_range if the
  // given key is not in the collection. 
template<typename K, typename V>
const V& BSTMap<K,V>::operator[](const K& key) const{
   if(empty()){
    throw std:: out_of_range("BSTMap<K,V>::operator[](const K& key");
  }
  Node* temp = root;
  while(temp!= nullptr){
    if(key == temp->key){
      return temp->value;
    }

    if(key > temp->key){
      temp = temp->right;
    }

    if(key < temp->key){
      temp = temp->left;
    }
  }
  throw std:: out_of_range("BSTMap<K,V>::operator[](const K& key");
}

  // Extends the collection by adding the given key-value
  // pair. Assumes the key being added is not present in the
  // collection. Insert does not check if the key is present.
template<typename K, typename V>
void BSTMap<K,V>::insert(const K& key, const V& value){
  Node* temp = root;

  Node* newNode = new Node;
  newNode->left = nullptr;
  newNode->right = nullptr;
  newNode->key = key;
  newNode->value = value;

  if(empty()){
    root = newNode;
    count++;
    return;
  }

  count++;
  while(temp != nullptr){
    if(key > temp->key){
      if(temp->right == nullptr){
        temp->right = newNode;
        return;
      }
      temp = temp->right;
    }
    if(key <= temp->key){
      if(temp->left == nullptr){
        temp->left = newNode;
        return;
      }

      temp = temp->left;
    }
  }

  return;
}

  // Shrinks the collection by removing the key-value pair with the
  // given key. Does not modify the collection if the collection does
  // not contain the key. Throws out_of_range if the given key is not
  // in the collection.
template<typename K, typename V>
void BSTMap<K,V>::erase(const K& key){
  if(empty()){
    throw std:: out_of_range("BSTMap<K,V>::erase(const K& key");
  }
  erase(key, root);
  return;
}


  // Returns true if the key is in the collection, and false otherwise.
template<typename K, typename V>
bool BSTMap<K,V>::contains(const K& key) const{
  if(empty()){return false;}
  Node* temp = root;
  while(temp != nullptr){
    if(key == temp->key){
      return true;
    }

    if(key > temp->key){
      if(temp->right == nullptr){
        return false;
      }
      temp = temp->right;
    }

    if(key < temp->key){
      if(temp->left == nullptr){
        return false;
      }
      temp = temp->left;
    }
  }
  return false;
}

  // Returns the keys k in the collection such that k1 <= k <= k2
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::find_keys(const K& k1, const K& k2) const{
  ArraySeq<K> keyList;
  find_keys(k1,k2,root, keyList);
  return keyList;
}

  // Returns the keys in the collection in ascending sorted order
template<typename K, typename V>
ArraySeq<K> BSTMap<K,V>::sorted_keys() const{
  ArraySeq<K> keyList;
  sorted_keys(root, keyList);
  return keyList;
} 

  // Returns the height of the binary search tree
template<typename K, typename V>
int BSTMap<K,V>::height() const{
  return height(root)+1;
}

template<typename K, typename V>
void BSTMap<K,V>::make_empty(Node* st_root){
  if(empty()){return;}
  if(st_root->left != nullptr){
    make_empty(st_root->left);
  }
  if(st_root->right != nullptr){
    make_empty(st_root->right);
  }
  delete st_root; 
  count--; 
  return;
}

template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::copy(const Node* rhs_st_root) const{
  if(rhs_st_root == nullptr){
    return root;
  }
  Node* temp = new Node;
  temp->left = nullptr;
  temp->right = nullptr;
  temp->key = rhs_st_root->key;
  temp->value = rhs_st_root->value;

  if(rhs_st_root->left != nullptr){
    temp->left = copy(rhs_st_root->left);
  }
  if(rhs_st_root->right != nullptr){
    temp->right = copy(rhs_st_root->right);
  }
  return temp;
}
  
  // erase helper
template<typename K, typename V>
typename BSTMap<K,V>::Node* BSTMap<K,V>::erase(const K& key, Node* st_root){
  if (key < st_root->key){
    if(st_root->left == nullptr){
      throw std:: out_of_range("BSTMap<K,V>::erase(const K& key");
    }
    st_root->left = erase(key, st_root->left);
  }
  else if (key > st_root->key){
    if(st_root->right == nullptr){
      throw std:: out_of_range("BSTMap<K,V>::erase(const K& key");
    }
    st_root->right = erase(key, st_root->right);
  }
  else if(key==st_root->key){
    Node* temp = st_root;
    if(st_root->left == nullptr){
      if(st_root == root){
        root = st_root->right;
      }
      st_root = st_root->right;
      count--;
      delete temp;
      return st_root;
    }
    else if(st_root->right == nullptr){
      if(st_root == root){
        root = st_root->left;
      }
      st_root = st_root->left;
      count--;
      delete temp;
      return st_root;
    }
    else{
      temp = temp->right;
      if(temp->left == nullptr){
        st_root->key = temp->key;
        st_root->value = temp->value;
        st_root->right = temp->right;
        count--;
        delete temp;
        return st_root;
      }
      Node* before = temp;
      temp = temp->left;
      while(temp->left != nullptr){
        before = before->left;
        temp = temp->left;
      }
      st_root->key = temp->key;
      st_root->value = temp->value;
      before->left = temp->right;
      count--;
      delete temp;
      return st_root;
    }
  }
  return st_root;
}

  // find_keys helper
template<typename K, typename V>
void BSTMap<K,V>::find_keys(const K& k1, const K& k2, const Node* st_root, ArraySeq<K>& keys) const{
   if(!st_root){
    return;
  }
  find_keys(k1,k2,st_root->left,keys);
  if(st_root->key >= k1 and st_root->key <= k2){
    keys.insert(st_root->key, keys.size());
  }
  find_keys(k1,k2,st_root->right,keys);
  return;
}

  // sorted_keys helper
template<typename K, typename V>
void BSTMap<K,V>::sorted_keys(const Node* st_root, ArraySeq<K>& keys) const{
  if(!st_root){
    return;
  }
  sorted_keys(st_root->left,keys);
  keys.insert(st_root->key, keys.size());
  sorted_keys(st_root->right,keys);

  return;
}

  // height helper
template<typename K, typename V>
int BSTMap<K,V>::height(const Node* st_root) const{
  if(empty()){ return 0;}
  int left=0,right=0;
  if(st_root->left != nullptr){
    left = height(st_root->left);
    left++;
  } 
  if(st_root->right != nullptr){
    right = height(st_root->right);
    right++;

  }
  if(right>left){return right;}

  return left;
}


#endif
