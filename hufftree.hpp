#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

#include "huffchar.hpp"
#include "bintree.hpp"  // 假设BinTree已定义

using HuffTree = BinTree<HuffChar>; //Huffman树：由BinTree派生

// 快捷方式：根节点的频数，即子树的权重
#define Weight(T) ((T).root()->data.weight)

// 检查节点是否为叶节点
bool IsLeaf( BinNode<HuffChar>* v ) {
   return v && !v->lc && !v->rc;
}

#endif // HUFFTREE_HPP