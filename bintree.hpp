#ifndef BINTREE_HPP
#define BINTREE_HPP

#include "binnode.hpp"

// Helper macro 
#ifndef FromParentTo
#define FromParentTo(x) /* Implementation depends on parent's child pointer */
#endif

template <typename T>
class BinTree {
protected:
   Rank _size;
   BNP<T> _root;
   
public:
   // Constructors
   BinTree() : _size(0), _root(NULL) {}
   BinTree(BNP<T> t); //复制子树
   BinTree(const BinTree<T>& t); //复制全树
   
   // Destructor (needs implementation)
   ~BinTree();
   
   // Assignment operator
   BinTree<T>& operator=(const BinTree<T>& t);
   
   // Insertion methods
   BNP<T> insert(T const&); //插入根节点
   BNP<T> insert(T const&, BNP<T>); //插入左孩子
   BNP<T> insert(BNP<T>, T const&); //插入右孩子

   // Attachment methods
   BNP<T> attach(BinTree<T>, BNP<T>); //接入左子树
   BNP<T> attach(BNP<T>, BinTree<T>); //接入右子树

   // Removal and separation
   BinTree<T> secede(BNP<T>); //子树分离
   Rank remove(BNP<T>); //子树删除
   
   // Accessors
   Rank size() const { return _size; }
   BNP<T> root() const { return _root; }
   bool empty() const { return _size == 0; }
   
   // Traversal methods
   template <typename V> void traverse(V& visit);
   
   // Friend declarations
   template <typename U> friend BNP<U> clone(BNP<U> p, BNP<U> t);
   template <typename U> friend Rank clean(BNP<U> x);
   
private:
   // Helper methods
   void clear();
}; //BinTree

// Clone function for deep copy
template <typename T> //p ~ Parent; t ~ source Tree
BNP<T> clone(BNP<T> p, BNP<T> t) { //深复制
   if (!t) return NULL;
   BNP<T> x = new BinNode<T>(t->data, p, NULL, NULL, t->height, t->color);
   x->lc = clone(x, t->lc);
   x->rc = clone(x, t->rc);
   return x; //由t复制出x
} //clone

// Clean function for removal
template <typename T>
Rank clean(BNP<T> x) {
   if (!x) return 0;
   Rank n = 1 + clean(x->lc) + clean(x->rc);
   delete x;
   return n;
}

// Constructors implementation
template <typename T>
BinTree<T>::BinTree(BNP<T> t) //复制子树
{ 
   _root = clone(NULL, t); 
   _size = t ? t->size() : 0; 
}

template <typename T>
BinTree<T>::BinTree(const BinTree<T>& t) //复制全树
{ 
   _root = clone<T>(NULL, t._root); 
   _size = t.size(); 
}

// Destructor
template <typename T>
BinTree<T>::~BinTree() {
   clear();
}

// Assignment operator
template <typename T>
BinTree<T>& BinTree<T>::operator=(const BinTree<T>& t) {
   if (this != &t && _root != t._root) {
      clear();
      _root = clone<T>(NULL, t._root);
      _size = t.size();
   }
   return *this;
}

// Insertion methods
template <typename T>
BNP<T> BinTree<T>::insert(T const& e) {
   if (_root) return NULL; // Root already exists
   _size = 1;
   return _root = new BinNode<T>(e, NULL);
}

template <typename T>
BNP<T> BinTree<T>::insert(T const& e, BNP<T> x) { //作为左孩子
   if (!x) return NULL;
   _size++;
   BNP<T> newChild = x->insertLc(e);
   x->updateHeightAbove();
   return newChild;
}

template <typename T>
BNP<T> BinTree<T>::insert(BNP<T> x, T const& e) { //作为右孩子
   if (!x) return NULL;
   _size++;
   BNP<T> newChild = x->insertRc(e);
   x->updateHeightAbove();
   return newChild;
}

// Attachment methods
template <typename T>
BNP<T> BinTree<T>::attach(BinTree<T> S, BNP<T> x) { //接入左子树
   if (!x) return NULL;
   if (!(x->lc = S._root)) return NULL; //空树无需费事
   x->lc->parent = x;
   _size += S._size;
   x->updateHeightAbove();
   S._root = NULL;
   S._size = 0;
   return x;
} //attach

template <typename T>
BNP<T> BinTree<T>::attach(BNP<T> x, BinTree<T> S) { //接入右子树
   if (!x) return NULL;
   if (!(x->rc = S._root)) return NULL; //空树无需费事
   x->rc->parent = x;
   _size += S._size;
   x->updateHeightAbove();
   S._root = NULL;
   S._size = 0;
   return x;
} //attach

// Subtree secession
template <typename T>
BinTree<T> BinTree<T>::secede(BNP<T> x) {
   if (!x) return BinTree<T>();
   
   // Disconnect from parent
   FromParentTo(x) = NULL;
   if (x->parent) x->parent->updateHeightAbove();
   
   // Create new tree
   BinTree<T> S; //创建空树
   S._root = x;
   x->parent = NULL; //新树以x为根
   S._size = x->size();
   _size -= S._size; //更新规模
   
   return S; //返回封装后的子树
} //secede

// Removal
template <typename T>
Rank BinTree<T>::remove(BNP<T> x) {
   if (!x) return 0;
   FromParentTo(x) = NULL;
   if (x->parent) x->parent->updateHeightAbove();
   Rank n = clean(x);
   _size -= n;
   return n;
} //remove

// Clear the entire tree
template <typename T>
void BinTree<T>::clear() {
   if (_root) {
      clean(_root);
      _root = NULL;
      _size = 0;
   }
}

#endif // BINTREE_HPP