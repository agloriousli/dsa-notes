#ifndef BINNODE_HPP
#define BINNODE_HPP
using Rank = unsigned int; 

// Forward declarations
template <typename T> class BinTree;
template <typename T> struct BinNode;

// Binary Node Position type alias
template <typename T>
using BNP = BinNode<T>*; //Binary Node Position

// RBColor enum (assuming it exists elsewhere, adding declaration here)
enum RBColor { RB_RED, RB_BLACK };

// BinNode structure
template <typename T>
struct BinNode {
   BNP<T> parent, lc, rc; //父亲、孩子
   T data;
   int height;
   RBColor color; //数据、（黑）高度/npl、颜色

   // Constructor (inferred from usage)
   BinNode(const T& d, BNP<T> p, BNP<T> l = NULL, BNP<T> r = NULL, 
           int h = 0, RBColor c = RB_RED) 
      : data(d), parent(p), lc(l), rc(r), height(h), color(c) {}

   // Height-related methods
   int updateHeight(); // O(1)
   void updateHeightAbove(); // O(n = depth(x))

   // Insertion methods
   BNP<T> insertLc(const T& e); //插入左孩子
   BNP<T> insertRc(const T& e); //插入右孩子

   // Attachment methods
   void attachLc(BNP<T> x); //插入左子树
   void attachRc(BNP<T> x); //插入右子树

   // Other methods
   BNP<T> succ(); //（中序遍历意义下）当前节点的直接后继
   template <typename V> void traverse(V&); //遍历
   
   // Size calculation (from preorder example)
   Rank size(); //统计子树规模
   
   // Friend declarations
   friend class BinTree<T>;
}; //BinNode

// Height constants and macro
constexpr int H_NULL = -1; //空的常规二叉树，高度为-1
#define Height(x) ((x) ? (x)->height : H_NULL) //简化描述，安全地处置边界情况

// BinNode method implementations
template <typename T>
int BinNode<T>::updateHeight() //O(1)
{ 
   return height = 1 + max(Height(lc), Height(rc)); 
}

template <typename T>
void BinNode<T>::updateHeightAbove() { //O(n = depth(x))
   for (BNP<T> x = this; x; x = x->parent) //可优化
      x->updateHeight();
} //updateHeightAbove

template <typename T>
BNP<T> BinNode<T>::insertLc(const T& e) {
   return lc = new BinNode<T>(e, this);
}

template <typename T>
BNP<T> BinNode<T>::insertRc(const T& e) {
   return rc = new BinNode<T>(e, this);
}

template <typename T>
void BinNode<T>::attachLc(BNP<T> x) {
   lc = x;
   if (x) x->parent = this;
}

template <typename T>
void BinNode<T>::attachRc(BNP<T> x) {
   rc = x;
   if (x) x->parent = this;
}

// Size calculation implementation
template <typename T>
Rank BinNode<T>::size() {
   Rank s = 1; //先计入本身
   if (lc) s += lc->size(); //递归计入左子树
   if (rc) s += rc->size(); //递归计入右子树
   return s; //也可改由中序、后序遍历得到
} //O(n=size)：懒惰策略，现用现算；也可改为勤奋策略，始终动态维护

#endif // BINNODE_HPP